#include"A_star.h"
#include<queue>
#include<algorithm>
using std::vector;
using std::priority_queue;

pos direction[8] = 
{
	pos(0,1),
	pos(1, 1),
	pos(1, 0),
	pos(1, -1),
	pos(0, -1),
	pos(-1, -1),
	pos(-1, 0),
	pos(-1, 1)
};

pos::pos(int _x, int _y):x(_x), y(_y)
{

}

bool pos::operator == (const pos& p) const
{
	return x == p.x && y == p.y;
}

bool pos::operator != (const pos& p) const
{
	return !(*this == p);
}

pos pos::operator + (const pos& p) const
{
	return pos(x + p.x, y + p.y);
}

node::node(pos &p, int _f, int _t, pos pre):_pos(p), from_sou(_f), to_des(_t), _pre(pre)
{
	
}

bool node::operator < (const node &_node) const
{
	return from_sou + to_des > _node.from_sou + _node.to_des;
}

void init_close_list(vector<vector<bool>> &close_list, size_t n, size_t m)
{
	for(size_t i = 0; i < n; ++i)
	{
		close_list.push_back(vector<bool>());
		for(size_t j = 0; j < m; ++j)
		{
			close_list[i].push_back(false);
		}
	}
}

void init_ans_link(vector<vector<pos>> &ans_link, size_t n, size_t m)
{
	for(size_t i = 0; i < n; ++i)
	{
		ans_link.push_back(vector<pos>());
		for(size_t j = 0; j < m; ++j)
		{
			ans_link[i].push_back(pos(-1, -1));
		}
	}
}

int pri_cal(vector<vector<int>> &map, pos &cur, pos &des)
{
	int tmpx = cur.x - des.x;
	int tmpy = cur.y - des.y;
	return (abs(tmpx) + abs(tmpy)) * 10;
}

pos move_to(pos &sou, pos dir)
{
	return sou + dir;
}

bool can_visit(vector<vector<int>> &map, vector<vector<bool>> &close_list, pos &p)
{
	if(p.x >= map.size() || p.y >= map[0].size())
	{
		return false;
	}
	if(map[p.x][p.y] == 1)
	{
		return false;
	}
	return close_list[p.x][p.y] == false;
}

vector<pos> A_star(vector<vector<int>> &map, pos &sou, pos &des)
{
	vector<pos> ans;
	priority_queue<node> search_list;
	vector<vector<bool>> close_list;
	vector<vector<pos>> ans_link;

	init_close_list(close_list, map.size(), map[0].size());
	init_ans_link(ans_link, map.size(), map[0].size());
	search_list.push(node(sou, 0, pri_cal(map, sou, des)));
	close_list[sou.x][sou.y] = true;

	while(search_list.empty() != true)
	{
		node cur = search_list.top();
		search_list.pop();
		if(cur._pos == des)
		{
			pos end(-1, -1);
			for(pos temp = cur._pos; ans_link[temp.x][temp.y] != end; temp = ans_link[temp.x][temp.y])
			{
				ans.push_back(temp);
			}
			ans.push_back(sou);
			reverse(ans.begin(), ans.end());
			break;
		}
		else
		{
			for(int i = 0; i < 8; ++i)
			{
				pos temp = move_to(cur._pos, direction[i]);
				if(can_visit(map, close_list, temp) == true)
				{
					close_list[temp.x][temp.y] = true;
					ans_link[temp.x][temp.y] = pos(cur._pos);
					if(i == 1 || i == 3 || i == 5 || i == 7)	//走斜线
					{
						search_list.push(node(temp, cur.from_sou + 15, pri_cal(map, temp, des)));
					}
					else		//走直线
					{
						search_list.push(node(temp, cur.from_sou + 10, pri_cal(map, temp, des)));
					}
				}
			}
		}
	}
	return ans;
}