#include <vector>

using namespace std;

bool isOutOfBounds(const int r, const int c, const int rowCount, const int columnCount);

vector<int> zigzagTraverse(vector<vector<int>> array)
{
    const int rowCount = array.size();
    const int columnCount = rowCount > 0 ? array[0].size() : 0;

    vector<int> traversal(rowCount * columnCount);

    int r = 0, c = 0;
    bool goingDown = true;
    int idx = 0;

    while (!isOutOfBounds(r, c, rowCount, columnCount))
    {
        traversal[idx++] = array[r][c];
        if (goingDown)
            if (r == rowCount - 1 or c == 0)
            {
                goingDown = false;

                if (r < rowCount - 1)
                    r++;
                else
                    c++;
            }
            else
            {
                r++;
                c--;
            }
        else if (r == 0 or c == columnCount - 1)
        {
            goingDown = true;

            if (c < columnCount - 1)
                c++;
            else
                r++;
        }
        else
        {
            r--;
            c++;
        }
    }

    return traversal;
}

bool isOutOfBounds(const int r, const int c, const int rowCount, const int columnCount)
{
    return r < 0 || r >= rowCount || c < 0 || c >= columnCount;
}

int main()
{
    const auto zt = zigzagTraverse({{1, 5, 9, 13},
                                    {2, 6, 10, 14},
                                    {3, 7, 11, 15},
                                    {4, 8, 12, 16}});
    return 0;
}