#include <vector>
using namespace std;

vector<int> selectionSort(vector<int> array)
{
    if(array.empty()) return array;

    for(auto i = array.size() - 1; i > 0; i--) {
        auto maxIdx = 0;
        auto maxNum {array[maxIdx]};
        for(auto j = 1; j <= i; j++) {
            if(array[j] > maxNum) {
                maxIdx=j;
                maxNum=array[j];
            }
        }
        swap(array[i], array[maxIdx]);
    }

    return array;
}
