#include <vector>
#include <iostream>
using namespace std;

pair<int, vector<int>> merge(vector<int> left, vector<int> right)
{
    vector<int> mergeResult(left.size() + right.size());
    int inversions{0};

    int idx1{0}, idx2{0}, mIdx{0};

    while (idx1 < left.size() and idx2 < right.size())
    {
        if (left[idx1] <= right[idx2])
            mergeResult[mIdx++] = left[idx1++];
        else
        {
            inversions += (left.size() - idx1);
            mergeResult[mIdx++] = right[idx2++];
        }
    }

    while (idx1 < left.size())
    {
        mergeResult[mIdx++] = left[idx1++];
    }

    while (idx2 < right.size())
        mergeResult[mIdx++] = right[idx2++];

    return {inversions, mergeResult};
}

pair<int, vector<int>> countInversionsWithMergeSort(vector<int> array)
{
    if (array.size() < 2)
        return {0, array};

    int mid = (array.size() - 1) / 2;
    vector<int> left(begin(array), begin(array) + mid + 1);
    vector<int> right(begin(array) + mid + 1, end(array));

    auto leftArrDetails = countInversionsWithMergeSort(left);
    auto rightArrDetails = countInversionsWithMergeSort(right);

    auto merged = merge(leftArrDetails.second, rightArrDetails.second);

    return {leftArrDetails.first + rightArrDetails.first + merged.first,
            merged.second};
}

int countInversions(vector<int> array)
{
    return countInversionsWithMergeSort(array).first;
}

int main()
{
    cout << "Test:" << countInversions({2, 2, 2, 2, 1, 1, 1, 1, 3, 3, 3, 3});
    return 0;
}