#include "maze-creating-abc.h"
#include "randomized-depth-first.h"


namespace maze_creating_and_solving
{
	extern char FREE_CELL;
	extern char CLOSED_CELL;

	Block::Block(const short& x, const short& y) : x_(x), y_(y)
	{
		isVisited_ = false;
		connectedWithUpperBlock_ = false;
		connectedWithRightBlock_ = false;
		connectedWithLowerBlock_ = false;
		connectedWithLeftBlock_ = false;
	}


	Maze_RDF::Maze_RDF(const unsigned short& rows, const unsigned short& columns, const unsigned short& passageLength, bool branching) : Maze(rows, columns), maxPassageLength_(passageLength), aLotOfBranches_(branching)
	{
		// Memory allocation
		blockRows_ = (matrixRows_ - 1) / 2;
		blockColumns_ = (matrixColumns_ - 1) / 2;
		blockSquare_ = blockRows_ * blockColumns_;
		blockArr_ = new Block[blockSquare_];

		// Create suitable graph
		short blockIndex = 0;
		for (short row = 1; row < matrixRows_; row += 2)
		{
			for (short column = 1; column < matrixColumns_; column += 2)
			{
				blockArr_[blockIndex++] = Block(row, column);
			}
		}
	}


	Maze_RDF::~Maze_RDF()
	{
		delete[] blockArr_;
	}


	bool Maze_RDF::blockCanBeConnected(const short& blockIndex) const
	{
		// CHECK UPPER BLOCK
		if (blockIndex - blockColumns_ > 0)
		{
			if (blockArr_[blockIndex - blockColumns_].getVisitedStatus() == false)
				return true;
		}

		// CHECK RIGHT BLOCK
		if (blockIndex + 1 != blockSquare_ && (blockIndex + 1) % blockColumns_ != 0)
		{
			if (blockArr_[blockIndex + 1].getVisitedStatus() == false)
				return true;
		}


		// CHECK LOWER BLOCK
		if (blockIndex + blockColumns_ < blockSquare_)
		{
			if (blockArr_[blockIndex + blockColumns_].getVisitedStatus() == false) 
				return true;
		}

		// CHECK LEFT BLOCK
		if (blockIndex - 1 >= 0 && blockIndex % blockColumns_ != 0)
		{
			if (blockArr_[blockIndex - 1].getVisitedStatus() == false)
				return true;
		}

		return false;

	}


	short Maze_RDF::connectBlocks(const short& blockIndex)
	{
		short link;
		short connectedBlockIndex;
		bool  bridgeIsCreated = false;

		blockArr_[blockIndex].setVisitedStatus(true);

		while (!bridgeIsCreated)
		{
			link = rand() % 4;

			switch (link)
			{
				case 0:
				{
					if (blockIndex - blockColumns_ > 0)
					{
						if (blockArr_[blockIndex - blockColumns_].getVisitedStatus() == false)
						{
							blockArr_[blockIndex].setConnectionWithUpperBlock(true);
							blockArr_[blockIndex - blockColumns_].setConnectionWithLowerBlock(true);
							connectedBlockIndex = blockIndex - blockColumns_;
							bridgeIsCreated = true;
						}
					}
					break;
				}

				case 1:
				{
					if (blockIndex + 1 != blockSquare_ && (blockIndex + 1) % blockColumns_ != 0)
					{
						if (blockArr_[blockIndex + 1].getVisitedStatus() == false)
						{
							blockArr_[blockIndex].setConnectionWithRightBlock(true);
							blockArr_[blockIndex + 1].setConnectionWithLeftBlock(true);
							connectedBlockIndex = blockIndex + 1;
							bridgeIsCreated = true;
						}
					}
					break;
				}	

				case 2:
				{
					if (blockIndex + blockColumns_ < blockSquare_)
					{
						if (blockArr_[blockIndex + blockColumns_].getVisitedStatus() == false)
						{
							blockArr_[blockIndex].setConnectionWithLowerBlock(true);
							blockArr_[blockIndex + blockColumns_].setConnectionWithUpperBlock(true);
							connectedBlockIndex = blockIndex + blockColumns_;
							bridgeIsCreated = true;
						}
					}
					break;
				}

				case 3:
				{
					if (blockIndex - 1 >= 0 && (blockIndex) % blockColumns_ != 0)
					{
						if (blockArr_[blockIndex - 1].getVisitedStatus() == 0)
						{
							blockArr_[blockIndex].setConnectionWithLeftBlock(true);
							blockArr_[blockIndex - 1].setConnectionWithRightBlock(true);
							connectedBlockIndex = blockIndex - 1;
							bridgeIsCreated = true;
						}
					}
					break;
				}
			}
		}

		blockArr_[connectedBlockIndex].setVisitedStatus(true);

		return connectedBlockIndex;

	}


	bool Maze_RDF::allBlocksAreVisited() const
	{
		for (short blockIndex = 0; blockIndex < blockSquare_; ++blockIndex) 
		{
			if (blockArr_[blockIndex].getVisitedStatus() == false)
				return false;
		}

		return true;

	}


	short Maze_RDF::findNewBlock_moreBranches(const short* visitedBlocks, const unsigned short& step) const
	{
		for (short blockIndex = 0; blockIndex <= step; ++blockIndex)
		{
			if (blockCanBeConnected(visitedBlocks[blockIndex]))
				return visitedBlocks[blockIndex];
		}
	}


	short Maze_RDF::findNewBlock_lessBranches(const short* visitedBlocks, const unsigned short& step) const
	{
		for (short blockIndex = step - 1; blockIndex >= 0; blockIndex--)
		{
			if (blockCanBeConnected(visitedBlocks[blockIndex]))
				return visitedBlocks[blockIndex];
		}
	}


	void Maze_RDF::updateMatrix()
	{
		for (short row = 1; row < matrixRows_; row += 2)
		{
			for (short column = 1; column < matrixColumns_; column += 2)
			{
				for (short blockIndex = 0; blockIndex < blockSquare_; ++blockIndex)
				{
					if (blockArr_[blockIndex].getCoordX() == row && blockArr_[blockIndex].getCoordY() == column)
					{
						matrix_[row - 1][column - 1] =
							matrix_[row - 1][column + 1] =
							matrix_[row + 1][column - 1] =
							matrix_[row + 1][column + 1] = CLOSED_CELL;

						matrix_[row][column] =
							(blockArr_[blockIndex].isConnectedWithUpperBlock() ||
							blockArr_[blockIndex].isConnectedWithRightBlock()  ||
							blockArr_[blockIndex].isConnectedWithLowerBlock()  ||
							blockArr_[blockIndex].isConnectedWithLeftBlock()) ? FREE_CELL : CLOSED_CELL;

						matrix_[row][column - 1] = (blockArr_[blockIndex].isConnectedWithLeftBlock())  ? FREE_CELL : CLOSED_CELL;
						matrix_[row][column + 1] = (blockArr_[blockIndex].isConnectedWithRightBlock()) ? FREE_CELL : CLOSED_CELL;
						matrix_[row - 1][column] = (blockArr_[blockIndex].isConnectedWithUpperBlock()) ? FREE_CELL : CLOSED_CELL;
						matrix_[row + 1][column] = (blockArr_[blockIndex].isConnectedWithLowerBlock()) ? FREE_CELL : CLOSED_CELL;
					}
				}
			}
		}
	}


	void Maze_RDF::createMaze()
	{
		short actualBlockIndex = 0;
		short* ptVisitedBlocksIndicies = new short[blockSquare_];
		ptVisitedBlocksIndicies[0] = actualBlockIndex;

		srand(time(0));
		unsigned short actualPassageLength = 0;
		bool generationIsOn = true;
		unsigned short generationStep = 1;

		while (generationIsOn) 
		{

			if (blockCanBeConnected(actualBlockIndex) && actualPassageLength != maxPassageLength_)
			{
				actualBlockIndex = connectBlocks(actualBlockIndex);
				ptVisitedBlocksIndicies[generationStep++] = actualBlockIndex;
				actualPassageLength++;
			}
			else
				if (allBlocksAreVisited()) 
				{
					// All blocks are visited, then the maze are generated
					generationIsOn = false;
				}
					
				else 
				{
					// Checks all visited blocks from first to find new way
					if (aLotOfBranches_) 
					{
						actualBlockIndex = findNewBlock_moreBranches(ptVisitedBlocksIndicies, generationStep);
					}
					else 
					{
						actualBlockIndex = findNewBlock_lessBranches(ptVisitedBlocksIndicies, generationStep);
					}
					
					actualPassageLength = 0;
				}
		
			// Code for step-by-step visualization of generation process
			/*updateMatrix();
			showMaze();
			Sleep(220);
			system("cls");*/
		
		}

		delete[] ptVisitedBlocksIndicies;
		updateMatrix();

	}
}
