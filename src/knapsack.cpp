#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> buildKnapsackEntries(const vector<vector<int>> &items, const int capacity)
{
    const int itemsCount = items.size();
    vector<vector<int>> calc(capacity + 1, vector(itemsCount + 1, 0));

    for (int currentCapacity{1}; currentCapacity <= capacity; currentCapacity++)
    {
        for (int itemIdx{1}; itemIdx <= itemsCount; itemIdx++)
        {
            const auto item = items[itemIdx - 1];
            const auto value = item[0];
            const auto weight = item[1];

            if (weight > currentCapacity)
            {
                calc[currentCapacity][itemIdx] = calc[currentCapacity][itemIdx - 1];
            }
            else
            {
                int remainingWeight = currentCapacity - weight;
                int runningValue = value;
                if (remainingWeight > 0)
                    runningValue += calc[remainingWeight][itemIdx - 1];

                calc[currentCapacity][itemIdx] = max(runningValue, calc[currentCapacity][itemIdx - 1]);
            }
        }
    }

    return calc;
}

vector<int> getItems(const vector<vector<int>> &calc, const int capacity, const vector<vector<int>> &items)
{
    const int itemsCount = items.size();
    vector<int> itemsIndices;

    int currentCapacity = capacity;
    int currentItemIdx = calc[0].size() - 1;
    while(calc[currentCapacity][itemsCount] != 0)
    {
        while(calc[currentCapacity][currentItemIdx] == calc[currentCapacity][currentItemIdx - 1]) currentItemIdx--;
        itemsIndices.push_back(currentItemIdx - 1);
        currentCapacity = currentCapacity - items[currentItemIdx - 1][1];
        currentItemIdx--;
    }

    reverse(begin(itemsIndices), end(itemsIndices));
    return itemsIndices;
}

vector<vector<int>> knapsackProblem(vector<vector<int>> items, int capacity)
{
    const int itemsCount = items.size();
    const auto calc = buildKnapsackEntries(items, capacity);
    const int totalValue = calc[capacity][itemsCount];
    return {
        {totalValue}, // total value
        getItems(calc, capacity, items)       // item indices
    };
}

int main()
{
    knapsackProblem({{1, 2}, {4, 3}, {5, 6}, {6, 7}}, 10);
    return 0;
}
