#include <vector>
using namespace std;

int largestRectangleUnderSkyline(vector<int> buildings)
{
    const int bLen = buildings.size();

    int largestArea{0};
    for (int bIdx{0}; bIdx < bLen; bIdx++)
    {
        const int height{buildings[bIdx]};

        int lIdx{bIdx - 1};
        while (lIdx >= 0 and buildings[lIdx] >= height)
            lIdx--;
        lIdx++;

        int rIdx{bIdx + 1};
        while (rIdx < bLen and buildings[rIdx] >= height)
            rIdx++;
        rIdx--;

        const int base = rIdx - lIdx + 1;
        const int currentArea = base * height;

        if (largestArea < currentArea)
            largestArea = currentArea;
    }

    return largestArea;
}

int main()
{
    int largestArea = largestRectangleUnderSkyline({1, 3, 3, 2, 4, 1, 5, 3, 2});
    return 0;
}
