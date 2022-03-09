#include<iostream>
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

pair<int, int> findKthLargestValueInBstHeper(const BST *tree, const int k, const int maxFound)
{
    if (tree)
    {
        if(tree->right == nullptr and tree->left == nullptr) 
        {
            return {maxFound + 1, tree->value};
        }

        const auto right = findKthLargestValueInBstHeper(tree->right, k, maxFound);
        if (right.first == k)
            return right;
        if (right.first == k - 1)
            return {k, tree->value};
        return findKthLargestValueInBstHeper(tree->left, k, right.first + 1);
    }
    return {maxFound, 0};
}

int findKthLargestValueInBst(BST *tree, int k)
{
    return findKthLargestValueInBstHeper(tree, k, 0).second;
}

int main() {
    auto root = new BST(15);
      root->left = new BST(5);
      root->left->left = new BST(2);
      root->left->left->left = new BST(1);
      root->left->left->right = new BST(3);
      root->left->right = new BST(5);
      root->right = new BST(20);
      root->right->left = new BST(17);
      root->right->right = new BST(22);
      int k = 3;
      int expected = 17;
      auto actual = findKthLargestValueInBst(root, k);
      cout<<"Test 1: " << actual;
}