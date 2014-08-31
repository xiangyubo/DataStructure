#include"priority queue.h"
#include<iostream>
using namespace std;
int main()
{
	priority_queue test;
	for(int i = 12; i > 4; --i)
	{
		test.push_back(i);
	}
	test.print();
	cout<<test.get_front()<<endl;
	test.pop();
	test.pop();
	test.pop();
	for(int i = 3; i < 9; i++)
	{
		test.push_back(i);
	}
	test.print();
	cout<<test.cur_size()<<endl;
	return 0;
}