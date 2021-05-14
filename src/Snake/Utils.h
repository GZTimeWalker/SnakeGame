#pragma once

#include <Windows.h>
#include <string>
#include <cmath>
#include <queue>

namespace GZ {
    /// <summary>
    /// An enumeration of available colors.
    /// </summary>
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
        CUT = B_BLUE | YELLOW,
    };

    /// <summary>
    /// An enumeration of all directions.
    /// </summary>
    enum class Direction : int
    {
        NONE = -1,
        UP = 0,
        LEFT = 1,
        DOWN = 2,
        RIGHT = 3
    };

    /// <summary>
    /// This exception is thrown when an unprocessable direction enumeration value is encountered.
    /// </summary>
    class unknown_direction : public std::exception {
    public:
        const char* what() const throw() {
            return "Unknown direction to move!";
        }
    };

    /// <summary>
    /// 2D position data structure.
    /// </summary>
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

    /// <summary>
    /// Utils class.
    /// </summary>
    class Utils
    {
    public:
        /// <summary>
        /// X coordinate offset value.
        /// </summary>
        static const int X_OFFSET = 20;

        /// <summary>
        /// Y coordinate offset value.
        /// </summary>
        static const int Y_OFFSET = 7;

        /// <summary>
        /// The height of the game area.
        /// </summary>
        static int HEIGHT;

        /// <summary>
        /// The width of the game area.
        /// </summary>
        static int WIDTH;

        /// <summary>
        /// The maximum count of items.
        /// </summary>
        static int ITEMCOUNT;

        /// <summary>
        /// Item generation probability(x/10000).
        /// </summary>
        static int ITEMRATE;

        /// <summary>
        /// Determine if the snake can get through the wall to the other side.
        /// </summary>
        static bool THROUGHWALL;

        /// <summary>
        /// Game version.
        /// </summary>
        static std::string VERSION;

        /// <summary>
        /// Determine whether to enable AI mode.
        /// </summary>
        static bool AIMODE;

        /// <summary>
        /// Determine whether to enable Debug mode.
        /// </summary>
        static bool DEBUG;

        /// <summary>
        /// Determine whether to skip Sleep() function to reduce lag.
        /// </summary>
        static bool SKIPSLEEP;

        /// <summary>
        /// Determine which items will be enabled.
        /// </summary>
        static unsigned int ITEMFLAG;

        /// <summary>
        /// The height to show dynamic infomation.
        /// </summary>
        static int INFOHEIGHT;

        /// <summary>
        /// Initialization window and random seed.
        /// </summary>
        static void Init();
        
        /// <summary>
        /// Move the cursor to the specified coordinate(with offset).
        /// </summary>
        /// <param name="x">x coordinate</param>
        /// <param name="y">y coordinate</param>
        static void To(int x, int y);

        /// <summary>
        /// Move the cursor to the specified coordinate(with offset).
        /// </summary>
        /// <param name="pos">coordinate position structure</param>
        static void To(Pos pos);

        /// <summary>
        /// Sets the output text color.
        /// </summary>
        /// <param name="color">color enumeration value</param>
        static void SetColor(Color color);

        /// <summary>
        /// Config the game.
        /// </summary>
        static void Config();

        /// <summary>
        /// Resize the window.
        /// </summary>
        static void Resize();
        
        /// <summary>
        /// When through-wall mode is enabled, ensure the coordinate are within range.
        /// </summary>
        /// <param name="pos">coordinate position structure</param>
        /// <returns>the coordinates after processing</returns>
        static Pos EnsureRange(Pos pos);

        /// <summary>
        /// The opposite direction of a direction.
        /// </summary>
        /// <param name="dir">direction</param>
        /// <returns>opposite direction</returns>
        static Direction Opposite(Direction dir);

        /// <summary>
        /// Calculate the coordinate distance in the through-wall mode.
        /// </summary>
        /// <param name="a">coordinate position a</param>
        /// <param name="b">coordinate position b</param>
        /// <returns>distance</returns>
        static int ThroughWallDistance(Pos a, Pos b);

        /// <summary>
        /// Determine if a position is outside the game area.
        /// </summary>
        /// <param name="pos">position</param>
        /// <returns>result</returns>
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