#include "CacheSystem.h"
#include <string>
#include <iostream>
using namespace std;

struct Data
{
    int x;
    float y;
    double z[100];
};

class CT : public CacheSystem<string, Data>
{
public:
    virtual Data LoadDataFrom(string key)
    {
        Data ret;
        ret.x = 1;
        ret.y = 10.0f;
        return ret;
    }
};

int main()
{
    CT test;
    Data *tt = test.GetData("xyb");
    cout<<tt->x<<tt->y<<endl;
    Data *tt1 = test.GetData("xyb");
    cout<<tt1->x<<tt1->y<<endl;
    test.ReturnData(tt);

    return 0;
}