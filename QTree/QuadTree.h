#ifndef __QUAD_TREE__
#define __QUAD_TREE__
#pragma execution_character_set("utf-8")
//*************************************
//  QuadTree四叉树类，对外提供统一接口
//  内部使用自定义QTreeNode类作为节点。
//*************************************

#include <list>
#include <vector>
#include <map>
#include "BasicType.h"

//*************************************
//  QTreePos结构体，作为QTreeNode存储的
//  类型。内部有所在QTreeNode管辖区域的
//  指针，以及对应实体的指针，支持延迟
//  更新。
//*************************************
template<typename T>
struct QTreePos : public Point
{
    //前一次所在的矩形区域指针，
    //指向四叉树节点的区域变量
    Rect    *rect;

    //坐标对应的实体指针
    T       *entity;

    QTreePos(T *_e):entity(_e)
    {
        x = entity->GetPos().x;
        y = entity->GetPos().y;
    } 

    void InitRect(Rect *r)
    {
        rect = r;
    }

    bool StillThere()
    {
        return rect->IsContain(entity->GetPos());
    }

    void Update()
    {
        Point::operator=(entity->GetPos());
    }

    bool operator == (Point &pos) 
    {
        return Point::operator==(pos);
    }

    Point GetPos()
    {
        return *this;
    }
};

template<typename T>
class QuadTree
{
protected:
    //*************************************
    //  QTreeNode类，QuadTree内部类型，四叉
    //  树节点类型。有管辖区域、QTreePos链
    //  表、父节点、所在四叉树、子节点等属
    //  性。递归实现插入\调整，配合四叉树实
    //  现节点内部直接删除。
    //*************************************
    template<typename U>
    class QTreeNode
    {
    public:
        //插入标志枚举类型
        enum InsertFlag
        {
            //插入新节点，使用entity的位置信息
            InsertPos = 0,

            //更新时候插入节点
            ReInsert = 1    
        };

    private:
        //四个象限方向枚举类型
        enum Direct
        {
            //左上方
            LeftUp = 0,

            //右上方
            RightUp = 1,

            //右下方
            RightDown = 2,

            //左下方
            LeftDown = 3
        };

        typedef std::list<QTreePos<U>*> Entities;
    private:
        //节点管理的区域
        Rect        area;

        //管理的entity链表
        Entities    entitys;

        //父节点，用于删除之后调整
        QTreeNode   *parent;

        //节点所属的四叉树
        QuadTree<T> *tree;

        //子区域
        QTreeNode   *subAreas[4];

        //叶子标志
        bool        isLeaf;

        //entitys链表最大长度
        static int count;

    public:
        QTreeNode(Rect &r, QuadTree<U> *tr, QTreeNode *par = nullptr):
            area(r), tree(tr), parent(par)
        {
            subAreas[LeftUp] = nullptr;
            subAreas[RightUp] = nullptr;
            subAreas[RightDown] = nullptr;
            subAreas[LeftDown] = nullptr;
            isLeaf = true;
        }

        ~QTreeNode()
        {
            ClearEntity();
            parent = nullptr;
            delete subAreas[LeftUp];
            delete subAreas[RightUp];
            delete subAreas[RightDown];
            delete subAreas[LeftDown];
        }

        //递归插入QTreePos<T>类型节点，
        void Insert(QTreePos<U> *pos, int flag)
        {
            Point location;
            if(flag == InsertPos)
            {
                location = pos->entity->GetPos();
            }
            else
            {
                location = pos->GetPos();
            }
            
            //不在这个区域则直接返回
            if(area.IsContain(location) != true)
            {
                return ;
            }
            if(IsLeaf() == true)
            {
                entitys.push_back(pos);
                pos->InitRect(&area);
                tree->findTable[pos->entity] = this;
                if(IsFull() == true)
                {
                    for(int i = LeftUp; i <= LeftDown; ++i)
                    {
                        if(subAreas[i] == nullptr)
                        {
                            subAreas[i] = new QTreeNode(CutRect(area, i), tree, this);
                        }
                        for(auto it = entitys.begin(); it != entitys.end(); )
                        {
                            if(subAreas[i]->area.IsContain(**it) == true)
                            {
                                subAreas[i]->Insert(*it, flag);
                                it = entitys.erase(it);
                            }
                            else
                            {
                                ++it;
                            }
                        }
                    }
                    isLeaf = false;
                }
            }
            else
            {
                for(int it = LeftUp; it <= LeftDown; ++it)
                {
                    subAreas[it]->Insert(pos, flag);
                }
            }
        }

        //直接删除T节点，配合QuadTree使用
        //支持热删除。删除时真正删除QTreePos
        void Remove(T *ptr) 
        {
            for(auto it = entitys.begin(); 
                it != entitys.end(); ++it)
            {
                if((*it)->entity == ptr)
                {
                    delete *it;
                    entitys.erase(it);
                    Adjust(this);
                    break;
                }
            }
        }

        //在所有T节点坐标更新后调用，更新整个QuadTree
        void Update()
        {
            if(IsLeaf() == true)
            {
                for(auto it = entitys.begin(); 
                    it != entitys.end(); )
                {
                    (*it)->Update();
                    if((*it)->StillThere() == false)
                    {
                        tree->root->Insert(*it, ReInsert);
                        it = entitys.erase(it);
                        Adjust(this);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            else
            {
                for(int i = LeftUp; i <= LeftDown; ++i)
                {
                    if(subAreas[i] != nullptr)
                    {
                        subAreas[i]->Update();
                    }
                }
            }
        }

        //找到某个区域内的所有T节点
        void FindInArea(Rect &rect, std::vector<U*> &ans)
        {
            if(area.IsIntersect(rect) == true)
            {
                if(IsLeaf() == true)
                {
                    for(auto it = entitys.begin(); it != entitys.end(); ++it)
                    {
                        if(rect.IsContain(**it) == true)
                        {
                            ans.push_back((*it)->entity);
                        }
                    }
                }
                else
                {
                    for(int i = LeftUp; i <= LeftDown; ++i)
                    {
                        subAreas[i]->FindInArea(rect, ans);
                    }
                }
            }
        }

    private:
        //是否是叶子
        bool IsLeaf() 
        {
            return isLeaf;
        }

        //叶子节点是否存储满T节点
        bool IsFull()
        {
            return count < entitys.size();
        }

        //是否是空叶子节点
        bool IsEmpty() 
        {
            return entitys.size() == 0;
        }

        //递归调整四叉树，每次删除之后调用
        void Adjust(QTreeNode *ptr)
        {
            //叶子节点还存储有实体或者已经降级到根了，不能再降
            if(ptr->parent == nullptr || ptr->IsEmpty() != true)	
            {
                return ;
            }
            QTreeNode *p = ptr->parent;
            bool flag = true;
            for(int dir = LeftUp; dir <= LeftDown; ++dir)
            {
                if(p->subAreas[dir]->IsLeaf() != true || 
                    p->subAreas[dir]->IsEmpty() != true)
                {
                    flag = false;
                    break;
                }
            }
            if(flag == true)//中间节点降级为叶子节点
            {
                for(int dir = LeftUp; dir <= LeftDown; ++dir)
                {
                    p->isLeaf = true;
                }
                Adjust(p);
            }
        }

        //清除叶子节点中所有实体
        void ClearEntity()
        {
            for(auto it = entitys.begin(); it != entitys.end(); ++it)
            {
                delete *it;
            }
            entitys.clear();
        }

        //生成四个子区域，当叶子节点存储满实体时使用，给子节点分配管辖区域
        Rect CutRect(Rect &rec,  int dir)
        {
            Point center((rec.leftUp.x + rec.rightDown.x)/2, (rec.leftUp.y + rec.rightDown.y)/2);
            switch (dir)
            {
            case LeftUp:
                return Rect(rec.leftUp, center);
            case RightUp:
                return Rect(Point(center.x, rec.leftUp.y), Point(rec.rightDown.x, center.y));
            case RightDown:
                return Rect(center, rec.rightDown);
            case LeftDown:
                return Rect(Point(rec.leftUp.x, center.y), Point(center.x, rec.rightDown.y));
            }
        }
    };

private:
    //四叉树树根
    QTreeNode<T> *root;

    //entity在四叉树中查找表，用于支持热删除
    std::map<T*, QTreeNode<T>*> findTable;

public:
    QuadTree(Rect &rect)
    {
        root = new QTreeNode<T>(rect, this);
    }

    ~QuadTree()
    {
        delete root;
    }

    //插入T节点
    void Insert(T *ptr)
    {
        QTreePos<T> *pos = new QTreePos<T>(ptr);
        root->Insert(pos, QTreeNode<T>::InsertFlag::InsertPos);
    }

    //删除T节点
    void Remove(T *ptr)
    {
        if(findTable.find(ptr) != findTable.end())
        {
            QTreeNode<T> *node = findTable[ptr];
            node->Remove(ptr);
        }
    }

    //更新四叉树
    void Update()
    {
        root->Update();
    }

    //找到某个区域内的T节点
    std::vector<T*> FindInArea(Rect &rect)
    {
        std::vector<T*> ans;
        root->FindInArea(rect, ans);
        return ans;
    }
};

template<typename T>
template<typename U>
int  QuadTree<T>::QTreeNode<U>::count = 4;

#endif