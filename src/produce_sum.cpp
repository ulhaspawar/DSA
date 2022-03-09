#include <any>
#include <vector>
#include <stack>
#include <tuple>

using namespace std;

// Tip: You can use el.type() == typeid(vector<any>) to check whether an item is
// a list or an integer.
// If you know an element of the array is vector<any> you can cast it using:
//     any_cast<vector<any>>(element)
// If you know an element of the array is an int you can cast it using:
//     any_cast<int>(element)

int productSum(const vector<any> array, const int depth) noexcept
{
    int prodSum{0};
    for (const auto n : array)
    {
        if (n.type() == typeid(vector<any>))
        {
            prodSum += productSum(any_cast<vector<any>>(n), depth + 1);
        }
        else
        {
            prodSum += any_cast<int>(n);
        }
    }

    return prodSum * depth;
}

int productSum(vector<any> array)
{
    return productSum(array, 1);
}

int productSumIterative(const vector<any> array)
{
    int prodSum{0};
    stack<tuple<const vector<any>, const int, const int>> arraysToProcess;

    arraysToProcess.push({array, 1, 1});

    while (!arraysToProcess.empty())
    {
        const auto top = move(arraysToProcess.top());
        arraysToProcess.pop();

        const auto vec = get<0>(top);
        const auto level = get<1>(top);
        const auto prevMult = get<2>(top);

        int sum{0};
        for (const auto &num : vec)
        {
            if (num.type() == typeid(vector<any>))
                arraysToProcess.push({any_cast<vector<any>>(num), level + 1, prevMult * level});
            else
                sum += any_cast<int>(num);
        }
        sum *= level;
        sum *= prevMult;

        prodSum += sum;
    }

    return prodSum;
}
