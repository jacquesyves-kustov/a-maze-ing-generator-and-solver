#include "maze-solving-abc.h"


namespace maze_creating_and_solving
{
	char VISITED_CELL = '*';
	char FINAL_CELL = '?';

	Solver::Solver(Maze* maze)
	{
		mazeRows_ = maze->getMatrixRows();
		mazeColumns_ = maze->getMatrixColumns();


		maze_ = new char* [mazeRows_];

		for (unsigned short row = 0; row < mazeRows_; ++row)
			maze_[row] = new char[mazeColumns_];


		copyMaze(*maze, maze_);
	}


	Solver::~Solver()
	{
		for (unsigned short row = 0; row < mazeRows_; ++row)
		{
			delete[] maze_[row];
		}

		delete[] maze_;
	}


	void Solver::showMaze() const
	{
		using std::cout;
		using std::endl;

		for (short row = 0; row < mazeRows_; ++row)
		{
			//cout << endl;
			for (short column = 0; column < mazeColumns_; ++column)
			{
				cout << std::setw(2) << maze_[row][column];
			}
			cout << endl;
		}
		cout << endl;
	}

}
