#include <vector>
using namespace std;

int validStartingCity(vector<int> distances, vector<int> fuel, int mpg)
{
    const int numOfCities = distances.size();
    int candidate = 0;
    int milesAvailable{0};
    for (int cityIdx = 0; cityIdx < numOfCities; cityIdx++)
    {
        const int fuelAvailableAtThisCity = fuel[cityIdx];
        const int distanceToNextCity = distances[cityIdx];
        milesAvailable += fuelAvailableAtThisCity * mpg;

        if (milesAvailable < distanceToNextCity)
        {
            milesAvailable = 0;
            candidate = cityIdx + 1;
            continue;
        }
        milesAvailable -= distanceToNextCity;
    }
    return candidate;
}
