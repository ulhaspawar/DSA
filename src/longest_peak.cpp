#include <vector>

using namespace std;

int longestPeak(vector<int> array)
{
    constexpr char INCREASE{'I'}, DECREASE{'D'};
    char phase = INCREASE;
    int longestPeak{0};
    int currentPeak{1};
    for (size_t idx{1}, size{array.size()}; idx < size; idx++)
    {
        if(phase == INCREASE) {
            if(array[idx] < array[idx-1]) {
                phase = DECREASE;
            }
            else
            if(array[idx] == array[idx - 1]){
                currentPeak = 1;
            }
        }
    }

    return longestPeak;
}
