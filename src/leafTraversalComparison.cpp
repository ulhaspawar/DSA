#include <utility>

using namespace std;

// This is an input class. Do not edit.
class BinaryTree
{
public:
    int value;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;

    BinaryTree(int value) { this->value = value; }

    bool isLeaf() const
    {
        return left == nullptr && right == nullptr;
    }
};

pair<BinaryTree *, BinaryTree *> toLeafLinkedList(BinaryTree *tree, BinaryTree *head, BinaryTree *tail)
{
    if (!tree)
        return {head, tail};

    if (tree->isLeaf())
    {
        if (head == nullptr)
        {
            return {tree, tree};
        }

        tail->right = tree;
        return {head, tree};
    }

    auto llDetails = toLeafLinkedList(tree->left, head, tail);
    llDetails = toLeafLinkedList(tree->right, llDetails.first, llDetails.second);

    return llDetails;
}

bool compareLL(const BinaryTree *ll1, const BinaryTree *ll2)
{
    auto currentNode1 = ll1;
    auto currentNode2 = ll2;

    while (ll1 != nullptr && ll2 != nullptr)
    {
        if (ll1->value != ll2->value)
        {
            break;
        }

        ll1 = ll1->right;
        ll2 = ll2->right;
    }

    return ll1 == nullptr && ll2 == nullptr;
}

bool compareLeafTraversal(BinaryTree *tree1, BinaryTree *tree2)
{
    auto ll1 = toLeafLinkedList(tree1, nullptr, nullptr);
    auto ll2 = toLeafLinkedList(tree2, nullptr, nullptr);
    return compareLL(ll1.first, ll2.first);
}
