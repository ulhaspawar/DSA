#include <vector>
using namespace std;

vector<int> searchInSortedMatrix(vector<vector<int>> matrix, int target)
{
    const int M = matrix.size();
    const int N = matrix[0].size();

    int row = 0, col = N - 1;

    while (row < M and col < N)
    {
        const int num = matrix[row][col];
        if (num == target)
        {
            return {row, col};
        }
        if (num < target)
            col--;
        else
            row++;
    }

    return {-1, -1};
}
