#include <vector>
#include <string>
#include <unordered_map>
#include <stack>
#include <algorithm>

using namespace std;

class AirRoutes
{
private:
    vector<vector<bool>> graph;
    unordered_map<size_t, string> idxToNameMap;
    unordered_map<string, size_t> nameToIdxMap;

    inline size_t getIdx(const string name) const;
    inline string getName(const size_t idx) const;
    vector<size_t> dfs(const size_t start, const size_t exclusion) const;
    vector<size_t> findUnreachables(const int start) const;

public:
    vector<string> getConnections(const string startingAirport) const;
    AirRoutes(const vector<string> &airports, const vector<vector<string>> &routes);
};

size_t AirRoutes::getIdx(const string name) const
{
    return nameToIdxMap.find(name)->second;
}

string AirRoutes::getName(const size_t idx) const
{
    return idxToNameMap.find(idx)->second;
}

AirRoutes::AirRoutes(const vector<string> &airports, const vector<vector<string>> &routes)
{
    const auto numOfAirports{airports.size()};
    const auto numOfRoutes{routes.size()};

    for (size_t idx{0}; idx < numOfAirports; idx++)
    {
        idxToNameMap.insert({idx, airports[idx]});
        nameToIdxMap.insert({airports[idx], idx});
        graph.push_back(vector(numOfAirports, false));
    }

    for (size_t idx{0}; idx < numOfRoutes; idx++)
    {
        const auto source{getIdx(routes[idx][0])};
        const auto destination{getIdx(routes[idx][1])};

        graph[source][destination] = true;
    }
}

vector<size_t> AirRoutes::dfs(const size_t start, const size_t exclusion) const
{
    const auto numOfAirports{graph.size()};

    vector<size_t> dfsTraversal;
    stack<size_t> toBeProcessed;
    toBeProcessed.push(start);

    while (!toBeProcessed.empty())
    {
        const auto current{toBeProcessed.top()};
        toBeProcessed.pop();
        if (current != exclusion and current != start)
            dfsTraversal.push_back(current);

        for (size_t idx{0}; idx < numOfAirports; idx++)
            if (idx != exclusion and graph[current][idx] and find(cbegin(dfsTraversal), cend(dfsTraversal), idx) == cend(dfsTraversal))
                toBeProcessed.push(idx);
    }

    return dfsTraversal;
}

vector<size_t> AirRoutes::findUnreachables(const int start) const
{
    const auto numOfAirports{graph.size()};

    const auto reachables{dfs(start, start)};
    vector<size_t> unreachables;

    for (size_t idx{0}; idx < numOfAirports; idx++)
        if (idx != start and find(cbegin(reachables), cend(reachables), idx) == cend(reachables))
            unreachables.push_back(idx);

    return unreachables;
}

vector<string> AirRoutes::getConnections(const string startingAirport) const
{
    const auto start{getIdx(startingAirport)};
    const auto unreachables{findUnreachables(start)};
    vector<string> missingRoutes;

    unordered_map<int, vector<size_t>> unreachablesMap;
    for (const auto idx : unreachables)
        unreachablesMap.insert({idx, dfs(idx, start)});

    while (!unreachablesMap.empty())
    {
        // Find longest unreachable path
        size_t longestLength{0};
        size_t bestNewRoute;
        vector<size_t> newConnections;
        for (auto const p : unreachablesMap)
        {
            if (longestLength <= p.second.size())
            {
                longestLength = p.second.size();
                bestNewRoute = p.first;
                newConnections = p.second;
            }
        }

        // Add new route
        missingRoutes.push_back(getName(bestNewRoute));
        unreachablesMap.erase(bestNewRoute);

        // Remove newly connected airports
        for (const auto connected : newConnections)
        {
            unreachablesMap.erase(connected);
            for (auto u : unreachablesMap)
            {
                auto match = find(begin(u.second), end(u.second), connected);
                if (match != end(u.second))
                    u.second.erase(match);
            }
        }
    }

    return missingRoutes;
}

int airportConnections(vector<string> airports, vector<vector<string>> routes,
                       string startingAirport)
{
    const AirRoutes airRoutes(airports, routes);

    return airRoutes.getConnections(startingAirport).size();
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

    const auto ans = airportConnections(airports, {}, "LGA");

    return 0;
}