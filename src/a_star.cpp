#include <vector>
#include <limits>
#include <algorithm>
#include <memory>

using namespace std;

class a_star_node
{
public:
    int r, c;
    bool isObstacle;
    shared_ptr<a_star_node>prev;
    int distanceFromStart{numeric_limits<int>::max()};
    int estimatedDistanceToEnd{numeric_limits<int>::max()};
    int total()
    {
        return distanceFromStart + estimatedDistanceToEnd;
    }
};

class min_heap
{
    vector<shared_ptr<a_star_node>> heap;

public:
    void siftUp(const int idx);
    void siftDown(const int idx);
    void insert(shared_ptr<a_star_node>n);
    shared_ptr<a_star_node>getMin() const
    {
        return heap[0];
    };
    void removeMin();
    void update(const int idx);
    bool empty()
    {
        return heap.empty();
    }
    int indexOf(const shared_ptr<a_star_node>node) const;
};

void min_heap::siftUp(const int idx)
{
    if (idx == 0)
        return;
    const auto parent = (idx - 1) / 2;
    if (heap[idx]->total() < heap[parent]->total())
    {
        swap(heap[idx], heap[parent]);
        siftUp(parent);
    }
}

void min_heap::siftDown(const int idx)
{
    const auto heapSize = heap.size();
    const auto left = 2 * idx + 1;
    const auto right = left + 1;
    int least = idx;
    if (left < heapSize and heap[left]->total() < heap[least]->total())
        least = left;
    if (right < heapSize and heap[right]->total() < heap[least]->total())
        least = right;
    if (least != idx)
    {
        swap(heap[least], heap[idx]);
        siftDown(least);
    }
}

void min_heap::insert(shared_ptr<a_star_node>n)
{
    heap.push_back(n);
    siftUp(heap.size() - 1);
}

void min_heap::removeMin()
{
    swap(heap[0], heap[heap.size() - 1]);
    heap.pop_back();
    siftDown(0);
}

int min_heap::indexOf(const shared_ptr<a_star_node>node) const
{
    int idx = -1;

    for (int i = 0; i < heap.size(); i++)
        if (heap[i]->r == node->r and heap[i]->c == node->c)
        {
            idx = i;
            break;
        }

    return idx;
}

void min_heap::update(const int idx)
{
    siftUp(idx);
}

vector<vector<shared_ptr<a_star_node>>> initializeNodes(const vector<vector<int>> &graph);
vector<vector<int>> constructPath(const shared_ptr<a_star_node>end);
int getManhattanDistance(const shared_ptr<a_star_node>start, const shared_ptr<a_star_node>end);
vector<shared_ptr<a_star_node>> getNeighbours(const vector<vector<shared_ptr<a_star_node>>> &g, const shared_ptr<a_star_node>node);

vector<vector<int>> aStarAlgorithm(int startRow, int startCol, int endRow,
                                   int endCol, vector<vector<int>> graph)
{
    auto aStarGraph = initializeNodes(graph);
    auto start = aStarGraph[startRow][startCol];
    const shared_ptr<a_star_node>end = aStarGraph[endRow][endCol];

    min_heap heap;

    start->distanceFromStart = 0;
    start->estimatedDistanceToEnd = getManhattanDistance(start, end);
    heap.insert(start);

    while (!heap.empty())
    {
        const auto candidate = heap.getMin();
        heap.removeMin();
        if (candidate->c == end->c and candidate->r == end->r)
            break;

        const int tentativeDistanceFromStart = candidate->distanceFromStart + 1;
        for (auto neighbour : getNeighbours(aStarGraph, candidate))
        {
            if (neighbour->isObstacle or neighbour->distanceFromStart < tentativeDistanceFromStart)
                continue;

            neighbour->distanceFromStart = tentativeDistanceFromStart;
            neighbour->prev = candidate;

            const int neighbourIdx = heap.indexOf(neighbour);
            if (neighbourIdx >= 0)
                heap.update(neighbourIdx);
            else
            {
                neighbour->estimatedDistanceToEnd = getManhattanDistance(neighbour, end);
                heap.insert(neighbour);
            }
        }
    }

    const auto path = constructPath(end);
    return path;
}

vector<vector<shared_ptr<a_star_node>>> initializeNodes(const vector<vector<int>> &graph)
{
    const int rowCount = graph.size();
    const int columnCount = graph[0].size();
    vector<vector<shared_ptr<a_star_node>>> aStarGraph(rowCount, vector<shared_ptr<a_star_node>>(columnCount, nullptr));

    for (int rIdx = 0; rIdx < rowCount; rIdx++)
        for (int cIdx = 0; cIdx < columnCount; cIdx++)
        {
            auto node = make_shared<a_star_node>();
            node->r = rIdx;
            node->c = cIdx;
            node->isObstacle = graph[rIdx][cIdx] == 1;
            aStarGraph[rIdx][cIdx] = node;
        }

    return aStarGraph;
}

int getManhattanDistance(const shared_ptr<a_star_node>start, const shared_ptr<a_star_node>end)
{
    return end->c - start->c + end->r - start->r;
}

vector<shared_ptr<a_star_node>> getNeighbours(const vector<vector<shared_ptr<a_star_node>>> &g, const shared_ptr<a_star_node>node)
{
    vector<shared_ptr<a_star_node>> neighbours;
    if (node->r > 0)
        neighbours.push_back(g[node->r - 1][node->c]);
    if (node->c > 0)
        neighbours.push_back(g[node->r][node->c - 1]);
    if (node->r < g.size() - 1)
        neighbours.push_back(g[node->r + 1][node->c]);
    if (node->c < g[0].size() - 1)
        neighbours.push_back(g[node->r][node->c + 1]);

    return neighbours;
}

vector<vector<int>> constructPath(const shared_ptr<a_star_node>endNode)
{
    if (endNode->distanceFromStart == numeric_limits<int>::max())
        return {};
    vector<vector<int>> path;
    auto current = endNode;
    while (current != nullptr)
    {
        path.push_back({current->r, current->c});
        current = current->prev;
    }
    reverse(begin(path), end(path));
    return path;
}

int main()
{
    const vector<vector<int>> g = {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1},
        {0, 0, 0, 0, 0}};

    const auto res = aStarAlgorithm(0, 1, 4, 3, g);
    return 0;
}