#include "input-functions.h"

namespace maze_creating_and_solving 
{
	void startMessage() 
	{
		std::cout << "Glad to see you in A-maze-ing generator and solver!" << std::endl << std::endl
			      << "In this program you can play with algorithms and create different mazes." << std::endl
			      << "It's a-MAZE-ing, isn't it?" << std::endl << std::endl;
	}


	unsigned short inputRows()
	{
		int input;
		unsigned short result = 7;

		while (true) 
		{
			std::cout << "Enter rows number: ";

			std::cin >> input;

			if (input % 2 != 0 && 6 < input && input < 62)
			{
				result = input;
				break;
			}
			else
				std::cout << "Sorry! Number of rows should be: " << std::endl
					      << "    - an odd number" << std::endl
				          << "    - more than 6" << std::endl
				          << "    - less than 62" << std::endl << std::endl;
		}
		
		std::cout << std::endl;

		return result;
	}


	unsigned short inputColumns()
	{
		int input;
		unsigned short result = 7;

		while (true)
		{
			std::cout << "Enter columns number: ";

			std::cin >> input;

			if (input % 2 != 0 && 6 < input && input < 118)
			{
				result = input;
				break;
			}
			else
				std::cout << "Sorry! Number of columns should be: " << std::endl
				          << "    - an odd number" << std::endl
				          << "    - more than 6" << std::endl
				          << "    - less than 118" << std::endl;
		}

		std::cout << std::endl;

		return result;
	}
	

	unsigned short inputMaxPassageLength(const unsigned short& rows, const unsigned short& columns)
	{
		int input;
		unsigned short result = 7;

		while (true)
		{
			std::cout << "Enter passage length: ";

			std::cin >> input;

			if (input == 0) 
			{
				result = rows * columns;
				break;
			}

			if (0 < input && input < rows * columns)
			{
				result = input;
				break;
			}
			else
				std::cout << "Sorry! Passage length should be: " << std::endl
				          << "    - more than 0" << std::endl
				          << "    - less than multiplying of rows and columns - " << rows * columns << std::endl
				          << "    *enter 0 to free algorithm's hands" << std::endl;
		}

		std::cout << std::endl;

		return result;
	}


	bool inputBranchingStrategy()
	{
		int input;
		bool result;

		while (true) 
		{
			std::cout << "It's time to choose branching strategy!" << std::endl;
			std::cout << "Enter 0: a maze with few junctions and long path to final point" << std::endl;
			std::cout << "Enter 1: a maze with a lot of junctions and short path to final point" << std::endl << std::endl;

			std::cout << "Enter 0 or 1: " << std::endl;
			std::cin >> input;

			if (input != 0 && input != 1)
			{
				std::cout << "Enter precisely 0 or 1!" << std::endl;
				continue;
			}

			else 
			{
				if (input == 0)
				{
					result = false;
					break;
				}

				if (input == 1) 
				{
					result = true;
					break;
				}
			}
		}

		std::cout << std::endl;

		return result;
	
	}
}