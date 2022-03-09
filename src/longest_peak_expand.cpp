#include <vector>

using namespace std;

int longestPeak(vector<int> array)
{
    int longestPeak = 0;

    int idx{1}, N{int(array.size())};

    while (idx < N - 1)
    {
        if (array[idx - 1] < array[idx] and array[idx + 1] < array[idx])
        {
            int leftIdx = idx - 2;
            while (array[leftIdx] < array[leftIdx + 1] && leftIdx >= 1)
                leftIdx--;

            int rightIdx = idx + 2;
            while (array[rightIdx - 1] > array[rightIdx] && rightIdx <= N - 2)
                rightIdx++;

            auto peakLength = rightIdx - leftIdx - 1;
            longestPeak = peakLength > longestPeak ? peakLength : longestPeak;
            idx = rightIdx - 1;
        }

        idx++;
    }

    return longestPeak;
}

int main()
{
    longestPeak({1, 2, 3, 3, 4, 0, 10, 6, 5, -1, -3, 23});
    return 0;
}