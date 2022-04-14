#include <vector>
#include <stack>
#include <limits>
#include <algorithm>

using namespace std;

bool isBridgeFound(const int vertex, const int parent, const int time, vector<int> &discoveryTime, const vector<vector<int>> &edges);
bool areAllNodesVisited(const vector<int> &discoveryTime);

bool twoEdgeConnectedGraph(vector<vector<int>> edges)
{
    if(edges.size() == 0) return true;
    vector<int> discoveryTime(edges.size(), -1);
    discoveryTime[0] = 0;
    return !isBridgeFound(0, -1, 1, discoveryTime, edges) and areAllNodesVisited(discoveryTime);
}

bool isBridgeFound(const int vertex, const int parent, const int time, vector<int> &discoveryTime, const vector<vector<int>> &edges)
{
    for (int idx = 0; idx < edges[vertex].size(); idx++)
    {
        const int neighbour = edges[vertex][idx];
        if (discoveryTime[neighbour] == -1)
        {
            discoveryTime[neighbour] = time;
            if (isBridgeFound(neighbour, vertex, time + 1, discoveryTime, edges))
            {
                return true;
            }
        }
    }

    if (parent != -1)
    {
        int leastDistance = numeric_limits<int>::max();
        const int parentDiscoveryTime = discoveryTime[parent];
        for (int idx = 0; idx < edges[vertex].size(); idx++)
        {
            const int neighbour = edges[vertex][idx];
            if (neighbour != parent)
            {
                if (leastDistance > discoveryTime[neighbour])
                {
                    leastDistance = discoveryTime[neighbour];
                }
            }
        }
        if (parentDiscoveryTime < leastDistance)
            return true;
        discoveryTime[vertex] = leastDistance;
    }
    return false;
}

bool areAllNodesVisited(const vector<int> &discoveryTime)
{
    return all_of(cbegin(discoveryTime), cend(discoveryTime), [](const int n)
                  { return n != -1; });
}

int main()
{
    auto result = twoEdgeConnectedGraph({{1},
                                         {0}});
    return 0;
}
