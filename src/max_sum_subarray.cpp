#include <vector>
#include <limits>
using namespace std;

int kadanesAlgorithm(vector<int> array)
{
    int maxSum{numeric_limits<int>::min()};

    for (int i = 0; i < array.size(); i++)
    {
        int sum{0};
        for (int j{i}; j < array.size(); j++)
        {
            sum += array[j];
            if (maxSum < sum)
                maxSum = sum;
        }
    }

    return maxSum;
}
