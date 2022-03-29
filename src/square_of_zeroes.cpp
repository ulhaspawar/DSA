#include <vector>

using namespace std;

struct zero_info
{
    int left{0}, right{0}, top{0}, bottom{0};
};

bool squareOfZeroes(vector<vector<int>> matrix)
{
    const int N = matrix.size();

    vector<vector<zero_info>> zeroesInfo(N, vector<zero_info>(N));

    for (int rLR{0}, rRL = N - 1; rLR < N; rLR++, rRL--)
    {
        for (int cUD{0}, cDU = N - 1; cUD < N; cUD++, cDU--)
        {
            if (matrix[rLR][cUD] == 0)
            {
                if (cUD > 0 and matrix[rLR][cUD - 1] == 0)
                    zeroesInfo[rLR][cUD].left = zeroesInfo[rLR][cUD - 1].left + 1;

                if (rLR > 0 and matrix[rLR - 1][cUD] == 0)
                    zeroesInfo[rLR][cUD].top = zeroesInfo[rLR - 1][cUD].top + 1;
            }

            if (matrix[rRL][cDU] == 0)
            {
                if (cDU < N - 1 and matrix[rRL][cDU + 1] == 0)
                    zeroesInfo[rRL][cDU].right = zeroesInfo[rRL][cDU + 1].right + 1;

                if (rRL < N - 1 and matrix[rRL + 1][cDU] == 0)
                    zeroesInfo[rRL][cDU].bottom = zeroesInfo[rRL + 1][cDU].bottom + 1;
            }
        }
    }

    for (int r{0}; r < N - 1; r++)
    {
        for (int c{0}; c < N - 1; c++)
        {
            const int maxS = r < c ? r : c;
            for (int s = 1; s <= N- maxS; s++)
            {
                if (zeroesInfo[r][c].right >= s and
                    zeroesInfo[r][c].bottom >= s and
                    zeroesInfo[r + s][c + s].top >= s and
                    zeroesInfo[r + s][c + s].left >= s)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

int main()
{
    squareOfZeroes({{1, 1, 1, 0, 1, 0},
                    {0, 0, 0, 0, 0, 1},
                    {0, 1, 1, 1, 0, 1},
                    {0, 0, 0, 1, 0, 1},
                    {0, 1, 1, 1, 0, 1},
                    {0, 0, 0, 0, 0, 1}});
    return 0;
}
