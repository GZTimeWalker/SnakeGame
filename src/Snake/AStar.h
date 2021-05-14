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
	/// A Star Path Finding algorithm.
	/// </summary>
	class AStar
	{
	private:
		/// <summary>
		/// A map to record status.
		/// </summary>
		std::vector<std::vector<Cell>>* map;

		/// <summary>
		/// The array of positions, which can be searched in the next step.
		/// </summary>
		std::vector<SortablePos> steps;

		bool drawStep;

		/// <summary>
		/// Last destination.
		/// </summary>
		Pos lastDest = { -1, -1 };

		/// <summary>
		/// Get the cell of a position.
		/// </summary>
		Cell& GetCell(Pos pos);

		/// <summary>
		/// Get the iterator of the step in steps which has the min value.
		/// </summary>
		auto GetMinStepPos();

		/// <summary>
		/// Show path finding step on game area.
		/// </summary>
		void RenderStep(Pos pos, Direction dir, Color color);

		/// <summary>
		/// Get next direction to go
		/// </summary>
		Direction Forward(Pos from);

	public:
		AStar(bool drawstep = false);
		~AStar();

		/// <summary>
		/// Get next step
		/// </summary>
		Direction Step(Pos dest, Snake* snake, std::vector<Item*>& items);

		/// <summary>
		/// clean the map
		/// </summary>
		void Clean();
	};
}


