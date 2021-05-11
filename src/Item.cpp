#include "Item.h"

#include <iostream>

void GZ::Portal::Show()
{
	Utils::To(pos);
	Utils::SetColor(Color::PORTAL);
	std::cout << "@";
}

bool GZ::Portal::Detect(Pos pos, Snake* snake)
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

void GZ::Portal::Get(Snake* snake)
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

void GZ::Gold::Show()
{
	Utils::To(pos);
	Utils::SetColor(Color::GOLD);
	std::cout << "G";
}

void GZ::Gold::Get(Snake* snake)
{
	snake->AddLength(5);
}
