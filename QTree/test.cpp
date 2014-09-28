#pragma execution_character_set("utf-8")
#include<iostream>
#include"QTree.h"
using namespace std;
const size_t N = 200;
int main()
{
	Rectangle rec(Position(0.0, 100.0), Position(100.0, 0.0));
	QTree phymap(rec);
    
    Position *dot[N];
	
    for(int i = 0; i < N; ++i)
	{
        cout<<i+(i*i)/19.0<<"   "<<i*(13*i%7) - 0.2*i<<endl;
		dot[i] = new Position(i+(i*i)/19.0, i*(13*i%7) - 0.2*i);
		phymap.insert(dot[i]);
	}
    cout<<"---------------------------"<<endl;
    auto ans = phymap.findInRect(rec);
    for(int i = 0; i < ans.size(); ++i)
    {
        cout<<ans[i].x<<"   "<<ans[i].y<<endl;
    }
    for(int i = 0; i < N; ++i)
	{
		phymap.remove(dot[i]);
	}
    for(int i = 0; i < N; ++i)
	{
		delete dot[i];
	}
	return 0;
}