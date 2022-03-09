#include <vector>

using namespace std;

vector<int> insertionSort(vector<int> array)
{

    for (auto i{1}; i < array.size(); i++)
    {
        auto num{array[i]};
        auto j{i - 1};
        auto ins{false};
        while (j >= 0 && array[j] > num)
        {
            array[j + 1] = array[j];
            ins = true;
            j--;
        }
        if (ins)
            array[j + 1] = num;
    }

    return array;
}

int main()
{
    insertionSort({8, 5, 2, 9, 5, 6, 3});
    return 0;
}
