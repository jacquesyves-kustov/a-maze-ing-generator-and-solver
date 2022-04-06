#pragma once
#include <iostream>
#include <string>

namespace maze_creating_and_solving
{
	void startMessage();
	unsigned short inputRows();
	unsigned short inputColumns();
	unsigned short inputMaxPassageLength(const unsigned short& rows, const unsigned short& columns);
	bool inputBranchingStrategy();
}