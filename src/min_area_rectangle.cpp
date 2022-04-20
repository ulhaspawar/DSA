#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <math.h>

using namespace std;

struct point
{
    int x, y;
    point(int _x, int _y) : x(_x), y(_y) {}
    string key() const
    {
        return to_string(x) + "_" + to_string(y);
    }
};

using neighbours = unordered_map<string, vector<point>>;

struct rectangle
{
    point tl, br;
    rectangle(point _tl, point _br) : tl(_tl), br(_br) {}
    int area() const
    {
        const int height = abs(tl.y - br.y);
        const int width = abs(br.x - tl.x);
        return height * width;
    }
};

neighbours getHorizontalNeighbours(vector<point> &points);
neighbours getVerticalNeighbours(vector<point> &points);
vector<point> toPoint(vector<vector<int>> &points);
vector<rectangle> getRects(vector<point> &points, neighbours &horizNeighbour, neighbours &vertNeighbours);

int minimumAreaRectangle(vector<vector<int>> points)
{
    auto pts = toPoint(points);
    auto hNeighbours = getHorizontalNeighbours(pts);
    auto vNeighbours = getVerticalNeighbours(pts);

    auto rects = getRects(pts, hNeighbours, vNeighbours);

    int minArea = numeric_limits<int>::max();
    for (const auto &rect : rects)
    {
        const int area = rect.area();
        minArea = min(minArea, area);
    }

    return rects.size() > 0 ? minArea : 0;
}

//O(n^2)
vector<rectangle> getRects(vector<point> &points, neighbours &horizNeighbour, neighbours &vertNeighbours)
{
    vector<rectangle> rects;
    for (const auto &topLeftPt : points)
    {
        const auto tlKey = topLeftPt.key();
        const auto trCandidatePts = horizNeighbour[tlKey];
        const auto blCandidatePts = vertNeighbours[tlKey];

        for (const auto &topRightPt : trCandidatePts)
        {
            for (const auto &bottomLeftPt : blCandidatePts)
            {
                const auto brCandidatesPts = horizNeighbour[bottomLeftPt.key()];
                for (const auto &bottomRightPt : brCandidatesPts)
                    if (bottomRightPt.x == topRightPt.x)
                        rects.push_back({topLeftPt, bottomRightPt});
            }
        }
    }
    return rects;
}

//O(n^2)
neighbours getHorizontalNeighbours(vector<point> &points)
{
    neighbours n;
    for (const auto &p1 : points)
        for (const auto &p2 : points)
            if (p1.y == p2.y and p1.x < p2.x)
            {
                const auto key = p1.key();
                n[key].push_back(p2);
            }
    return n;
}

//O(n^2)
neighbours getVerticalNeighbours(vector<point> &points)
{
    neighbours n;
    for (const auto &p1 : points)
        for (const auto &p2 : points)
            if (p1.x == p2.x and p1.y > p2.y)
            {
                const auto key = p1.key();
                n[key].push_back(p2);
            }
    return n;
}

//O(n)
vector<point> toPoint(vector<vector<int>> &points)
{
    vector<point> pts;
    for (const auto &p : points)
        pts.push_back(point(p[0], p[1]));
    return pts;
}

int main()
{
    auto result = minimumAreaRectangle({{1, 5}, {5, 1}, {4, 2}, {2, 4}, {2, 2}, {1, 2}, {4, 5}, {2, 5}, {-1, -2}});
    return 0;
}
