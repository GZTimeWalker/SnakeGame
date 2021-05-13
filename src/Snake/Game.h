#pragma once

#include "Snake.h"
#include "Item.h"
#include "AI.h"

#include <vector>

namespace GZ {
    /// <summary>
    /// The game object.
    /// </summary>
    class Game
    {
    private:
        /// <summary>
        /// Current score.
        /// </summary>
        unsigned long long score = 0;

        /// <summary>
        /// The record score.
        /// </summary>
        unsigned long long record = 0;

        /// <summary>
        /// The time interval between each step(millisecond).
        /// </summary>
        unsigned int speed = 150;

        /// <summary>
        /// The position for food.
        /// </summary>
        Pos food;

        /// <summary>
        /// The snake object.
        /// </summary>
        Snake* snake;

        /// <summary>
        /// Determine whether the game is running.
        /// <para>Doesn't seem to help</para>
        /// </summary>
        bool isRunning = false;

        /// <summary>
        /// Determine whether the game is pausing.
        /// </summary>
        bool pause = false;

        /// <summary>
        /// The item array.
        /// </summary>
        std::vector<Item*> items;

        /// <summary>
        /// The AI object to control the snake.
        /// </summary>
        AI* ai = nullptr;

        /// <summary>
        /// Run the game event loop.
        /// </summary>
        void Run();

        /// <summary>
        /// Draw the map.
        /// </summary>
        void DrawMap();

        /// <summary>
        /// Print game infomation.
        /// </summary>
        void PrintInfo();

        /// <summary>
        /// Print current configuration.
        /// </summary>
        void PrintConfig();

        /// <summary>
        /// Show gameover text.
        /// </summary>
        void GameOver();

        /// <summary>
        /// Generate a random available position.
        /// </summary>
        /// <returns>random position</returns>
        Pos GenPos();

        /// <summary>
        /// Generate food.
        /// </summary>
        void GenFood();

        /// <summary>
        /// Try to generate a item.
        /// </summary>
        void GenItem();

        /// <summary>
        /// Clear the window and redraw the map.
        /// </summary>
        void Clear();

        /// <summary>
        /// Returns whether the position is occupied by the item.
        /// </summary>
        /// <param name="pos">position</param>
        /// <returns>whether the position is occupied by the item.</returns>
        bool ItemOccupying(Pos pos);

        /// <summary>
        /// Listen to keyboard event.
        /// </summary>
        void ListenKeyBoard();

    public:
        Game();
        ~Game();

        /// <summary>
        /// The main function to start the game.
        /// </summary>
        void Main();
    };
}


