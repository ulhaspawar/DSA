#include<vector>

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

struct listptrs
{
    LinkedList *head{nullptr}, *tail{nullptr};

    void insert(LinkedList *node)
    {
        node->next = nullptr;

        if (head == nullptr)
            head = tail = node;
        else
        {
            tail->next = node;
            tail = tail->next;
        }
    }

    listptrs merge(listptrs next)
    {
        listptrs merged;
        if (head == nullptr)
        {
            if (next.head != nullptr)
                merged = next;
        }
        else
        {
            merged = *this;
            if (next.head != nullptr)
            {
                merged.tail->next = next.head;
                merged.tail = next.tail;
            }
        }
        return merged;
    }
};

LinkedList *rearrangeLinkedList(LinkedList *head, int k)
{
    listptrs l, e, g;

    auto current = head;
    while (current != nullptr)
    {
        listptrs *addToList;

        if (current->value == k)
            addToList = &e;
        else if (current->value < k)
            addToList = &l;
        else
            addToList = &g;

        auto next = current->next;
        addToList->insert(current);
        current = next;
    }

    auto merged = l.merge(e.merge(g));

    return merged.head;
}

vector<int> linkedListToArray(LinkedList *head)
{
    vector<int> array{};
    auto current = head;
    while (current != nullptr)
    {
        array.push_back(current->value);
        current = current->next;
    }
    return array;
}

int main()
{
    auto head = new LinkedList(3);
    head->next = new LinkedList(0);
    head->next->next = new LinkedList(5);
    head->next->next->next = new LinkedList(2);
    head->next->next->next->next = new LinkedList(1);
    head->next->next->next->next->next = new LinkedList(4);
    auto result = rearrangeLinkedList(head, 3);
    auto array = linkedListToArray(result);

    vector<int> expected{0, 2, 1, 3, 5, 4};

    return 0;
}
