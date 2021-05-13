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
    award = 3;
    keepLen = 0;
    trimLen = 0;

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

void Snake::ChangeDirection(char dir)
{
    // support arrow key input

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

    // can not turn to backward directly

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
    // get next positon, step forward

    Pos next = Pos(Head);
    next = Utils::EnsureRange(next + Toward);

    if (!IsSafe(next))
    {
        isAlive = false;
        return 0;
    }

    Head = next;

    int score = 0;

    // whether the snake touch the item

    auto getitem = items.end();

    for (auto item = items.begin(); item != items.end(); ++item)
    {
        if ((*item)->pos == Head)
        {
            // let item to process the snake
            (*item)->Get(this);
            score = (*item)->score;
            getitem = item;
            break;
        }
    }

    // let head to be the last one in body

    Body.push_back(Head);

    Pos lastTail = { -1, -1 };

    // if did not touch any item

    if (!score)
    {
        // whether the snake get the food
        bool getfood = (Head == food);

        // update the snake
        // trim tail when didn't get the food and trimTail flag is true
        lastTail = Update(!getfood && trimTail);

        // update the score
        if(getfood)
            score = award;
    }
    else 
    {
        // update the snake with trimTail flag
        lastTail = Update(trimTail);
    }
    
    // let AI to choose where to go next.

    if (Utils::AIMODE)
        Toward = ai->Step(food, items, getitem, lastTail);

    // remove the item

    if (getitem != items.end())
    {
        delete (*getitem);
        items.erase(getitem);
    }

    return score;
}

Pos Snake::Update(bool trim)
{
    // last head become body, and head need to draw
    Utils::Print("*", Body[length - 1], Color::YELLOW);
    Utils::Print("@", Body[length]);

    if(trim)
    {
        // erase tail
        Utils::Print(" ", Body[0]);
        Pos tail = Body[0];
        Body.erase(Body.begin());

        // if need to erase more
        if (trimLen > 0 && length > 3)
        {
            Utils::Print(" ", Body[0]);
            tail = Body[0];
            Body.erase(Body.begin());
            --trimLen;
            --length;
        }

        return tail;
    }

    // use this to lengthen your snake
    if (!trimTail)
        if (!keepLen--)
            trimTail = true;

    length += 1;
    award += 1;

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

void Snake::CutLength(int len)
{
    trimLen += len;
}

bool Snake::IsSafe(Pos next)
{
    // if next step is out of game area
    if (Utils::OutOfRange(next))
        return false;

    // if touch self
    for (auto& pos : Body)
        if (next == pos)
            return false;

    return true;
}

int Snake::Length()
{
    return length;
}

int GZ::Snake::Award()
{
    return award;
}
