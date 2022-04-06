#pragma once
#include "maze-creating-abc.h"
#include "maze-solving-abc.h"

namespace maze_creating_and_solving
{
	struct Point
	{
		unsigned short x_;
		unsigned short y_;
	};

	// DEF means Dead-End Filling
	class Solver_DEF : public Solver
	{
		unsigned short deadEndsTotal;
		Point* ptDeadEndsArr;
		Point finalPoint;

		bool isJunction(const unsigned short row, const unsigned short column);
		void fillDeadEnd(Point&);

	public:
		Solver_DEF(Maze* maze);
		~Solver_DEF();

		void solveMaze();
	};

}



