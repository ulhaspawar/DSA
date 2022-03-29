#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

template <class NODE_TYPE>
class DirectedGraph
{
    int size;
    vector<vector<int>> adjecancyMatrix;
    unordered_map<NODE_TYPE, int> labelToIdxMap;
    unordered_map<int, NODE_TYPE> idxToLabel;

public:
    DirectedGraph(const vector<NODE_TYPE> &vertices, const vector<vector<NODE_TYPE>> &edges);
    vector<NODE_TYPE> dfs(NODE_TYPE start);
};

template <class NODE_TYPE>
DirectedGraph<NODE_TYPE>::DirectedGraph(const vector<NODE_TYPE> &vertices, const vector<vector<NODE_TYPE>> &edges)
{
    int idx{0};
    for (const auto v : vertices)
    {
        const int n = idx++;
        labelToIdxMap.insert({v, n});
        idxToLabel.insert({n, v});
    }

    size = vertices.size();

    for (idx = 0; idx < size; idx++)
        adjecancyMatrix.push_back(vector<int>(size, 0));

    for (const auto e : edges)
        adjecancyMatrix[labelToIdxMap[e[0]]][labelToIdxMap[e[1]]] = 1;
}

template <class NODE_TYPE>
vector<NODE_TYPE> DirectedGraph<NODE_TYPE>::dfs(NODE_TYPE start)
{
    stack<int> unprocessed;
    unprocessed.push(labelToIdxMap[start]);
    vector<NODE_TYPE> dfsTraversal;
    while (!unprocessed.empty())
    {
        const auto vIdx = unprocessed.top();
        unprocessed.pop();
        dfsTraversal.push_back(idxToLabel[vIdx]);
        for (int nIdx{0}; nIdx < size; nIdx++)
            if (adjecancyMatrix[vIdx][nIdx] == 1 and find(cbegin(dfsTraversal), cend(dfsTraversal), idxToLabel[nIdx]) == cend(dfsTraversal))
                unprocessed.push(nIdx);
    }
    return dfsTraversal;
}

using Map = DirectedGraph<string>;

vector<string> getReachableAirports(string startingAirport, const vector<string> airports, Map map)
{
    return map.dfs(startingAirport);
}

vector<string> getUnreachableAirports(const string startingAirport, const vector<string> airports, Map map)
{
    vector<string> unreachableAirports;
    const auto dfs = getReachableAirports(startingAirport, airports, map);
    for (const auto a : airports)
        if (find(cbegin(dfs), cend(dfs), a) == cend(dfs))
            unreachableAirports.push_back(a);
    return unreachableAirports;
}

vector<vector<string>> getReachableAirports(const vector<string> startingAirports, const vector<string> airports, const Map map)
{
    vector<vector<string>> reachables;

    for (const auto sa : startingAirports)
        reachables.push_back(getReachableAirports(sa, airports, map));

    return reachables;
}

vector<vector<string>> removeAirport(vector<vector<string>> &reachables, const string airportToRemove)
{
    vector<vector<string>> remainings;

    for (const auto r : reachables)
        if (find(cbegin(r), cend(r), airportToRemove) == cend(r))
            remainings.push_back(r);    

    return remainings;
}

int airportConnections(vector<string> airports, vector<vector<string>> routes,
                       string startingAirport)
{
    Map map(airports, routes);
    const auto unreachableAirports = getUnreachableAirports(startingAirport, airports, map);

    auto unreachableRoutes = getReachableAirports(unreachableAirports, airports, map);

    int newRoutes{0};
    while (!unreachableRoutes.empty())
    {
        sort(begin(unreachableRoutes), end(unreachableRoutes), [](auto v1, auto v2)
             { return v1.size() > v2.size(); });
        newRoutes++;
        const auto newDestination = unreachableRoutes[0][0];
        for()
        unreachableRoutes = removeAirport(unreachableRoutes, newDestination);
    }

    return newRoutes;
}

int main()
{
    const vector<string> airports{"BGI", "CDG", "DEL", "DOH", "DSM", "EWR", "EYW", "HND", "ICN", "JFK", "LGA", "LHR", "ORD", "SAN", "SFO", "SIN", "TLV", "BUD"};
    const vector<vector<string>> routes{
        {"DSM", "ORD"},
        {"ORD", "BGI"},
        {"BGI", "LGA"},
        {"SIN", "CDG"},
        {"CDG", "SIN"},
        {"CDG", "BUD"},
        {"DEL", "DOH"},
        {"DEL", "CDG"},
        {"TLV", "DEL"},
        {"EWR", "HND"},
        {"HND", "ICN"},
        {"HND", "JFK"},
        {"ICN", "JFK"},
        {"JFK", "LGA"},
        {"EYW", "LHR"},
        {"LHR", "SFO"},
        {"SFO", "SAN"},
        {"SFO", "DSM"},
        {"SAN", "EYW"}};

    int n = airportConnections(airports, routes, "LGA");

    return 0;
}
