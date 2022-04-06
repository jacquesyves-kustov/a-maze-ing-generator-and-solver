#include "maze-solving-abc.h"
#include "dead-end-filling.h"


namespace maze_creating_and_solving
{
	extern char FREE_CELL;
	extern char CLOSED_CELL;
	extern char VISITED_CELL;
	extern char FINAL_CELL;


	Solver_DEF::Solver_DEF(Maze* maze) : Solver(maze)
	{

		// temporary storage
		Point* deadEndsPoints = new Point[((getColumns() - 1) / 2) * ((getRows() - 1) / 2)];


		deadEndsTotal = 0;


		// it counts free cells around another cell
		unsigned short openCells;

		// find all dead-ends
		for (unsigned short row = 1; row < getRows(); row += 2)
		{
			for (unsigned short column = 1; column < getColumns(); column += 2)
			{

				if (row == 1 && column == 1)
					continue;


				openCells = 0;

				// check upper cell
				if (maze_[row - 1][column] == FREE_CELL)
				{
					openCells++;
				}

				// check right cell
				if ((maze_[row][column + 1] == FREE_CELL))
				{
					openCells++;
				}

				// check lower cell
				if (maze_[row + 1][column] == FREE_CELL)
				{
					openCells++;
				}

				// check left cell
				if ((maze_[row][column - 1] == FREE_CELL))
				{
					openCells++;
				}


				// if there is only one free cell around then this cell is the dead-end
				if (openCells == 1)
				{
					deadEndsPoints[deadEndsTotal].x_ = row;
					deadEndsPoints[deadEndsTotal].y_ = column;
					deadEndsTotal++;
				}
			}
		}


		// last dead-end is the final point 
		finalPoint.x_ = deadEndsPoints[deadEndsTotal - 1].x_;
		finalPoint.y_ = deadEndsPoints[deadEndsTotal - 1].y_;
		maze_[finalPoint.x_][finalPoint.y_] = FINAL_CELL;


		// the final point is not the "dead-end", so we will not add it to the 'ptDeadEndsArr' 
		deadEndsTotal--;


		// create array of dead-ends without empty slots
		ptDeadEndsArr = new Point[deadEndsTotal];

		for (unsigned short deadEndIndex = 0; deadEndIndex < deadEndsTotal; ++deadEndIndex) 
		{
			ptDeadEndsArr[deadEndIndex] = deadEndsPoints[deadEndIndex];
		}

		// free temporary strorage
		delete[] deadEndsPoints;
	}


	Solver_DEF::~Solver_DEF() 
	{
		delete[] ptDeadEndsArr;
	}


	bool Solver_DEF::isJunction(const unsigned short row, const unsigned short column) 
	{
		unsigned short openCells = 0;

		// check upper cell
		if ((maze_[row - 1][column] == FREE_CELL))
		{
			openCells++;
		}

		// check right cell
		if ((maze_[row][column + 1] == FREE_CELL))
		{
			openCells++;
		}

		// check lower cell
		if (maze_[row + 1][column] == FREE_CELL)
		{
			openCells++;
		}

		// check left cell
		if ((maze_[row][column - 1] == FREE_CELL))
		{
			openCells++;
		}


		// junction is the cell with 2 or more free cells around
		if (openCells > 1)
			return true;
		else
			return false;
	}


	void Solver_DEF::fillDeadEnd(Point& point) 
	{
		maze_[point.x_][point.y_] = VISITED_CELL;

		while (true) 
		{
			// find free cell
			
			// check upper cell
			if (maze_[point.x_ + 1][point.y_] == FREE_CELL)
				point.x_++;

			// check right cell
			else if (maze_[point.x_][point.y_ + 1] == FREE_CELL)
				point.y_++;

			// check lower cell
			else if (maze_[point.x_ - 1][point.y_] == FREE_CELL)
				point.x_--;

			// check left cell
			else if (maze_[point.x_][point.y_ - 1] == FREE_CELL)
				point.y_--;
			

			// junction and start position
			if ((point.x_ == 1 && point.y_ == 1) || (isJunction(point.x_, point.y_)))         // не развилка и не старт
				break;
			

			maze_[point.x_][point.y_] = VISITED_CELL;
		}

	}


	void Solver_DEF::solveMaze()
	{
		for (unsigned short deadEndIndex = 0; deadEndIndex < deadEndsTotal; ++deadEndIndex) 
		{
			fillDeadEnd(ptDeadEndsArr[deadEndIndex]);
			
			// Code for step-by-step visualization of solving process
			/*showMaze();
			Sleep(250);
			system("cls");*/
		}
	}
}