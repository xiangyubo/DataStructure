#ifndef __TIMER__
#define __TIMER__

#include <Windows.h>
#include <cstdint>

class Timer
{
private:
    BOOL    isPause;        //�Ƿ���ͣ
    LARGE_INTEGER time;     //ϵͳ����ʱ��
    uint64_t lastTime;      //��һ�μ�¼ʱ���ʱ��
    float scale;            //ʱ�����ű���
    static double Freq;     //ͳһϵͳʱ��Ƶ��

public:
    Timer():isPause(false), scale(1.0f)
    {
        QueryPerformanceCounter(&time);
        lastTime = time.QuadPart;
    }

    ~Timer(){}

    void SetScale(float _scale)
    {
        scale = _scale;
    }

    float GetScale()
    {
        return scale;
    }

    void SetPause(BOOL pau)
    {
        isPause = pau;
    }

    BOOL IsPause()
    {
        return isPause;
    }

    //��ʼ����ʱ��ͳһʱ��Ƶ��
    static bool InitTimer()
    {
        LARGE_INTEGER _time;
        if(!QueryPerformanceFrequency(&_time))
        {
            return false;
        }

        Freq = double(_time.QuadPart)/1000.0;

        return true;
    }

    //���ͬһ����ʱ��������һ�ζ�ʱ��ʱ��
    double GetDelta()
    {
        QueryPerformanceCounter(&time);
        double delta = double(time.QuadPart - lastTime)/Freq;
        lastTime = time.QuadPart;
        if(isPause == TRUE)
        {
            return 0.0;
        }
        return delta * scale;
    }

    //��úͲ�ͬ��ʱ��֮���ʱ��
    double GetDelta(const Timer &t)
    {
        QueryPerformanceCounter(&time);
        double delta = double(time.QuadPart - t.lastTime )/Freq;
        lastTime = time.QuadPart;
        if(isPause == TRUE)
        {
            return 0.0;
        }
        return delta * scale;
    }
};

#endif