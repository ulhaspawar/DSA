#include <vector>
#include <climits>
#include<math.h>

using namespace std;

vector<vector<int>> getSums(const vector<vector<int>> &matrix);

int maximumSumSubmatrix(vector<vector<int>> matrix, int size)
{
    const auto M{matrix.size()}, N{matrix[0].size()};
    const auto sums = getSums(matrix);

    int maxSum{INT_MIN};
    for (size_t r = size; r < M + 1; r++)
        for (size_t c = size; c < N + 1; c++)
            maxSum = max(maxSum, sums[r][c] - sums[r - size][c] - sums[r][c - size] + sums[r - size][c - size]);

    return maxSum;
}

vector<vector<int>> getSums(const vector<vector<int>> &matrix)
{
    const auto M{matrix.size()}, N{matrix[0].size()};
    vector<vector<int>> sums(M + 1, vector<int>(N + 1, 0));

    for (size_t r{1}; r < M + 1; r++)
        for (size_t c{1}; c < N + 1; c++)
            sums[r][c] = sums[r - 1][c] + sums[r][c - 1] - sums[r - 1][c - 1] + matrix[r - 1][c - 1];

    return sums;
}

int main()
{
    maximumSumSubmatrix(
        {{5, 3, -1, 5},
         {-7, 3, 7, 4},
         {12, 8, 0, 0},
         {1, -8, -8, 2}},
        2);
}
