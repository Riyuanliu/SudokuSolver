///Riyuan Liu
///CS 235
///April 28th, 2023
///Project 6
//The objective of the puzzle is to fill up the grid. Each square must be filled with a digit 1-9, as follows:
//
//Each digit in a row must be unique, that is, if we place a 9 into a square that MUST  be the only 9 in that row.
//Similarly, each digit in a column must be unique, that is, if we place a 9 into a square that MUST  be the only 9 in that column and cannot repeat.
//The grid is further subdivided into nine 3x3 sub-grids. Each digit in a sub-grid must also be unique. Note in the example there is a thicker line that subdivides the 9x9 Sudoku board into 3x3 sub-grids. Each of these sub-grids must contain each digit 1-9 without repetition.

#include "SudokuSolver.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <cstring>
#include <stdexcept>
//------------------------------------------Constructors:-----------------------------
SudokuSolver::SudokuSolver(){
    mySudoku_=new int*[9];
    for (int i = 0; i < 9; i++) {
        mySudoku_[i] = new int[9];
        memset(mySudoku_[i], 0, 9 * sizeof(int));
    }
    solvable=false;
    
}
SudokuSolver::SudokuSolver(std::string input_file){
    mySudoku_ = new int*[9];
    for (int i = 0; i < 9; i++) {
        mySudoku_[i] = new int[9];
    }
    //check if file is readable
    std::ifstream infile(input_file);
    if (!infile) {
        throw std::invalid_argument("File not found");
    }
    std::string line;
    int row = 0;
    //read in data, line by line, and item by item
    while (std::getline(infile, line)) {
        if (row >= 9) {
            break;
        }
        std::string token;
        int col = 0;
        std::stringstream ss(line);
        while (std::getline(ss, token, ',')) {
            if (col >= 9) {
                break;
            }
            int value = std::stoi(token);
            mySudoku_[row][col] = value;
            col++;
        }
        if (col < 9) {
            throw std::invalid_argument("Invalid input file");
        }
        row++;
    }
    if (row < 9) {
        throw std::invalid_argument("Invalid input file");
    }
    //close the file
    infile.close();
//    call the solver;
    solver();
}

//--------------------------------------Accessors and mutators:
//call if puzzle is sovlerable
bool SudokuSolver::isPuzzleSolvable(){
    return solvable;
}
//set the solvable of the puzzle to true
void SudokuSolver::setSolvable(){
    solvable=true;
}
//return the sudoku that is store;
int** SudokuSolver::getPuzzleNumbers(){
    return mySudoku_;
}
//set the current sudoku to
void SudokuSolver::setPuzzleNumbers(int** puzzle){
    mySudoku_=puzzle;
}
//---------------------------------------Utility functions:
//find the emoty value
Sudoku::Location SudokuSolver::returnNextEmpty(){
    Sudoku::Location a;
        a.row=-1;
        a.col=-1;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(mySudoku_[i][j]==0){
                    a.row=i;
                    a.col=j;
                    return a;
                }
            }
        }
        
        return a;
}
//check the value able to place in
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location){
    return isValidPlace(location.row, location.col, value);
}
//display the sudoku
void SudokuSolver::display() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                std::cout << " | ";
            }
            if (mySudoku_[i][j] == 0) {
                std::cout << "X ";
            }else {
                std::cout << mySudoku_[i][j] << " ";
            }
        }
        std::cout << std::endl;
        if ((i+1) % 3 == 0 && i != 8) {
            std::cout << "- - - - - - - - - - - -" << std::endl;
        }
    }
}
//find if number is find in col
bool SudokuSolver::isPresentInCol(int col, int num){
    for (int row = 0; row < 9; row++)
          if (mySudoku_[row][col] == num)
             return true;
       return false;
}
//find if the value are find in row
bool SudokuSolver::isPresentInRow(int row, int num){
    for (int col = 0; col < 9; col++)
          if (mySudoku_[row][col] == num)
             return true;
       return false;
}
//find if the value are find in the 3x3 box
bool SudokuSolver::isPresentInBox(int boxStartRow, int boxStartCol, int num){
    for (int row = 0; row < 3; row++)
          for (int col = 0; col < 3; col++)
             if (mySudoku_[row+boxStartRow][col+boxStartCol] == num)
                return true;
       return false;
}
//check if the value can be place in the location
bool SudokuSolver::isValidPlace(int row, int col, int num){
   //when item not found in col, row and current 3x3 box
   return !isPresentInRow(row, num) && !isPresentInCol(col, num) && !isPresentInBox(row - row%3 ,col - col%3, num);
}
//solve the sudoku, by calling solver every time it reach a new empty box, until all the box is fill.
bool SudokuSolver::solver(){
    Sudoku::Location empty=returnNextEmpty();
    if(empty.row==-1&&empty.col==-1){
        return true;
    }
    for(int num=1;num<=9;num++){
        if(isValidPlace(empty.row, empty.col, num)){
            mySudoku_[empty.row][empty.col]=num;
            if(solver()){
                setSolvable();
                return true;
            }
            mySudoku_[empty.row][empty.col]=0;
        }
    }
    return false;
}

