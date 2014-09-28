enum Direct
{
	lu = 0,
	ru = 1,
	rd = 2,
	ld = 3
};

//基本坐标
struct Position
{
	double x;
	double y;
	Position(double _x = 0.0, double _y = 0.0):x(_x), y(_y){}
	inline bool operator = (const Position &pos) const
	{
		return x == pos.x && y == pos.y;
	}
};

//矩形
struct Rectangle
{
	Position lu;
	Position rd;
	Rectangle(const Position _lu, const Position _rd):lu(_lu), rd(_rd) {}
    inline bool isContain(const Position &pos) const
    {
        return lu.x <= pos.x && 
			lu.y >= pos.y &&
			rd.x >= pos.x && 
			rd.y <= pos.y;
    }
    inline bool isIntersect(const Rectangle &rt) const
    {
        Position ld(lu.x, rd.y);
        Position ru(rd.x, lu.y);
        Position rld(rt.lu.x, rt.rd.y);
        Position rru(rt.rd.x, rt.lu.y);

        return rt.isContain(ld) ||
            rt.isContain(lu) ||
            rt.isContain(rd) ||
            rt.isContain(ru) ||
            isContain(rld) ||
            isContain(rt.lu) ||
            isContain(rru) ||
            isContain(rt.rd);
    }
};

