#pragma once

#include "Utils.h"
#include "Snake.h"
#include "AStar.h"

namespace GZ {
	/// <summary>
	/// AI object.
	/// </summary>
	class AI
	{
	private:
		/// <summary>
		/// Snake object.
		/// </summary>
		Snake* snake;

		/// <summary>
		/// A Star to find way to food
		/// </summary>
		AStar* shortestPathToFood;

		/// <summary>
		/// Get the next direction to go.
		/// </summary>
		Direction Wander();

	public:
		AI();
		~AI();

		/// <summary>
		/// Set the snake object.
		/// </summary>
		void SetSnake(Snake* snake);

		/// <summary>
		/// Get next step to go.
		/// </summary>
		Direction Step(Pos food, std::vector<Item*>& items, std::vector<Item*>::iterator& getitem);
	};
}


