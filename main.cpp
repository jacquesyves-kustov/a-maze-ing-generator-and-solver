#include <iostream>
#include "input-functions.h"
#include "randomized-depth-first.h"
#include "dead-end-filling.h"


int main()
{
    using namespace maze_creating_and_solving;

    // GENERAL VARIABLES
    unsigned short MATRIX_ROWS;
    unsigned short MATRIX_COLUMNS;

    // RANDOMIZED DEPTH FIRST VARIABLES
    bool BRANCHING_STRATEGY;
    unsigned short MAX_PASSAGE_LENGTH;

 
    // Program starts
    startMessage();


    // Set maze parameters
    MATRIX_ROWS = inputRows();
    MATRIX_COLUMNS = inputColumns();
    MAX_PASSAGE_LENGTH = inputMaxPassageLength(MATRIX_ROWS, MATRIX_COLUMNS);
    BRANCHING_STRATEGY = inputBranchingStrategy();


    // Create Maze and Solver instances
    Maze* ptMaze = new Maze_RDF{ MATRIX_ROWS, MATRIX_COLUMNS, MAX_PASSAGE_LENGTH, BRANCHING_STRATEGY};
    ptMaze->createMaze();

    Solver* ptSolver = new Solver_DEF{ ptMaze };
    

    // SHOW A NEW MAZE
    std::cout << "YOUR MAZE: " << std::endl;
    ptMaze->showMaze();


    // SOLVE IT
    ptSolver->solveMaze();


    // SHOW THE SOLVED MAZE
    std::cout << "SOLVED MAZE: " << std::endl;
    ptSolver->showMaze();


    delete ptMaze;
    delete ptSolver;
}