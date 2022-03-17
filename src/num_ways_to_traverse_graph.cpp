#include <vector>

using namespace std;

int numberOfWaysToTraverseGraph(int width, int height)
{
    vector<vector<int>> counts(height, vector<int>(width, 1));

    for (int rIdx{1}; rIdx < height; rIdx++)
    {
        for (int cIdx{1}; cIdx < width; cIdx++)
        {
            counts[rIdx][cIdx] = counts[rIdx - 1][cIdx] + counts[rIdx][cIdx - 1];
        }
    }

    return counts[height - 1][width - 1];
}
