#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<char> longestCommonSubsequence(string str1, string str2)
{
    vector<char> subsequence;

    int idx2 = str2.size() - 1;

    for (int idx1 = str1.size() - 1; idx1 >= 0; idx1--)
    {
        for(int idx3 = idx2; idx3 >= 0; idx3--) {
            if(str1[idx1] == str2[idx3]){
                subsequence.push_back(str1[idx1]);
                idx2 = idx3 - 1;
                break;
            }
        }
    }

    reverse(begin(subsequence), end(subsequence));
    return subsequence;
}
