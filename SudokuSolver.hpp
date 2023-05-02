/* 
    Name: Eric Wu
    Professor: Ms.Tiziana Ligorio
    Course: CS235
    Date Due: 05/02/2023
    Description: This is the implementation for a Sudoku Solver
*/

#ifndef SUDOKU_SOLVER_HPP_
#define SUDOKU_SOLVER_HPP_
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

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
 
//Add your public members here
SudokuSolver();//default constructors
SudokuSolver(std::string input_file);//parameterized constructor, *** will need to implement other functions to support this and make it easier***

bool isPuzzleSolvable();//isPuzzleSolvable() returns true if the puzzle is solvable, false otherwise. We suggest you keep track of this when solving the problem at construction, rather than solving the puzzle again each time this function is called.
void setSolvable();//records if puzzle is solvable or not
int** getPuzzleNumbers();//returns the 2D pointer array representing the puzzle
void setPuzzleNumbers(int** puzzle);//sets the 2D pointer array representing the puzzle to the value of the parameter 

/*
returnNextEmpty() returns a Location object with the coordinates of the first 0 found in the 2D pointer array, meaning that it is an empty square in the sudoku board. 
To find the first empty square you must read the 2D array from top-left (0,0) to bottom right (8,8), one row at a time. 
Set the row and col of the Location to the indices at which the first 0 is found in the 2D array. 
If there are no empty squares the Location object should have row and col values of -1.
*/
Sudoku::Location returnNextEmpty() const;

/*
checkLegalValue(int value, Sudoku::Location location) returns true if the value parameter (which can take on values 1-9) can legally be placed at the given location in the 2D array without breaking the rules of sudoku. 
It returns false if placing value at location is not a legal move. 
Remember, in order to be a valid move, the value must be unique with a row, column, and sub-grid.
*/
bool checkLegalValue(int value, Sudoku::Location location);

/*
display will print the current board
-N is an integer 1-9 (the function displays the actual integer not an N)
-X represents a blank box where there is a zero (the function displays the X not the zero)
-After every 3 numbers (columns), we have a " | " to separate sub-grids. Note that each " | " is preceded by two space characters and followed by a single space character.
-After every 3 rows, we have 12 dashes " - " to separate the sub-grids.
*/
void display();

/*
Function to solve the sudoku board
*/
bool SudokuSolution();

private:
//Add your private members here
bool puzzle_solvability_;
int** puzzle_numbers_;
};
#endif
