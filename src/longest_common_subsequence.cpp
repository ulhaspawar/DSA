#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

vector<char> findLCS(const string str1, const int str1Start, const string str2, const int str2Start,
                     unordered_map<string, vector<char>> &cache)
{
    const string cacheKey = to_string(str1Start) + to_string(str2Start);
    if (cache.count(cacheKey) == 1)
        return cache[cacheKey];

    vector<char> subsequence;

    for (int sIdx1 = str1Start; sIdx1 < str1.size(); sIdx1++)
    {
        vector<char> runningLCS;
        const char seqStartCh = str1[sIdx1];
        int sIdx2 = str2Start;
        while (sIdx2 < str2.size() and str2[sIdx2] != seqStartCh)
            sIdx2++;

        if (sIdx2 == str2.size())
            continue;

        runningLCS.push_back(seqStartCh);

        if (sIdx1 < str1.size() - 1 and sIdx2 < str2.size() - 1)
        {
            const auto restSubsequence = findLCS(str1, sIdx1 + 1, str2, sIdx2 + 1, cache);

            for (const auto c : restSubsequence)
                runningLCS.push_back(c);
        }

        if (subsequence.size() < runningLCS.size())
            subsequence = runningLCS;
    }

    cache[cacheKey] = subsequence;
    return subsequence;
}

vector<char> longestCommonSubsequence(string str1, string str2)
{
    unordered_map<string, vector<char>> cache;
    return findLCS(str1, 0, str2, 0, cache);
}
