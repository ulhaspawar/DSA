#include<math.h>

using namespace std;

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

int getSize(const LinkedList *head);
void makeCircular(LinkedList *head);
void makeLinear(LinkedList *head, const int n);

LinkedList *shiftLinkedList(LinkedList *head, int k)
{
    const int n = getSize(head);

    if(n < 2) return head;

    auto _k = abs(k) % n;

    makeCircular(head);
    auto newHeadDistance = (k > 0) ? (n - _k) : _k;

    while(newHeadDistance > 0) {
        head = head->next;
        newHeadDistance--;
    }

    makeLinear(head, n);

    return head;
}

int getSize(const LinkedList *head)
{
    int n{0};
    auto current = head;

    while (current != nullptr)
    {
        n++;
        current = current->next;
    }

    return n;
}

void makeCircular(LinkedList *head)
{
    if (!head)
        return;

    auto current = head;
    while (current->next != nullptr)
    {
        current = current->next;
    }

    current->next = head;
}

void makeLinear(LinkedList *head, const int n)
{
    auto _n = n;
    auto current = head; 
    while(_n > 1) {
        current = current->next;
        _n--;
    }
    current->next = nullptr;
}
