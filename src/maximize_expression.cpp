#include<iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int maximizeExpression(vector<int> array)
{
    const auto size{array.size()};

    if (size < 4)
        return 0;

    const auto noOfChoices = size - 3;
    //vector<int> a_max(noOfChoices, 0), a_b_max(noOfChoices, 0), a_b_c_max(noOfChoices, 0), a_b_c_d_max(noOfChoices, 0);
    auto a_max{0}, a_b_max{0}, a_b_c_max{0}, a_b_c_d_max{0};

    a_max = array[0];
    a_b_max = a_max - array[1];
    a_b_c_max = a_b_max + array[2];
    a_b_c_d_max = a_b_c_max - array[3];

    for (auto idx{1}; idx < noOfChoices; idx++)
    {
        const auto a{array[idx]}, b{array[idx + 1]}, c{array[idx + 2]}, d{array[idx + 3]};

        // Compute 'a'
        a_max = max(a, a_max);

        // Compute 'a-b'
        a_b_max = max(a_max - b, a_b_max);

        // Compute 'a-b+c'
        a_b_c_max = max(a_b_max + c, a_b_c_max);

        // Compute 'a-b+c-d'
        a_b_c_d_max = max(a_b_c_max - d, a_b_c_d_max);
    }

    return a_b_c_d_max;
}

int main()
{
    cout<<"Test 1: "<<maximizeExpression({3,6,1,-3,2,7});
}