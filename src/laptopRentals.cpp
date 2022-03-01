#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int laptopRentals(vector<vector<int>> times)
{
    vector<int> startTimes;
    transform(times.cbegin(), times.cend(), back_inserter(startTimes), [](auto t)
              { return t[0]; });
    sort(startTimes.begin(), startTimes.end());

    vector<int> endTimes;
    transform(times.cbegin(), times.cend(), back_inserter(endTimes), [](auto t)
              { return t[1]; });
    sort(endTimes.begin(), endTimes.end());

    auto laptopsNeeded{0};
    size_t startIdx{0}, endIdx{0};

    while (startIdx < startTimes.size())
    {
        if (startTimes[startIdx] >= endTimes[endIdx])
        {
            laptopsNeeded--;
            endIdx++;
        }
        laptopsNeeded++;
        startIdx++;
    }

    return laptopsNeeded;
}

int main()
{
    cout << "\n\n\nLaptop Rentals:" << laptopRentals({{0, 2}, {1, 4}, {4, 6}, {0, 4}, {7, 8}, {9, 11}, {3, 10}});
    return 0;
}