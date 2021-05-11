#include "Utils.h"

#include <Windows.h>
#include <time.h>
#include <cstdio>
#include <iostream>

using namespace GZ;

int Utils::HEIGHT = 32;
int Utils::WIDTH = 70;
int Utils::ITEMCOUNT = 3;
int Utils::ITEMRATE = 50;
bool Utils::THROUGHWALL = false;

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

void Utils::Setting()
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
    std::cout << ">>> Use Through-Wall mode?(y/N) ";
    char ch;
    std::cin >> ch;
    THROUGHWALL = ch == 'y';
}

void Utils::Resize()
{
    system("cls");
    char buffer[32];
    sprintf_s(buffer, "mode con:cols=%d lines=%d", WIDTH + X_OFFSET, HEIGHT + Y_OFFSET);
    system(buffer);
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