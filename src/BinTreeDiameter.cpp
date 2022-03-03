#include <utility>
#include <math.h>

using namespace std;

// This is an input class. Do not edit.
class BinaryTree
{
public:
    int value;
    BinaryTree *left;
    BinaryTree *right;

    BinaryTree(int value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

pair<int, int> getBinaryTreeDiameterDetails_1(BinaryTree *tree) {
    if(!tree) return {0, 0};

    
}

// Return pair <diameter, longestPathLength>
pair<int, int> getBinaryTreeDiameterDetails(BinaryTree *tree)
{
    if (tree->left == nullptr && tree->right == nullptr)
        return {0, 0};

    pair<int, int> zeroPair{0, 0};
    auto leftDiameter = tree->left ? getBinaryTreeDiameterDetails(tree->left) : zeroPair;
    auto rightDiameter = tree->right ? getBinaryTreeDiameterDetails(tree->right) : zeroPair;

    auto longestPathLength = max(leftDiameter.second, rightDiameter.second) + 1;
    auto biggestDiameterBelow = max(leftDiameter.first, rightDiameter.first);
    auto diameter = leftDiameter.second + rightDiameter.second +
                    (tree->left ? 1 : 0) + (tree->right ? 1 : 0);

    return {max(diameter, biggestDiameterBelow), longestPathLength};
}

int binaryTreeDiameter(BinaryTree *tree)
{
    return getBinaryTreeDiameterDetails(tree).first;
}
