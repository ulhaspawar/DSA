#include <vector>

using namespace std;

bool isMonotonic(vector<int> array)
{
    bool isMonotonic = true;
    
    if(array.size() < 2) return true; //Monotic array need atleast 3 numbers

    auto dir = array[1] - array[0];
    for(auto idx{2}; idx < array.size(); idx++) {
        auto diff = array[idx] - array[idx-1];
        if(dir == 0) //dir not found yet
        {
            dir = diff;
            continue;
        }

        if(!((diff >= 0 && dir > 0) || (diff <= 0 && dir < 0))) {
            isMonotonic = false;
            break;
        }
    }


    return isMonotonic;
}

int main()
{
    isMonotonic({-1, -5, -10, -1100, -1100, -1101, -1102, -9001});
    return 0;
}