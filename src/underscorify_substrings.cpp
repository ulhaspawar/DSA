#include <string>
#include <vector>

using namespace std;

string underscorifySubstring(string str, string subStr)
{
    const auto strLen{str.size()}, subStrLen{subStr.size()};
    vector<pair<int, int>> matchDetails;

    for (size_t start{0}; start < strLen - subStrLen + 1; start++)
    {
        auto s = str.substr(start, subStrLen);
        if (s == subStr)
        {
            if (matchDetails.empty() or start > matchDetails.back().second + 1)
                matchDetails.push_back({start, start + subStrLen - 1});
            else
                matchDetails[matchDetails.size() - 1].second = start + subStrLen - 1;
        }
    }

    string result = str;

    for (size_t idx{matchDetails.size() - 1}; idx < matchDetails.size(); idx--)
    {
        const auto underscoreDetail = matchDetails[idx];
        result.insert(underscoreDetail.second + 1, 1, '_');
        result.insert(underscoreDetail.first, 1, '_');
    }

    return result;
}

int main()
{
    underscorifySubstring("testthis is a testtest to see if testestest it works", "test");
}