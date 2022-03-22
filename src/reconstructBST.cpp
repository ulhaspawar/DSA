#include <vector>
#include<limits>

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

BST *reconstructBst(const vector<int> preOrderTraversalValues, int &idx, const int min, const int max)
{
    if(idx == preOrderTraversalValues.size()) return nullptr;
    
    const auto n = preOrderTraversalValues[idx];

    if(n < min or n >= max) return nullptr;

    idx++;
    
    const auto left = reconstructBst(preOrderTraversalValues, idx, min, n);
    const auto right = reconstructBst(preOrderTraversalValues, idx, n, max);

    BST *tree = new BST(n);
    tree->left = left;
    tree->right = right;
    return tree;
}

BST *reconstructBst(vector<int> preOrderTraversalValues)
{
    int idx = 0;
    return reconstructBst(preOrderTraversalValues, idx, numeric_limits<int>::min(), numeric_limits<int>::max());
}

int main()
{
    reconstructBst({10, 4, 2, 1, 5, 17, 19, 18});
}