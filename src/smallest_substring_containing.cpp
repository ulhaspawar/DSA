#include <string>
#include <unordered_map>

using namespace std;

const unordered_map<char, int> getCharCount(const string str);
int getL(const string str, const int start, const unordered_map<char, int> &charCount);
int getR(const string str, const int start, const unordered_map<char, int> &charCount, unordered_map<char, int> &encounteredCharCount);

const unordered_map<char, int> getCharCount(const string str)
{
    unordered_map<char, int> charCount;

    for (const auto c : str)
        charCount[c]++;

    return charCount;
}

int getL(const string str, const int start, const unordered_map<char, int> &charCount)
{
    int match = -1;
    const auto sLen{str.size()};
    for (int idx = start; idx < sLen; idx++)
    {
        const auto c = str[idx];
        if (charCount.count(c) > 0)
        {
            match = idx;
            break;
        }
    }
    return match;
}

int getR(const string str, const int start, const unordered_map<char, int> &charCount, unordered_map<char, int> &encounteredCharCount)
{
    const auto sLen{str.size()};
    int r = -1;

    unordered_map<char, int> charTracker;

    for (const auto &[c, n] : encounteredCharCount)
        if (n < charCount.at(c))
            charTracker.insert({c, charCount.at(c) - n});

    if (charTracker.empty())
        return start;

    for (int idx = start; idx < sLen; idx++)
    {
        const auto c = str[idx];

        if (!charCount.count(c) > 0)
            continue;

        encounteredCharCount[c]++;
        if (charTracker.count(c) > 0)
        {
            charTracker[c]--;
            if (charTracker[c] == 0)
                charTracker.erase(c);

            if (charTracker.empty())
            {
                r = idx;
                break;
            }
        }
    }

    return r;
}

string smallestSubstringContaining(string bigString, string smallString)
{
    const int bLen = bigString.size();
    auto l{-1}, r{0};

    const auto charCount{getCharCount(smallString)};

    unordered_map<char, int> encounteredCharCount;

    for (const auto &p : charCount)
        encounteredCharCount.insert({p.first, 0});

    int runningMin = bLen + 1, lMin, rMin;
    while (l < bLen and r < bLen)
    {
        l = getL(bigString, l + 1, charCount);
        if (l == -1)
            break;

        const auto lChar = bigString[l];

        r = getR(bigString, r <= l ? l : r, charCount, encounteredCharCount);
        if (r == -1)
            break;

        const auto currentLen = r - l + 1;
        if (runningMin > currentLen)
        {
            runningMin = currentLen;
            lMin = l;
            rMin = r;
        }

        encounteredCharCount[lChar]--;
        if (encounteredCharCount[lChar] < charCount.at(lChar))
            r++;
    }

    return runningMin <= bLen ? bigString.substr(lMin, rMin - lMin + 1) : "";
}

int main()
{
    const auto result = smallestSubstringContaining("a$fuu+afff+affaffa+a$Affab+a+a+$a$", "a+$aaAaaaa$++");
    return 0;
}