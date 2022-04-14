#include <vector>

using namespace std;

bool isSafe(const vector<int> &board, const int row, const int col);
int placeQueenInCol(vector<int> &board, const int col);

int nonAttackingQueens(int n)
{
    int count = 0;

    vector<int> board(n, -1);
    count = placeQueenInCol(board, 0);

    return count;
}

int placeQueenInCol(vector<int> &board, const int col)
{
    int possibleCombinations = 0;
    const int n = board.size();
    for (int idx = 0; idx < n; idx++)
    {
        const auto safeLoc = isSafe(board, idx, col);
        if (safeLoc)
        {
            board[col] = idx;
            if (col < n - 1)
                possibleCombinations += placeQueenInCol(board, col + 1);
            else
                possibleCombinations++;
        }
    }

    return possibleCombinations;
}

bool isSafe(const vector<int> &board, const int row, const int col)
{
    // row
    for (int idx = col - 1; idx >= 0; idx--)
        if (board[idx] == row)
            return false;

    // Up diagonal
    for (int idx = col - 1, rIdx = row - 1; idx >= 0 and rIdx >=0; idx--, rIdx--)
        if (board[idx] == rIdx)
            return false;

    // Down diagonal
    for (int idx = col - 1, rIdx = row + 1; idx >= 0 and rIdx < board.size(); idx--, rIdx++)
        if (board[idx] == rIdx)
            return false;

    return true;
}


int main()
{
    const auto n = nonAttackingQueens(4);
    return 0;
}