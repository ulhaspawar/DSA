#include <vector>
using namespace std;

bool isValidStartingCity(int startingCity, const vector<int> &distances, const vector<int> &fuel, const int mpg);

int validStartingCity(vector<int> distances, vector<int> fuel, int mpg)
{
    const int numOfCities = distances.size();
    int validCity{-1};
    for (int cityIdx = 0; cityIdx < numOfCities; cityIdx++)
        if (isValidStartingCity(cityIdx, distances, fuel, mpg))
        {
            validCity = cityIdx;
            break;
        }

    return validCity;
}

bool isValidStartingCity(int startingCity, const vector<int> &distances, const vector<int> &fuel, const int mpg)
{
    bool isValid{true};
    const int numOfCities = distances.size();
    int fuelcapacity{0};
    for (int idx{0}; idx < numOfCities; idx++)
    {
        const int cityIdx = (startingCity + idx) % numOfCities;
        const int distanceToNext = distances[cityIdx];
        fuelcapacity += fuel[cityIdx] * mpg;
        if (fuelcapacity < distanceToNext)
        {
            isValid = false;
            break;
        }
        fuelcapacity -= distanceToNext;
    }
    return isValid;
}
