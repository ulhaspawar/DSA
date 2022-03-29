#include <string>
#include <unordered_map>

using namespace std;

template <typename KEY, typename VALUE>
class DoublyLinkedListNode
{
    DoublyLinkedListNode<KEY, VALUE> *next{nullptr};
    DoublyLinkedListNode<KEY, VALUE> *prev{nullptr};
    KEY key;
    VALUE value;

public:
    DoublyLinkedListNode(KEY k, VALUE v) : key(k), value(v) {}

    inline DoublyLinkedListNode<KEY, VALUE> *get_next()
    {
        return next;
    }

    void set_next(DoublyLinkedListNode<KEY, VALUE> *nxtPtr)
    {
        next = nxtPtr;
    }

    inline DoublyLinkedListNode<KEY, VALUE> *get_prev()
    {
        return prev;
    }

    void set_prev(DoublyLinkedListNode<KEY, VALUE> *prevPtr)
    {
        prev = prevPtr;
    }

    void set_value(VALUE v)
    {
        value = v;
    }

    KEY get_key() const
    {
        return key;
    }

    VALUE *get_value()
    {
        return &value;
    }
};

template <typename KEY, typename VALUE>
class DoublyLinkedList
{
    DoublyLinkedListNode<KEY, VALUE> *head{nullptr};
    DoublyLinkedListNode<KEY, VALUE> *tail{nullptr};

public:
    DoublyLinkedListNode<KEY, VALUE> *prepend(KEY key, VALUE value)
    {
        DoublyLinkedListNode<KEY, VALUE> *node = new DoublyLinkedListNode(key, value);

        if (!head)
            head = tail = node;
        else
        {
            node->set_next(head);
            head->set_prev(node);
            if (head == tail)
                tail = head;
            head = node;
        }

        return node;
    }

    KEY first()
    {
        return head->get_key();
    }

    KEY last()
    {
        return tail->get_key();
    }

    void removeLast()
    {
        if (head == tail)
        {
            head = tail = nullptr;
            return;
        }

        tail = tail->get_prev();
        tail->set_next(nullptr);
    }

    void moveToFront(DoublyLinkedListNode<KEY, VALUE> *node)
    {
        if (node == head)
            return;
        if (node == tail)
            tail = tail->get_prev();

        auto prev = node->get_prev();
        auto next = node->get_next();

        node->set_next(nullptr);
        node->set_prev(nullptr);

        prev->set_next(next);

        if (next != nullptr)
            next->set_prev(prev);

        head->set_prev(node);
        node->set_next(head);
        head = node;
    }
};

class LRUCache
{
    unordered_map<string, DoublyLinkedListNode<string, int> *> store;
    DoublyLinkedList<string, int> list;

public:
    int maxSize;

    LRUCache(int maxSize) { this->maxSize = maxSize > 1 ? maxSize : 1; }

    void insertKeyValuePair(string key, int value)
    {
        if (store.count(key) == 1)
        {
            store[key]->set_value(value);
            list.moveToFront(store[key]);
            return;
        }

        if (store.size() == maxSize)
        {
            const auto leastUsedKey = list.last();
            list.removeLast();
            store.erase(leastUsedKey);
        }

        auto newNode = list.prepend(key, value);
        store.insert({key, newNode});
    }

    int *getValueFromKey(string key)
    {
        if (store.count(key) == 0)
            return nullptr;

        list.moveToFront(store[key]);
        return store[key]->get_value();
    }

    string getMostRecentKey()
    {
        if (store.size() == 0)
            return "";
        return list.first();
    }
};

int main()
{
    LRUCache cache(1);

    string k;
    int *v;

    v = cache.getValueFromKey("a");
    cache.insertKeyValuePair("a",1);
    v=cache.getValueFromKey("a");
    cache.insertKeyValuePair("a",9001);
    v=cache.getValueFromKey("a");
    cache.insertKeyValuePair("b",2);
    v=cache.getValueFromKey("a");
    v=cache.getValueFromKey("b");
    cache.insertKeyValuePair("c",3);
    v=cache.getValueFromKey("a");
    v=cache.getValueFromKey("b");
    v=cache.getValueFromKey("c");

    return 0;
}