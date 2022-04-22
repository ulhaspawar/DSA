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

bool isDescendent(const BST *const parent, const BST *const child);

bool validateThreeNodes(BST *nodeOne, BST *nodeTwo, BST *nodeThree)
{
    auto fromOne{nodeOne};
    auto fromThree{nodeThree};

    while (true)
    {
        bool foundThreeFromOne = fromOne == nodeThree;
        bool foundOneFromThree = fromThree == nodeOne;
        bool foundTwo = fromOne == nodeTwo or fromThree == nodeTwo;
        bool stopSearch = fromOne == nullptr and fromThree == nullptr;

        if (foundOneFromThree or foundThreeFromOne or foundTwo or stopSearch)
            break;

        if (fromOne != nullptr)
            fromOne = fromOne->value > nodeTwo->value ? fromOne->left : fromOne->right;

        if (fromThree != nullptr)
            fromThree = fromThree->value > nodeTwo->value ? fromThree->left : fromThree->right;
    }

    if (fromOne != nodeTwo and fromThree != nodeTwo)
        return false;

    auto from = fromOne == nodeTwo ? nodeTwo : nodeThree;
    auto to = fromOne == nodeTwo ? nodeThree : nodeOne;

    return isDescendent(from, to);
}

bool isDescendent(const BST *const parent, const BST *const child)
{
    bool isDesc{false};

    auto current{parent};
    while (current != nullptr)
    {
        if (current == child)
        {
            isDesc = true;
            break;
        }

        current = current->value < child->value ? current->right : current->left;
    }

    return isDesc;
}