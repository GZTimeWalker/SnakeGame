#include "Item.h"

#include <iostream>

using namespace GZ;

void Portal::Show()
{
    Utils::Print("@", pos, Color::PORTAL);
}

bool Portal::Detect(Pos pos, Snake* snake)
{
    Pos next;
    for (int i = 0; i < 4; ++i)
    {
        next = pos;
        switch (snake->Toward)
        {
        case Direction::UP:
            next.y -= i;
            break;
        case Direction::DOWN:
            next.y += i;
            break;
        case Direction::LEFT:
            next.x -= i;
            break;
        case Direction::RIGHT:
            next.x += i;
            break;
        default:
            throw unknown_direction();
        }
        if (snake->HasPos(next))
            return true;
    }
    return false;
}

void Portal::Get(Snake* snake)
{
    Pos randPos;
    do{
        randPos = { 6 + rand() % (Utils::WIDTH - 12), 6 + rand() % (Utils::HEIGHT - 12) };
    } while (snake->HasPos(randPos) || Detect(randPos, snake));
    snake->Head = randPos;
    Utils::Print(" ", pos, Color::ORIGIN);
}

void Gold::Show()
{
    Utils::Print("G", pos, Color::GOLD);
}

void Gold::Get(Snake* snake)
{
    snake->AddLength(5);
}
