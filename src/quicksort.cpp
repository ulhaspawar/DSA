#include <vector>
using namespace std;

int partition(vector<int> &array, const int start, const int end)
{
    const int pivot = array[start];
    int l{start + 1}, r{end};
    while (l <= r)
    {
        if (array[l] > pivot and array[r] < pivot)
            swap(array[l], array[r]);

        if (array[l] <= pivot)
            l++;
        if (array[r] >= pivot)
            r--;
    }
    swap(array[start], array[r]);
    return r;
}

void sort(vector<int> &array, const int start, const int end)
{
    if (start >= end)
        return;

    auto pivot = partition(array, start, end);
    sort(array, start, pivot - 1);
    sort(array, pivot + 1, end);
}

vector<int> quickSort(vector<int> array)
{
    sort(array, 0, array.size() - 1);
    return array;
}

int main()
{
    quickSort({1, 3, 2});
}