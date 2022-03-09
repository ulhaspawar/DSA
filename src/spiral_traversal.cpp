#include <vector>
#include <iostream>

using namespace std;

void traverseBorder(const vector<vector<int>> array,
                    const size_t rowStart, const size_t rowEnd,
                    const size_t colStart, const size_t colEnd,
                    vector<int> &borderTraversal)
{
    for (size_t idx{colStart}; idx <= colEnd; idx++)
        borderTraversal.push_back(array[rowStart][idx]);

    for (size_t idx{rowStart + 1}; idx <= rowEnd; idx++)
        borderTraversal.push_back(array[idx][colEnd]);

    if (rowStart < rowEnd)
        for (size_t idx{colEnd - 1}; idx >= colStart && idx < colEnd; idx--)
            borderTraversal.push_back(array[rowEnd][idx]);

    if (colStart < colEnd)
        for (size_t idx{rowEnd - 1}; idx > rowStart && idx < rowEnd; idx--)
            borderTraversal.push_back(array[idx][colStart]);
}

vector<int> spiralTraverse(vector<vector<int>> array)
{
    if (array.empty())
        return {};

    const auto m{array.size()}, n{array[0].size()};

    vector<int> result;
    result.reserve(m * n);

    for (size_t hf{0}, hl{m - 1}, vf{0}, vl{n - 1}; (hf <= hl && hl < m) && (vf <= vl && vl < n); hf++, hl--, vf++, vl--)
        traverseBorder(array, hf, hl, vf, vl, result);

    return result;
}

int main()
{
    cout << "Spiral Traversal (recursive): ";
    // auto result = spiralTraverse(
    //     {{1, 2, 3, 4, 5},
    //      {14, 15, 16, 17, 6},
    //      {13, 20, 19, 18, 7},
    //      {12, 11, 10, 9, 8}});

    auto result = spiralTraverse({{1, 2, 3, 4}, {10, 11, 12, 5}, {9, 8, 7, 6}});
    for (auto n : result)
        cout << n << "\t";

    return 0;
}
