#include <vector>

using namespace std;

int main()
{
    vector<int> nums{3, 4, 6, 2, 1, 8, 9};

    bool less = true;

    for (int idx = 1; idx < nums.size(); idx++)
    {
        if (less)
        {
            if (nums[idx - 1] > nums[idx])
                swap(nums[idx - 1], nums[idx]);
        }
        else if (nums[idx - 1] < nums[idx])
            swap(nums[idx - 1], nums[idx]);

        less = !less;
    }

    return 0;
}