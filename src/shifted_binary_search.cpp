#include <vector>

using namespace std;

int shiftedBinarySearch(vector<int> array, int target)
{
    int leftIdx{0}, rightIdx = array.size() - 1;
    int matchIdx = -1;

    while (leftIdx <= rightIdx)
    {
        const int midIdx = (leftIdx + rightIdx) / 2;
        const int mid = array[midIdx];
        if (target == mid)
        {
            matchIdx = midIdx;
            break;
        }
        const int left = array[leftIdx];
        const int right = array[rightIdx];

        if (left <= mid)
        {
            // Left halve is regular sorted
            if (target < mid and target >= left)
                rightIdx = midIdx - 1;
            else
                leftIdx = midIdx + 1;
        }
        else
        {
            // Right halve is regular sorted
            if (target > mid and target <= right)
                leftIdx = midIdx + 1;
            else
                rightIdx = midIdx - 1;
        }
    }

    return matchIdx;
}

int main()
{
    const auto result = shiftedBinarySearch({45,61,71,72,73,0,1,21,33,37})
}