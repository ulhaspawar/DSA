#include <string>
#include <stack>

using namespace std;

inline bool isOpeningBracket(char c)
{
    return c == '(' || c == '[' || c == '{';
}

inline bool isClosingBracket(char c)
{
    return c == ')' || c == ']' || c == '}';
}

inline bool isMatchingBrackets(const char o, const char c)
{
    return (o == '(' and c == ')') or (o == '[' and c == ']') or (o == '{' and c == '}');
}

bool balancedBrackets(string str)
{
    bool areAllClosingBracketsMatched = true;
    stack<char> openingBracketsEncountered;

    for (const auto c : str)
    {
        if (isOpeningBracket(c))
        {
            openingBracketsEncountered.push(c);
            continue;
        }

        if (isClosingBracket(c))
        {
            if (!openingBracketsEncountered.empty() && isMatchingBrackets(openingBracketsEncountered.top(), c))
                openingBracketsEncountered.pop();
            else
            {
                areAllClosingBracketsMatched = false;
                break;
            }
        }
    }

    return areAllClosingBracketsMatched && openingBracketsEncountered.empty();
}
