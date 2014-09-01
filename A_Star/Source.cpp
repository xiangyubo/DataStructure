#include"A_star.h"
#include<iostream>
using namespace std;

void init_map(vector<vector<int>> &map)
{
	for(int i = 0; i < 6; ++i)
	{
		map.push_back(vector<int>());
		for(int j = 0; j < 8; ++j)
		{
			map[i].push_back(0);
		}
	}
	map[1][4] = map[2][4] = map[3][4] = 1;
}

int main()
{
	vector<vector<int>> map;
	init_map(map);
	vector<pos> ans = A_star(map, pos(2, 2), pos(2, 6));
	for(size_t i = 0; i < ans.size(); ++i)
	{
		cout<<"x:"<<ans[i].x<<"		y:"<<ans[i].y<<endl;
	}
	return 0;
}