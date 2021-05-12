#pragma once

#include "Utils.h"
#include <vector>

namespace GZ {
    class Item;
    class Snake
    {
    private:
        bool isAlive;
        std::vector<Pos> body;
        int length;
        bool trimTail;
        int keepLen;

        void Update(bool trim);
        bool IsSafe(Pos next);

    public:
        Direction Toward;
        Pos Head;

        Snake();
        bool HasPos(Pos pos);
        bool Alive();
        int Move(Pos food, std::vector<Item*>& items);
        void ChangeDir(char dir);
        unsigned int Length();
        void Draw();
        void AddLength(int len);
    };
}

