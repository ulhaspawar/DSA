#include <tuple>
#include <vector>

using namespace std;

struct TreeNode
{
    int num;
    int leftNodeCount{0};
    TreeNode *left{nullptr};
    TreeNode *right{nullptr};
};

pair<TreeNode *, int> insert(int num, TreeNode *root)
{
    int smallerCount{0};
    TreeNode *node = new TreeNode();
    node->num = num;
    if (root == nullptr)
        root = node;
    else
    {
        auto current = root;
        bool inserted{false};
        while (!inserted)
        {
            if (num < current->num)
            {
                current->leftNodeCount++;
                if (current->left == nullptr)
                {
                    current->left = node;
                    inserted = true;
                }
                else
                    current = current->left;
            }
            else
            {
                if (current->num < num)
                    smallerCount++;
                smallerCount += current->leftNodeCount;

                if (current->right == nullptr)
                {
                    current->right = node;
                    inserted = true;
                }
                else
                    current = current->right;
            }
        }
    }

    return {root, smallerCount};
}

vector<int> rightSmallerThan(vector<int> array)
{
    vector<int> result(array.size());
    TreeNode *root{nullptr};
    for (int idx = array.size() - 1; idx >= 0; idx--)
    {
        int smaller{0};
        tie(root, smaller) = insert(array[idx], root);
        result[idx] = smaller;
    }

    return result;
}

int main()
{
    rightSmallerThan({8, 5, 11, -1, 3, 4, 2});
    return 0;
}