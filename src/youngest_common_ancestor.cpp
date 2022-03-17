#include <vector>
#include <math.h>

using namespace std;

class AncestralTree
{
public:
    char name;
    AncestralTree *ancestor;

    AncestralTree(char name)
    {
        this->name = name;
        this->ancestor = nullptr;
    }

    void addAsAncestor(vector<AncestralTree *> descendants);
};

AncestralTree *getYoungestCommonAncestor(AncestralTree *topAncestor,
                                         AncestralTree *descendantOne,
                                         AncestralTree *descendantTwo)
{
    // Find depth of descendantOne
    int descendantOneDepth = 0;
    auto current = descendantOne;
    while (current != topAncestor)
    {
        current = current->ancestor;
        descendantOneDepth++;
    }

    // Find depth of descendantTwo
    int descendantTwoDepth = 0;
    current = descendantTwo;
    while (current != topAncestor)
    {
        current = current->ancestor;
        descendantTwoDepth++;
    }

    auto toBeAscended = descendantOneDepth > descendantTwoDepth ? descendantOne : descendantTwo;
    auto other = descendantOneDepth <= descendantTwoDepth ? descendantOne : descendantTwo;
    int stepsToAscend = abs(descendantOneDepth - descendantTwoDepth);

    while (stepsToAscend != 0)
    {
        stepsToAscend--;
        toBeAscended = toBeAscended->ancestor;
    }

    while(other) {
        if(other == toBeAscended) break;
        other = other->ancestor;
        toBeAscended=toBeAscended->ancestor;
    }

    return other;
}
