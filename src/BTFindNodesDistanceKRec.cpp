#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class BinaryTree
{
public:
    int value;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;

    BinaryTree(int value) { this->value = value; }
};

void addEligibleChild(BinaryTree *tree, int currentDistance, int k, vector<int> &nodes)
{
    if (!tree)
        return;

    if (currentDistance == k)
    {
        nodes.push_back(tree->value);
        return;
    }

    addEligibleChild(tree->left, currentDistance + 1, k, nodes);
    addEligibleChild(tree->right, currentDistance + 1, k, nodes);
}

int addNodes(BinaryTree *tree, int k, int target, vector<int> &nodes) {
    if(!tree) return -1;

    if(tree->value == target) {
        addEligibleChild(tree, 0, k, nodes);
        return 1;
    }

    auto leftDistance = addNodes(tree->left, k, target, nodes);
    auto rightDistance = addNodes(tree->right, k, target, nodes);

    if(leftDistance == k || rightDistance == k) {
        nodes.push_back(tree->value);
        return -1;
    }

    if(leftDistance != -1) {
        addEligibleChild(tree->right, leftDistance + 1, k, nodes);
        return leftDistance + 1;
    }

    if(rightDistance != -1) {
        addEligibleChild(tree->left, rightDistance + 1, k, nodes);
        return rightDistance + 1;
    }

    return -1;
}

vector<int> findNodesDistanceK(BinaryTree *tree, int target, int k)
{
    vector<int> nodes;
    addNodes(tree, k, target, nodes);
    return nodes;
}

int main()
{
    BinaryTree *root = new BinaryTree(1);
    root->left = new BinaryTree(2);
    root->right = new BinaryTree(3);
    root->left->left = new BinaryTree(4);
    root->left->right = new BinaryTree(5);
    root->right->right = new BinaryTree(6);
    root->right->right->left = new BinaryTree(7);
    root->right->right->right = new BinaryTree(8);
    int target = 3;
    int k = 2;
    vector<int> expected = {2, 7, 8};
    auto actual = findNodesDistanceK(root, target, k);
    sort(actual.begin(), actual.end());
    cout << "Test 1: " << (expected == actual);

    cout << endl;
    return 0;
}
