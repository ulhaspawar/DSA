#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

vector<int> topologicalSort(vector<int> jobs, vector<vector<int>> deps)
{
    vector<int> topologicalOrder;
    unordered_map<int, int> incidentEdgeCount;
    unordered_map<int, vector<int>> prerequisites;

    for (const auto j : jobs)
    {
        incidentEdgeCount.insert({j, 0});
        prerequisites.insert({j, {}});
    }

    for (const auto &d : deps)
    {
        incidentEdgeCount[d[1]]++;
        prerequisites[d[0]].push_back(d[1]);
    }

    size_t idx{0};
    while (idx < jobs.size())
    {
        for (const auto &ec : incidentEdgeCount)
        {
            auto j = ec.first;
            if (ec.second == 0)
            {
                topologicalOrder.push_back(j);
                incidentEdgeCount.erase(j);

                for (const auto pre : prerequisites[j])
                {
                    incidentEdgeCount[pre]--;
                }

                break;
            }
        }
        idx++;
    }

    return topologicalOrder;
}

bool isValidTopologicalOrder(vector<int> order, vector<int> jobs,
                             vector<vector<int>> deps);

int main()
{
    vector<int> jobs = {1, 2, 3, 4};
    vector<vector<int>> deps = {{1, 2}, {1, 3}, {3, 2}, {4, 2}, {4, 3}};
    vector<int> order = topologicalSort(jobs, deps);
    cout << "Test: " << isValidTopologicalOrder(order, jobs, deps);
    return 0;
}

bool isValidTopologicalOrder(vector<int> order, vector<int> jobs,
                             vector<vector<int>> deps)
{
    unordered_map<int, bool> visited;
    for (int candidate : order)
    {
        for (vector<int> dep : deps)
        {
            if (candidate == dep[0] && visited.find(dep[1]) != visited.end())
                return false;
        }
        visited[candidate] = true;
    }
    for (int job : jobs)
    {
        if (visited.find(job) == visited.end())
            return false;
    }
    return order.size() == jobs.size();
}
