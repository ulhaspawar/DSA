#include <vector>
#include <string>
#include <iostream>

using namespace std;

using namespace std;

char shift(const int c, const int key)
{
    constexpr char A = 97, Z = 122, SIZE = 26;
    const char k = key % 26;
    int newCode = c + k;
    if (newCode > Z)
    {
        const char wrapCount = newCode - Z;
        newCode = A + wrapCount - 1;
    }
    return newCode;
}

string caesarCypherEncryptor(string str, int key)
{
    vector<char> encrypted;
    encrypted.reserve(str.length());

    for (const auto c : str)
    {
        encrypted.push_back(shift(c, key));
    }

    return string(begin(encrypted), end(encrypted));
}


int main()
{
    cout << "Test 1: " << caesarCypherEncryptor("xyz", 2);
}
