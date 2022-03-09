#include <vector>
#include <stack>

using namespace std;

class BST
{
public:
    int value;
    BST *left;
    BST *right;

    BST(int value)
    {
        this->value = value;
        left = nullptr;
        right = nullptr;
    }

    void insert(int value)
    {
        if (value < this->value)
        {
            if (left == nullptr)
            {
                left = new BST(value);
            }
            else
            {
                left->insert(value);
            }
        }
        else
        {
            if (right == nullptr)
            {
                right = new BST(value);
            }
            else
            {
                right->insert(value);
            }
        }
    }
};

void pushLeftRightFragments(const int left, const int mid, const int right, stack<pair<int, int>> &arrayFragments)
{
    if (mid > left)
        arrayFragments.emplace(left, mid - 1);

    if (mid < right)
        arrayFragments.emplace(mid + 1, right);
}

BST *minHeightBst(vector<int> array)
{
    const int N = array.size();
    const auto rootIdx = (N - 1) / 2;
    BST *root = new BST {array[rootIdx]};
    stack<pair<int, int>> arrayFragments;

    pushLeftRightFragments(0, rootIdx, N - 1, arrayFragments);

    while (!arrayFragments.empty())
    {
        const auto p = move(arrayFragments.top());
        arrayFragments.pop();

        int mid = (p.second + p.first) / 2;
        root->insert(array[mid]);
        pushLeftRightFragments(p.first, mid, p.second, arrayFragments);
    }

    return root;
}
