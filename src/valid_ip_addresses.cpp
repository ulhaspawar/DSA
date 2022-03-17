#include <string>
#include <vector>

using namespace std;

bool isIPAddressComponent(const string s, const int start, const int length)
{
    bool isValidIPComponent = true;

    isValidIPComponent = length > 0 and length < 4;
    isValidIPComponent = isValidIPComponent and (length > 1 ? s[start] != '0' : true);
    isValidIPComponent = isValidIPComponent and stoi(s.substr(start, length)) < 256;

    return isValidIPComponent;
}

vector<string> validIPAddresses(string s)
{
    const int sLen = s.length();
    vector<string> ipAddresses;

    const int p1Start{0};
    for (int p1Len{1}; p1Len <= 3 and p1Len <= sLen - 3; p1Len++)
    {
        if (!isIPAddressComponent(s, p1Start, p1Len))
            continue;
        const int p2Start{p1Len};
        for (int p2Len{1}; p2Len <= 3 and p1Len + p2Len <= sLen - 2; p2Len++)
        {
            if (!isIPAddressComponent(s, p2Start, p2Len))
                continue;
            const int p3Start{p1Len + p2Len};
            for (int p3Len{1}; p3Len <= 3 and p1Len + p2Len + p3Len <= sLen - 1; p3Len++)
            {
                if (!isIPAddressComponent(s, p3Start, p3Len))
                    continue;
                const int p4Start{p1Len + p2Len + p3Len};
                const int p4Len = sLen - p1Len - p2Len - p3Len;

                if (isIPAddressComponent(s, p4Start, p4Len))
                    ipAddresses.push_back(s.substr(p1Start, p1Len) + "." +
                                          s.substr(p2Start, p2Len) + "." +
                                          s.substr(p3Start, p3Len) + "." +
                                          s.substr(p4Start, p4Len));
            }
        }
    }

    return ipAddresses;
}

int main()
{
    validIPAddresses("1921860");
}