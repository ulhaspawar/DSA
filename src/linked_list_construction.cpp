using namespace std;

class Node
{
public:
  int value;
  Node *prev;
  Node *next;

  Node(int value)
  {
    this->value = value;
    prev = next = nullptr;
  };
};

// Feel free to add new properties and methods to the class.
class DoublyLinkedList
{
public:
  Node *head;
  Node *tail;

  DoublyLinkedList()
  {
    head = nullptr;
    tail = nullptr;
  }

  void setHead(Node *node)
  {
    if (head == nullptr)
    {
      head = tail = node;
    }
    else
    {
      insertBefore(head, node);
    }
  }

  void setTail(Node *node)
  {
    if (tail == nullptr)
    {
      // Empty list
      head = tail = node;
    }
    else
    {
      insertAfter(tail, node);
    }
  }

  void insertBefore(Node *node, Node *nodeToInsert)
  {
    remove(nodeToInsert);
    if (head == nullptr)
      setHead(nodeToInsert);
    else
    {
      Node *prev = node->prev;

      nodeToInsert->next = node;
      node->prev = nodeToInsert;

      if (prev != nullptr)
      {
        prev->next = nodeToInsert;
        nodeToInsert->prev = prev;
      }
      else
        head = nodeToInsert;
    }
  }

  void insertAfter(Node *node, Node *nodeToInsert)
  {
    remove(nodeToInsert);
    if (tail == nullptr)
      setTail(nodeToInsert);
    else
    {
      Node *next = node->next;

      if (next != nullptr)
      {
        nodeToInsert->next = next;
        next->prev = nodeToInsert;
      }
      else
      {
        tail = nodeToInsert;
      }
      node->next = nodeToInsert;
      nodeToInsert->prev = node;
    }
  }

  void insertAtPosition(int position, Node *nodeToInsert)
  {
    if (position == 1)
    {
      setHead(nodeToInsert);
      return;
    }

    auto currentNode = head;
    int idx{1};
    while (idx != position)
    {
      idx++;
      currentNode = currentNode->next;
    }

    if (currentNode)
    {
      insertBefore(currentNode, nodeToInsert);
    }
    else
    {
      setTail(nodeToInsert);
    }
  }

  void removeNodesWithValue(int value)
  {
    Node *currentNode = head;

    while (currentNode)
    {
      auto next = currentNode->next;
      if (currentNode->value == value)
        remove(currentNode);
      currentNode = next;
    }
  }

  void remove(Node *node)
  {
    if (node == head)
      head = head->next;
    if (node == tail)
      tail = tail->prev;

    Node *prev = node->prev;
    Node *next = node->next;

    node->prev = node->next = nullptr;

    if (prev != nullptr)
      prev->next = next;

    if (next != nullptr)
      next->prev = prev;
  }

  bool containsNodeWithValue(int value)
  {
    bool found = false;
    Node *currentNode = head;
    while (currentNode)
    {
      if (currentNode->value == value)
      {
        found = true;
        break;
      }
      currentNode = currentNode->next;
    }
    return false;
  }
};

int main()
{
  Node *n5 = new Node{5};
  DoublyLinkedList dll;
  dll.setHead(n5);

  Node *n4 = new Node{4};
  dll.setHead(n4);

  return 0;
}
