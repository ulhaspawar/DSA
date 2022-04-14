#include <vector>
#include <numeric>

using namespace std;

vector<int> getLocalMin(const vector<int> &scores);
vector<int> expandFromLocalMin(const vector<int> &localMins, const vector<int> &scores);

int minRewards(vector<int> scores)
{
    const auto rewards = expandFromLocalMin(getLocalMin(scores), scores);
    return accumulate(cbegin(rewards), cend(rewards), 0);
}

vector<int> getLocalMin(const vector<int> &scores)
{
    const int numOfStudents = scores.size();
    vector<int> localMin;
    for (int idx = 0; idx < numOfStudents; idx++)
    {
        if (idx == 0 and numOfStudents > 1 and scores[0] < scores[1])
            localMin.push_back(0);
        if (idx == numOfStudents - 1 and numOfStudents > 1 and scores[numOfStudents - 1] < scores[numOfStudents - 2])
            localMin.push_back(numOfStudents - 1);
        if (idx == 0 or idx == numOfStudents - 1)
            continue;
        if (scores[idx] < scores[idx - 1] and scores[idx] < scores[idx + 1])
            localMin.push_back(idx);
    }
    return localMin;
}

vector<int> expandFromLocalMin(const vector<int> &localMins, const vector<int> &scores)
{
    const int numOfStudents = scores.size();
    vector<int> rewards(numOfStudents, 1);

    for (const auto minIdx : localMins)
    {
        int left = minIdx - 1;
        while (left >= 0 and scores[left] > scores[left + 1])
        {
            rewards[left] = max(rewards[left], rewards[left + 1] + 1);
            left--;
        }

        int right = minIdx + 1;
        while (right < numOfStudents and scores[right] > scores[right - 1])
        {
            rewards[right] = rewards[right - 1] + 1;
            right++;
        }
    }

    return rewards;
}
