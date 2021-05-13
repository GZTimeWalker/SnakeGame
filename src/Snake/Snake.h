#pragma once

#include "Utils.h"

#include <vector>

namespace GZ {
    class Item;
    class AI;
    class Snake
    {
    private:
        bool isAlive;
        int length;
        bool trimTail;
        int keepLen;
        int trimLen;
        int award;
        AI* ai;

        Pos Update(bool trim);
        bool IsSafe(Pos next);

    public:
        Direction Toward;
        Pos Head;
        std::vector<Pos> Body;

        Snake(AI* ai);
        bool HasPos(Pos pos);
        bool Alive();
        int Length();
        int Award();
        int Move(Pos food, std::vector<Item*>& items);
        void ChangeDir(char dir);
        void Draw();
        void AddLength(int len);
        void CutLength(int len);
    };
}

