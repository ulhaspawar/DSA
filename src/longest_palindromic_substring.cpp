#include <string>

using namespace std;

bool isPalindrom(const string str, const int s, const int e)
{
    bool match{true};

    int l{s}, r{e};

    while (l <= r)
    {
        if (str[l++] != str[r--])
        {
            match = false;
            break;
        }
    }

    return match;
}

string longestPalindromicSubstring(string str)
{
    int len = 0;
    int start;
    const int str_len = str.length();
    for (size_t l{0}; l < str_len and (str_len - l) > len; l++)
    {
        for (size_t r{str.length() - 1}; (r - l + 1) > len and r >= l and r < str_len; r--)
        {
            if (isPalindrom(str, l, r) and (r - l + 1) > len)
            {
                len = r - l + 1;
                start = l;
            }
        }
    }
    return str.substr(start, len);
}
