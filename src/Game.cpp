#include "Game.h"

#include <conio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace GZ;

Game::Game()
{
    snake = new Snake();
    snake->Draw();
    DrawMap();

    Utils::SetColor(Color::RED);
    Utils::To(-Utils::X_OFFSET, 22);
    std::cout << "Press S to start!   " << std::endl;
}

Game::~Game()
{
    delete snake;
    for (auto& item : items)
        delete item;
}

void Game::Main()
{
    while (true)
    {
        if (_kbhit())
        {
            char ch = _getch();
            if (ch == 's' || ch == 'S')
                Run();
            else if (ch == 'c' || ch == 'C')
            {
                Utils::Setting();
                Utils::Resize();
                Clear();
                Utils::SetColor(Color::RED);
                Utils::To(-Utils::X_OFFSET, 22);
                std::cout << "Press S to start!   " << std::endl;
            }
        }
    }
}

void Game::DrawMap()
{
    Utils::SetColor(Color::YELLOW);
    Utils::To(-Utils::X_OFFSET, -Utils::Y_OFFSET);
    std::string blank((Utils::WIDTH - Utils::X_OFFSET) / 2 - 3, ' ');
    std::cout << blank << "    ____   __                 _____  _   __ ___     __ __  ______" << std::endl
              << blank << "   / __ \\ / /____ _ __  __   / ___/ / | / //   |   / //_/ / ____/" << std::endl
              << blank << "  / /_/ // // __ `// / / /   \\__ \\ /  |/ // /| |  / ,<   / __/   " << std::endl
              << blank << " / ____// // /_/ // /_/ /   ___/ // /|  // ___ | / /| | / /___   " << std::endl
              << blank << "/_/    /_/ \\__,_/ \\__, /   /____//_/ |_//_/  |_|/_/ |_|/_____/   " << std::endl
              << blank << "                 /____/                                          " << std::endl;
    std::string border(Utils::WIDTH, '#');
    Utils::To(0, 0);
    Utils::SetColor(Color::WHITE);
    std::cout << border;
    for (int i = 1; i < Utils::HEIGHT - 1; ++i)
    {
        Utils::To(0, i);
        std::cout << "#";
        Utils::To(Utils::WIDTH - 1, i);
        std::cout << "#";
    }
    Utils::To(0, Utils::HEIGHT - 1);
    std::cout << border;

    PrintInfo();

    Utils::SetColor(Color::WHITE);
    std::cout << "Use W/↑ to UP" << std::endl;
    std::cout << "Use S/↓ to DOWN" << std::endl;
    std::cout << "Use A/← to LEFT" << std::endl;
    std::cout << "Use D/→ to RIGHT" << std::endl;
    std::cout << "Use 1 to SPEED UP" << std::endl;
    std::cout << "Use 2 to SLOW DOWN" << std::endl;
    std::cout << "Use c to CONFIG" << std::endl;
    std::cout << std::endl << std::endl << std::endl << std::endl;
    Utils::To(-Utils::X_OFFSET, Utils::HEIGHT - 5);
    std::cout << "      V2.1.0      " << std::endl;
    std::cout << "  Made by GZTime  " << std::endl;
}


void Game::Clear()
{
    system("cls");
    DrawMap();
    delete snake;
    snake = new Snake();
    snake->Draw();
    GenFood();
    score = 0;
    for (auto& item : items)
        delete item;
    items.clear();
}

void Game::Run()
{
    isRunning = true;

    Clear();

    Utils::SetColor(Color::RED);
    Utils::To(-Utils::X_OFFSET, 22);
    std::cout << "Press 3 to pause!   " << std::endl;

    while (true)
    {
        if (pause)
        {
            if (_kbhit())
            {
                char ch = _getch();
                if (ch == '3')
                {
                    pause = false;
                    Utils::SetColor(Color::RED);
                    Utils::To(-Utils::X_OFFSET, 22);
                    std::cout << "Press 3 to pause!   " << std::endl;
                }
                else if (ch == 'c' || ch == 'C')
                {
                    Utils::Setting();
                    Utils::Resize();
                    Clear();
                    Utils::SetColor(Color::RED);
                    Utils::To(-Utils::X_OFFSET, 22);
                    std::cout << "Press 3 to pause!   " << std::endl;
                }
            }
        }
        else
        {
            if (record < score) record = score;

            PrintInfo();

            if (!snake->Alive())
            {
                GameOver();
                break;
            }

            ListenKeyBoard();
            score += snake->Move(food, items);

            if (snake->Head == food)
                GenFood();

            GenItem();
            Sleep(speed);
        }
    }

    Utils::SetColor(Color::RED);
    Utils::To(-Utils::X_OFFSET, 22);
    std::cout << "Press S to restart! " << std::endl;

    isRunning = false;
}

void Game::PrintInfo()
{
    Utils::To(-Utils::X_OFFSET, 3);
    std::cout << std::setiosflags(std::ios::right);

    Utils::SetColor(Color::WHITE);
    std::cout << "Score : " << std::endl;
    Utils::SetColor(Color::GREEN);
    std::cout << std::setw(17) << score << std::endl << std::endl;

    Utils::SetColor(Color::WHITE);
    std::cout << "Record: " << std::endl;
    Utils::SetColor(Color::GREEN);
    std::cout << std::setw(17) << record << std::endl << std::endl;

    Utils::SetColor(Color::WHITE);
    std::cout << "Speed : ";
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(7) << speed << "ms" << std::endl << std::endl;

    Utils::SetColor(Color::WHITE);
    std::cout << "Length: ";
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(9) << snake->Length() << std::endl << std::endl;

    std::cout << std::setiosflags(std::ios::left);
}

void Game::GameOver()
{
    Utils::SetColor(Color::RED);
    std::string gameover[] = {  "  ______                                    ",
                                " /      \\                                   ",
                                "/$$$$$$  |  ______   _____  ____    ______  ",
                                "$$ | _$$/  /      \\ /     \\/    \\  /      \\ ",
                                "$$ |/    | $$$$$$  |$$$$$$ $$$$  |/$$$$$$  |",
                                "$$ |$$$$ | /    $$ |$$ | $$ | $$ |$$    $$ |",
                                "$$ \\__$$ |/$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/ ",
                                "$$    $$/ $$    $$ |$$ | $$ | $$ |$$       |",
                                " $$$$$$/   $$$$$$$/ $$/  $$/  $$/  $$$$$$$/ ",
                                "                                            ",
                                "  ______                                    ",
                                " /      \\                                   ",
                                "/$$$$$$  | __     __  ______    ______      ",
                                "$$ |  $$ |/  \\   /  |/      \\  /      \\     ",
                                "$$ |  $$ |$$  \\ /$$//$$$$$$  |/$$$$$$  |    ",
                                "$$ |  $$ | $$  /$$/ $$    $$ |$$ |  $$/     ",
                                "$$ \\__$$ |  $$ $$/  $$$$$$$$/ $$ |          ",
                                "$$    $$/    $$$/   $$       |$$ |          ",
                                " $$$$$$/      $/     $$$$$$$/ $$/           " };
    for (int i = 0; i < 19; ++i)
    {
        Utils::To((Utils::WIDTH - 12) / 2 - 16, Utils::HEIGHT / 2 - 10 + i);
        std::cout << gameover[i];
    }
}

Pos Game::GenPos()
{
    Pos pos;
    do {
        pos = { 1 + rand() % (Utils::WIDTH - 2), 1 + rand() % (Utils::HEIGHT - 2) };
    } while (snake->HasPos(pos) || ItemOccupying(pos));
    return pos;
}

void Game::GenFood()
{
    food = GenPos();
    Utils::SetColor(Color::FOOD);
    Utils::To(food);
    std::cout << ' ';
}

void Game::GenItem()
{
    if (rand() % 10000 < Utils::ITEMRATE && items.size() < Utils::ITEMCOUNT)
    {
        int rate = rand() % 100;
        if (rate < 50)
        {
            Gold* g = new Gold(GenPos());
            g->Show();
            items.push_back(g);
        }
        else
        {
            Portal* p = new Portal(GenPos());
            p->Show();
            items.push_back(p);
        }
    }
}

bool Game::ItemOccupying(Pos pos)
{
    for (auto& item : items)
        if (pos == item->pos)
            return true;
    return false;
}

void Game::ListenKeyBoard()
{
    if (_kbhit())
    {
        char ch = _getch();
        switch (ch)
        {
        case '1':
            if (speed > 25) speed -= 25;
            else if (speed > 10) speed -= 5;
            else if (speed > 1) speed -= 1;
            break;
        case '2':
            if (speed < 25) speed = 25;
            else if (speed < 1000) speed += 25;
            break;
        case '3':
            pause = true;
            Utils::SetColor(Color::RED);
            Utils::To(-Utils::X_OFFSET, 22);
            std::cout << "Press 3 to continue!" << std::endl;
            break;
        case 'c':
        case 'C':
            Utils::Setting();
            Utils::Resize();
            Clear();
            Utils::SetColor(Color::RED);
            Utils::To(-Utils::X_OFFSET, 22);
            std::cout << "Press 3 to pause!   " << std::endl;
            break;
        default:
            snake->ChangeDir(ch);
            break;
        }
    }
}
