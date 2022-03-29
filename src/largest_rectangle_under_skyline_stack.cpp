#include <vector>
#include <stack>

using namespace std;

int largestRectangleUnderSkyline(vector<int> buildings)
{
    if (buildings.empty())
        return 0;

    stack<int> rectToExpand;
    int largestArea{buildings[0]};
    rectToExpand.push(0);
    int idx{1};

    while (!rectToExpand.empty())
    {
        const int nextBuildingHeight = idx < buildings.size() ? buildings[idx] : 0;

        const int rectIdx = rectToExpand.top();
        const int rectHeight = buildings[rectIdx];

        if (rectHeight > nextBuildingHeight)
        {
            const int right = idx - 1;
            while (!rectToExpand.empty() and buildings[rectToExpand.top()] > nextBuildingHeight)
            {
                const int height = buildings[rectToExpand.top()];
                rectToExpand.pop();
                const int left = rectToExpand.empty() ? 0 : rectToExpand.top() + 1;
                const int width = right - left + 1;
                const int area = height * width;
                if (area > largestArea)
                    largestArea = area;
            }
        }

        if (nextBuildingHeight != 0)
        {
            rectToExpand.push(idx);
            idx++;
        }
    }

    return largestArea;
}

int main()
{
    largestRectangleUnderSkyline({1, 3, 3, 2, 4, 1, 5, 3, 2});
    return 0;
}
