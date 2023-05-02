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
    puzzle_numbers_ = new int*[9];
    for (int i = 0; i < 9; i++) 
        {
          puzzle_numbers_[i] = new int[9];
        }
    std::ifstream sudokuboard(input_file);

        // returns error if file wasn't successfully opened
        if (!sudokuboard.is_open()) 
        {
            std::cerr << "Failed to open file " << input_file << std::endl;
            exit(1);
        }
        std::string temp_reader;
        // read the file using a nested loop
        if(sudokuboard.is_open())
        {
            for(int row = 0; row < 9; row++)
            {
                std::getline(sudokuboard,temp_reader);
                std::stringstream iss(temp_reader);
                for(int col = 0;col < 9;col++)
                {
                    std::string line;
                    std::getline(iss,line,',');
                    std::stringstream num(line);
                    num >> puzzle_numbers_[row][col];
                }
            }
        }
        else
        {
            puzzle_solvability_ = false;
        }

    SudokuSolution();
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

Sudoku::Location SudokuSolver::returnNextEmpty() const
{
    Sudoku::Location zero_finder;
    zero_finder.row = -1;
    zero_finder.col = -1;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(puzzle_numbers_[i][j] == 0)
            {
                zero_finder.row = i;
                zero_finder.col = j;
                return zero_finder;
            }
        }
    }
    return zero_finder;
}

bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location)
{
    for(int row = 0; row < 9; row++)
    {
        if(row != location.row){
            if(puzzle_numbers_[row][location.col] == value)
            {
                return false;
            }
        }
    }
    for(int col = 0; col < 9; col++)
    {
        if(col != location.col){
            if(puzzle_numbers_[location.row][col] == value)
            {
                return false;
            }
        }
    }
    int start_row = (location.row / 3) * 3;
    int start_col = (location.col / 3) * 3;
    for(int row = start_row; row < start_row + 3; row++)
    {
        for(int col = start_col; col < start_col + 3; col++)
        {
            if(puzzle_numbers_[row][col] == value)
            {
                return false;
            }
        }
    }
    return true;
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
            if(puzzle_numbers_[row][col] == 0)
            {
                std::cout << "X ";
            }
            else
            {
            std::cout << puzzle_numbers_[row][col] << " ";
            }
        }
        if(row == 2 || row == 5)
        {
            std::cout << std::endl;
            for(int i = 0; i < 12; i++)
            {
                std::cout << "- ";
            }
        }
        std::cout << std::endl;
    }
}

bool SudokuSolver::SudokuSolution()
{
    Sudoku::Location empty = returnNextEmpty();
    if(empty.row == -1 && empty.col == -1)
        return true;
    for(int i = 1; i <= 9; i++)
    {   
        if(checkLegalValue(i, empty))
        {
            puzzle_numbers_[empty.row][empty.col] = i;
            if(SudokuSolution())
            {
                puzzle_solvability_ = true;
                return true;
            }
            else
            {
                puzzle_solvability_ = false;
                puzzle_numbers_[empty.row][empty.col] = 0;
            }
        }
    }
}



