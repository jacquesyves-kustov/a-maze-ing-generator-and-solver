#pragma once
#include <iostream>
#include <iomanip>
#include <ctime>
#include "Windows.h"

namespace maze_creating_and_solving 
{
	// Abstract base class

	class Maze
	{
	protected:
		unsigned short  matrixRows_;
		unsigned short  matrixColumns_;
		char** matrix_;

	public:
		Maze(const unsigned short& rows = 11, const unsigned short& columns = 11);
		virtual ~Maze();

		// METHODS
		void showMaze() const;

		// GETTERS
		unsigned short getMatrixRows() const { return matrixRows_; };
		unsigned short getMatrixColumns() const { return matrixColumns_; };
		
		// PURE VIRTUAL METHODS
		virtual void createMaze() = 0;
		
		// FRIENDS
		friend void copyMaze(const Maze& original, char** copy);

	};
}
