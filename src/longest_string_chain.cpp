#include <algorithm>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

unordered_map<string, pair<string, int>> initMap(const vector<string> &strs);
vector<string> getStringChain(const unordered_map<string, pair<string, int>> &map);
string findLongestChainStart(const unordered_map<string, pair<string, int>> &map);
void findStringChain(const string s, unordered_map<string, pair<string, int>> &map);

vector<string> longestStringChain(vector<string> strings)
{
    auto map{initMap(strings)};
    sort(begin(strings), end(strings), [](string s1, string s2)
         { return s1.size() < s2.size(); });

    for (const auto &s : strings)
        findStringChain(s, map);

    return getStringChain(map);
}

unordered_map<string, pair<string, int>> initMap(const vector<string> &strs)
{
    unordered_map<string, pair<string, int>> map;
    for (auto &s : strs)
        map.insert({s, {"", 1}});

    return map;
}

vector<string> getStringChain(const unordered_map<string, pair<string, int>> &map)
{
    const auto longestChainStartsAt{findLongestChainStart(map)};
    if (longestChainStartsAt.empty())
        return {};

    vector<string> chain;
    string link{longestChainStartsAt};
    while (link != "")
    {
        chain.push_back(link);
        link = (*map.find(link)).second.first;
    }

    return chain;
}

string findLongestChainStart(const unordered_map<string, pair<string, int>> &map)
{
    string longestChainStartsAt;
    int longestChainLength{1};
    for (const auto link : map)
    {
        if (longestChainLength < link.second.second)
        {
            longestChainLength = link.second.second;
            longestChainStartsAt = link.first;
        }
    }
    return longestChainStartsAt;
}

void findStringChain(const string s, unordered_map<string, pair<string, int>> &map)
{
    const auto sLen{s.size()};
    for (size_t idx{0}; idx < sLen; idx++)
    {
        string nextInChain(s);
        nextInChain.erase(idx, 1);
        if (map.count(nextInChain) == 1)
            if (map[nextInChain].second >= map[s].second)
                map[s] = {nextInChain, map[nextInChain].second + 1};
    }
}

int main()
{
    const auto chain = longestStringChain({"abde", "abc", "abd", "abcde", "ade", "ae", "1abde", "abcdef"});
    return 0;
}
