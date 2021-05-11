#include "Snake.h"
#include "Game.h"
#include "Utils.h"

#include <Windows.h>
#include <iostream>
#include <conio.h>

using namespace GZ;

Snake::Snake()
{
	isAlive = true;
	trimTail = true;
	Toward = Direction::UP;
	length = 3;
	keepLen = 0;
	for (int i = 0; i < length; ++i)
	{
		Head = {(Utils::WIDTH - 12) / 2, Utils::HEIGHT / 2 + 2 - i };
		body.push_back(Head);
	}
}

bool GZ::Snake::HasPos(Pos pos)
{
	for (auto& p : body)
		if (pos == p)
			return true;
	return false;
}

bool GZ::Snake::Alive()
{
	return isAlive;
}

void GZ::Snake::ChangeDir(char dir)
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

int GZ::Snake::Move(Pos food, std::vector<Item*>& items)
{
	Pos next = Pos(body[length - 1]);
	switch (Toward)
	{
	case Direction::UP:
		next.y -= 1;
		break;
	case Direction::DOWN:
		next.y += 1;
		break;
	case Direction::LEFT:
		next.x -= 1;
		break;
	case Direction::RIGHT:
		next.x += 1;
		break;
	default:
		throw std::exception("Unknown direction!");
	}

	if (Utils::THROUGHWALL)
	{
		if (next.x == 0)
			next.x = Utils::WIDTH - 2;
		else if (next.x == Utils::WIDTH - 1)
			next.x = 1;

		if (next.y == 0)
			next.y = Utils::HEIGHT - 2;
		else if (next.y == Utils::HEIGHT - 1)
			next.y = 1;
	}

	if (!IsSafe(next))
	{
		isAlive = false;
		return false;
	}

	int score = 0;

	Head = next;

	for (int i = 0; i < items.size(); ++i)
	{
		if (items[i]->pos == next)
		{
			items[i]->Get(this);
			score = items[i]->score;
			delete items[i];
			items.erase(items.begin() + i);
			break;
		}
	}

	body.push_back(Head);

	if (!score)
	{
		bool getfood = (Head == food);
		Update(!getfood && trimTail);
		return getfood ? length : 0;
	}
	else 
	{
		Update(trimTail);
	}
	
	return score;
}

void GZ::Snake::Update(bool trim)
{
	Utils::SetColor(Color::YELLOW);
	Utils::To(body[length - 1]);
	std::cout << "*";
	Utils::To(body[length]);
	std::cout << "@";
	if(trim)
	{
		Utils::To(body[0]);
		std::cout << " ";
		body.erase(body.begin());
		return;
	}
	if (!trimTail)
		if (!keepLen--)
			trimTail = true;
	length += 1;
}

void GZ::Snake::Draw()
{
	Utils::SetColor(Color::YELLOW);
	for (unsigned int i = 0; i < length - 1; ++i)
	{
		Utils::To(body[i]);
		std::cout << "*";
	}
	Utils::To(body[length - 1]);
	std::cout << "@";

	Utils::SetColor(Color::ORIGIN);
}

void GZ::Snake::AddLength(int len)
{
	trimTail = false;
	keepLen += len;
}

bool GZ::Snake::IsSafe(Pos next)
{
	bool succ = next.x > 0 && next.y > 0 && next.x < Utils::WIDTH - 1&& next.y < Utils::HEIGHT - 1;
	if (!succ)
		return false;
	for (auto& pos : body)
		if (next == pos)
			return false;
	return true;
}

unsigned int GZ::Snake::Length()
{
	return length;
}
