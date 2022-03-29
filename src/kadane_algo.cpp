#include <vector>
#include <math.h>

using namespace std;

int kadanesAlgorithm(vector<int> array)
{
    int maxSoFar{array[0]};
    int maxEndingHere{array[0]};

    for (int i{1}; i < array.size(); i++)
    {
        const auto num{array[i]};
        maxEndingHere = max(num, maxEndingHere + num);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }

    return maxSoFar;
}
