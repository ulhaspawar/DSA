#include <math.h>

using namespace std;

// This is an input class. Do not edit.
class BinaryTree
{
public:
    int value;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;

    BinaryTree(int value) { this->value = value; }
};

pair<bool, int> getHeight(const BinaryTree *tree)
{
    pair<bool, int> result{true, -1};

    if (!tree)
        return result;

    const auto leftTreeDetails = getHeight(tree->left);
    const auto rightTreeDetails = getHeight(tree->right);

    result.second = max(leftTreeDetails.second, rightTreeDetails.second) + 1;
    result.first = leftTreeDetails.first and rightTreeDetails.first and (abs(leftTreeDetails.second - rightTreeDetails.second) < 2);

    return result;
}

bool heightBalancedBinaryTree(BinaryTree *tree)
{
    return getHeight(tree).first;
}
