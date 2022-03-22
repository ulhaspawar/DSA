#include <vector>
#include <string>

using namespace std;

void generateDivTagsHelper(const string current, const int openingTagsRemaining, const int closingTagsRemaining,
                           vector<string> &listings);

vector<string> generateDivTags(int numberOfTags)
{
    vector<string> listings;

    generateDivTagsHelper("", numberOfTags, numberOfTags, listings);

    return listings;
}

void generateDivTagsHelper(const string current, const int openingTagsRemaining, const int closingTagsRemaining,
                           vector<string> &listings)
{
    if (closingTagsRemaining == 0)
    {
        listings.push_back(current);
        return;
    }

    if (closingTagsRemaining > openingTagsRemaining)
        generateDivTagsHelper(current + "</div>", openingTagsRemaining, closingTagsRemaining - 1, listings);

    if (openingTagsRemaining > 0)
        generateDivTagsHelper(current + "<div>", openingTagsRemaining - 1, closingTagsRemaining, listings);
}