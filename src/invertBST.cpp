#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class BinaryTree
{
public:
    int value;
    BinaryTree *left;
    BinaryTree *right;

    BinaryTree(int value);
    void insert(vector<int> values, int i = 0);
    void invertedInsert(vector<int> values, int i = 0);
};

BinaryTree::BinaryTree(int value)
{
    this->value = value;
    this->left = nullptr;
    this->right = nullptr;
}

void BinaryTree::insert(vector<int> values, int i)
{
    if (i >= values.size())
    {
        return;
    }
    deque<BinaryTree *> queue;
    queue.push_back(this);
    while (queue.size() > 0)
    {
        BinaryTree *current = queue.front();
        queue.pop_front();
        if (current->left == nullptr)
        {
            current->left = new BinaryTree(values[i]);
            break;
        }
        queue.push_back(current->left);
        if (current->right == nullptr)
        {
            current->right = new BinaryTree(values[i]);
            break;
        }
        queue.push_back(current->right);
    }
    this->insert(values, i + 1);
}

void BinaryTree::invertedInsert(vector<int> values, int i)
{
    if (i >= values.size())
    {
        return;
    }
    deque<BinaryTree *> queue;
    queue.push_back(this);
    while (queue.size() > 0)
    {
        BinaryTree *current = queue.front();
        queue.pop_front();
        if (current->right == nullptr)
        {
            current->right = new BinaryTree(values[i]);
            break;
        }
        queue.push_back(current->right);
        if (current->left == nullptr)
        {
            current->left = new BinaryTree(values[i]);
            break;
        }
        queue.push_back(current->left);
    }
    this->invertedInsert(values, i + 1);
}

bool compareBT(BinaryTree *a, BinaryTree *b)
{
    if (a == nullptr && b == nullptr)
    {
        return true;
    }
    if (a != nullptr && b != nullptr)
    {
        return a->value == b->value && compareBT(a->left, b->left) &&
               compareBT(a->right, b->right);
    }
    return false;
}

void invertBinaryTree_recursive(BinaryTree *tree)
{
    if (tree)
    {
        swap(tree->left, tree->right);
        invertBinaryTree_recursive(tree->left);
        invertBinaryTree_recursive(tree->right);
    }
}

void invertBinaryTree_nonRecursive(BinaryTree *tree)
{
    if (tree)
    {
        deque<BinaryTree *> q;
        q.push_front(tree);

        while (!q.empty())
        {
            auto subTreeRoot = move(q.back());
            q.pop_back();

            swap(subTreeRoot->left, subTreeRoot->right);
            if (subTreeRoot->left)
                q.push_front(subTreeRoot->left);
            if (subTreeRoot->right)
                q.push_front(subTreeRoot->right);
        }
    }
}

int main()
{
    BinaryTree tree(1);
    tree.insert({2, 3, 4, 5, 6, 7, 8, 9});
    invertBinaryTree_nonRecursive(&tree);
    BinaryTree invertedTree(1);
    invertedTree.invertedInsert({2, 3, 4, 5, 6, 7, 8, 9});
    cout << "Test 1: " << (compareBT(&tree, &invertedTree) == 1);
}
