#include <stack>
#include<tuple>

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

bool heightBalancedBinaryTree(BinaryTree *tree)
{
    bool isHeightBalanced = false;

    //Tuple description - node, height
    stack<tuple<BinaryTree *, int>> toBeProcessed;
    toBeProcessed.push({tree->left, -1}); 
    toBeProcessed.push({tree->right, -1});

    while (!toBeProcessed.empty())
    {
        const auto leftTree = toBeProcessed.top();
        toBeProcessed.pop();
        const auto rightTree = toBeProcessed.top();
        toBeProcessed.pop();
    }

    return isHeightBalanced;
}
