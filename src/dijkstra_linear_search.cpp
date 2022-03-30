#include <vector>
#include <limits>

using namespace std;

constexpr int INFINITY = numeric_limits<int>::max();

struct vertext_detail
{
    int idx;
    bool visited{false};
    int pathLength{INFINITY};
};

int findNearestUnvisited(const vector<vertext_detail> &vd)
{
    int match = -1;

    int leastPath = INFINITY;
    for (int idx = 0; idx < vd.size(); idx++)
        if (!vd[idx].visited and vd[idx].pathLength < INFINITY)
        {
            leastPath = vd[idx].pathLength;
            match = idx;
        }

    return match;
}

vector<int> dijkstrasAlgorithm(int start, vector<vector<vector<int>>> edges)
{
    const int VERTEX_COUNT = edges.size();
    vector<int> shortestPathLengths(VERTEX_COUNT, -1);
    vector<vertext_detail> vertexDet(VERTEX_COUNT);

    for (int idx = 0; idx < VERTEX_COUNT; idx++)
        vertexDet[idx].idx = idx;

    vertexDet[start].pathLength = 0;

    int vIdx;
    while ((vIdx = findNearestUnvisited(vertexDet)) != -1)
    {
        auto vd = vertexDet[vIdx];
        const auto currentPathLength = vd.pathLength;
        const auto neighbours = edges[vIdx];

        for (const auto edgeToNeighbour : neighbours)
        {
            const int nIdx = edgeToNeighbour[0];
            const int weight = edgeToNeighbour[1];

            const int pathLength = vertexDet[nIdx].pathLength;

            if (!vertexDet[nIdx].visited)
                if (pathLength > currentPathLength + weight)
                    vertexDet[nIdx].pathLength = currentPathLength + weight;
        }

        vertexDet[vIdx].visited = true;
        shortestPathLengths[vIdx] = currentPathLength;
    }

    return shortestPathLengths;
}

int main()
{
    auto len = dijkstrasAlgorithm(0, {{{1, 7}},
                                      {{2, 6}, {3, 20}, {4, 3}},
                                      {{3, 14}},
                                      {{4, 2}},
                                      {},
                                      {}});

    return 0;
}