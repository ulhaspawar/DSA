#include <vector>
#include <unordered_map>

using namespace std;

using input = vector<vector<int>>;

class point
{
public:
    int x;
    int y;
    point(const int _x, const int _y) : x(_x), y(_y) {}
    point(vector<int> p) : x(p[0]), y(p[1]) {}
};

using coordList = vector<point>;

class coordinates
{
private:
    void buildXMap(input coords);
    void buildYMap(input coords);

public:
    unordered_map<int, coordList> xMap;
    unordered_map<int, coordList> yMap;
    vector<point> coords;

    coordinates(input coordinates);

    coordList findP2(const point p1);
    coordList findP4(const point p1);
    coordList findP3(const point p2, const point p4);
};

coordinates::coordinates(input coords)
{
    buildXMap(coords);
    buildYMap(coords);

    for (const auto p : coords)
    {
        this->coords.push_back(p);
    }
}

void coordinates::buildXMap(input coords)
{
    for (const auto p : coords)
    {
        if (xMap.count(p[0]) == 0)
        {
            xMap.insert({p[0], {}});
        }
        xMap[p[0]].push_back({p});
    }
}

void coordinates::buildYMap(input coords)
{
    for (const auto p : coords)
    {
        if (yMap.count(p[1]) == 0)
        {
            yMap.insert({p[1], {}});
        }
        yMap[p[1]].push_back({p});
    }
}

coordList coordinates::findP2(point p1)
{
    coordList p2s;
    if (yMap.count(p1.y))
    {
        for (const auto p : yMap[p1.y])
        {
            if (p.x > p1.x)
            {
                p2s.push_back(p);
            }
        }
    }
    return p2s;
}

coordList coordinates::findP4(const point p1)
{
    coordList p4s;
    if (xMap.count(p1.x))
    {
        for (const auto p : xMap[p1.x])
        {
            if (p.y < p1.y)
            {
                p4s.push_back(p);
            }
        }
    }
    return p4s;
}

coordList coordinates::findP3(const point p2, const point p4)
{
    coordList p3s;

    if (xMap.count(p2.x) > 0)
    {
        if (yMap.count(p4.y) > 0)
        {
            for (auto p : xMap[p2.x])
                if (p.x > p4.x and p.y == p4.y)
                {
                    p3s.push_back(p);
                }
        }
    }

    return p3s;
}

int rectangleMania(input coords)
{
    int count{0};

    coordinates c{coords};

    for (const auto p1 : c.coords)
    {
        const auto p2s = c.findP2(p1);
        if (p2s.empty())
            continue;
        const auto p4s = c.findP4(p1);
        if (p4s.empty())
            continue;
        
        for(const auto p2:p2s) {
            for(const auto p4: p4s) {
                const auto p3s = c.findP3(p2, p4);
                count+=p3s.size();
            }
        }
    }

    return count;
}


int main(){
    rectangleMania({{0,0},{0,1},{1,1},{1,0},{2,1},{2,0},{3,1},{3,0}});
    return 0;
}