#include "maze-creating-abc.h"

namespace maze_creating_and_solving
{
	char FREE_CELL = ' ';
	char CLOSED_CELL = '0';


	Maze::Maze(const unsigned short& rows, const unsigned short& columns) : matrixRows_(rows), matrixColumns_(columns)
	{
		// Выделение памяти
		matrix_ = new char* [matrixRows_];
		for (short row = 0; row < matrixRows_; ++row)
		{
			matrix_[row] = new char[matrixColumns_];
		}

		// Заполнение
		for (short row = 0; row < matrixRows_; ++row)
		{
			for (short column = 0; column < matrixColumns_; ++column)
			{
				matrix_[row][column] = CLOSED_CELL;
			}
		}
	}


	Maze::~Maze()
	{
		for (short row = 0; row < matrixRows_; ++row) {
			delete[] matrix_[row];
		}

		delete[] matrix_;
	}


	void Maze::showMaze() const
	{
		using std::cout;
		using std::endl;

		for (short row = 0; row < matrixRows_; ++row)
		{
			//cout << endl;
			for (short column = 0; column < matrixColumns_; ++column)
			{
				cout << std::setw(2) << matrix_[row][column];
			}
			cout << endl;
		}
		cout << endl;
	}


	void copyMaze(const Maze& maze, char** copy)
	{
		for (unsigned short row = 0; row < maze.matrixRows_; ++row)
		{
			for (unsigned short column = 0; column < maze.matrixColumns_; ++column)
			{
				copy[row][column] = maze.matrix_[row][column];
			}
		}
	}
}