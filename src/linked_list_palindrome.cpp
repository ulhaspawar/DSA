using namespace std;

// This is an input struct. Do not edit.
class LinkedList
{
public:
    int value;
    LinkedList *next;

    LinkedList(int value)
    {
        this->value = value;
        this->next = nullptr;
    }
};

LinkedList *reverse(LinkedList *head);
LinkedList *findMid(LinkedList *head);

bool linkedListPalindrome(LinkedList *head)
{
    if (head == nullptr or head->next == nullptr)
        return true;

    auto mid = findMid(head);
    LinkedList *prevToMid{head};
    while (prevToMid->next != mid)
        prevToMid = prevToMid->next;
    auto reversedHalfHead = reverse(mid);
    prevToMid->next = reversedHalfHead;

    auto first{head}, second{reversedHalfHead};
    while (first != reversedHalfHead and second != nullptr)
    {
        if (first->value != second->value)
            break;
        first = first->next;
        second = second->next;
    }

    return first == reversedHalfHead;
}

LinkedList *findMid(LinkedList *head)
{
    if (head == nullptr)
        return nullptr;

    auto slow = head;
    auto fast = head;

    while (fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
        if (fast->next != nullptr)
            fast = fast->next;
    }
    return slow;
}

LinkedList *reverse(LinkedList *head)
{
    auto prev{head};
    auto current{prev->next};
    LinkedList *next;

    while (current != nullptr)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    head->next = nullptr;

    return prev;
}
