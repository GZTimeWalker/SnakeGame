#include "AI.h"
#include "Item.h"

using namespace GZ;
using namespace std;


AI::AI()
{
	vector<Cell> cell_line(Utils::HEIGHT, Cell());
	map = new vector<vector<Cell>>(Utils::WIDTH, cell_line);
	snake = nullptr;
}

AI::~AI()
{
	delete map;
}

void AI::SetSnake(Snake* snake)
{
	this->snake = snake;
}

Cell& AI::GetCell(Pos pos)
{
	return map->at(pos.x).at(pos.y);
}

Direction AI::GoNext()
{
	Pos next;
	for (int dir = 0; dir < 4; ++dir)
	{
		// try to go to the next position safely
		// but this method is stupid (:
		next = Utils::EnsureRange(snake->Head + (Direction)dir);
		if (!snake->HasPos(next) && (Utils::THROUGHWALL || !Utils::OutOfRange(next)))
			return (Direction)dir;
	}
	return Direction::NONE;
}

auto AI::GetMinStepPos()
{
	auto minpos = steps.begin();
	for (auto pos = steps.begin(); pos != steps.end(); ++pos)
		if ((*pos) < (*minpos))
			minpos = pos;

	return minpos;
}

Direction AI::Backtrace(Pos pos)
{
	Direction forward = Direction::NONE;

	while (pos != snake->Head)
	{
		forward = GetCell(pos).fromDirection;
		switch (forward)
		{
		case Direction::UP:
			pos.y += 1;
			break;
		case Direction::DOWN:
			pos.y -= 1;
			break;
		case Direction::LEFT:
			pos.x += 1;
			break;
		case Direction::RIGHT:
			pos.x -= 1;
			break;
		case Direction::NONE:
			break;
		default:
			throw unknown_direction();
		}
		pos = Utils::EnsureRange(pos);

		if (Utils::DEBUG)
			Utils::Print("o", pos, Color::B_CYAN);
	}
	return forward;
}

void AI::Clean()
{
	for (auto& line : *map)
	{
		for (auto& ele : line)
		{
			ele.vis = false;
			ele.step_count = 0;
			ele.dis = 0;
			ele.fromDirection = Direction::NONE;
		}
	}
}

Direction AI::AStar(Pos dest, std::vector<Item*>& items)
{
	SortablePos cur = { snake->Head, dest - snake->Head };

	auto curitr = GetMinStepPos();

	if (curitr != steps.end() && (*curitr).pos == dest)
		return Backtrace(dest);

	// ready to find path

	bool success = false;
	Clean();

	// push the start position

	steps.push_back(cur);

	while (!steps.empty())
	{
		// get current pos, keep the iterator to erase later.
		curitr = GetMinStepPos();
		cur = *curitr;

		// if get the destination break
		if (cur.pos == dest)
		{
			success = true;
			break;
		}

		auto& cell = GetCell(cur.pos);

		// already searched this cell
		cell.vis = true;

		if(Utils::DEBUG)
			RenderStep(cur.pos, cell.fromDirection, Color::B_RED);

		steps.erase(curitr);

		// for every direction

		for (int i = 0; i < 4; ++i)
		{
			// try step forward
			SortablePos next;
			next.pos = Utils::EnsureRange(cur.pos + (Direction)(i + 1));
			

			if (Utils::OutOfRange(next.pos))
				continue;

			// get next cell
			auto& next_cell = GetCell(next.pos);

			if (snake->HasPos(next.pos) || next_cell.vis)
				continue;

			// calculate next h(pos) = dis(pos,dest) + step_count
			next.val = Utils::THROUGHWALL ?
				Utils::ThroughWallDistance(next.pos, dest) : (next.pos - dest);

			next.val += next_cell.step_count + 1;

			auto pos = find(steps.begin(), steps.end(), next);

			if (pos == steps.end())
			{
				// if the position is not in steps
				// save data and push it into steps
				next_cell.fromDirection = (Direction)(i + 1);
				next_cell.step_count = cell.step_count + 1;
				next_cell.dis = Utils::THROUGHWALL ? Utils::ThroughWallDistance(next.pos, dest) : next.pos - dest;
				
				if (Utils::DEBUG)
					RenderStep(next.pos, next_cell.fromDirection, Color::B_GREEN);
				
				steps.push_back(next);
			}
			else
			{
				// if the position in steps
				// and the value is smaller than the existing ones
				if (next < *pos)
				{
					// update the value and cell data
					next_cell.fromDirection = (Direction)(i + 1);
					next_cell.step_count = cell.step_count + 1;
					next_cell.dis = Utils::THROUGHWALL ? Utils::ThroughWallDistance(next.pos, dest) : next.pos - dest;
					(*pos).val = next.val;
				}

				// Addition: 
				// This is why I am not use some better data structure to save them.
				// The change of values always make them behave badly.
				// 
				// If you have any better idea, plz let me know.
			}
		}
	}

	// if success, backtrace to get direction

	return success ? Backtrace(dest) : Direction::NONE;
}

void AI::RenderStep(Pos pos, Direction dir, Color color)
{
	switch (dir)
	{
	case Direction::UP:
		Utils::Print("^", pos, color);
		break;
	case Direction::DOWN:
		Utils::Print("|", pos, color);
		break;
	case Direction::LEFT:
		Utils::Print("<", pos, color);
		break;
	case Direction::RIGHT:
		Utils::Print(">", pos, color);
		break;
	case Direction::NONE:
		Utils::Print("x", pos, color);
		break;
	default:
		break;
	}
}

Direction AI::Step(Pos food, std::vector<Item*>& items, std::vector<Item*>::iterator& getitem, Pos lastTail)
{
	if (snake == nullptr)
		return Direction::NONE;

	// if get an item
	if (getitem != items.end())
	{
		// and it is portal
		if ((*getitem)->GetType() == ItemType::PORTAL)
		{
			// clean and wait to find the path again.
			Clean();
			steps.clear();
			return snake->Toward;
		}
	}

	// if get food
	if (snake->Head == food)
	{
		// just go
		steps.clear();
		return GoNext();
	}

	// Use A Star to get next direction
	Direction step = AStar(food, items);

	// if A Star can not find a way to the food, just go
	if (step == Direction::NONE)
		step = GoNext();

	// if in debug mode, redraw the snake to avoid it to be covered.
	if (Utils::DEBUG)
		snake->Draw();

	return step;
}
