#include <unordered_map>
#include <string>
#include <limits>

using namespace std;

bool isPalindrome(const string s, const int start, const int end)
{
    int isPalindrome{true};

    int left{start}, right{end};
    while (left <= right)
        if (s[left++] != s[right--])
        {
            isPalindrome = false;
            break;
        }

    return isPalindrome;
}

int palindromePartitioningMinCuts(const string str, const int start, const int end, unordered_map<string, int> &cache)
{
    if (start == end)
        return 1;

    const string key = to_string(start) + "_" + to_string(end);
    if (cache.count(key))
        return cache[key];

    int minNumOfPalindromes{numeric_limits<int>::max()};

    for (auto idx{start}; idx <= end; idx++)
    {
        if (isPalindrome(str, start, idx))
        {
            int numOfPalindromes = 1;
            if (idx < end)
                numOfPalindromes += palindromePartitioningMinCuts(str, idx + 1, end, cache);
            minNumOfPalindromes = minNumOfPalindromes > numOfPalindromes ? numOfPalindromes : minNumOfPalindromes;
        }
    }

    cache[key] = minNumOfPalindromes;
    return minNumOfPalindromes;
}

int palindromePartitioningMinCuts(string str)
{
    unordered_map<string, int> cache;
    return palindromePartitioningMinCuts(str, 0, str.size() - 1, cache) - 1;
}

int main()
{
    auto num = palindromePartitioningMinCuts("noonabbad");
    return 0;
}
