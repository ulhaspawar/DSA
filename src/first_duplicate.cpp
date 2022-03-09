#include <vector>
#include <math.h>

using namespace std;

int firstDuplicateValue(vector<int> array)
{
    int duplicate{-1};

    for (size_t idx = 0; idx < array.size(); idx++)
    {
        const auto absVal = abs(array[idx]);
        const auto n = absVal;
        const auto nIdx = n - 1;

        if (array[nIdx] < 0)
        {
            duplicate = absVal;
            break;
        }

        array[nIdx] *= -1;
    }

    return duplicate;
}
