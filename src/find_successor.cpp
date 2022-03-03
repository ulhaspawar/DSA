using namespace std;

// This is an input class. Do not edit.
class BinaryTree
{
public:
    int value;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;
    BinaryTree *parent = nullptr;

    BinaryTree(int value) { this->value = value; }
};

BinaryTree *getLeftmostChild(BinaryTree *tree)
{
    auto currentNode = tree;
    while (currentNode->left)
        currentNode = currentNode->left;
    return currentNode;
}

BinaryTree *getRightmostParent(BinaryTree *tree)
{
    auto currentNode = tree;

    while (currentNode->parent && currentNode->parent->right == currentNode)
        currentNode = currentNode->parent;

    return currentNode->parent;
}

BinaryTree *findSuccessor(BinaryTree *tree, BinaryTree *node)
{
    BinaryTree *successor{nullptr};

    if (node->right)
    {
        successor = getLeftmostChild(node->right);
    }
    else
    {
        successor = getRightmostParent(node);
    }

    return successor;
}
