#include"priority queue.h"
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
priority_queue::priority_queue()
{
	buff.push_back(-1);
}

priority_queue::~priority_queue()
{
	
}

bool priority_queue::is_empty()
{
	return buff.size() == 1;
}

void priority_queue::make_empyt()
{
	buff.empty();
	buff.push_back(-1);
}

int priority_queue::get_front()
{
	if(is_empty() == false)
	{
		return buff[1];
	}
}

int priority_queue::pop()
{
	if(is_empty() == false)
	{
		int res = get_front();
		buff.erase(buff.begin() + 1);
		modify();
		return res;
	}
}

void priority_queue::push_back(int val)
{
	buff.push_back(val);
	for(size_t index = buff.size() - 1; buff[index] < buff[index/2]; index /= 2)
	{
		swap(buff[index], buff[index/2]);
	}
}

size_t priority_queue::cur_size()
{
	return buff.size() - 1;
}

void priority_queue::print()
{
	print_node(1, "");
}

void priority_queue::modify()
{
	for(size_t index = buff.size()/2; index > 0; --index)
	{
		for(size_t ch, par = index; par*2 < buff.size(); par = ch)
		{
			ch = par * 2;
			if(ch + 1 < buff.size() && buff[ch] > buff[ch + 1])
			{
				ch = ch + 1;
			}
			if(buff[par] > buff[ch])
			{
				swap(buff[par], buff[ch]);
			}
		}
	}
}

void priority_queue::print_node(size_t index, char * prefix)
{
	if(index < buff.size())
	{
		cout<<prefix<<buff[index]<<endl;
		char *p = new char[3+strlen(prefix)];
		p[0] = '-'; p[1] = '-'; p[2] = '\0';
		print_node(index*2, strcat(p, prefix));
		print_node(index*2 + 1, p);
		delete[] p;
	}
}