#include <unordered_map>
#include <string>

using namespace std;

bool generateDocument(string characters, string document)
{
    unordered_map<char, int> charAvailability;
    bool canGenerate{true};

    for (const auto c : characters)
    {
        if (charAvailability.count(c) == 0)
            charAvailability[c] = 0;
        charAvailability[c]++;
    }

    for (const auto c : document)
    {
        if (charAvailability.count(c) > 0 && charAvailability[c] > 0)
        {
            charAvailability[c]--;
        }
        else
        {
            canGenerate = false;
            break;
        }
    }

    return canGenerate;
}
