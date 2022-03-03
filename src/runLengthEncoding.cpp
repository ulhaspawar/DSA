#include<iostream>
#include <string>
#include <vector>

using namespace std;

string runLengthEncoding(string str)
{
    if (str.empty())
        return "";

    vector<char> rle;

    char runOf{str[0]};
    int runLength = '1';
    for (size_t idx{1}; idx < str.length(); idx++)
    {
        if (runLength == '9' || str[idx] != runOf)
        {
            rle.push_back(runLength);
            rle.push_back(runOf);

            runLength = '1';
            runOf = str[idx];
            continue;
        }
        runLength++;
    }
    rle.push_back(runLength);
    rle.push_back(runOf);

    return string(cbegin(rle), cend(rle));
}


int main() {
    cout<<"Test 1: "<<runLengthEncoding("AAAAAAAAAAAAABBCCCCDD");
}