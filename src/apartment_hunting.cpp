#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

vector<int> getDistanceToNearest(const vector<bool> &blocks)
{
    const auto bLen{blocks.size()};
    const int INFINITY = bLen + 1;
    vector<int> dist(bLen, INFINITY);

    for (size_t idx{0}; idx < bLen; idx++)
        if (blocks[idx])
            dist[idx] = 0;
        else if (idx > 0 and dist[idx - 1] < INFINITY)
            dist[idx] = dist[idx - 1] + 1;

    for (size_t idx{bLen - 2}; idx < bLen; idx--)
        if (!blocks[idx])
        {
            if (dist[idx + 1] < INFINITY)
                dist[idx] = min(dist[idx], dist[idx + 1] + 1);
        }

    return dist;
}

unordered_map<string, vector<int>> getDistanceToNearest(const vector<unordered_map<string, bool>> &blocks,
                                                        const vector<string> &reqs)
{
    const auto bLen{blocks.size()};
    unordered_map<string, vector<int>> distances;
    unordered_map<string, vector<bool>> features;

    for (const auto &req : reqs)
        features.insert({req, vector(bLen, false)});

    for (size_t idx{0}; idx < bLen; idx++)
    {
        const auto b = blocks[idx];
        for (const auto f : b)
            if (features.count(f.first) == 1 and f.second)
                features[f.first][idx] = f.second;
    }

    for (const auto f : features)
        distances.insert({f.first, getDistanceToNearest(f.second)});

    return distances;
}

int apartmentHunting(vector<unordered_map<string, bool>> blocks,
                     vector<string> reqs)
{
    const auto bLen{blocks.size()};
    const auto distances = getDistanceToNearest(blocks, reqs);
    vector<int> maxDist(bLen, -1);

    for (const auto d : distances)
        for (size_t idx{0}; idx < bLen; idx++)
            maxDist[idx] = max(d.second[idx], maxDist[idx]);

    int minIdx{0}, min{maxDist[0]};

    for (size_t idx{1}; idx < bLen; idx++)
        if (maxDist[idx] < min)
        {
            min = maxDist[idx];
            minIdx = idx;
        }

    return minIdx;
}

int main()
{
    auto res = apartmentHunting({{{"gym", false},
                                  {"school", true},
                                  {"store", false}},
                                 {{"gym", true},
                                  {"school", false},
                                  {"store", false}},
                                 {{"gym", true},
                                  {"school", true},
                                  {"store", false}},
                                 {{"gym", false},
                                  {"school", true},
                                  {"store", false}},
                                 {{"gym", false},
                                  {"school", true},
                                  {"store", true}}},
                                {"gym", "school", "store"});
    return 0;
}