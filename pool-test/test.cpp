#pragma execution_character_set("utf-8")
#include"EntityPool.h"
#include"DataType.h"
#include<iostream>
using namespace std;
int main()
{
	Pool<Position> pool;
	for(int id = 0; id < 200; ++id)
	{
		pool.add_with_id(id, Position(id+(id*id)/19.0, id*(13*id%7) - 0.2*id));
	}

	Position temp = pool.get_by_id(128);
	cout<<"x:"<<temp.x<<" y:"<<temp.y<<endl;

	pool.set_by_id(128, Position(100.0, 100.0));

	temp = pool.get_by_id(128);
	cout<<"x:"<<temp.x<<" y:"<<temp.y<<endl;

	for(int id = 0; id < 100; ++id)
	{
		Position temp(pool.get_by_id(id));
		cout<<"x:"<<temp.x<<" y:"<<temp.y<<endl;
	}
	for(int id = 0; id < 100; ++id)
	{
		pool.remove_by_id(id);
	}
	for(int id = 100; id < 200; ++id)
	{
		Position temp(pool.get_by_id(id));
		cout<<"x:"<<temp.x<<" y:"<<temp.y<<endl;
	}
	return 0;
}