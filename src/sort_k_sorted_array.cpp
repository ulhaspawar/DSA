#include <vector>

using namespace std;

class fixed_sized_heap
{
    vector<int> heap;

    void heapify()
    {
        const int heapSize = heap.size();
        int lastParent = (heapSize - 2 / 2);
        for (int pIdx = lastParent; pIdx >= 0; pIdx--)
            siftDown(pIdx);
    }

    void siftUp(const int idx)
    {
        const int heapSize = heap.size();
        if (idx == 0)
            return;

        int parentIdx = (idx - 1) / 2;
        if (parentIdx > 0 and heap[parentIdx] > heap[idx])
        {
            swap(heap[parentIdx], heap[idx]);
            siftUp(parentIdx);
        }
    }

    void siftDown(const int parentIdx)
    {
        const int heapSize = heap.size();

        const int left = 2 * parentIdx + 1;
        const int right = left + 1;

        int least = parentIdx;
        if (left < heapSize and heap[left] < heap[least])
            least = left;
        if (right < heapSize and heap[right] < heap[least])
            least = right;

        if (parentIdx != least)
        {
            swap(heap[parentIdx], heap[least]);
            siftDown(least);
        }
    }

public:
    fixed_sized_heap(const vector<int> &v)
    {
        heap = vector(v);
        heapify();
    }

    void insert(const int num)
    {
        heap.push_back(num);
        siftUp(heap.size() - 1);
    }

    int getMin()
    {
        return heap[0];
    }

    void removeMin()
    {
        const int heapSize = heap.size();
        if (heapSize == 0)
            return;
        swap(heap[0], heap[heapSize - 1]);
        heap.pop_back();
        siftDown(0);
    }

    void replaceMin(const int num)
    {
        heap[0] = num;
        siftDown(0);
    }
};

vector<int> sortKSortedArray(vector<int> array, int k)
{
    const int size = array.size();
    const int _k = (k + 1) > size ? size : (k + 1);
    fixed_sized_heap heap(vector(cbegin(array), cbegin(array) + _k));

    for (int idx = 0; idx < size; idx++)
    {
        array[idx] = heap.getMin();
        int nextIdx = idx + k + 1;
        if (nextIdx < size)
            heap.replaceMin(array[nextIdx]);
        else
            heap.removeMin();
    }

    return array;
}

int main()
{
    auto sorted = sortKSortedArray({5, 4, 3, 2, -100}, 5);
    return 0;
}
