#include "AI.h"
#include "Item.h"

using namespace GZ;
using namespace std;


AI::AI()
{
    snake = nullptr;
    shortestPathToFood = new AStar(true);
}

AI::~AI()
{
    delete shortestPathToFood;
}

void AI::SetSnake(Snake* snake)
{
    this->snake = snake;
}

Direction AI::Wander()
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



Direction AI::Step(Pos food, std::vector<Item*>& items, std::vector<Item*>::iterator& getitem)
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
            shortestPathToFood->Clean();
            return snake->Toward;
        }
    }

    // if get the food
    if (food == snake->Head)
    {
        shortestPathToFood->Clean();
        return Wander();
    }

    auto step = shortestPathToFood->Step(food, snake, items);

    if (step == Direction::NONE)
        return Wander();

    return step;
}
