#include"QTree.h"
int main()
{
	Rectangle rec(Position(0.0, 100.0), Position(100.0, 0.0));
	QTree phymap(rec);

	Position *dot[20];
	
	for(int i = 0; i < 20; ++i)
	{
		dot[i] = new Position(i+(i*i)/19.0, i*(13*i%7) - 0.2*i);
		phymap.insert(dot[i]);
	}
	for(int i = 0; i < 20; ++i)
	{
		phymap.remove(dot[i]);
	}
	
	return 0;
}