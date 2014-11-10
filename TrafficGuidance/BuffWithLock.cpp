#include"BuffWithLock.h"

unsigned int BuffWithLock::total = 0;
CRITICAL_SECTION BuffWithLock::cs;

BuffWithLock::BuffWithLock(unsigned int size):buff_size(size), in_use(0)
{
    semaphore = CreateSemaphore(NULL, buff_size, buff_size, NULL);
    InitializeCriticalSection(&cs);
    SetCriticalSectionSpinCount(&cs, 1000);
}

void BuffWithLock::EnterOne()
{
    WaitForSingleObject(semaphore, INFINITE);
    EnterCriticalSection(&cs);
    ++in_use;
    ++total;
    LeaveCriticalSection(&cs);
}

bool BuffWithLock::IsAllEmpty()
{
    bool res = false;
    EnterCriticalSection(&cs);
    if(total == 0)
    {
        res = true;
    }
    else
    {
        res = false;
    }
    LeaveCriticalSection(&cs);
    return res;
}

unsigned int BuffWithLock::FlashBuff()
{
    EnterCriticalSection(&cs);
    unsigned int res = in_use;
    total -= in_use;
    if(in_use != 0)
    {    
        ReleaseSemaphore(semaphore, in_use, NULL);
        in_use = 0;
    }   
    LeaveCriticalSection(&cs);
    return res;
}

BuffWithLock::~BuffWithLock()
{
    CloseHandle(semaphore);
}