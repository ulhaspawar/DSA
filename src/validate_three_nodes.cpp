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
    return (isDescendent(nodeOne, nodeTwo) and isDescendent(nodeTwo, nodeThree)) or
           (isDescendent(nodeThree, nodeTwo) and isDescendent(nodeTwo, nodeOne));
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
