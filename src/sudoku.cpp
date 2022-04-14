#include <vector>
using namespace std;

struct Cell
{
    int r;
    int c;
};

bool isRowSafe(Cell cell, short n, vector<vector<int>> &sudoku)
{
    vector<int> row = sudoku[cell.r];

    for (int idx = 0; idx < 9; idx++)
    {
        if (row[idx] == n)
        {
            return false;
        }
    }

    return true;
}

bool isColSafe(Cell cell, short n, vector<vector<int>> &sudoku)
{
    for (int idx = 0; idx < 9; idx++)
    {
        if (sudoku[idx][cell.c] == n)
        {
            return false;
        }
    }

    return true;
}

bool isSquareSafe(Cell cell, short n, vector<vector<int>> &sudoku)
{
    short startingRow = cell.r >= 6
                            ? 6
                        : cell.r >= 3
                            ? 3
                            : 0;

    short startingCol = cell.c >= 6
                            ? 6
                        : cell.c >= 3
                            ? 3
                            : 0;
    for (int rowIdx = startingRow; rowIdx < startingRow + 3; rowIdx++)
    {
        for (int colIdx = startingCol; colIdx < startingCol + 3; colIdx++)
        {
            if (sudoku[rowIdx][colIdx] == n)
            {
                return false;
            }
        }
    }

    return true;
}

Cell getEmptyCell(vector<vector<int>> &sudoku)
{
    struct Cell cell = {-1, -1};
    for (int r = 0; r < 9; r++)
    {
        for (int c = 0; c < 9; c++)
        {
            if (sudoku[r][c] == 0)
            {
                cell.r = r;
                cell.c = c;
                return cell;
            }
        }
    }

    return cell;
}

bool solve(vector<vector<int>> &sudoku)
{
    Cell cell = getEmptyCell(sudoku);

    if (cell.r == -1)
    {
        // No empty cell found, Sudoku solved
        return true;
    }

    for (int n = 1; n < 10; n++)
    {
        if (isRowSafe(cell, n, sudoku) and isColSafe(cell, n, sudoku) and isSquareSafe(cell, n, sudoku))
        {
            sudoku[cell.r][cell.c] = n;

            if (solve(sudoku))
            {
                return true;
            }
        }
    }

    sudoku[cell.r][cell.c] = 0;
    return false;
}

vector<vector<int>> solveSudoku(vector<vector<int>> board)
{
    solve(board);
    return board;
}