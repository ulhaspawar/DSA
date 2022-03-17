#include <array>
#include <vector>
#include <algorithm>

using namespace std;

int getDigitAtPos(const int num, const int pos);
int getDigitCount(const int num);

int getDigitAtPos(const int num, const int pos)
{
    int dig = 1;
    for (int i = 1; i < pos; i++)
        dig *= 10;

    return (num / dig) % 10;
}

int getDigitCount(int num)
{
    if (num == 0)
        return 0;
    int digCount = 1;
    while ((num = num / 10) > 0)
    {
        digCount++;
    }
    return digCount;
}

vector<int> radixSort(vector<int> array)
{
    if(array.empty()) return array;
    
    const int largestNumber = *max_element(cbegin(array), cend(array));
    const int numOfDigits = getDigitCount(largestNumber);

    std::array<int, 10> occurences{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> temp(array.size());

    for (int d = 1; d <= numOfDigits; d++)
    {
        occurences.fill(0);
        for (const auto n : array)
            occurences[getDigitAtPos(n, d)]++;

        for (int idx = 1; idx < 10; idx++)
            occurences[idx] += occurences[idx - 1];

        for (int idx = array.size() - 1; idx >=0; idx--)
        {
            const auto digit = getDigitAtPos(array[idx], d);
            temp[--occurences[digit]] = array[idx];
        }

        array.clear();
        for (const auto n : temp)
        {
            array.push_back(n);
        }
    }

    return array;
}

int main()
{
    radixSort({8762, 654, 3008, 345, 87, 65, 234, 12, 2});
}