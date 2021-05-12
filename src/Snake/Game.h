#pragma once

#include "Snake.h"
#include "Item.h"
#include <vector>

namespace GZ {
    class Game
    {
    private:
        unsigned long long score = 0;
        unsigned long long record = 0;
        unsigned int speed = 150;
        Pos food;
        Snake* snake;
        bool isRunning = false;
        bool pause = false;
        std::vector<Item*> items;

        void Run();
        void DrawMap();
        void PrintInfo();
        void GameOver();
        Pos GenPos();
        void GenFood();
        void GenItem();
        void Clear();
        bool ItemOccupying(Pos pos);
        void ListenKeyBoard();

    public:
        Game();
        ~Game();
        void Main();
    };
}


