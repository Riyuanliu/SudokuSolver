//
//  main.cpp
//  Sudoko Solver
//
//  Created by Riyuan Liu on 11/1/23.
//
#include <iostream>
#include "SudokuSolver.hpp"

int main()
{
    std::cout << "Welcome to Sudoku Solver" << std::endl;
    
    std::string filename;
    std::cout << "Please enter the name of the CSV file containing the Sudoku puzzle you would like to solve: ";
    std::cin >> filename;

    SudokuSolver solver(filename);

    if (solver.isPuzzleSolvable())
    {
        std::cout << "Solving the Sudoku puzzle...\n";

        if (solver.solver())
        {
            std::cout << "Solved Sudoku Puzzle:\n";
            solver.display();
        }
        else
        {
            std::cout << "No solution found for the Sudoku puzzle.\n";
        }
    }
    else
    {
        std::cout << "The provided Sudoku puzzle is not solvable. Please check the puzzle and try again.\n";
    }

    return 0;
}

