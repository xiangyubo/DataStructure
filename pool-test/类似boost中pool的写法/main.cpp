#include <iostream>
#include "Pool.h"
#include "Timer.h"
using namespace std;;

class Point
{
    float x;
    float y;
    float z;
};

int main()
{
    Pool<sizeof(Point)> pool;
    Point *arr[10000];
    Timer timer;
    Timer::InitTimer();

    cout<<"创建若干";
    timer.GetDelta();
    for(int j = 0; j < 10000; ++j)
    {
        for(int i = 0; i < 10000; ++i)
        {
            arr[i] = new (pool.Malloc())Point;
        }
        for(int i = 0; i < 10000; ++i)
        {
            pool.Free(arr[i]);
        }
    }
    cout<<"耗时："<<timer.GetDelta()<<endl;
    return 0;
}