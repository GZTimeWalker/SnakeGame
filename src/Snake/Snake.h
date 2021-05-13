#pragma once

#include "Utils.h"

#include <vector>

namespace GZ {
    class Item;
    class AI;
    class Snake
    {
    private:
        /// <summary>
        /// Determine whether the snake is alive.
        /// </summary>
        bool isAlive;

        /// <summary>
        /// The length of this snake.
        /// </summary>
        int length;

        /// <summary>
        /// Determine whether to trim the snake tail.
        /// </summary>
        bool trimTail;

        /// <summary>
        /// Number of blocks the snake needs to extend.
        /// </summary>
        int keepLen;

        /// <summary>
        /// Number of blocks the snake needs to trim.
        /// </summary>
        int trimLen;

        /// <summary>
        /// The score to get when snake get a food.
        /// </summary>
        int award;

        /// <summary>
        /// AI object to control this snake.
        /// </summary>
        AI* ai;

        /// <summary>
        /// Update the snake on the map.
        /// </summary>
        /// <param name="trim">Whether to trim the snake tail</param>
        /// <returns>the position of trimed block</returns>
        Pos Update(bool trim);

        /// <summary>
        /// Returns whether the next position is safe.
        /// </summary>
        /// <param name="next">next position</param>
        bool IsSafe(Pos next);

    public:
        /// <summary>
        /// The direction where the snake's head towards.
        /// </summary>
        Direction Toward;

        /// <summary>
        /// The position of snake head.
        /// </summary>
        Pos Head;

        /// <summary>
        /// The position array of snake body.
        /// </summary>
        std::vector<Pos> Body;

        Snake(AI* ai);

        /// <summary>
        /// Returns whether the snake's body has the position.
        /// </summary>
        /// <param name="pos">position</param>
        bool HasPos(Pos pos);

        /// <summary>
        /// Returns whether the snake is alive.
        /// </summary>
        bool Alive();

        /// <summary>
        /// Returns the length of this snake.
        /// </summary>
        int Length();

        /// <summary>
        /// Returns the current score when get a food.
        /// </summary>
        int Award();

        /// <summary>
        /// Move the snake.
        /// </summary>
        /// <param name="food">food position</param>
        /// <param name="items">the array of items</param>
        /// <returns></returns>
        int Move(Pos food, std::vector<Item*>& items);

        /// <summary>
        /// Change the direction the snake towards.
        /// </summary>
        /// <param name="dir">new direction</param>
        void ChangeDirection(char dir);

        /// <summary>
        /// Draw the whole snake on game area.
        /// </summary>
        void Draw();

        /// <summary>
        /// Lengthen the snake.
        /// </summary>
        /// <param name="len">numbers of blocks to lengthen.</param>
        void AddLength(int len);

        /// <summary>
        /// Cut the snake.
        /// </summary>
        /// <param name="len">numbers of blocks to cut.</param>
        void CutLength(int len);
    };
}

