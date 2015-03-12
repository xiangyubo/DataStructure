#include <iostream>
#include <windows.h>
#include "Timer.h"
using namespace std;

#include "MemoryPool.h"

class CTest
{
public:
    int m_n;
    int m_n1;

    void* operator new(size_t size)
    {
        void* p = s_pool->Alloc(size);
        return p;
    }

    void operator delete(void* p, size_t size)
    {
        s_pool->Free(p);
    }

    static void NewPool()
    {
        s_pool = new CMemoryPool<CTest>;
    }

    static void DeletePool()
    {
        delete s_pool;
        s_pool = NULL;
    }
    
    static CMemoryPool<CTest>* s_pool;
};

CMemoryPool<CTest>* CTest::s_pool = NULL;

class Test
{
private:
    int m_n;
    int m_n1;
};

void testFun()
{
    int i;
    const int nLoop = 10000;
    const int nCount = 10000;
    
    for(int j = 0; j<nLoop; ++j)
    {
        typedef CTest* LPTest;
        LPTest arData[nCount];
        for(i=0;i <nCount; ++i)
        {
            arData[i] = new CTest;
        }

        for(i=0;i <nCount; ++i)
        {
            delete arData[i];
        }
    }
}

int main(int argc, char* argv[])
{
    Timer timer;
    Timer::InitTimer();
    {
        unsigned int dwStartTickCount = GetTickCount();
        timer.GetDelta();
        CTest::NewPool();

        testFun();
        
        CTest::DeletePool();
        
        cout << "total cost:" << timer.GetDelta()<< endl;
    }

    {
        Test *arr[10000];
        unsigned int dwStartTickCount = GetTickCount();

        timer.GetDelta();
        for(int i = 0; i < 10000; ++i)
        {
            for(int j = 0; j < 10000; ++j)
            {
                arr[j] = new Test;
            }
            for(int j = 0; j < 10000; ++j)
            {
                delete arr[j];
            }
        }
        
        cout << "total cost:" << timer.GetDelta()<< endl;
    
    
    }
    system("pause");

    return 0;
}