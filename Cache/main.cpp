#include "CacheSystem.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;

struct Data
{
    int x[3000];
    float y[2000];
    double z[1000];
};

class CT : public CacheSystem<int, Data>
{
public:
    virtual Data LoadDataFrom(int key)
    {
        Data ret;
        ret.x[0] = rand()%100;
        ret.y[0] = rand()+100;
        return ret;
    }
};

int main()
{
    CT test;
    int index[3000];
    for(int i = 0; i < 3000; ++i)
    {
        index[i] = rand();
        Data *tt = test.GetData(index[i]);
    }

    for(int i = 0; i < 1000; ++i)
    {
        for(int j = 0; j < 3000; ++j)
        {
            int k = rand()%30;
            Data *tt = test.GetData(index[k]);
        }
    }
    Data *tt = test.GetData(100);
    cout<<tt->x<<tt->y<<endl;
    Data *tt1 = test.GetData(100);
    cout<<tt1->x<<tt1->y<<endl;
    test.ReturnData(tt);

    return 0;
}