#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class BinaryTree
{
public:
    int value;
    BinaryTree *left = nullptr;
    BinaryTree *right = nullptr;

    BinaryTree(int value) { this->value = value; }
};

void populateNodeToParentMap(unordered_map<int, BinaryTree *> &nodeToParentMap, BinaryTree *tree, BinaryTree *parent)
{
    nodeToParentMap[tree->value] = parent;
    if (tree->left)
        populateNodeToParentMap(nodeToParentMap, tree->left, tree);
    if (tree->right)
        populateNodeToParentMap(nodeToParentMap, tree->right, tree);
}

BinaryTree *findNodeByValue(const int value, BinaryTree *tree, const unordered_map<int, BinaryTree *> nodeToParentMap)
{
    if (tree->value == value)
        return tree;
    auto parent = nodeToParentMap.find(value)->second;
    if (parent->left && parent->left->value == value)
        return parent->left;
    return parent->right;
}

vector<int> findNodesDistanceK(BinaryTree *targetNode, int k, unordered_map<int, BinaryTree *> nodeToParentMap)
{
    deque<pair<BinaryTree *, int>> nodes{{targetNode, 0}};
    unordered_set<int> visited;

    while (!nodes.empty())
    {
        
        auto node = move(nodes.front());
        nodes.pop_front();

        visited.insert(node.first->value);

        if (node.second == k)
        {
            vector<int> result;
            result.push_back(node.first->value);
            for (const auto &n : nodes)
                result.push_back(n.first->value);
            return result;
        }

        vector<BinaryTree *> adjacents{
            node.first->left,
            node.first->right,
            nodeToParentMap[node.first->value]};

        for (const auto &a : adjacents)
            if (a)
                if (visited.count(a->value) == 0)
                    nodes.push_back({a, node.second + 1});
    }

    return {};
}

vector<int> findNodesDistanceK(BinaryTree *tree, int target, int k)
{
    unordered_map<int, BinaryTree *> nodeToParentMap;
    populateNodeToParentMap(nodeToParentMap, tree, nullptr);
    auto targetNode = findNodeByValue(target, tree, nodeToParentMap);

    return findNodesDistanceK(targetNode, k, nodeToParentMap);
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
