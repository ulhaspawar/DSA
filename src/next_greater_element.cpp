#include <vector>
#include <stack>

using namespace std;

vector<int> nextGreaterElement(vector<int> array)
{
    vector<int> greaterElements(array.size(), -1);
    const int N = array.size();
    for (int idx{0}; idx < N; idx++)
    {
        for (int idx1{(idx + 1) % N}; idx1 != idx; idx1 = (idx1 + 1) % N)
        {
            if (array[idx1] > array[idx])
            {
                greaterElements[idx] = array[idx1];
                break;
            }
        }
    }

    return greaterElements;
}

vector<int> nextGreaterElement_stack_idx(vector<int> array)
{
    vector<int> nge(array.size(), -1);

    stack<int> unknownNextGreater;

    for (int i = 0; i < 2 * array.size(); i++)
    {
        const auto idx = i % array.size();
        while (!unknownNextGreater.empty() and array[unknownNextGreater.top()] < array[idx])
        {
            nge[unknownNextGreater.top()] = array[idx];
            unknownNextGreater.pop();
        }
        unknownNextGreater.push(idx);
    }

    return nge;
}

vector<int> nextGreaterElement_stack_idx(vector<int> array)
{
    vector<int> nge(array.size(), -1);
    stack<int> nextGreater;

    for (int i = 2 * array.size() - 1; i >= 0; i--)
    {
        const auto idx = i % array.size();
        const auto current = array[idx];

        while (!nextGreater.empty() and current >= nextGreater.top())
            nextGreater.pop();

        if (!nextGreater.empty() and current < nextGreater.top())
        {
            nge[idx] = nextGreater.top();
        }
        nextGreater.push(current);
    }

    return nge;
}
