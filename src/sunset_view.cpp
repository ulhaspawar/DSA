#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> sunsetViews(vector<int> buildings, string direction)
{
    if (buildings.size() == 0)
        return {};

    vector<int> buildingsWithView;

    // Normalize - always consider L2R
    if (direction == "EAST")
        reverse(buildings.begin(), buildings.end());

    buildingsWithView.push_back(0);
    auto currentMax{buildings[0]};
    for (size_t idx = 1, numOfBuildings{buildings.size()}; idx < numOfBuildings; idx++)
    {
        if (currentMax < buildings[idx])
        {
            currentMax = buildings[idx];
            buildingsWithView.push_back(int(idx));
        }
    }

    if (direction == "EAST")
    {
        reverse(buildingsWithView.begin(), buildingsWithView.end());
        auto size = buildings.size() - 1;
        transform(buildingsWithView.begin(), buildingsWithView.end(), buildingsWithView.begin(), [size](auto n)
                  { return size - n; });
    }

    return buildingsWithView;
}

vector<int> sunsetViews_1(vector<int> buildings, string direction)
{
    vector<int> buildingsWithSunsetView;

    size_t idx;
    int step;
    if (direction == "EAST")
    {
        idx = buildings.size() - 1;
        step = -1;
    }
    else
    {
        idx = 0;
        step = 1;
    }

    int currentMax = 0;
    while(idx < buildings.size()) {
        if(currentMax < buildings[idx]) {
            currentMax = buildings[idx];
            buildingsWithSunsetView.push_back(idx);
        }
        idx += step;
    }

    if(direction == "EAST") {
        reverse(buildingsWithSunsetView.begin(), buildingsWithSunsetView.end());
    }

    return buildingsWithSunsetView;
}

int main()
{
    vector<int> buildings = {3, 5, 4, 4, 3, 1, 3, 2};
    string direction = "EAST";
    vector<int> expected = {1, 3, 6, 7};
    vector<int> actual = sunsetViews(buildings, direction);
    cout << (expected == actual);
}