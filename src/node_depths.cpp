#include<stack>

using namespace std;

class BinaryTree
{
public:
    int value;
    BinaryTree *left;
    BinaryTree *right;

    BinaryTree(int value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }
};

int nodeDepthsRec(const BinaryTree *root) {
    int nodeDepths{0};
    stack<pair<const BinaryTree*, int>> nodesToProcess;
    nodesToProcess.push({root, 0});

    while(!nodesToProcess.empty()) {
        auto entry = move(nodesToProcess.top());
        nodesToProcess.pop();
        nodeDepths += entry.second;

        if(entry.first->left)
        nodesToProcess.push({entry.first->left, entry.second + 1});
        
        if(entry.first->right)
        nodesToProcess.push({entry.first->right, entry.second + 1});
    }

    return nodeDepths;
}

int nodeDepths(const BinaryTree *tree, const int depth)
{
    if (tree == nullptr)
        return 0;

    return nodeDepths(tree->left, depth + 1) + nodeDepths(tree->right, depth + 1) + depth;
}

int nodeDepths(BinaryTree *root)
{
    return nodeDepths(root, 0);
}
