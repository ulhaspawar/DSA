#include <vector>
using namespace std;

vector<int> bubbleSort(vector<int> array)
{
    for (auto size{array.size()}, i{size - 1}; i < size; i--)
    {
        bool swapHappened = false;
        for (size_t j{1}; j <= i; j++)
        {
            if (array[j] < array[j - 1])
            {
                swap(array[j], array[j - 1]);
                swapHappened = true;
            }
        }
        if (!swapHappened)
            break;
    }

    return array;
}
