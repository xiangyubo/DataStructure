#include<vector>

struct pos
{
	int x;
	int y;
	pos(int _x, int _y);
	bool operator == (const pos&) const;
	bool operator != (const pos&) const;
	pos operator + (const pos&) const;
};

struct node
{
	pos _pos;
	pos _pre;
	int from_sou;
	int to_des; 	
	node(pos &, int _f, int _t, pos pre = pos(-1, -1));
	bool operator < (const node &) const;
};

std::vector<pos> A_star(std::vector<std::vector<int>> &map, pos &sou, pos &des);
int pri_cal(std::vector<std::vector<int>> &map, pos &cur, pos &des);