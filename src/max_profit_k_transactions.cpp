#include <vector>

using namespace std;

int maxProfitWithKTransactions(vector<int> prices, int k)
{
    if(k == 0 or prices.empty()) return 0;
    
    vector<vector<int>> profits;

    // Insert zero for no transaction
    profits.push_back({});
    for (int idx = 0; idx < prices.size(); idx++)
        profits[0].push_back(0);

    for (int txn = 1; txn <= k; txn++)
    {
        profits.push_back({});

        for (int idx = 0; idx <= ((2 * txn) - 2); idx++)
            profits[txn].push_back(profits[txn - 1][idx]);

        for (int soldOn = (2 * txn) - 1; soldOn < prices.size(); soldOn++)
        {
            auto sellPrice = prices[soldOn];
            auto maxProfit = profits[txn][soldOn - 1];

            for (int boughtOn = soldOn - 1; boughtOn >= 0; boughtOn--)
            {
                auto profit = sellPrice - prices[boughtOn];
                profit += boughtOn > 0 ? profits[txn - 1][boughtOn - 1] : 0;
                if (profit > maxProfit)
                {
                    maxProfit = profit;
                }
            }
            profits[txn].push_back(maxProfit);
        }
    }

    return profits[k][prices.size() - 1];
}

int main()
{
    maxProfitWithKTransactions({5, 11, 3, 50, 60, 90}, 2);
}