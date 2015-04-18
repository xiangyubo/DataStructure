#pragma execution_character_set("utf-8")
#include <iostream>
#include "Entity.h"
#include "QuadTree.h"
using namespace std;

int main()
{
    Point leftUp(-1000, 1000);
    Point rightDown(1000, -1000);
    Rect world(leftUp, rightDown);
    QuadTree<Entity> *tree = new QuadTree<Entity>(world);
    
    Entity  entitys[10000];
    int lopNum = 10000;

    for(int i = 0; i < lopNum; ++i)
    {
        entitys[i].SetId(i);
        entitys[i].SetPos(rand()%1000, rand()%1000);
        tree->Insert(&entitys[i]);
    }

    auto res = tree->FindInArea(world);
    cout<<res.size()<<endl;

    cout<<"update:"<<endl;
    for(int i = 0; i < lopNum; ++i)
    {
        entitys[i].SetPos(rand()%1000, rand()%1000);
    }
    tree->Update();
    res = tree->FindInArea(world);
    cout<<res.size()<<endl;

    for(int i = 0; i < lopNum; ++i)
    {
        tree->Remove(&entitys[i]);
    }

    res = tree->FindInArea(world);
    cout<<res.size()<<endl;

    delete tree;
	return 0;
}