using namespace std;

int numberOfBinaryTreeTopologies(int n)
{
    if (n == 0)
        return 1;
    int count = 0;

    const auto childrenCount = n - 1;
    for (int leftTreeNodes = childrenCount; leftTreeNodes >= 0; leftTreeNodes--)
    {
        count += (numberOfBinaryTreeTopologies(leftTreeNodes) *
                  numberOfBinaryTreeTopologies(childrenCount - leftTreeNodes));
    }

    return count;
}

int main()
{
    auto n = numberOfBinaryTreeTopologies(5);
    return 0;
}
