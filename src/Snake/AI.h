#pragma once

#include "Utils.h"
#include "Snake.h"

namespace GZ {
	/// <summary>
	/// The cell object of the map.
	/// </summary>
	struct Cell {
		/// <summary>
		/// Determine whether the position is visited.
		/// </summary>
		bool vis = false;

		/// <summary>
		/// The step count from the start position.
		/// </summary>
		int step_count = 0;

		/// <summary>
		/// The manhattan distance to the destination.
		/// </summary>
		int dis = 0;

		/// <summary>
		/// The direction to get to this cell.
		/// </summary>
		Direction fromDirection = Direction::NONE;
	};

	/// <summary>
	/// Sortable position with an integer value.
	/// </summary>
	struct SortablePos {
		/// <summary>
		/// The position.
		/// </summary>
		Pos pos = { -1, -1 };

		/// <summary>
		/// The value.
		/// </summary>
		int val = 0;

		bool operator==(const SortablePos& other) const {
			return pos == other.pos;
		}
	};

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
		/// A map to record status.
		/// </summary>
		std::vector<std::vector<Cell>>* map;

		/// <summary>
		/// The array of positions, who can be searched in the next step.
		/// </summary>
		std::vector<SortablePos> steps;

		static int dx[4];
		static int dy[4];

		/// <summary>
		/// Get the cell of a position.
		/// </summary>
		Cell& GetCell(Pos pos);

		/// <summary>
		/// Get the next direction to go.
		/// </summary>
		Direction GoNext();

		/// <summary>
		/// Get the iterator of the step in steps which has the min value.
		/// </summary>
		auto GetMinStepPos();

		/// <summary>
		/// A Star Path Finding algorithm.
		/// </summary>
		Direction AStar(Pos dest, std::vector<Item*>& items);

		/// <summary>
		/// Backtrace to get next step
		/// </summary>
		Direction Backtrace(Pos pos);

		/// <summary>
		/// Show path finding step on game area.
		/// </summary>
		void RenderStep(Pos pos, Direction dir, Color color);

		/// <summary>
		/// clean the map
		/// </summary>
		void Clean();

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
		Direction Step(Pos food, std::vector<Item*>& items, std::vector<Item*>::iterator& getitem, Pos lastTail);
	};
}


