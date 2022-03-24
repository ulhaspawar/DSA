#include <vector>

using namespace std;

// This is an input class. Do not edit.
class LinkedList
{
public:
    int value;
    LinkedList *next;

    LinkedList(int value)
    {
        this->value = value;
        next = nullptr;
    }
};

LinkedList *mergeLinkedLists(LinkedList *headOne, LinkedList *headTwo)
{
    LinkedList *merged = nullptr;
    LinkedList *mergedNode = nullptr;

    auto l1Node{headOne}, l2Node{headTwo};

    while (true)
    {
        LinkedList *lesser, *larger;
        if (l1Node->value < l2Node->value)
        {
            lesser = l1Node;
            larger = l2Node;
            l1Node = l1Node->next;
        }
        else
        {
            lesser = l2Node;
            larger = l1Node;
            l2Node = l2Node->next;
        }

        if (merged == nullptr)
            merged = mergedNode = lesser;
        else
        {
            mergedNode->next = lesser;
            mergedNode = mergedNode->next;
        }

        if (lesser->next == nullptr)
        {
            mergedNode->next = larger;
            break;
        }
    }

    return merged;
}
