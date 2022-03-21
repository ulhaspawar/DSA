#include <string>
#include <vector>

using namespace std;

vector<int> preprocess(const string s)
{
    vector<int> preprocessed(s.size(), -1);

    size_t j{0}, i{1};
    const auto sLen{s.size()};

    while (i < (sLen + 1))
    {
        if (s[i] == s[j])
        {
            preprocessed[i] = j;
            i++;
            j++;
        }
        else
        {
            if (j > 0)
            {
                if (preprocessed[j - 1] != -1)
                    j = preprocessed[j - 1] + 1;
                else
                {
                    j = 0;
                    i++;
                }
            }
            else
                i++;
        }
    }

    return preprocessed;
}

bool knuthMorrisPrattAlgorithm(string str, string substr)
{
    auto preprocessedPattern = preprocess(substr);

    size_t i{0}, j{0};
    const auto txtLen{str.size()}, patLen{substr.size()};

    bool match{false};

    while (i < txtLen)
    {
        if (str[i] == substr[j])
        {
            if (j == patLen - 1)
            {
                match = true;
                break;
            }

            i++;
            j++;
            continue;
        }

        if (j == 0)
            i++;
        else
            j = preprocessedPattern[j - 1] + 1;
    }

    return match;
}

int main()
{
    knuthMorrisPrattAlgorithm("aefoaefcdaefcdaed", "aefcdaed");
    return 0;
}