#include <vector>

using namespace std;

bool isValidSubsequence(vector<int> array, vector<int> sequence)
{
    size_t aIdx{0}, sIdx{0}, aSize{array.size()}, sSize{sequence.size()}, found = false;

    while(aIdx < aSize) {
        if(array[aIdx] == sequence[sIdx]) {
            sIdx++;
            if(sIdx == sSize) {
                found = true;
                break;
            };
        }
        aIdx++;
    }

    return found;
}
