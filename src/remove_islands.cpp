#include <vector>
#include <stack>
#include <tuple>

using namespace std;

void dfs(vector<vector<int>> &matrix, const int r, const int c);
void markNonIslands(vector<vector<int>> &matrix);
void removeIslandsHelper(vector<vector<int>> &matrix);
void unmarkNonIslands(vector<vector<int>> &matrix);

vector<vector<int>> removeIslands(vector<vector<int>> matrix)
{
    markNonIslands(matrix);
    removeIslandsHelper(matrix);
    unmarkNonIslands(matrix);
    return matrix;
}

void markNonIslands(vector<vector<int>> &matrix)
{
    const int M = matrix.size(), N = matrix[0].size();

    // Top
    for (int col{0}; col < N; col++)
        if (matrix[0][col] == 1)
            dfs(matrix, 0, col);

    // Right
    for (int row{1}; row < M; row++)
        if (matrix[row][N - 1] == 1)
            dfs(matrix, row, N - 1);

    // Bottom
    if (M > 1)
        for (int col{0}; col < N - 1; col++)
            if (matrix[M - 1][col] == 1)
                dfs(matrix, M - 1, col);

    // Left
    if (N > 1)
        for (int row{1}; row < M - 1; row++)
            if (matrix[row][0] == 1)
                dfs(matrix, row, 0);
}

void unmarkNonIslands(vector<vector<int>> &matrix)
{
    const int M = matrix.size(), N = matrix[0].size();

    for (int r{0}; r < M; r++)
        for (int c{0}; c < N; c++)
            if (matrix[r][c] == 2)
                matrix[r][c] = 1;
}

void dfs(vector<vector<int>> &matrix, const int r, const int c)
{
    const auto M{matrix.size()}, N{matrix[0].size()};

    stack<pair<int, int>> toBeProcessed;

    toBeProcessed.push({r, c});

    while (!toBeProcessed.empty())
    {
        int row, col;
        tie(row, col) = toBeProcessed.top();

        toBeProcessed.pop();
        matrix[row][col] = 2;

        if (row > 0 and matrix[row - 1][col] == 1)
            toBeProcessed.push({row - 1, col});
        if (row < M - 1 and matrix[row + 1][col] == 1)
            toBeProcessed.push({row + 1, col});
        if (col > 0 and matrix[row][col - 1] == 1)
            toBeProcessed.push({row, col - 1});
        if (col < N - 1 and matrix[row][col + 1] == 1)
            toBeProcessed.push({row, col + 1});
    }
}

void removeIslandsHelper(vector<vector<int>> &matrix)
{
    const int M = matrix.size(), N = matrix[0].size();
    for (int r{1}; r < M - 1; r++)
        for (int c{1}; c < N - 1; c++)
            if (matrix[r][c] == 1)
                matrix[r][c] = 0;
}

int main()
{
    removeIslands({{1, 0, 0, 0, 0, 0},
                   {0, 1, 0, 1, 1, 1},
                   {0, 0, 1, 0, 1, 0},
                   {1, 1, 0, 0, 1, 0},
                   {1, 0, 1, 1, 0, 0},
                   {1, 0, 0, 0, 0, 1}});
}