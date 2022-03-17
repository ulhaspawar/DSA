#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

using mat_el = pair<int, int>;
using matrix = vector<vector<int>>;

queue<mat_el> getPositiveElementPos(const matrix &m);
vector<mat_el> getNegativeElementPos(const matrix &m);
const vector<mat_el> getNegativeNeigbours(const mat_el pos, const matrix &m);
inline void makePositive(matrix &m, const mat_el pos);

int minimumPassesOfMatrix(matrix m)
{
    auto negatives{getNegativeElementPos(m)};
    auto positives{getPositiveElementPos(m)};
    int numOfPasses{0};

    while (!positives.empty())
    {

        vector<mat_el> negativeNeigbours;
        while (!positives.empty())
        {
            const auto positiveEl = move(positives.front());
            positives.pop();

            for (const auto &negNeigbour : getNegativeNeigbours(positiveEl, m))
            {
                if (find(cbegin(negativeNeigbours), cend(negativeNeigbours), negNeigbour) == cend(negativeNeigbours))
                    negativeNeigbours.push_back(negNeigbour);
            }
        }

        if (!negativeNeigbours.empty())
            numOfPasses++;

        while (!negativeNeigbours.empty())
        {
            const auto negNeighbour = move(negativeNeigbours.back());
            negativeNeigbours.pop_back();
            makePositive(m, negNeighbour);
            negatives.erase(find(cbegin(negatives), cend(negatives), negNeighbour));
            positives.push(negNeighbour);
        }
    }

    return negatives.empty() ? numOfPasses : -1;
}

queue<mat_el> getPositiveElementPos(const matrix &m)
{
    queue<mat_el> positives;
    for (int r = 0; r < m.size(); r++)
        for (int c = 0; c < m[r].size(); c++)
            if (m[r][c] > 0)
                positives.emplace(r, c);
    return positives;
}

vector<mat_el> getNegativeElementPos(const matrix &m)
{
    vector<mat_el> negatives;
    for (int r = 0; r < m.size(); r++)
        for (int c = 0; c < m[r].size(); c++)
            if (m[r][c] < 0)
                negatives.emplace_back(r, c);
    return negatives;
}

const vector<mat_el> getNegativeNeigbours(const mat_el pos, const matrix &m)
{
    vector<mat_el> negativeNeighbours;
    const auto r = pos.first, c = pos.second;
    if (r > 0 and m[r - 1][c] < 0)
        negativeNeighbours.emplace_back(r - 1, c);
    if (r < m.size() - 1 and m[r + 1][c] < 0)
        negativeNeighbours.emplace_back(r + 1, c);
    if (c > 0 and m[r][c - 1] < 0)
        negativeNeighbours.emplace_back(r, c - 1);
    if (c < m[0].size() - 1 and m[r][c + 1] < 0)
        negativeNeighbours.emplace_back(r, c + 1);

    negativeNeighbours.shrink_to_fit();
    return negativeNeighbours;
}

inline void makePositive(matrix &m, const mat_el pos)
{
    m[pos.first][pos.second] *= -1;
}

int main()
{
    minimumPassesOfMatrix({{0, -1, -3, 2, 0}, {1, -2, -5, -1, -3}, {3, 0, 0, -4, -1}});
}
