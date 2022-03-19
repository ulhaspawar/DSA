#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

vector<vector<int>> maxSumIncreasingSubsequence(vector<int> array)
{
    const auto LEN{array.size()};
    vector<int> subsequenceSum(array);
    vector<int> prevInSeq(LEN, -1);

    for (size_t idx{0}; idx < LEN; idx++)
    {
        for (size_t prevIdx{idx - 1}; prevIdx < LEN; prevIdx--)
        {
            if (array[prevIdx] < array[idx] and subsequenceSum[idx] < (subsequenceSum[prevIdx] + array[idx]))
            {
                subsequenceSum[idx] = subsequenceSum[prevIdx] + array[idx];
                prevInSeq[idx] = prevIdx;
            }
        }
    }

    int maxSubSequenceSum{subsequenceSum[0]};
    int maxSubSequenceEndsAt{0};
    for (int idx{1}; idx < LEN; idx++)
        if (maxSubSequenceSum < subsequenceSum[idx])
        {
            maxSubSequenceSum = subsequenceSum[idx];
            maxSubSequenceEndsAt = idx;
        }

    vector<int> subsequence;
    while (maxSubSequenceEndsAt != -1)
    {
        subsequence.push_back(array[maxSubSequenceEndsAt]);
        maxSubSequenceEndsAt = prevInSeq[maxSubSequenceEndsAt];
    }

    reverse(begin(subsequence), end(subsequence));

    return {
        {maxSubSequenceSum},
        subsequence};
}
