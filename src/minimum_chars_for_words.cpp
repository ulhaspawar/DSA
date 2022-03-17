#include <vector>
#include <string>
#include <unordered_map>
#include<math.h>

using namespace std;

const unordered_map<char, int> getCharFrequency(const string word);
vector<char> makeCharVector(const unordered_map<char, int> &charFreq);
void updateWordCharFrequency(const unordered_map<char, int> &wordCharFreq, unordered_map<char, int> &charFreq);

vector<char> minimumCharactersForWords(vector<string> words)
{
    unordered_map<char, int> charFreq;

    for(const auto word: words){
        updateWordCharFrequency(getCharFrequency(word), charFreq);
    }

    return makeCharVector(charFreq);
}

const unordered_map<char, int> getCharFrequency(const string word)
{
    unordered_map<char, int> charFreq;

    for (const auto c : word)
    {
        if (charFreq.count(c) == 0)
            charFreq.emplace(c, 1);
        else
            charFreq[c]++;
    }

    return charFreq;
}

vector<char> makeCharVector(const unordered_map<char, int> &charFreq)
{
    vector<char> chars;

    for (const auto p : charFreq)
        for (int idx{0}; idx < p.second; idx++)
            chars.push_back(p.first);

    return chars;
}

void updateWordCharFrequency(const unordered_map<char, int> &wordCharFreq, unordered_map<char, int> &charFreq)
{
    for (const auto p : wordCharFreq)
    {
        if (charFreq.count(p.first))
            charFreq[p.first] = max(charFreq[p.first], p.second);
        else
            charFreq.emplace(p.first, p.second);
    }
}
