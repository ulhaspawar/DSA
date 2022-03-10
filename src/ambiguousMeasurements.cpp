#include <vector>
#include<unordered_set>
#include<string>

using namespace std;

constexpr int LOW = 0;
constexpr int HIGH = 1;

bool ambiguousMeasurementsHelper(const vector<vector<int>> measuringCups, const int low,
                                 const int high, const int runningLow, const int runningHigh, unordered_set<string> &measurementFailures)
{
    if(measurementFailures.count(to_string(runningLow) + "-" + to_string(runningHigh)) == 1) return false;

    if(runningLow >= low && runningHigh <= high) return true;

    bool isMeasurable = false;
    
    for(const auto cup : measuringCups) {
        if(runningHigh + cup[HIGH] <= high) {
            if(ambiguousMeasurementsHelper(measuringCups, low, high, runningLow + cup[LOW], runningHigh + cup[HIGH], measurementFailures)) {
                isMeasurable = true;
                break;
            }
            measurementFailures.insert(to_string(runningLow + cup[LOW]) + "-" + to_string(runningHigh + cup[HIGH]));
        }
    }

    return isMeasurable;
}

bool ambiguousMeasurements(vector<vector<int>> measuringCups, int low,
                           int high)
{
    unordered_set<string> measurementFailures;
    return ambiguousMeasurementsHelper(measuringCups, low, high, 0, 0, measurementFailures);
}

int main()
{
    ambiguousMeasurements({{200, 210}, {450, 465}, {800, 850}}, 2100, 2300);
    return 0;
}