#include <vector>

using namespace std;

// This is an input struct. Do not edit.
class LinkedList
{
public:
    int value;
    LinkedList *next = nullptr;

    LinkedList(int value) { this->value = value; }
};

LinkedList *nodeSwap(LinkedList *head)
{
    LinkedList *prev = nullptr;
    auto current = head;
    auto next = current->next;

    while (current != nullptr and next != nullptr)
    {
        current->next = next->next;
        next->next = current;

        if (prev != nullptr)
            prev->next = next;
        else
            head = next;

        prev = current;
        current = current->next == nullptr ? nullptr : current->next;
        next = current != nullptr ? current->next : nullptr;
    }

    return head;
}

// This file is initialized with a code version of this
// question's sample test case. Feel free to add, edit,
// or remove test cases in this file as you see fit!

LinkedList *addMany(LinkedList *linkedList, vector<int> values);
vector<int> getNodesInArray(LinkedList *linkedList);

int main()
{
    LinkedList *linkedList = addMany(new LinkedList(0), {1, 2, 3, 4, 5});
    vector<int> expectedNodes = {1, 0, 3, 2, 5, 4};
    auto output = nodeSwap(linkedList);
}

LinkedList *addMany(LinkedList *linkedList, vector<int> values)
{
    LinkedList *current = linkedList;
    while (current->next != nullptr)
    {
        current = current->next;
    }
    for (auto value : values)
    {
        current->next = new LinkedList(value);
        current = current->next;
    }
    return linkedList;
}

vector<int> getNodesInArray(LinkedList *linkedList)
{
    vector<int> nodes;
    LinkedList *current = linkedList;
    while (current != nullptr)
    {
        nodes.push_back(current->value);
        current = current->next;
    }
    return nodes;
}
