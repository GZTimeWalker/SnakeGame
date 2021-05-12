#include "Snake.h"
#include "Game.h"
#include "Utils.h"
#include "AI.h"

#include <Windows.h>
#include <iostream>
#include <conio.h>

using namespace GZ;

Snake::Snake(AI* ai)
{
    this->ai = ai;
    this->ai->SetSnake(this);

    isAlive = true;
    trimTail = true;
    Toward = Direction::UP;
    length = 3;
    keepLen = 0;
    for (int i = 0; i < length; ++i)
    {
        Head = {(Utils::WIDTH - 12) / 2, Utils::HEIGHT / 2 + 2 - i };
        Body.push_back(Head);
    }
}

bool Snake::HasPos(Pos pos)
{
    for (auto& p : Body)
        if (pos == p)
            return true;
    return false;
}

bool Snake::Alive()
{
    return isAlive;
}

void Snake::ChangeDir(char dir)
{
    if (!isascii(dir))
    {
        dir = _getch();
        switch (dir)
        {
        case 72:
            dir = 'W';
            break;
        case 80:
            dir = 'S';
            break;
        case 75:
            dir = 'A';
            break;
        case 77:
            dir = 'D';
            break;
        default:
            break;
        }
    }
    dir = dir < 'a' ? dir : dir - ('a' - 'A');
    switch (dir)
    {
    case 'W':
        if (Toward == Direction::DOWN)
            break;
        Toward = Direction::UP;
        break;
    case 'A':
        if (Toward == Direction::RIGHT)
            break;
        Toward = Direction::LEFT;
        break;
    case 'S':
        if (Toward == Direction::UP)
            break;
        Toward = Direction::DOWN;
        break;
    case 'D':
        if (Toward == Direction::LEFT)
            break;
        Toward = Direction::RIGHT;
        break;
    default:
        break;
    }
}

int Snake::Move(Pos food, std::vector<Item*>& items)
{
    Pos next = Pos(Head);
    next = Utils::EnsureRange(next + Toward);

    if (!IsSafe(next))
    {
        isAlive = false;
        return 0;
    }

    int score = 0;

    Head = next;
    auto getitem = items.end();

    for (auto item = items.begin(); item != items.end(); ++item)
    {
        if ((*item)->pos == next)
        {
            (*item)->Get(this);
            score = (*item)->score;
            getitem = item;
            break;
        }
    }

    Body.push_back(Head);
    Pos lastTail = { -1, -1 };

    if (!score)
    {
        bool getfood = (Head == food);
        lastTail = Update(!getfood && trimTail);
        if(getfood)
            score = length;
    }
    else 
    {
        lastTail = Update(trimTail);
    }
    
    if (Utils::AIMODE)
        Toward = ai->Step(food, items, getitem, lastTail);

    if (getitem != items.end())
    {
        delete (*getitem);
        items.erase(getitem);
    }

    return score;
}

Pos Snake::Update(bool trim)
{
    Utils::Print("*", Body[length - 1], Color::YELLOW);
    Utils::Print("@", Body[length]);
    if(trim)
    {
        Utils::Print(" ", Body[0]);
        Pos tail = Body[0];
        Body.erase(Body.begin());
        return tail;
    }
    if (!trimTail)
        if (!keepLen--)
            trimTail = true;
    length += 1;
    return { -1, -1 };
}

void Snake::Draw()
{
    Utils::SetColor(Color::YELLOW);
    for (unsigned int i = 0; i < length - 1; ++i)
        Utils::Print("*", Body[i]);
    Utils::Print("@", Head);
    Utils::SetColor(Color::ORIGIN);
}

void Snake::AddLength(int len)
{
    trimTail = false;
    keepLen += len;
}

bool Snake::IsSafe(Pos next)
{
    bool succ = next.x > 0 && next.y > 0 && next.x < Utils::WIDTH - 1&& next.y < Utils::HEIGHT - 1;
    if (!succ)
        return false;
    for (auto& pos : Body)
        if (next == pos)
            return false;
    return true;
}

unsigned int Snake::Length()
{
    return length;
}
