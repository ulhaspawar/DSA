#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

vector<string> getPathParts(const string path)
{
    stringstream strm(path);
    vector<string> pathParts;
    string part;

    while (getline(strm, part, '/'))
        pathParts.push_back(part);

    return pathParts;
}

string buildPath(const vector<string> &pathParts)
{
    ostringstream oss;
    const int len = pathParts.size();

    bool isAbsolutePath = pathParts[0] == "";

    if (isAbsolutePath)
        oss << "/";

    for (int pIdx = isAbsolutePath ? 1 : 0; pIdx < len; pIdx++)
    {
        oss << pathParts[pIdx];
        if (pIdx < len - 1)
            oss << "/";
    }

    return oss.str();
}

string shortenPath(string path)
{
    const string ROOT{""};

    bool isAbsolutePath = path[0] == '/';
    const auto pathParts = getPathParts(path);
    vector<string> shortenedPathParts;

    if (isAbsolutePath)
        shortenedPathParts.push_back(ROOT);

    for (int pIdx = isAbsolutePath ? 1 : 0; pIdx < pathParts.size(); pIdx++)
    {
        const auto part = pathParts[pIdx];

        // Remove . and extra /
        if (part == "." or part == "")
            continue;

        if (part == "..")
        {
            // Ignore ".." if root
            if (shortenedPathParts.size() == 1 and shortenedPathParts.back() == ROOT)
                continue;

            // Remove current folder
            if (!shortenedPathParts.empty() and shortenedPathParts.back() != "..")
            {
                shortenedPathParts.pop_back();
                continue;
            }
        }

        shortenedPathParts.push_back(part);
    }

    return buildPath(shortenedPathParts);
}

int main()
{
    string path = "/foo/../test/../test/../foo//bar/./baz";
    string shortened = shortenPath(path);
    return 0;
}
