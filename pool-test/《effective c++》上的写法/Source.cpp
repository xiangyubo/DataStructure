#include<iostream>
#include<string>
#include<vector>
#include"Timer.h"
#include"object_pool.h"
using namespace std;

class Person:public object_pool<Person>
{
public:
    Person(string _name = "nobody"){}
    string get_name() const
    {
        return name;
    }
private:
    string name;
    vector<float> data;
};


class TPerson
{
public:
    TPerson(string _name = "nobody"){}
private:
    string  name;
    vector<float> data;
};

int main()
{
    Person *arry[10000];

    Timer timer;
    Timer::InitTimer();

    cout<<"创建若干个Person";
    timer.GetDelta();
    for(int j = 0; j < 10000; j++)
    {
        for(int i = 0; i < 10000; ++i)
        {
            arry[i] = new Person;
        }
        for(int i = 0; i < 10000; ++i)
        {
            delete arry[i];
        }
    }
    cout<<"耗时"<<timer.GetDelta()<<endl;

    TPerson *arry1[10000];
    cout<<"创建若干个TPerson";
    timer.GetDelta();
    for(int j = 0; j < 10000; ++j)
    {
        for(int i = 0; i < 10000; ++i)
        {
            arry1[i] = new TPerson;
        }
        for(int i = 0; i < 10000; ++i)
        {
            delete arry1[i];
        }
    }
    cout<<"耗时"<<timer.GetDelta()<<endl;

    return 0;
}