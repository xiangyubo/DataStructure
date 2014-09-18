//基本坐标
struct Position
{
	double x;
	double y;
	Position(double _x = 0.0, double _y = 0.0):x(_x), y(_y){}
	inline bool operator == (const Position &pos) const
	{
		return x == pos.x && y == pos.y;
	}
};