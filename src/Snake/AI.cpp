#include "AI.h"
#include "Item.h"

using namespace GZ;
using namespace std;

int AI::dx[4] = { 0, 0, -1, 1 };
int AI::dy[4] = { -1, 1, 0, 0 };

Cell& GZ::AI::GetCell(Pos pos)
{
	return map->at(pos.x).at(pos.y);
}

Direction GZ::AI::GoRand()
{
	Pos next;
	for (int dir = 0; dir < 4; ++dir)
	{
		next = snake->Head + (Direction)dir;
		if (!snake->HasPos(next) && (Utils::THROUGHWALL || !Utils::OutOfRange(next)))
			return (Direction)dir;
	}
	return Direction::NONE;
}

auto GZ::AI::GetMinStepPos()
{
	auto minpos = steps.begin();
	for (auto pos = steps.begin(); pos != steps.end(); ++pos)
		if ((*pos).val < (*minpos).val)
			minpos = pos;

	return minpos;
}

Direction AI::AStar(Pos dest, std::vector<Item*>& items)
{
	SortablePos cur = { snake->Head, dest - snake->Head };
	steps.push_back(cur);

	for (auto& line : *map)
	{
		for (auto& ele : line)
		{
			ele.vis = false;
			ele.step_count = 0;
			ele.dis = 0;
		}
	}

	bool success = false;

	while (!steps.empty())
	{
		auto curitr = GetMinStepPos();
		cur = *curitr;

		if (cur.pos == dest)
		{
			success = true;
			break;
		}
		
		auto& cell = GetCell(cur.pos);
		cell.vis = true;

		if(Utils::DEBUG)
			RenderStep(cur.pos, cell.backDir, Color::B_RED);

		steps.erase(curitr);

		for (int i = 0; i < 4; ++i)
		{
			// Step forward
			SortablePos next;
			next.pos.x = cur.pos.x + dx[i];
			next.pos.y = cur.pos.y + dy[i];

			if (Utils::THROUGHWALL)
			{
				if (next.pos.x == 0)
					next.pos.x = Utils::WIDTH - 2;
				else if (next.pos.x == Utils::WIDTH - 1)
					next.pos.x = 1;

				if (next.pos.y == 0)
					next.pos.y = Utils::HEIGHT - 2;
				else if (next.pos.y == Utils::HEIGHT - 1)
					next.pos.y = 1;
			}

			if (Utils::OutOfRange(next.pos))
				continue;

			// Get next cell
			auto& next_cell = GetCell(next.pos);

			if (snake->HasPos(next.pos) || next_cell.vis)
				continue;

			// Calculate next h(pos) = dis(pos,dest) + step_count
			next.val =  (next.pos - dest) + next_cell.step_count + 1;

			auto pos = find(steps.begin(), steps.end(), next);

			if (pos == steps.end())
			{
				next_cell.backDir = (Direction)(i + 1);
				next_cell.step_count = cell.step_count + 1;
				next_cell.dis = next.pos - dest;
				if (Utils::DEBUG)
					RenderStep(next.pos, next_cell.backDir, Color::B_GREEN);
				steps.push_back(next);
			}
			else
			{
				if (next < *pos)
				{
					next_cell.backDir = (Direction)(i + 1);
					next_cell.step_count = cell.step_count + 1;
					next_cell.dis = next.pos - dest;
					(*pos).val = next.val;
				}
			}
		}
	}

	Direction forward = Direction::NONE;

	while (success && cur.pos != snake->Head)
	{
		forward = GetCell(cur.pos).backDir;
		switch (forward)
		{
		case Direction::UP:
			cur.pos.y += 1;
			break;
		case Direction::DOWN:
			cur.pos.y -= 1;
			break;
		case Direction::LEFT:
			cur.pos.x += 1;
			break;
		case Direction::RIGHT:
			cur.pos.x -= 1;
			break;
		case Direction::NONE:
			break;
		default:
			throw unknown_direction();
		}

		if (Utils::THROUGHWALL)
		{
			if (cur.pos.x == 0)
				cur.pos.x = Utils::WIDTH - 2;
			else if (cur.pos.x == Utils::WIDTH - 1)
				cur.pos.x = 1;

			if (cur.pos.y == 0)
				cur.pos.y = Utils::HEIGHT - 2;
			else if (cur.pos.y == Utils::HEIGHT - 1)
				cur.pos.y = 1;
		}
		if (Utils::DEBUG)
			Utils::Print("o", cur.pos, Color::B_CYAN);
	}

	return forward;
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

Direction AI::Step(Pos food, std::vector<Item*>& items, std::vector<Item*>::iterator& getitem, Pos lastTail)
{
	if (snake == nullptr)
		return Direction::NONE;

	if (getitem != items.end())
	{
		if ((*getitem)->GetType() == ItemType::PORTAL)
		{
			for (auto& line : *map)
			{
				for (auto& ele : line)
				{
					ele.vis = false;
					ele.step_count = 0;
					ele.dis = 0;
					ele.backDir = Direction::NONE;
				}
			}
			steps.clear();
			return snake->Toward;
		}
	}

	if (snake->Head == food)
	{
		steps.clear();
		return GoRand();
	}

	Direction step = AStar(food, items);

	if (step == Direction::NONE)
		step = GoRand();

	return step;
}
