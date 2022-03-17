#include <string>

using namespace std;

pair<int, int> evenLengthPalindrom(const string s, const int center)
{
  int start = -1, len = -1;
  int l = center, r = center + 1;
  while (l >= 0 and r <= s.length() - 1)
  {
    if (s[l] == s[r])
    {
      start = l;
      len = r - l + 1;
    }
    else
    {
      break;
    }
    l--;
    r++;
  }

  return {start, len};
}

pair<int, int> oddLengthPalindrom(const string s, const int center)
{
  int start = center, len = 1;
  int l = center - 1, r = center + 1;
  while (l >= 0 and r <= s.length() - 1)
  {
    if (s[l] == s[r])
    {
      start = l;
      len = r - l + 1;
    }
    else
    {
      break;
    }
    l--;
    r++;
  }

  return {start, len};
}

string longestPalindromicSubstring(string str)
{
  const int len = str.length();
  int largestPalindromLength = 0;
  int largestPalindromStart = 0;
  for (int center = 0; center < len; center++)
  {
    // Even length palindrom
    const auto evenLenPal = evenLengthPalindrom(str, center);
    if (largestPalindromLength < evenLenPal.second)
    {
      largestPalindromLength = evenLenPal.second;
      largestPalindromStart = evenLenPal.first;
    }

    // Odd length palindrom
    const auto oddLenPal = oddLengthPalindrom(str, center);
    if (largestPalindromLength < oddLenPal.second)
    {
      largestPalindromLength = oddLenPal.second;
      largestPalindromStart = oddLenPal.first;
    }
  }

  return str.substr(largestPalindromStart, largestPalindromLength);
}

int main()
{
  longestPalindromicSubstring("it's highnoon");
}