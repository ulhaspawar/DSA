#include <vector>
#include <math.h>
#include<limits>

using namespace std;

class BinaryTree
{
public:
    int value;
    BinaryTree *left;
    BinaryTree *right;

    BinaryTree(int value);
    void insert(vector<int> values, int i = 0);
};

struct TreeDetails
{
    int maxBranchSum;
    int maxPathSum;

    TreeDetails(int b, int p) : maxBranchSum(b), maxPathSum(p) {}
};

TreeDetails maxPathSum(const BinaryTree *tree)
{
    if (!tree)
        return {0, numeric_limits<int>::min()};

    auto leftTreeDetails = maxPathSum(tree->left);
    auto rightTreeDetails = maxPathSum(tree->right);

    int maxPathThroughNode = max(leftTreeDetails.maxBranchSum + rightTreeDetails.maxBranchSum + tree->value,
                                 max(leftTreeDetails.maxBranchSum + tree->value, rightTreeDetails.maxBranchSum + tree->value));
    int maxBranch = max(leftTreeDetails.maxBranchSum, rightTreeDetails.maxBranchSum) + tree->value;

    return {
        maxBranch,
        max(maxPathThroughNode, max(leftTreeDetails.maxPathSum, rightTreeDetails.maxPathSum))};
}

int maxPathSum(BinaryTree tree)
{
    return maxPathSum(&tree).maxPathSum;
}
