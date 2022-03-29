#include <string>
#include <math.h>

using namespace std;

size_t longestBalancedSubstring(const string str, const int direction);

int longestBalancedSubstring(string str)
{
    return max(longestBalancedSubstring(str, 0), longestBalancedSubstring(str, 1));
}

size_t longestBalancedSubstring(const string str, const int direction)
{
    const auto sLen{str.size()};
    if (sLen == 0)
        return 0;

    size_t longest{0};
    size_t openingParans{0}, closingParans{0};

    const char OPENING = direction == 0 ? '(' : ')';
    const char CLOSING = direction == 0 ? ')' : '(';
    const int step = direction == 0 ? 1 : -1;
    size_t idx = direction == 0 ? 0 : str.size() - 1;

    while (idx < sLen)
    {
        if (str[idx] == OPENING)
            openingParans++;
        else
        {
            closingParans++;
            if (closingParans > openingParans)
                openingParans = closingParans = 0;
            else if (closingParans == openingParans)
            {
                const auto len = openingParans * 2;
                longest = longest < len ? len : longest;
            }
        }

        idx += step;
    }

    return longest;
}
