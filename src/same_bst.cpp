#include <vector>
#include <stack>

using namespace std;

pair<vector<int>, vector<int>> getLeftRightNodes(const vector<int> &array)
{
    if (array.empty())
        return {{}, {}};

    vector<int> leftNodes;
    vector<int> rightNodes;
    const int root{array[0]};
    for (int idx{1}; idx < array.size(); idx++)
        if (array[idx] < root)
            leftNodes.push_back(array[idx]);
        else
            rightNodes.push_back(array[idx]);

    return {leftNodes, rightNodes};
}

bool sameBsts(vector<int> arrayOne, vector<int> arrayTwo)
{
    bool areSameBSTs{true};
    stack<pair<vector<int>, vector<int>>> toBeProcessed;
    toBeProcessed.push({arrayOne, arrayTwo});

    while (!toBeProcessed.empty())
    {
        const auto trees{toBeProcessed.top()};
        toBeProcessed.pop();
        const auto tree1 = trees.first;
        const auto tree2 = trees.second;

        if (tree1.empty() and tree2.empty())
            continue;

        if (tree1.size() != tree2.size() or tree1.front() != tree2.front())
        {
            areSameBSTs = false;
            break;
        }

        const auto tree1Nodes = getLeftRightNodes(tree1);
        const auto tree2Nodes = getLeftRightNodes(tree2);
        toBeProcessed.push({tree1Nodes.first, tree2Nodes.first});
        toBeProcessed.push({tree1Nodes.second, tree2Nodes.second});
    }

    return areSameBSTs;
}
