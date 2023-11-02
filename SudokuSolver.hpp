///Riyuan Liu
///CS 235
///March 16th, 2023
///Project 6
///The objective of the puzzle is to fill up the grid. Each square must be filled with a digit 1-9, as follows:
//
//Each digit in a row must be unique, that is, if we place a 9 into a square that MUST  be the only 9 in that row.
//Similarly, each digit in a column must be unique, that is, if we place a 9 into a square that MUST  be the only 9 in that column and cannot repeat.
//The grid is further subdivided into nine 3x3 sub-grids. Each digit in a sub-grid must also be unique. Note in the example there is a thicker line that subdivides the 9x9 Sudoku board into 3x3 sub-grids. Each of these sub-grids must contain each digit 1-9 without repetition.
#include <iostream>
#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_


//We define Location within the Sudoku namespace.
//To use Location, you must specify the namespace Sudoku::Location
//Just like you do when using the standard namespace std::
namespace Sudoku
{
  struct Location
  {
    int row;
    int col;
  };
}

class SudokuSolver
{
public:
//------------------------------------------Constructors:
    SudokuSolver();
    SudokuSolver(std::string input_file);
//--------------------------------------Accessors and mutators:
    bool isPuzzleSolvable();
    void setSolvable();
    int** getPuzzleNumbers();
    void setPuzzleNumbers(int** puzzle) ;
//---------------------------------------Utility functions:
    Sudoku::Location returnNextEmpty();
    bool checkLegalValue(int value, Sudoku::Location location);
    void display();
    bool isPresentInCol(int col, int num);
    bool isPresentInRow(int row, int num);
    bool isPresentInBox(int boxStartRow, int boxStartCol, int num);
    bool isValidPlace(int row, int col, int num);
    bool solver();
private:
    int** mySudoku_;
    bool solvable;
};

#endif
