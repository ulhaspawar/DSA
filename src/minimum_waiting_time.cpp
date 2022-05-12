#include <algorithm>
#include <vector>

using namespace std;

int minimumWaitingTime(vector<int> queries)
{
    sort(begin(queries), end(queries));
    const auto qLen{queries.size()};
    int totalWaitingTime{0}, waitingTimeForQuery{0};
    for (size_t qIdx{1}; qIdx < qLen; qIdx++)
    {
        waitingTimeForQuery += queries[qIdx - 1];
        totalWaitingTime += waitingTimeForQuery;
    }
    return totalWaitingTime;
}
