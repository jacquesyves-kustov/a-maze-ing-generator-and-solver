#pragma once
#include "maze-creating-abc.h"

namespace maze_creating_and_solving
{
	// Blocks are sort of graph nodes behind a maze
	class Block 
	{
		short x_;
		short y_;
		bool  isVisited_;
		bool  connectedWithUpperBlock_;
		bool  connectedWithRightBlock_;
		bool  connectedWithLowerBlock_;
		bool  connectedWithLeftBlock_;
	
	public:
		Block(const short& x = 1, const short& y = 1);

		// Getters
		short getCoordX() const { return x_; };
		short getCoordY() const { return y_; };
		bool getVisitedStatus() const { return isVisited_; };
		bool isConnectedWithUpperBlock() const { return connectedWithUpperBlock_; };
		bool isConnectedWithRightBlock() const { return connectedWithRightBlock_; };
		bool isConnectedWithLowerBlock() const { return connectedWithLowerBlock_; };
		bool isConnectedWithLeftBlock()  const { return connectedWithLeftBlock_; };
		
		// Setters
		void setVisitedStatus(const bool val) { isVisited_ = val; };
		void setConnectionWithUpperBlock(const bool val) { connectedWithUpperBlock_ = val; };
		void setConnectionWithRightBlock(const bool val) { connectedWithRightBlock_ = val; };
		void setConnectionWithLowerBlock(const bool val) { connectedWithLowerBlock_ = val; };
		void setConnectionWithLeftBlock(const bool val)  { connectedWithLeftBlock_ = val; };
	};

	// RDF means Rando,ized Depth First
	class Maze_RDF : public Maze
	{
		unsigned short maxPassageLength_;
		short   blockRows_;
		short   blockColumns_;
		short   blockSquare_;
		Block*  blockArr_;
		bool aLotOfBranches_;

		bool blockCanBeConnected(const short& blockIndex) const;
		short connectBlocks(const short& blockIndex);
		bool allBlocksAreVisited() const;
		short findNewBlock_moreBranches(const short* visitedBlocks, const unsigned short& step) const;
		short findNewBlock_lessBranches(const short* visitedBlocks, const unsigned short& step) const;
		void updateMatrix();
		
	public:
		Maze_RDF(const unsigned short& rows = 7, const unsigned short& columns = 7, const unsigned short& passageLength = 5, bool branching = true);
		~Maze_RDF();

		virtual void createMaze();
		//virtual void showMaze() const;
	};
}



