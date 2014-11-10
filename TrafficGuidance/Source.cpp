#include<stdio.h>
#include<process.h>
#include"Vehicle.h"
#include"Dispatcher.h"

BuffWithLock left(10), right(10);

int main()
{
    HANDLE dispatcher = (HANDLE)_beginthread(Dispatcher,0, NULL);
    HANDLE left_road = (HANDLE)_beginthread(ModelingTraffic, 0, &left);
    HANDLE right_road = (HANDLE)_beginthread(ModelingTraffic, 0, &right);

    WaitForSingleObject(dispatcher, INFINITE);
    WaitForSingleObject(left_road, INFINITE);
    WaitForSingleObject(right_road, INFINITE);
    return 0;
}