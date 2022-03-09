#include <vector>

using namespace std;

int binarySearch(vector<int> array, int target)
{
    int match = -1;
    size_t left{0}, right{array.size() - 1};

    while (left <= right)
    {
        size_t mid{(right + left) / 2};
        if (array[mid] == target)
        {
            match = mid;
            break;
        }
        else
        {
            if (array[mid] > target)
                right = mid - 1;
            else
                left = mid + 1;
        }
    }

    return match;
}

int binarySearchRec(const vector<int> array, const int target,
                    const int left, const int right)
{
    if (left > right)
        return -1;

    int mid = (left + right) / 2;
    if (array[mid] == target)
        return mid;
    else if (array[mid] > target)
        return binarySearchRec(array, target, left, right - 1);
    else
        return binarySearchRec(array, target, left + 1, right);
}