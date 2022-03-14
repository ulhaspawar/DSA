#include <vector>
using namespace std;

void buildMaxHeap(vector<int> &array);
void siftDown(vector<int> &array, size_t current, size_t endIdx);

void buildMaxHeap(vector<int> &array)
{
    size_t lastParent = (array.size() - 2) / 2;

    for (auto idx = lastParent; idx < array.size(); idx--)
    {
        siftDown(array, idx, array.size() - 1);
    }
}

void siftDown(vector<int> &array, size_t current, size_t endIdx)
{
    size_t child = 2 * current + 1;
    while (child <= endIdx)
    {
        size_t rightChild = child < endIdx ? child + 1 : -1;
        size_t maxChild = child;
        if (array[maxChild] < array[rightChild] and rightChild != -1)
            maxChild = rightChild;

        if (array[maxChild] > array[current])
        {
            swap(array[maxChild], array[current]);
            current = maxChild;
            child = 2 * current + 1;
        }
        else
        {
            break;
        }
    }
}

vector<int> heapSort(vector<int> array)
{
    buildMaxHeap(array);
    for (size_t idx{array.size() - 1}; idx >= 1; idx--)
    {
        swap(array[0], array[idx]);
        siftDown(array, 0, idx - 1);
    }

    return array;
}

int main()
{
    heapSort({-823, 164, 48, -987, 323, 399, -293, 183, -908, -376, 14, 980, 965, 842, 422, 829, 59, 724, -415, -733, 356, -855, -155, 52, 328, -544, -371, -160, -942, -51, 700, -363, -353, -359, 238, 892, -730, -575, 892, 490, 490, 995, 572, 888, -935, 919, -191, 646, -120, 125, -817, 341, -575, 372, -874, 243, 610, -36, -685, -337, -13, 295, 800, -950, -949, -257, 631, -542, 201, -796, 157, 950, 540, -846, -265, 746, 355, -578, -441, -254, -941, -738, -469, -167, -420, -126, -410, 59});
    return 0;
}