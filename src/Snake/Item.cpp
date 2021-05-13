#include "Item.h"

#include <iostream>

using namespace GZ;

/* Portal */

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

bool Portal::TryGen()
{
    return (rand() % 10 < 5);
}

ItemType Portal::GetType()
{
    return ItemType::PORTAL;
}

/* Portal END */

/* Gold */

void Gold::Show()
{
    Utils::Print("G", pos, Color::GOLD);
}

void Gold::Get(Snake* snake)
{
    snake->AddLength(5);
}

bool Gold::TryGen()
{
    return (rand() % 10 < 4);
}

ItemType Gold::GetType()
{
    return ItemType::GOLD;
}

/* Gold  END */

/* Cut */

void Cut::Show()
{
    Utils::Print("U", pos, Color::CUT);
}

void Cut::Get(Snake* snake)
{
    snake->CutLength(5);
}

bool Cut::TryGen()
{
    return (rand() % 10 < 4);
}

ItemType Cut::GetType()
{
    return ItemType::CUT;
}

/* Cut  END */

