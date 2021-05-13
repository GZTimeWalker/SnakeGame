#pragma once

#include "Snake.h"

namespace GZ {
    enum class ItemType: int {
        NONE = 0,
        PORTAL = 1,
        GOLD = 2,
        CUT = 3,
    };
    class Item
    {
    public:
        Item(Pos p,int s) : pos(p), score(s) {};
        Pos pos;
        int score;

        virtual void Get(Snake* snake) = 0;
        virtual void Show() = 0;
        virtual ItemType GetType() = 0;
    };

    class Portal : public Item {
    private:
        bool Detect(Pos pos, Snake* snake);

    public:

        Portal(Pos p): Item(p, 20) {}
        void Show();
        void Get(Snake* snake);
        ItemType GetType();
    };

    class Gold : public Item {
    public:

        Gold(Pos p) : Item(p, 100) {}
        void Show();
        void Get(Snake* snake);
        ItemType GetType();
    };

    class Cut : public Item {
    public:

        Cut(Pos p) : Item(p, 50) {}
        void Show();
        void Get(Snake* snake);
        ItemType GetType();
    };
}


