#include<stdio.h>
#include"Dispatcher.h"
#include"BuffWithLock.h"

void Dispatcher(void *)
{
    unsigned int wait_time;
    while(true)
    {
        if(BuffWithLock::IsAllEmpty() == true)
        {
            Sleep(500);
        }
        wait_time = left.FlashBuff();
        if(wait_time > 0)
        {
            printf("flash left road vehicles\n");
            Sleep(wait_time * 100);
        }
        wait_time = right.FlashBuff();
        if(wait_time > 0)
        {
            printf("flash right road vehicles\n");
            Sleep(wait_time * 100);
        }
    }
}