#include <vector>
#include <numeric>
#include<math.h>

using namespace std;

int minRewards(vector<int> scores)
{
    const int numOfStudents = scores.size();
    vector<int> rewards(numOfStudents, 1);

    for (int idx = 1; idx < numOfStudents; idx++)
    {
        if (scores[idx] < scores[idx - 1])
        {
            int lIdx = idx - 1;
            while (lIdx >= 0 and scores[lIdx] > scores[lIdx + 1])
            {
                rewards[lIdx] = max(rewards[lIdx + 1] + 1, rewards[lIdx]);
                lIdx--;
            }
        }
        if (scores[idx] > scores[idx - 1])
        {
            rewards[idx] = rewards[idx - 1] + 1;
        }
    }

    return accumulate(cbegin(rewards), cend(rewards), 0);
}
