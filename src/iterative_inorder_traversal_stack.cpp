#include <vector>
#include <stack>

using namespace std;

class BinaryTree
{
public:
    int value;
    BinaryTree *left;
    BinaryTree *right;
    BinaryTree *parent;

    BinaryTree(int value, BinaryTree *parent = nullptr);
    void insert(vector<int> values, int i = 0);
};

void iterativeInOrderTraversal(BinaryTree *tree,
                               void (*callback)(BinaryTree *tree))
{
    stack<BinaryTree *> parents;

    auto node = tree;
    while (!parents.empty() or node != nullptr)
    {
        if (node != nullptr)
        {
            parents.push(node);
            node = node->left;
        }
        else
        {
            node = parents.top();
            parents.pop();
            callback(node);
            node = node->right;
        }
    }
}
