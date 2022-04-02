#include <vector>
#include <string>
#include <math.h>

using namespace std;

vector<vector<bool>> buildPalindromicityMatrix(const string str)
{
    const int sLen = str.size();
    vector<vector<bool>> palindromicity(sLen, vector<bool>(sLen));

    for (int i = 0; i < sLen; i++)
        palindromicity[i][i] = true;

    for (int len = 2; len <= sLen; len++)
        for (int start = 0; start < sLen - len + 1; start++)
        {
            const int end = start + len - 1;
            if (len == 2)
                palindromicity[start][end] = str[start] == str[end];
            else
                palindromicity[start][end] = str[start] == str[end] and palindromicity[start + 1][end - 1];
        }
    return palindromicity;
}

int palindromePartitioningMinCuts(string str)
{
    const int sLen = str.size();
    const auto palindromicity = buildPalindromicityMatrix(str);
    vector<int> minNumOfPalindromes(sLen, 1);

    for (int idx{0}; idx < sLen; idx++)
    {
        if (palindromicity[0][idx])
            minNumOfPalindromes[idx] = 1;
        else
        {
            minNumOfPalindromes[idx] = minNumOfPalindromes[idx - 1] + 1;
            for (int j = 1; j < idx; j++)
                if (palindromicity[j][idx])
                    minNumOfPalindromes[idx] = min(minNumOfPalindromes[idx], minNumOfPalindromes[j - 1] + 1);
        }
    }

    return minNumOfPalindromes[sLen - 1] - 1;
}

int main()
{
    auto result = palindromePartitioningMinCuts("abba");
    return 0;
}
