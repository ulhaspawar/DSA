#include <vector>

using namespace std;

vector<int> algo1()
{
    vector<int> nums{-1, 3, 8, -4, 5, -6, 7, -20, 30, 40};
    int l = 0, r = nums.size() - 1;
    while (l <= r)
    {
        if (nums[l] > 0)
            swap(nums[l], nums[r--]);
        if (nums[l] < 0)
            l++;
    }
    return nums;
}

vector<int> algo2()
{
    vector<int> nums{-1, 3, 8, -4, 5, -6, 7, -20, 30, 40};
    int neg = 0, pos = 0;
    for (int idx = 1; idx < nums.size(); idx++)
    {
        if (nums[idx] < 0)
        {
            int temp = nums[idx];
            int i = idx;
            while (nums[i - 1] > 0){
                nums[i] = nums[i-1];
                i--;
            }
            nums[i] = temp;
        }
    }

    return nums;
}

int main()
{
    algo1();
    algo2();
    return 0;
}