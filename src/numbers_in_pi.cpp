#include <vector>
#include <string>
#include <unordered_map>
#include <climits>

using namespace std;

unordered_map<string, bool> toMap(const vector<string> numbers);
int getMinSpaces(const string piSubStr, const unordered_map<string, bool> &numbers, const int start, unordered_map<int, int> &cache);

int numbersInPi(string pi, vector<string> numbers)
{
    unordered_map<int, int> cache;
    auto numsFound = getMinSpaces(pi, toMap(numbers), 0, cache);
    return numsFound == -1 ? -1 : numsFound - 1;
}

int getMinSpaces(const string pi, const unordered_map<string, bool> &numbers, const int start, unordered_map<int, int> &cache)
{
    if (start == pi.size())
        return 0;

    if (cache.count(start) == 1)
        return cache[start];

    int minSpaces{INT_MAX};

    int runningCount{0};
    for (int len{1}; len < pi.size() - start + 1; len++)
    {
        const auto s = pi.substr(start, len);
        if (numbers.count(s) == 1)
        {
            runningCount = 1;
            int minSpacesInRem = getMinSpaces(pi, numbers, start + len, cache);
            if (minSpacesInRem == -1)
                continue;
            runningCount += minSpacesInRem;

            if (minSpaces > runningCount)
                minSpaces = runningCount;
        }
    }

    auto result = minSpaces == INT_MAX ? -1 : minSpaces;
    cache.insert({start, result});
    return result;
}

unordered_map<string, bool> toMap(const vector<string> numbers)
{
    unordered_map<string, bool> nums;
    for (const auto n : numbers)
        nums.insert({n, true});

    return nums;
}

int main()
{
    numbersInPi("3141592653589793238462643383279", {"314159265358979323846", "26433", "8", "3279", "314159265", "35897932384626433832", "79"});
}