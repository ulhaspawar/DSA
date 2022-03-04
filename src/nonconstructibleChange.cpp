#include <vector>
#include <algorithm>

using namespace std;

int nonConstructibleChange(vector<int> coins)
{
    sort(begin(coins), end(coins));

    auto changeConstructible{0};

    for (const auto coin : coins)
    {
        if (coin > changeConstructible + 1)
            return changeConstructible + 1;
        changeConstructible += coin;
    }

    return changeConstructible + 1;
}