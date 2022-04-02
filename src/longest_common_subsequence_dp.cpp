#include <math.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const vector<vector<int>> buildLCSMatrix(const string str1, const string str2)
{
    const auto s1Len{str1.size()}, s2Len{str2.size()};
    vector<vector<int>> lcs(s1Len + 1, vector<int>(s2Len + 1, 0));

    for (auto s1Idx{1}; s1Idx <= s1Len; s1Idx++)
        for (auto s2Idx{1}; s2Idx <= s2Len; s2Idx++)
        {
            lcs[s1Idx][s2Idx] = max(lcs[s1Idx][s2Idx - 1], lcs[s1Idx - 1][s2Idx]);
            if (str1[s1Idx - 1] == str2[s2Idx - 1])
            {
                const int lcsWithThisChar = lcs[s1Idx - 1][s2Idx - 1] + 1;
                lcs[s1Idx][s2Idx] = max(lcs[s1Idx][s2Idx], lcsWithThisChar);
            }
        }

    return lcs;
}

vector<char> buildSubsequence(const string str2, const vector<vector<int>> lcs)
{
    const int str1Len = lcs.size() - 1;
    const int str2Len = lcs[0].size() - 1;
    const int lcsLen = lcs[str1Len][str2Len];
    vector<char> seq;

    int r = str1Len, c = str2Len;

    while (lcs[r][c] != 0)
    {
        if (lcs[r][c] == lcs[r - 1][c])
            r--;
        else if (lcs[r][c] == lcs[r][c - 1])
            c--;
        else if (lcs[r][c] != lcs[r - 1][c - 1])
        {
            seq.push_back(str2[c - 1]);
            r--;
            c--;
        }
    }

    reverse(begin(seq), end(seq));
    return seq;
}

vector<char> longestCommonSubsequence(string str1, string str2)
{
    auto lcs = buildLCSMatrix(str1, str2);
    return buildSubsequence(str2, lcs);
}

int main()
{
    auto result = longestCommonSubsequence("clement", "antoine");
    return 0;
}