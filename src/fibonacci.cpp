#include <unordered_map>

using namespace std;

int getNthFib(int n)
{
    if (n <= 2)
        return (n - 1);
    return getNthFib(n - 1) + getNthFib(n - 2);
}

int getNthFibMem(int n, unordered_map<int, int> &cache)
{
    if (cache.count(n))
        return cache[n];
    auto fibN = getNthFib(n - 1) + getNthFib(n - 2);
    cache.insert({n, fibN});
    return fibN;
}

int getNthFibIt(int n)
{
    if (n <= 2)
        return n - 1;

    auto fibN1{0}, fibN2{1};
    auto fib{0};
    for (int idx{3}; idx <= n; idx++)
    {
        fib = fibN2 + fibN1;
        fibN1 = fibN2;
        fibN2 = fib;
    }
    return fib;
}
