#include <vector>
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
    BinaryTree *prev{nullptr};
    BinaryTree *current{tree};

    BinaryTree *nextNode;

    while (current != nullptr)
    {
        if (prev == current->parent)
        {
            if (current->left != nullptr)
            {
                nextNode = current->left;
            }
            else
            {
                callback(current);
                nextNode = current->right != nullptr ? current->right : current->parent;
            }
        }
        else
        {
            if (prev == current->left)
            {
                callback(current);
                nextNode = current->right != nullptr ? current->right : current->parent;
            }
            else
                nextNode = current->parent;
        }

        prev = current;
        current = nextNode;
    }
}
