#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<string>> groupAnagrams(vector<string> words)
{
    unordered_map<string, vector<string>> sortedToOrigMap;

    for (auto s : words)
    {
        auto origS = s;
        sort(begin(s), end(s));
        if (sortedToOrigMap.count(s) == 0)
            sortedToOrigMap.insert({s, {}});
        sortedToOrigMap[s].push_back(origS);
    }

    vector<vector<string>> anagramGroups;
    for (const auto p : sortedToOrigMap)
        anagramGroups.push_back(p.second);

    return anagramGroups;
}
