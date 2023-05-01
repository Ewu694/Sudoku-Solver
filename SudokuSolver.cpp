/* 
    Name: Eric Wu
    Professor: Ms.Tiziana Ligorio
    Course: CS235
    Date Due: 05/02/2023
    Description: This program creates a sudoku solver using multiple functions
*/
#include "SudokuSolver.hpp"

SudokuSolver::SudokuSolver()
{
    puzzle_numbers_ = new int*[9];
    for(int row = 0; row < 9; row++)
    {
        puzzle_numbers_[row] = new int[9];
    }
    for (int row = 0; row < 9; row++)
    {
        for (int col = 0; col < 9; col++) {
            puzzle_numbers_[row][col] = 0;
        }
    }
    puzzle_solvability_ = false;
}

SudokuSolver::SudokuSolver(std::string input_file)
{
    std::ifstream sudoku_board(input_file);
    if(sudoku_board.fail())
    {
        std::cout << "File cannot be opened for reading \n";
        exit(1);//exit if file cannot be opened
    }
    
    puzzle_numbers_ = new int*[9];
    for(int row = 0; row < 9; row++)
    {
        puzzle_numbers_[row] = new int[9];
    }
    std::string temp_line_reader; //holds the values that will be read from the file
    int board_num; //used for stringstream to convert string to int
    while(!sudoku_board.eof())
    {
        for(int row = 0; row = 9; row++)
        {
            for(int col = 0; col = 9; col++)
            {
                getline(sudoku_board, temp_line_reader, ',');
                std::stringstream int_num_hold;
                int_num_hold << temp_line_reader;
                int_num_hold >> board_num;
                puzzle_numbers_[row][col] = board_num;
            }
        }
    }
}

bool SudokuSolver::isPuzzleSolvable()
{
    return puzzle_solvability_;
}

void SudokuSolver::setSolvable()
{
    puzzle_solvability_ = true;
}

int** SudokuSolver::getPuzzleNumbers()
{
    return puzzle_numbers_;
}

void SudokuSolver::setPuzzleNumbers(int** puzzle)
{
    puzzle_numbers_ = puzzle;
}

Sudoku::Location SudokuSolver::retiurnNextEmpty()
{
    Sudoku::Location zero_finder;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(puzzle_numbers_[i][j] == 0)
            {
                zero_finder.row = i;
                zero_finder.col = j;
            }
        }
    }
    return zero_finder;
}

bool SudokuSolver::IsPresentInCol(int col, int value)
{
    for(int row = 0; row < 9; row++)
    {
        if(puzzle_numbers_[row][col] == value)
        {
            return true;
        }
    }
    return false;
}

bool SudokuSolver::IsPresentInRow(int row, int value)
{
    for(int col = 0; col < 9; col++)
    {
        if(puzzle_numbers_[row][col] == value)
        {
            return true;
        }
    }
    return false;
}

bool SudokuSolver::IsPresentInSubgrid(int subgrid_row, int subgrid_col, int value)
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
        if(puzzle_numbers_[row + subgrid_row][col + subgrid_col] == value)
        {
            return true;
        }
        }
    }
  return false;
}

bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location)
{
    return !IsPresentInRow(location.row, value) && !IsPresentInCol(location.col, value) && !IsPresentInSubgrid(location.row - location.row % 3, location.col - location.col % 3, value);//checks to see if value is in any of the rows, cols and 3x3 subgrids. If it is found, return false, else true.
}

void SudokuSolver::display()
{
    for(int row = 0; row < 9; row++)
    {
        for(int col = 0; col < 9; col++)
        {
            if(col == 3 || col == 6)
            {
                std::cout << " | ";
            }
            else if(puzzle_numbers_[row][col] == 0)
            {
                std::cout << 0;
            }
            else
            {
                std::cout << puzzle_numbers_[row][col];
            }
        }
        if(row == 2 || row == 5)
        {
            std::cout << std::endl;
        }
        for(int i = 0; i < 9; i++)
        {
            std::cout << "- ";
        }
        std::cout << std::endl;
    }
}



