#include<vector>

using namespace std;

// This is the class of the input root. Do not edit it.
class BinaryTree {
public:
  int value;
  BinaryTree *left;
  BinaryTree *right;

  BinaryTree(int value) {
    this->value = value;
    left = nullptr;
    right = nullptr;
  }
};

void calculateBranchSums(const BinaryTree *tree, const int sumAtParent, vector<int> &branchSums) noexcept {
    if(tree == nullptr) return;

    if(tree->left == nullptr and tree->right == nullptr) {
        branchSums.push_back(sumAtParent + tree->value);
    }

    calculateBranchSums(tree->left, sumAtParent + tree->value, branchSums);
    calculateBranchSums(tree->right, sumAtParent + tree->value, branchSums);
}

vector<int> branchSums(BinaryTree *root) {
  vector<int> branchSums;
  calculateBranchSums(root, 0, branchSums);
  return branchSums;
}
