#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<vector<int>> computeMaxProfit(const int rodLength, const vector<int> profitPerLength)
{
    vector<vector<int>> profits(profitPerLength.size() + 1);

    for (int i{0}; i < profitPerLength.size() + 1; i++)
        for (int j{0}; j < rodLength + 1; j++)
            profits[i].push_back(0);

    for (int p{1}; p <= profitPerLength.size(); p++)
    {
        for (int l{1}; l <= rodLength; l++)
        {
            if (p > l)
            {
                profits[p][l] = profits[p - 1][l];
            }
            else
            {
                int noOfRodPieces = l / p;
                int remainingLength = l % p;

                int profitWithLength = noOfRodPieces * profitPerLength[p - 1] + profits[p][remainingLength];
                int profitWithoutCurrentPiece = profits[p - 1][l];

                profits[p][l] = max(profitWithLength, profitWithoutCurrentPiece);
            }
        }
    }

    return profits;
}

int main()
{
    cout << "\n\n\nMaximizing Profit - Rod Cutting\n\n\n";

    auto profits = computeMaxProfit(5, {2, 5, 7, 8});
    cout << "Profit calculation\n";
    for (int p{0}; p < profits.size(); p++)
    {
        cout << p << "=>";
        for (int l{0}; l < profits[p].size(); l++)
        {
            cout << profits[p][l] << "\t";
        }
        cout << "\n";
    }

    cout << endl;
    return 0;
}