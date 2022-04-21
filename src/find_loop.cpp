#include <vector>
using namespace std;

class LinkedList
{
public:
    int value;
    LinkedList *next;

    LinkedList(int value);
};

LinkedList *findLoop(LinkedList *head)
{
    auto fastPtr{head}, slowPtr{head};

    do
    {
        slowPtr = slowPtr->next;
        fastPtr = fastPtr->next->next;
    } while (fastPtr != slowPtr);

    auto ptr{head};

    while (ptr != slowPtr)
    {
        ptr = ptr->next;
        slowPtr = slowPtr->next;
    }

    return ptr;
}
