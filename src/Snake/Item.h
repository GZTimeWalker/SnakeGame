#pragma once

#include "Snake.h"

namespace GZ {
    class Item
    {
    public:
        Item(Pos p,int s) : pos(p), score(s) {};
        Pos pos;
        int score;

        virtual void Get(Snake* snake) = 0;
        virtual void Show() = 0;
    };

    class Portal : public Item {
    private:
        bool Detect(Pos pos, Snake* snake);

    public:
        Portal(Pos p): Item(p, 20) {}
        void Show();
        void Get(Snake* snake);
    };

    class Gold : public Item {
    public:
        Gold(Pos p) : Item(p, 100) {}
        void Show();
        void Get(Snake* snake);
    };
}


