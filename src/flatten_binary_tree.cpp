#include <vector>
#include <tuple>

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

pair<BinaryTree*, BinaryTree*> inorder(BinaryTree *tree)
{
    if (tree == nullptr)
        return {nullptr, nullptr};

    
    const auto leftList = inorder(tree->left);

    if (leftList.second != nullptr)
    {
        leftList.second->right = tree;
    }

    const auto rightList = inorder(tree->right);

    if (rightList.first != nullptr)
    {
        rightList.first->left = tree;
    }

    tree->left = leftList.second;
    tree->right = rightList.first;

    return {
        leftList.first != nullptr ? leftList.first : tree,
        rightList.second != nullptr ? rightList.second : tree
    };
}

BinaryTree *flattenBinaryTree(BinaryTree *root)
{
    auto dll = inorder(root);    
    return dll.first;
}
