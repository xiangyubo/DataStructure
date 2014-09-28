#include"TowerAlgorithm.h"
#include<iostream>
using namespace std;
const size_t N = 200;
int main()
{
    TowerMap xmap(10, 10, 10.0, 10.0);
    Position *dot[N];

    for(int i = 0; i < N; ++i)
	{
        cout<<i+(i*i)/19.0<<"   "<<i*(13*i%7) - 0.2*i<<endl;
		dot[i] = new Position(i+(i*i)/19.0, i*(13*i%7) - 0.2*i);
		xmap.insert(dot[i]);
	}
    cout<<"---------------------------"<<endl;
    auto ans = xmap.find_in_rect(Rectangle(Position(5.0, 5.0), Position(5.10, 5.10)));
    for(size_t i = 0; i < ans.size(); ++i)
    {
        cout<<ans[i].x<<"   "<<ans[i].y<<endl;
    }
    cout<<"---------------------------"<<endl;
    ans = xmap.find_in_rect(Rectangle(Position(25.0, 75.0), Position(75.0, 25.0)));
    for(size_t i = 0; i < ans.size(); ++i)
    {
        cout<<ans[i].x<<"   "<<ans[i].y<<endl;
    }
    for(int i = 0; i < N; ++i)
	{
		xmap.remove(dot[i]);
	}
    for(int i = 0; i < N; ++i)
    {
        delete dot[i];
    }
    return 0;
}