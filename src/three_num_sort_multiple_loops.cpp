#include <vector>
using namespace std;

vector<int> threeNumberSort(vector<int> array, vector<int> order)
{
    const int first{order[0]}, third{order[2]};
    int fIdx{-1}, tIdx{int(array.size())};

    for (int idx{0}; idx < array.size(); idx++)
        if (array[idx] == first)
            swap(array[++fIdx], array[idx]);

    for (int idx{int(array.size()) - 1}; idx > fIdx; idx--)
        if (array[idx] == third)
            swap(array[--tIdx], array[idx]);

    return array;
}
