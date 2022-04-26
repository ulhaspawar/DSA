#include <vector>
#include <limits>

using namespace std;

bool areSameBSTs(const vector<int> &tree1, const int tree1Root,
                 const vector<int> &tree2, const int tree2Root,
                 const int min, const int max);
int getLeftTreeRoot(const vector<int> &tree, const int root, const int min);
int getRightTreeRoot(const vector<int> &tree, const int root, const int max);

bool sameBsts(vector<int> arrayOne, vector<int> arrayTwo)
{
    return areSameBSTs(arrayOne, 0, arrayTwo, 0, numeric_limits<int>::min(), numeric_limits<int>::max());
}

bool areSameBSTs(const vector<int> &tree1, const int tree1Root,
                 const vector<int> &tree2, const int tree2Root, const int min, const int max)
{
    if (tree1Root == -1 or tree2Root == -1)
        return tree1Root == tree2Root;

    bool same{true};

    const int tree1RootValue = tree1[tree1Root];
    const int tree2RootValue = tree2[tree2Root];

    if (tree1RootValue != tree2RootValue)
        return false;

    const int tree1LeftIdx = getLeftTreeRoot(tree1, tree1Root, min);
    const int tree2LeftIdx = getLeftTreeRoot(tree2, tree2Root, min);
    const int tree1RightIdx = getRightTreeRoot(tree1, tree1Root, max);
    const int tree2RightIdx = getRightTreeRoot(tree2, tree2Root, max);

    same = areSameBSTs(tree1, tree1LeftIdx, tree2, tree2LeftIdx, min, tree1RootValue) and
           areSameBSTs(tree1, tree1RightIdx, tree2, tree2RightIdx, tree1RootValue, max);
    return same;
}

int getLeftTreeRoot(const vector<int> &tree, const int root, const int min)
{
    int leftRootIdx = -1;
    const int rootValue = tree[root];
    for (int idx = root + 1; idx < tree.size(); idx++)
        if (tree[idx] < rootValue and tree[idx] >= min)
        {
            leftRootIdx = idx;
            break;
        }
    return leftRootIdx;
}

int getRightTreeRoot(const vector<int> &tree, const int root, const int max)
{
    int rightRootIdx = -1;
    const int rootValue = tree[root];
    for (int idx = root + 1; idx < tree.size(); idx++)
        if (tree[idx] >= rootValue and tree[idx] < max)
        {
            rightRootIdx = idx;
            break;
        }
    return rightRootIdx;
}

int main()
{
    auto result = sameBsts({10, 15, 8, 12, 94, 81, 5, 2, 11}, {10, 8, 5, 15, 2, 12, 11, 94, 81});
    return 0;
}
