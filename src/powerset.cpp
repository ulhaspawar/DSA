#include <vector>
using namespace std;

vector<vector<int>> powerset(vector<int> array)
{
    vector<vector<int>> powersets{{}};

    for(const auto n : array) {
        for(int idx {0}, size = powersets.size(); idx < size; idx++) {
            auto s = powersets[idx];
            s.push_back(n);
            powersets.push_back(s);
        }
    }

    return powersets;
}
