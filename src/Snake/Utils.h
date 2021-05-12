#pragma once

#include <Windows.h>
#include <string>
#include <cmath>
#include <queue>

namespace GZ {
    enum class Color: int 
    {
        ORIGIN = FOREGROUND_INTENSITY,
        RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
        GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
        BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
        CYAN = FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN,
        YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
        PINK = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
        WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

        B_ORIGIN = BACKGROUND_INTENSITY,
        B_RED = BACKGROUND_INTENSITY | BACKGROUND_RED,
        B_GREEN = BACKGROUND_INTENSITY | BACKGROUND_GREEN,
        B_BLUE = BACKGROUND_INTENSITY | BACKGROUND_BLUE,
        B_CYAN = BACKGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN,
        B_YELLOW = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN,
        B_PINK = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE,
        B_WHITE = BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,

        FOOD = B_PINK,
        GOLD = B_YELLOW | RED,
        PORTAL = B_CYAN | BLUE,
    };

    enum class Direction : int
    {
        NONE = 0,
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4
    };

    class unknown_direction : public std::exception {
    public:
        const char* what() const throw() {
            return "Unknown direction to move!";
        }
    };

    struct Pos 
    {
        int x;
        int y;
        bool operator==(const Pos& other) const {
            return x == other.x && y == other.y;
        }
        bool operator!=(const Pos& other) const {
            return x != other.x || y != other.y;
        }
        int operator-(const Pos& other) const {
            return std::abs(x - other.x) + std::abs(y - other.y);
        }
        Pos operator+(const Direction& dir)
        {
            Pos pos = { x, y };
            switch (dir)
            {
            case Direction::UP:
                pos.y -= 1;
                break;
            case Direction::DOWN:
                pos.y += 1;
                break;
            case Direction::LEFT:
                pos.x -= 1;
                break;
            case Direction::RIGHT:
                pos.x += 1;
                break;
            case Direction::NONE:
                break;
            default:
                throw unknown_direction();
            }
            return pos;
        }
    };

    class Utils
    {
    public:
        static const int X_OFFSET = 20;
        static const int Y_OFFSET = 7;
        static int HEIGHT;
        static int WIDTH;
        static int ITEMCOUNT;
        static int ITEMRATE;
        static bool THROUGHWALL;
        static std::string VERSION;
        static bool AIMODE;
        static bool DEBUG;
        static bool SKIPSLEEP;

        static void Init();
        static void To(int x, int y);
        static void To(Pos pos);
        static void SetColor(Color color);
        static void Config();
        static void Resize();
        static Pos EnsureRange(Pos pos);
        static Direction Back(Direction dir);
        static int ThroughWallDis(Pos a, Pos b);
        static bool OutOfRange(Pos pos);
        static void Print(std::string msg);
        static void Print(std::string msg, Pos pos);
        static void Print(std::string msg, Color color);
        static void Print(std::string msg, Pos pos, Color color);
        static void PrintLine(std::string msg);
        static void PrintLine(std::string msg, Pos pos);
        static void PrintLine(std::string msg, Color color);
        static void PrintLine(std::string msg, Pos pos, Color color);
    };
}