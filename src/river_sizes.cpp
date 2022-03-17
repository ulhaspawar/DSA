#include <vector>
#include <stack>
#include <tuple>
using namespace std;

int getRiverLength(vector<vector<int>> &matrix, const int row, const int col)
{
    int riverLength{0};
    stack<pair<int, int>> toBeVisited;
    toBeVisited.emplace(row, col);
    matrix[row][col] = 0;
    while (!toBeVisited.empty())
    {
        int r, c;
        tie(r, c) = move(toBeVisited.top());
        toBeVisited.pop();
        riverLength++;

        if (r > 0 and matrix[r - 1][c] == 1)
        {
            matrix[r - 1][c] = 0;
            toBeVisited.emplace(r - 1, c);
        }

        if (r < matrix.size() - 1 and matrix[r + 1][c] == 1)
        {
            matrix[r + 1][c] = 0;
            toBeVisited.emplace(r + 1, c);
        }
        if (c > 0 and matrix[r][c - 1] == 1)
        {
            matrix[r][c - 1] = 0;
            toBeVisited.emplace(r, c - 1);
        }
        if (c < (matrix[0].size() - 1) and matrix[r][c + 1] == 1)
        {
            matrix[r][c + 1] = 0;
            toBeVisited.emplace(r, c + 1);
        }
    }
    return riverLength;
}

vector<int> riverSizes(vector<vector<int>> matrix)
{
    vector<int> riverLengths;

    for (int r = 0; r < matrix.size(); r++)
    {
        for (int c = 0; c < matrix[r].size(); c++)
        {
            if (matrix[r][c] == 1)
            {
                riverLengths.push_back(getRiverLength(matrix, r, c));
            }
        }
    }

    return riverLengths;
}
