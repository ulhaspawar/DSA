#include <vector>
#include <climits>
#include <math.h>

using namespace std;

int minNumberOfCoinsForChange(int n, vector<int> denoms)
{
    vector<int> coinsCount(n + 1, INT_MAX);
    coinsCount[0] = 0;
    for (int denom : denoms)
    {
        if (denom > n)
            continue;
        for (int amt{denom}; amt <= n; amt++)
        {
            const int restAmt = amt - denom;
            coinsCount[amt] = min(coinsCount[amt], (coinsCount[restAmt] == INT_MAX ? INT_MAX : +coinsCount[restAmt] + 1));
        }
    }

    return coinsCount[n] == INT_MAX ? -1 : coinsCount[n];
}

int main()
{
    minNumberOfCoinsForChange(10, {1, 3, 4});
}