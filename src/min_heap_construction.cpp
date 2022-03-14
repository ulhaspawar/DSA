#include <vector>

using namespace std;

// Do not edit the class below except for the buildHeap,
// siftDown, siftUp, peek, remove, and insert methods.
// Feel free to add new properties and methods to the class.
class MinHeap
{
public:
    vector<int> heap;

    MinHeap(vector<int> vector) { heap = buildHeap(vector); }

    vector<int> buildHeap(vector<int> &vector)
    {
        int lastParent = ((vector.size() - 1) - 1) / 2;

        for (int idx = lastParent; idx >= 0; idx--)
        {
            siftDown(idx, vector.size() - 1, vector);
        }

        return vector;
    }

    void siftDown(int currentIdx, int endIdx, vector<int> &heap)
    {
        int child = 2 * currentIdx + 1;
        while (child <= endIdx)
        {
            int rightChild = child == endIdx ? -1 : child + 1;
            int leastChild = child;
            if (rightChild != -1 and heap[leastChild] > heap[rightChild])
                leastChild = rightChild;

            if (heap[leastChild] < heap[currentIdx])
            {
                swap(heap[leastChild], heap[currentIdx]);
                currentIdx = leastChild;
                child = 2 * currentIdx + 1;
            }
            else
            {
                break;
            }
        }
    }

    void siftUp(int currentIdx, vector<int> &heap)
    {
        int parentIdx = (currentIdx - 1) / 2;
        while (parentIdx > 0 and heap[parentIdx] > heap[currentIdx])
        {
            swap(heap[currentIdx], heap[parentIdx]);
            currentIdx = parentIdx;
            parentIdx = (currentIdx - 1) / 2;
        }
    }

    int peek()
    {
        return heap[0];
    }

    int remove()
    {
        swap(heap[0], heap[heap.size() - 1]);
        auto n = heap.back();
        heap.pop_back();
        siftDown(0, heap.size() - 1, heap);
        return n;
    }

    void insert(int value)
    {
        heap.push_back(value);
        siftUp(heap.size() - 1, heap);
    }
};
