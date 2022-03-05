#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

size_t previous(const size_t loc, const vector<int> &array, const vector<size_t> &length)
{
    const auto currentNum = array[loc];

    size_t candidateIndex = UINT_MAX;
    int candidateLength = 0;

    for (size_t idx = loc - 1; idx < array.size(); idx--)
    {
        if (array[idx] < currentNum && length[idx] > candidateLength)
        {
            candidateLength = length[idx];
            candidateIndex = idx;
        }
    }

    return candidateIndex;
}

vector<int> longestIncreasingSubsequence(vector<int> array)
{
    const int N = array.size();

    if (N <= 1)
        return array;

    vector<size_t> length(N, 1);
    vector<size_t> sequence(N, UINT_MAX);

    length[0] = 1;

    for (size_t idx{1}; idx < N; idx++)
    {
        auto prev = previous(idx, array, length);
        if (prev != UINT_MAX)
        {
            sequence[idx] = prev;
            length[idx] = length[prev] + 1;
        }
    }

    vector<int> result;

    auto maxLenIdx{N - 1};
    auto maxLen{length[N - 1]};
    for (size_t idx = N - 2; idx < N; idx--)
        if (length[idx] > maxLen)
        {
            maxLen = length[idx];
            maxLenIdx = idx;
        }

    size_t idx = maxLenIdx;
    while (idx != UINT_MAX)
    {
        result.push_back(array[idx]);
        idx = sequence[idx];
    }

    return (reverse(begin(result), end(result)), result);
}

int main()
{
    longestIncreasingSubsequence({5, 7, -24, 12, 10, 2, 3, 12, 5, 6, 35});
}