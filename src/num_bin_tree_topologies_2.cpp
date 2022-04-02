#include <vector>

using namespace std;

int numberOfBinaryTreeTopologies(int n)
{
    vector<int> cache(n + 1);
    cache[0] = 1;

    for (int totalNodes = 1; totalNodes <= n; totalNodes++)
    {
        int count = 0;
        for (int leftSubtreeNodes = totalNodes - 1; leftSubtreeNodes >= 0; leftSubtreeNodes--)
        {
            const auto rightSubtreeNodes = totalNodes - 1 - leftSubtreeNodes;
            const int leftSubtreeConfigurations = cache[leftSubtreeNodes];
            const int rightSubtreeConfigurations = cache[rightSubtreeNodes];
            count += (leftSubtreeConfigurations * rightSubtreeConfigurations);
        }
        cache[totalNodes] = count;
    }

    return cache[n];
}

int main()
{
    auto n = numberOfBinaryTreeTopologies(5);
    return 0;
}
