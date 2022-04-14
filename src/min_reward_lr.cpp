#include <vector>
#include <numeric>
#include <math.h>

using namespace std;

int minRewards(vector<int> scores)
{
    const int numOfStudents = scores.size();
    vector<int> rewards(numOfStudents, 1);

    for (int idx = 1; idx < numOfStudents; idx++)
        if (scores[idx] > scores[idx - 1])
            rewards[idx] = rewards[idx - 1] + 1;

    for (int idx = numOfStudents - 2; idx >= 0; idx--)
        if (scores[idx] > scores[idx + 1])
            rewards[idx] = max(rewards[idx], rewards[idx + 1] + 1);

    return accumulate(cbegin(rewards), cend(rewards), 0);
}
