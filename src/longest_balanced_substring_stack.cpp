#include <stack>
#include <string>

using namespace std;

int longestBalancedSubstring(string str)
{
    constexpr char OPENING{'('}, CLOSING{')'};
    const auto sLen{str.size()};
    stack<int> startOfSubstrings;
    int longest{0};

    startOfSubstrings.push(-1);

    for (size_t idx{0}; idx < sLen; idx++)
    {
        if (str[idx] == OPENING)
            startOfSubstrings.push(idx);
        else
        {
            startOfSubstrings.pop();
            if (startOfSubstrings.empty())
                startOfSubstrings.push(idx);
            else
            {
                const auto length = idx - startOfSubstrings.top();
                if (longest < length)
                    longest = length;
            }
        }
    }

    return longest;
}
