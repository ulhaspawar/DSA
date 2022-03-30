#include <vector>

using namespace std;

struct heap_node
{
  int num;
  int elementIdx;
  int arrayIdx;
};

class min_heap
{
  vector<heap_node> heap;

  void siftDown(const int idx)
  {
    const int heapSize = heap.size();
    const int left = 2 * idx + 1;
    const int right = left + 1;

    int least = idx;
    least = left < heapSize and heap[left].num < heap[least].num ? left : least;
    least = right < heapSize and heap[right].num < heap[least].num ? right : least;

    if (idx != least)
    {
      swap(heap[idx], heap[least]);
      siftDown(least);
    }
  }

  void siftUp(const int idx)
  {
    if (idx == 0)
      return;

    const int heapSize = heap.size();
    const int parent = (idx - 1) / 2;

    if (heap[parent].num > heap[idx].num)
    {
      swap(heap[idx], heap[parent]);
      siftUp(parent);
    }
  }

public:
  void insert(const int num, const int elementIdx, const int arrayIdx)
  {
    heap_node node;
    node.num = num;
    node.elementIdx = elementIdx;
    node.arrayIdx = arrayIdx;
    heap.push_back(node);
    siftUp(heap.size() - 1);
  }

  heap_node getMin()
  {
    const int heapSize = heap.size();
    auto min = heap[0];
    heap[0] = heap[heapSize - 1];
    heap.pop_back();
    siftDown(0);

    return min;
  }
};

vector<int> mergeSortedArrays(vector<vector<int>> arrays)
{
  const int numOfArrays = arrays.size();
  int totalElements = 0;

  for (int idx = 0; idx < numOfArrays; idx++)
    totalElements += arrays[idx].size();

  vector<int> sortedArray(totalElements);

  min_heap heap;

  for (int idx = 0; idx < numOfArrays; idx++)
    heap.insert(arrays[idx][0], 0, idx);

  int idx = 0;
  while (idx < totalElements)
  {
    const auto least = heap.getMin();
    sortedArray[idx] = least.num;
    if (least.elementIdx < arrays[least.arrayIdx].size() - 1)
      heap.insert(arrays[least.arrayIdx][least.elementIdx + 1], least.elementIdx + 1, least.arrayIdx);

    idx++;
  }

  return sortedArray;
}

int main()
{
  auto sorted = mergeSortedArrays({{1, 5, 9, 21}, {-1, 0}, {-124, 81, 121}, {3, 6, 12, 20, 150}});
  return 0;
}