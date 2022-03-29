#include <string>

using namespace std;

bool isBalancedString(const string s, const size_t start, const size_t end);
int longestBalancedSubstring_bruteforce(const string str);

int longestBalancedSubstring(string str)
{
    return longestBalancedSubstring_bruteforce(str);
}

int longestBalancedSubstring_bruteforce(const string str)
{
    if (str.empty())
        return 0;
    const auto sLen{str.size()};
    int longest{0};

    for (size_t idxStart{0}; idxStart < sLen - 1; idxStart++)
    {
        if (str[idxStart] == ')')
            continue;
        for (size_t idxEnd{idxStart + 1}; idxEnd < sLen; idxEnd += 2)
        {
            if (str[idxEnd] == '(')
                continue;
            if (isBalancedString(str, idxStart, idxEnd) and longest < (idxEnd - idxStart + 1))
                longest = idxEnd - idxStart + 1;
        }
    }

    return longest;
}

bool isBalancedString(const string s, const size_t start, const size_t end)
{
    int paranthesisTracker{0};
    bool isBalanced{true};

    for (auto idx{start}; idx < end + 1; idx++)
        if (s[idx] == '(')
            paranthesisTracker++;
        else if (paranthesisTracker > 0)
            paranthesisTracker--;
        else
        {
            isBalanced = false;
            break;
        }

    isBalanced = isBalanced && paranthesisTracker == 0;
    return isBalanced;
}

int main()
{
    longestBalancedSubstring("(()))(");
    return 0;
}