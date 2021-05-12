#include "Item.h"

#include <iostream>

using namespace GZ;

void Portal::Show()
{
    Utils::To(pos);
    Utils::SetColor(Color::PORTAL);
    std::cout << "@";
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
            throw std::exception("Unknown direction!");
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
    Utils::To(pos);
    Utils::SetColor(Color::ORIGIN);
    std::cout << " ";
}

void Gold::Show()
{
    Utils::To(pos);
    Utils::SetColor(Color::GOLD);
    std::cout << "G";
}

void Gold::Get(Snake* snake)
{
    snake->AddLength(5);
}
