#include <vector>

using namespace std;

const int longestPeak(const vector<int> array)
{
    if (array.size() < 3)
        return -1;

    int longestPeak = 0;
    int runningPeak = 0;
    char direction = 'U'; // U:undefined, I: increasing, D: decreasing
    for (int idx = 1; idx < array.size(); idx++)
    {
        auto diff = array[idx] - array[idx - 1];
        diff = diff > 0 ? 1 : diff < 0 ? -1
                                       : 0;
        switch (diff)
        {
        case 1:
            if (direction != 'I')
            {
                runningPeak = 1;
            }
            direction = 'I';
            runningPeak++;
            break;

        case -1:
            if (direction == 'I' || direction == 'D')
            {
                runningPeak++;
                longestPeak = runningPeak > longestPeak ? runningPeak : longestPeak;
                direction = 'D';
            }
            break;

        case 0:
            direction = 'U';
            runningPeak = 0;
            break;
        }
    }

    return longestPeak;
}
