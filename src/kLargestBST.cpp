#include<vector>
#include <utility>

using namespace std;

// This is an input class. Do not edit.
class BST
{
public:
    int value;
    BST *left = nullptr;
    BST *right = nullptr;

    BST(int value) { this->value = value; }
};

void findKthLargestValueInBstHeper(const BST *tree, const int k, vector<int> &traversal)
{
    if(tree) {
        findKthLargestValueInBstHeper(tree->right, k, traversal);
        if(traversal.size() == k) return;
        traversal.push_back(tree->value);
        if(traversal.size() == k) return;
        findKthLargestValueInBstHeper(tree->left, k, traversal);
    }
}

int findKthLargestValueInBst(BST *tree, int k)
{
    vector<int> traversal;
    findKthLargestValueInBstHeper(tree, k, traversal);
    return traversal.back();
}
