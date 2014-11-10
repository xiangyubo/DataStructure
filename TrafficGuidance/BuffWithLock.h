#ifndef _BUFF_WITH_LOCK_
#define _BUFF_WITH_LOCK_

#include<Windows.h>

struct BuffWithLock
{
    static unsigned int total;
    static CRITICAL_SECTION cs;
    static bool IsAllEmpty();

    HANDLE  semaphore;
    unsigned int        in_use;
    const unsigned int  buff_size;

    BuffWithLock(unsigned int size);
    ~BuffWithLock();
    unsigned int FlashBuff();
    void EnterOne();
};

#endif