#include"Vehicle.h"
#include<stdio.h>

void ModelingTraffic(void *road)
{
    int interval;
    BuffWithLock *road_traffic = (BuffWithLock*)road;
    while(true)
    {
        interval = rand();
        Sleep(interval%30);
        road_traffic->EnterOne();
        printf("inter an vehicle\n");
    }
}