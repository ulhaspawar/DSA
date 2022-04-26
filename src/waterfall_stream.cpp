#include <vector>

using namespace std;

vector<double> getWaterPercentInSink(const vector<double> &sinkRow)
{
    const int w = sinkRow.size();
    vector<double> sink(w, 0);

    for (size_t idx{0}; idx < w; idx++)
        if (sinkRow[idx] < 0)
            sink[idx] = sinkRow[idx] * -100;

    return sink;
}

vector<double> waterfallStreams(vector<vector<double>> array, int source)
{
    auto rowAbove = array[0];
    rowAbove[source] = -1;
    const auto height = array.size();
    const auto width = rowAbove.size();

    for (size_t currentRowIdx{1}; currentRowIdx < height; currentRowIdx++)
    {
        auto currentRow = array[currentRowIdx];

        for (size_t idx{0}; idx < width; idx++)
        {
            const auto hasWaterAbove = rowAbove[idx] < 0;
            const auto hasBlock = currentRow[idx] == 1;

            if (!hasWaterAbove)
                continue;

            if (!hasBlock)
            {
                currentRow[idx] += rowAbove[idx];
                continue;
            }

            const auto splitWater = rowAbove[idx] / 2;

            auto left{idx - 1};
            while (left < width)
            {
                if (currentRow[left] == 1)
                    break;
                if (currentRow[left] <= 0)
                {
                    currentRow[left] += splitWater;
                    break;
                }
                left--;
            }

            auto right{idx + 1};
            while (right < width)
            {
                if (currentRow[right] == 1)
                    break;
                if (currentRow[right] <= 0)
                {
                    currentRow[right] += splitWater;
                    break;
                }
                right++;
            }
        }

        rowAbove = currentRow;
    }

    return getWaterPercentInSink(rowAbove);
}

int main()
{
    const auto v = waterfallStreams(
        {{0, 0, 0, 0, 0, 0, 0},
         {1, 0, 0, 0, 0, 0, 0},
         {0, 0, 1, 1, 1, 0, 0},
         {0, 0, 0, 0, 0, 0, 0},
         {1, 1, 1, 0, 0, 1, 0},
         {0, 0, 0, 0, 0, 0, 1},
         {0, 0, 0, 0, 0, 0, 0}},
        3);
    return 0;
}