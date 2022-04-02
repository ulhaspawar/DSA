#include <vector>
using namespace std;

// This is the class of the input root. Do not edit it.
class BinaryTree
{
public:
    int value;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;

    BinaryTree(int value);
};

void transform(BinaryTree *tree, BinaryTree *rightSibling)
{
    if (!tree)
        return;

    transform(tree->left, tree->right);
    transform(tree->right, rightSibling ? rightSibling->left : nullptr);
    
    tree->right = rightSibling;
}

BinaryTree *rightSiblingTree(BinaryTree *root)
{
    transform(root, nullptr);
    return root;
}
