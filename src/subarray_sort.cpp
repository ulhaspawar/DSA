#include <vector>
#include <math.h>
#include <climits>

using namespace std;

vector<int> subarraySort(vector<int> array)
{
    const auto size{array.size()};
    int minOutOfOrder{INT_MAX}, maxOutOfOrder{INT_MIN};
    size_t idx;
    for (idx = 1; idx < size; idx++)
    {
        if (array[idx] < array[idx - 1])
        {
            minOutOfOrder = min(minOutOfOrder, array[idx]);
            maxOutOfOrder = max(maxOutOfOrder, array[idx - 1]);
        }
    }

    if (minOutOfOrder == INT_MAX)
        return {-1, -1};

    idx = 0;
    while (idx < size && array[idx++] <= minOutOfOrder)
        ;
    auto minIdx{idx - 1};

    idx = size - 1;
    while (idx < size && array[idx--] >= maxOutOfOrder)
        ;
    auto maxIdx{idx + 1};

    return {int(minIdx), int(maxIdx)};
}
