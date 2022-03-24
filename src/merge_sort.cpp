#include <vector>

using namespace std;

class array_view
{
public:
    vector<int> &array;
    int start, length;

    array_view(vector<int> &a) : array(a), start(0), length(a.size()) {}
    array_view(vector<int> &a, int s, int l) : array(a), start(s), length(l) {}
};

vector<int> merge(const array_view &array1, const array_view &array2)
{
    int idx1{array1.start}, idx2{array2.start};
    const int idx1End{idx1 + array1.length}, idx2End{idx2 + array2.length};

    vector<int> merged(array1.length + array2.length);
    int mIdx{0};

    while (idx1 < idx1End and idx2 < idx2End)
        if (array1.array[idx1] < array2.array[idx2])
            merged[mIdx++] = array1.array[idx1++];
        else
            merged[mIdx++] = array2.array[idx2++];

    while (idx2 < idx2End)
        merged[mIdx++] = array2.array[idx2++];

    while (idx1 < idx1End)
        merged[mIdx++] = array1.array[idx1++];

    return merged;
}

void mergeSort(array_view &array)
{
    if (array.length == 1)
        return;

    int mid = array.length / 2;
    array_view left(array.array, array.start, mid);
    array_view right(array.array, array.start + mid, array.length - mid);
    mergeSort(left);
    mergeSort(right);
    auto sorted = merge(left, right);

    int idx{array.start};
    for (const auto n : sorted)
        array.array[idx++] = n;
}

vector<int> mergeSort(vector<int> array)
{
    array_view arrView(array);
    mergeSort(arrView);
    return arrView.array;
}

int main()
{
    mergeSort({8, 5, 2, 9, 5, 6, 3});
    return 0;
}
