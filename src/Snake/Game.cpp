#include "Game.h"

#include <conio.h>
#include <Windows.h>
#include <string>
#include <iostream>
#include <iomanip>

using namespace GZ;

Game::Game()
{
    Utils::SetColor(Color::ORIGIN);
    ai = new AI();
    snake = new Snake(ai);
    
    snake->Draw();
    ai->SetSnake(snake);

    DrawMap();
    Utils::PrintLine("Press S to start!   ", { -Utils::X_OFFSET, 22 }, Color::RED);
}

Game::~Game()
{
    delete snake;
    delete ai;
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
                Utils::Config();
                Utils::Resize();
                Clear();
                Utils::PrintLine("Press S to start!   ", { -Utils::X_OFFSET, 22 }, Color::RED);
            }
        }
    }
}

void Game::DrawMap()
{
    Utils::SetColor(Color::YELLOW);
    std::string title[] = { "    ____   __                 _____  _   __ ___     __ __  ______",
                            "   / __ \\ / /____ _ __  __   / ___/ / | / //   |   / //_/ / ____/",
                            "  / /_/ // // __ `// / / /   \\__ \\ /  |/ // /| |  / ,<   / __/   ",
                            " / ____// // /_/ // /_/ /   ___/ // /|  // ___ | / /| | / /___   ",
                            "/_/    /_/ \\__,_/ \\__, /   /____//_/ |_//_/  |_|/_/ |_|/_____/   ",
                            "                 /____/                                          " };
    
    for(int i = 0; i < 6; ++i)
        Utils::Print(title[i], { (Utils::WIDTH - (int)title[i].length())/ 2 , i - Utils::Y_OFFSET});

    std::string border(Utils::WIDTH, '#');
    Utils::Print(border, { 0, 0 }, Color::WHITE);

    for (int i = 1; i < Utils::HEIGHT - 1; ++i)
    {
        Utils::Print("#", { 0, i });
        Utils::Print("#", { Utils::WIDTH - 1, i });
    }

    Utils::Print(border, { 0, Utils::HEIGHT - 1 });

    PrintConfig();
    PrintInfo();

    Utils::SetColor(Color::WHITE);
    Utils::PrintLine("Use W/↑ to UP");
    Utils::PrintLine("Use S/↓ to DOWN");
    Utils::PrintLine("Use A/← to LEFT");
    Utils::PrintLine("Use D/→ to RIGHT");
    Utils::PrintLine("Use 1 to SPEED UP");
    Utils::PrintLine("Use 2 to SLOW DOWN");
    Utils::PrintLine("Use c to CONFIG");

    Utils::PrintLine("      " + Utils::VERSION + "      ", {-Utils::X_OFFSET, Utils::HEIGHT - 5});
    Utils::PrintLine("  Made by GZTime  ");
}


void Game::Clear()
{
    system("cls");
    DrawMap();

    delete ai;
    ai = new AI();

    delete snake;
    snake = new Snake(ai);

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

    Utils::PrintLine("Press 3 to pause!   ", { -Utils::X_OFFSET, 22 }, Color::RED);

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
                    Utils::PrintLine("Press 3 to pause!   ", { -Utils::X_OFFSET, 22 }, Color::RED);
                }
                else if (ch == 'c' || ch == 'C')
                {
                    Utils::Config();
                    Utils::Resize();
                    Clear();
                    Utils::PrintLine("Press 3 to pause!   ", { -Utils::X_OFFSET, 22 }, Color::RED);
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
            {
                GenFood();
                if (Utils::DEBUG)
                {
                    Utils::SetColor(Color::ORIGIN);
                    system("cls");
                    for (auto &item:items)
                        item->Show();
                    snake->Draw();
                    DrawMap();
                    Utils::PrintLine("Press 3 to pause!   ", { -Utils::X_OFFSET, 22 }, Color::RED);
                }
            }

            GenItem();

            if(!Utils::SKIPSLEEP)
                Sleep(speed);
        }
    }

    Utils::PrintLine("Press S to restart! ", { -Utils::X_OFFSET, 22 }, Color::RED);

    isRunning = false;
}

void Game::PrintInfo()
{
    Utils::To(-Utils::X_OFFSET, 3);
    std::cout << std::setiosflags(std::ios::right);

    Utils::PrintLine("Score : ", Color::WHITE);
    Utils::SetColor(Color::GREEN);
    std::cout << std::setw(17) << score << std::endl << std::endl;

    Utils::PrintLine("Record: ", Color::WHITE);
    Utils::SetColor(Color::GREEN);
    std::cout << std::setw(17) << record << std::endl << std::endl;

    Utils::Print("Speed : ", Color::WHITE);
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(7) << speed << "ms" << std::endl << std::endl;

    Utils::Print("Length: ", Color::WHITE);
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(9) << snake->Length() << std::endl << std::endl;

    Utils::Print("Award : ", Color::WHITE);
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(9) << snake->Award() << std::endl << std::endl;

    std::cout << std::setiosflags(std::ios::left);
}

void Game::PrintConfig()
{
    Utils::To(-Utils::X_OFFSET, -Utils::Y_OFFSET + 2);

    std::cout << std::setiosflags(std::ios::right);

    Utils::Print(" AI Mode : ", Color::WHITE);
    Utils::PrintLine(Utils::AIMODE ? "   Yes" : "    No", Utils::AIMODE ? Color::GREEN : Color::RED);

    Utils::Print(" T - Wall: ", Color::WHITE);
    Utils::PrintLine(Utils::THROUGHWALL ? "   Yes" : "    No", Utils::THROUGHWALL ? Color::GREEN : Color::RED);

    Utils::Print("SkipSleep: ", Color::WHITE);
    Utils::PrintLine(Utils::SKIPSLEEP ? "   Yes" : "    No", Utils::SKIPSLEEP ? Color::GREEN : Color::RED);

    Utils::Print("ItemCount: ", Color::WHITE);
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(6) << Utils::ITEMCOUNT << std::endl;

    Utils::Print("ItemRate : ", Color::WHITE);
    Utils::SetColor(Color::YELLOW);
    std::cout << std::setw(6) << std::setprecision(5) << Utils::ITEMRATE / 10000.0 << std::endl;

    if (Utils::DEBUG)
        Utils::Print("  DEBUG Mode ON  ", { -Utils::X_OFFSET, -Utils::Y_OFFSET + 1}, Color::RED);

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
        Utils::Print(gameover[i], { (Utils::WIDTH - (int)gameover[i].length()) / 2, Utils::HEIGHT / 2 - 10 + i });
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
    Utils::Print(" ", food, Color::FOOD);
}

void Game::GenItem()
{
    if (rand() % 10000 < Utils::ITEMRATE && items.size() < Utils::ITEMCOUNT)
    {
        int rate = rand() % 100;
        if (rate < 35)
        {
            Gold* g = new Gold(GenPos());
            g->Show();
            items.push_back(g);
        }
        else if (rate < 70)
        {
            Cut* c = new Cut(GenPos());
            c->Show();
            items.push_back(c);
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
            Utils::PrintLine("Press 3 to continue!", { -Utils::X_OFFSET, 22 }, Color::RED);
            break;
        case 'c':
        case 'C':
            Utils::Config();
            Utils::Resize();
            Clear();
            Utils::PrintLine("Press 3 to pause!   ", { -Utils::X_OFFSET, 22 }, Color::RED);
            break;
        default:
            if (Utils::AIMODE)
                break;
            snake->ChangeDir(ch);
            break;
        }
    }
}
