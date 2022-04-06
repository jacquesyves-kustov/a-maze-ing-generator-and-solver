#pragma once
#include "maze-creating-abc.h"

namespace maze_creating_and_solving 
{
	// ABC
	class Solver
	{
		unsigned short mazeRows_;
		unsigned short mazeColumns_;

	protected:
		char** maze_;

	public:
		Solver(Maze* maze);
		~Solver();


		unsigned short getRows() const { return mazeRows_; };
		unsigned short getColumns() const { return mazeColumns_; };
		void showMaze() const;

		virtual void solveMaze() = 0;
	};
}

