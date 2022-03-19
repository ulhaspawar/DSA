#include <vector>

using namespace std;

int getNextIdx(const vector<int> array, const int currentIdx)
{
    const int N = array.size();

    int nextIdx = (currentIdx + array[currentIdx]) % N;
    return nextIdx >= 0 ? nextIdx : nextIdx + N;
}

bool hasSingleCycle(vector<int> array)
{
    int currentIdx{0};
    int numOfJumps{0};
    const int size = array.size();
    while (numOfJumps < size)
    {
        if (numOfJumps > 0 and currentIdx == 0)
            return false;
        numOfJumps++;
        currentIdx = getNextIdx(array, currentIdx);
    }
    return currentIdx == 0;
}

int main()
{
    hasSingleCycle({2, 3, 1, -4, -4, 2});
}