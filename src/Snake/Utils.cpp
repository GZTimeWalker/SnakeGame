#include "Utils.h"

#include <Windows.h>
#include <time.h>
#include <cstdio>
#include <iostream>
#include <string>

using namespace GZ;

int Utils::HEIGHT = 32;
int Utils::WIDTH = 70;
int Utils::ITEMCOUNT = 3;
int Utils::ITEMRATE = 50;
// int Utils::ITEMCOUNT = 300;
// int Utils::ITEMRATE = 5000;
bool Utils::THROUGHWALL = true;
bool Utils::SKIPSLEEP = false;
bool Utils::AIMODE = false;
bool Utils::DEBUG = false;
std::string Utils::VERSION = "V3.2.1";

void Utils::To(int x, int y)
{
    COORD pos = { x + X_OFFSET, y + Y_OFFSET };
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handle, pos);
}

void Utils::To(Pos pos)
{
    To(pos.x, pos.y);
}

void Utils::SetColor(Color color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)color);
}

void Utils::Config()
{
    system("cls");
    SetColor(Color::WHITE);
    int input;
    std::cout << ">>> Please input your game size:" << std::endl;
    std::cout << ">>> WIDTH (70 <= w <= 140) = ";
    std::cin >> input;
    if (input < 70)
        input = 70;
    else if (input > 140)
        input = 140;
    WIDTH = input;
    std::cout << ">>> Set WIDTH to " << WIDTH << std::endl;
    std::cout << ">>> HEIGHT (32 <= h <= 60) = ";
    std::cin >> input;
    if (input < 32)
        input = 32;
    else if (input > 60)
        input = 60;
    HEIGHT = input;
    std::cout << ">>> Set HEIGHT to " << HEIGHT << std::endl;
    std::cout << ">>> ITEMCOUNT = ";
    std::cin >> ITEMCOUNT;
    std::cout << ">>> Set ITEMCOUNT to " << ITEMCOUNT << std::endl;
    std::cout << ">>> ITEMRATE (0 <= r <= 10000) = ";
    std::cin >> input;
    if (input < 0 || input > 10000)
        input = 50;
    ITEMRATE = input;
    std::cout << ">>> Set ITEMRATE to " << ITEMRATE << std::endl;

    char ch;
    std::cout << ">>> Use Through-Wall mode?(y/N) ";
    std::cin >> ch;
    THROUGHWALL = ch == 'y';
    std::cout << ">>> Set THROUGHWALL to " << (THROUGHWALL ? "True" : "False") << std::endl;

    std::cout << ">>> Use AI mode?(y/N) ";
    std::cin >> ch;
    AIMODE = ch == 'y';
    std::cout << ">>> Set AIMODE to " << (AIMODE ? "True" : "False") << std::endl;

    std::cout << ">>> Skip sleep time?(y/N) ";
    std::cin >> ch;
    SKIPSLEEP = ch == 'y';
    std::cout << ">>> Set SKIPSLEEP to " << (SKIPSLEEP ? "True" : "False") << std::endl;
}

void Utils::Resize()
{
    system("cls");
    char buffer[32];
    sprintf_s(buffer, "mode con:cols=%d lines=%d", WIDTH + X_OFFSET, HEIGHT + Y_OFFSET);
    system(buffer);
}

Pos Utils::EnsureRange(Pos pos)
{
    if (GZ::Utils::THROUGHWALL)
    {
        if (pos.x == 0)
            pos.x = GZ::Utils::WIDTH - 2;
        else if (pos.x == GZ::Utils::WIDTH - 1)
            pos.x = 1;

        if (pos.y == 0)
            pos.y = GZ::Utils::HEIGHT - 2;
        else if (pos.y == GZ::Utils::HEIGHT - 1)
            pos.y = 1;
    }
    return pos;
}

Direction Utils::Back(Direction dir)
{
    switch (dir)
    {
    case Direction::UP:
        return Direction::DOWN;
    case Direction::DOWN:
        return Direction::UP;
    case Direction::LEFT:
        return Direction::RIGHT;
    case Direction::RIGHT:
        return Direction::LEFT;
    case Direction::NONE:
        return Direction::NONE;
    default:
        throw unknown_direction();
    }
}

int GZ::Utils::ThroughWallDis(Pos a, Pos b)
{
    return min(std::abs(a.x - b.x), std::abs(b.x - a.x)) + min(std::abs(a.y - b.y), std::abs(b.y - a.y));
}

bool Utils::OutOfRange(Pos pos)
{
    return !(pos.x > 0 && pos.y > 0 && pos.x < Utils::WIDTH - 1 && pos.y < Utils::HEIGHT - 1);
}

void Utils::Init()
{
    Resize();
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO CursorInfo;
    GetConsoleCursorInfo(handle, &CursorInfo);
    CursorInfo.bVisible = false;
    SetConsoleCursorInfo(handle, &CursorInfo);
    srand((unsigned int)time(0));
}

void GZ::Utils::Print(std::string msg)
{
    std::cout << msg;
}

void GZ::Utils::Print(std::string msg, Pos pos)
{
    To(pos);
    std::cout << msg;
}

void GZ::Utils::Print(std::string msg, Color color)
{
    SetColor(color);
    std::cout << msg;
}

void GZ::Utils::Print(std::string msg, Pos pos, Color color)
{
    To(pos);
    SetColor(color);
    std::cout << msg;
}

void GZ::Utils::PrintLine(std::string msg)
{
    std::cout << msg << std::endl;
}

void GZ::Utils::PrintLine(std::string msg, Pos pos)
{
    To(pos);
    std::cout << msg << std::endl;
}

void GZ::Utils::PrintLine(std::string msg, Color color)
{
    SetColor(color);
    std::cout << msg << std::endl;
}

void GZ::Utils::PrintLine(std::string msg, Pos pos, Color color)
{
    To(pos);
    SetColor(color);
    std::cout << msg << std::endl;
}