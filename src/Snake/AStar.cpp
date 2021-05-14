#include "AStar.h"

using namespace GZ;
using namespace std;

AStar::AStar()
{
    vector<Cell> cell_line(Utils::HEIGHT, Cell());
    map = new vector<vector<Cell>>(Utils::WIDTH, cell_line);
}

AStar::~AStar()
{
    delete map;
}

Cell& AStar::GetCell(Pos pos)
{
    return map->at(pos.x).at(pos.y);
}

auto AStar::GetMinStepPos()
{
    auto minpos = steps.begin();
    for (auto pos = steps.begin(); pos != steps.end(); ++pos)
        if ((*pos).val < (*minpos).val)
            minpos = pos;

    return minpos;
}

Direction AStar::Forward(Pos from)
{

    return GetCell(from).fromDirection;
}

void AStar::Clean()
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
    steps.clear();
}

Direction AStar::Step(Pos dest, Snake* snake, std::vector<Item*>& items)
{


    auto dir = Forward(snake->Head);
    if (dir != Direction::NONE)
        return dir;

    // ready to find path

    bool success = false;

    if(dest != lastDest)
        Clean();

    // push the start position
    Pos head = snake->Head;
    SortablePos cur = { dest, Utils::THROUGHWALL ? Utils::ThroughWallDistance(dest, head) : dest - head };

    steps.push_back(cur);
    while (!steps.empty())
    {
        // get current pos, keep the iterator to erase later.
        auto curitr = GetMinStepPos();
        cur = *curitr;

        // if get the destination break
        if (cur.pos == head)
        {
            success = true;
            break;
        }

        auto& cell = GetCell(cur.pos);

        // already searched this cell
        cell.vis = true;

        if (Utils::DEBUG)
            RenderStep(cur.pos, cell.fromDirection, Color::B_RED);

        steps.erase(curitr);

        // for every direction

        for (int i = 0; i < 4; ++i)
        {
            // try step forward
            SortablePos next;
            next.pos = Utils::EnsureRange(cur.pos + (Direction)i);


            if (Utils::OutOfRange(next.pos))
                continue;

            // get next cell
            auto& next_cell = GetCell(next.pos);

            if (next.pos == head)
            {
                next.val = next_cell.step_count + 1;
                next_cell.fromDirection = (Direction)((i + 2) % 4);
                next_cell.step_count = cell.step_count + 1;
                next_cell.dis = 0;
                steps.push_back(next);
            }

            if (snake->HasPos(next.pos) || next_cell.vis)
                continue;

            // calculate next h(pos) = dis(pos,dest) + step_count
            next.val = Utils::THROUGHWALL ?
                Utils::ThroughWallDistance(next.pos, head) : (next.pos - head);

            next.val += next_cell.step_count + 1;

            auto pos = find(steps.begin(), steps.end(), next);

            if (pos == steps.end())
            {
                // if the position is not in steps
                // save data and push it into steps
                next_cell.fromDirection = (Direction)((i + 2) % 4);
                next_cell.step_count = cell.step_count + 1;
                next_cell.dis = Utils::THROUGHWALL ? Utils::ThroughWallDistance(next.pos, head) : next.pos - head;

                if (Utils::DEBUG)
                    RenderStep(next.pos, next_cell.fromDirection, Color::B_GREEN);

                steps.push_back(next);
            }
            else
            {
                // if the position in steps
                // and the value is smaller than the existing ones
                if (next.val < (*pos).val)
                {
                    // update the value and cell data
                    next_cell.fromDirection = (Direction)((i + 2) % 4);
                    next_cell.step_count = cell.step_count + 1;
                    next_cell.dis = Utils::THROUGHWALL ? Utils::ThroughWallDistance(next.pos, head) : next.pos - head;
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

    return success ? Forward(head) : Direction::NONE;
}

void AStar::RenderStep(Pos pos, Direction dir, Color color)
{
    switch (dir)
    {
    case Direction::UP:
        Utils::Print("^", pos, color);
        break;
    case Direction::DOWN:
        Utils::Print("v", pos, color);
        break;
    case Direction::LEFT:
        Utils::Print("<", pos, color);
        break;
    case Direction::RIGHT:
        Utils::Print(">", pos, color);
        break;
    case Direction::NONE:
        Utils::Print("x", pos, Color::FOOD);
        break;
    default:
        break;
    }
}