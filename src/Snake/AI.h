#pragma once

#include "Utils.h"
#include "Snake.h"

namespace GZ {
	struct Cell {
		bool vis = false;
		int step_count = 0;
		int dis = 0;
		Direction backDir = Direction::NONE;
	};
	struct SortablePos {
		Pos pos = { -1, -1 };
		int val = 0;
		bool operator==(const SortablePos& other) const {
			return pos == other.pos;
		}
		bool operator<(const SortablePos& other) const {
			return val < other.val;
		}
	};
	class AI
	{
	private:
		Snake* snake;
		std::vector<std::vector<Cell>>* map;
		std::vector<SortablePos> steps;
		static int dx[4];
		static int dy[4];

		Cell& GetCell(Pos pos);
		Direction GoRand();
		auto GetMinStepPos();
		Direction AStar(Pos dest, std::vector<Item*>& items);
		void RenderStep(Pos pos, Direction dir, Color color);

	public:
		AI();
		~AI();
		void SetSnake(Snake* snake);
		Direction Step(Pos food, std::vector<Item*>& items, std::vector<Item*>::iterator& getitem, Pos lastTail);
	};
}


