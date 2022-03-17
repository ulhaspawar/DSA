#include <vector>
using namespace std;

vector<int> threeNumberSort(vector<int> array, vector<int> order)
{
    if (array.empty())
        return array;
    const int first{order[0]}, second{order[1]}, third{order[2]};

    size_t tIdx{array.size() - 1}, fIdx{0}, sIdx{0};

    while (sIdx <= tIdx and tIdx < array.size())
    {
        if (array[sIdx] == third)
        {
            swap(array[sIdx], array[tIdx]);
            tIdx--;
        }

        if (array[sIdx] == first)
        {
            swap(array[fIdx], array[sIdx]);
            fIdx++;
            sIdx++;
        }

        if (array[sIdx] == second)
            sIdx++;
    }

    return array;
}
