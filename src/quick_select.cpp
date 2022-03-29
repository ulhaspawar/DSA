#include <vector>

using namespace std;

int partition(vector<int> &array, const int start, const int end)
{
    const int pivot{array[start]};
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

int quickselect(vector<int> &array, const int k, const int start, const int end)
{
    int l{start}, r{end};
    while (l <= r)
    {
        const int pivotIndex = partition(array, l, r);
        const int pivot = array[pivotIndex];
        if (pivotIndex == k - 1)
            return pivot;

        if (pivotIndex < k - 1)
            l = pivotIndex + 1;
        else
            r = pivotIndex - 1;
    }
    return -1;
}

int quickselect(vector<int> array, int k)
{
    int n = quickselect(array, k, 0, array.size() - 1);
    return n;
}

int main()
{
    quickselect({43, 24, 37}, 1);
    return 0;
}
