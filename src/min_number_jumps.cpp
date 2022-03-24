#include <vector>
using namespace std;

int minNumberOfJumps(vector<int> array)
{
    if (array.size() < 2)
        return 0;

    int numOfJumps = 0;
    int range = array[0];
    int idx{1};
    int stepCount = array[0];
    while (range < array.size() - 1)
    {
        if (idx + array[idx] > range)
        {
            range = idx + array[idx];

            if (range >= array.size() - 1)
            {
                numOfJumps++;
                break;
            }
        }

        stepCount--;

        if (stepCount == 0)
        {
            numOfJumps++;
            stepCount = range - idx;
        }
        idx++;
    }

    return numOfJumps + 1;
}
