#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

vector<string> phoneNumberMnemonics(string phoneNumber)
{
    const unordered_map<char, const vector<char>> keypad{
        {'0', {'0'}},
        {'1', {'1'}},
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}};

    vector<vector<char>> mnemonics;

    // Count number of mnemonics
    int count = 1;
    for (const char &c : phoneNumber)
        count *= keypad.find(c)->second.size();

    for (int idx{0}; idx < count; idx++)
        mnemonics.push_back({});

    int groupSize{1};
    for (const char c : phoneNumber)
    {
        const vector<char> chars = keypad.find(c)->second;
        const int numOfChars = chars.size();
        for (int idx{0}, cIdx{0}; idx < count;)
        {
            const char ch = chars[cIdx];
            mnemonics[idx].push_back(ch);
            idx++;
            if (idx % groupSize == 0)
                cIdx = (cIdx + 1) % numOfChars;
        }
        groupSize *= numOfChars;
    }

    vector<string> mnem;
    for (int idx{0}; idx < mnemonics.size(); idx++)
    {
        mnem.emplace_back(cbegin(mnemonics[idx]), cend(mnemonics[idx]));
    }

    return mnem;
}

int main()
{
    phoneNumberMnemonics("444");
    return 0;
}
