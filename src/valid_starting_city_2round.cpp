#include <vector>
using namespace std;

int getCitiesTravelled(const int fromCity, const vector<int> &distances, const vector<int> &fuel, const int mpg)
{
    auto citiesTravelled{0};
    const int numOfCities = distances.size();
    int mileageAvailable{0};
    for (int idx{0}; idx < numOfCities; idx++)
    {
        const int cityIdx = (fromCity + idx) % numOfCities;
        const int distanceToNextCity = distances[cityIdx];
        mileageAvailable += fuel[cityIdx] * mpg;

        if (distanceToNextCity > mileageAvailable)
            break;

        citiesTravelled++;
        mileageAvailable -= distanceToNextCity;
    }

    return citiesTravelled;
}

int validStartingCity(vector<int> distances, vector<int> fuel, int mpg)
{
    const int numOfCities = distances.size();
    int candidateCityIdx{0};
    int validStartingCity = -1;
    while (true)
    {
        const auto citiesTravelled = getCitiesTravelled(candidateCityIdx, distances, fuel, mpg);
        if (citiesTravelled == numOfCities)
        {
            validStartingCity = candidateCityIdx;
            break;
        }
        candidateCityIdx = (candidateCityIdx + citiesTravelled + 1) % numOfCities;
    }
    return validStartingCity;
}
