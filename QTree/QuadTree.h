#ifndef __QUAD_TREE__
#define __QUAD_TREE__
#pragma execution_character_set("utf-8")
//*************************************
//  QuadTree�Ĳ����࣬�����ṩͳһ�ӿ�
//  �ڲ�ʹ���Զ���QTreeNode����Ϊ�ڵ㡣
//*************************************

#include <list>
#include <vector>
#include <map>
#include "BasicType.h"

//*************************************
//  QTreePos�ṹ�壬��ΪQTreeNode�洢��
//  ���͡��ڲ�������QTreeNode��Ͻ�����
//  ָ�룬�Լ���Ӧʵ���ָ�룬֧���ӳ�
//  ���¡�
//*************************************
template<typename T>
struct QTreePos : public Point
{
    //ǰһ�����ڵľ�������ָ�룬
    //ָ���Ĳ����ڵ���������
    Rect    *rect;

    //�����Ӧ��ʵ��ָ��
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
    //  QTreeNode�࣬QuadTree�ڲ����ͣ��Ĳ�
    //  ���ڵ����͡��й�Ͻ����QTreePos��
    //  �����ڵ㡢�����Ĳ������ӽڵ����
    //  �ԡ��ݹ�ʵ�ֲ���\����������Ĳ���ʵ
    //  �ֽڵ��ڲ�ֱ��ɾ����
    //*************************************
    template<typename U>
    class QTreeNode
    {
    public:
        //�����־ö������
        enum InsertFlag
        {
            //�����½ڵ㣬ʹ��entity��λ����Ϣ
            InsertPos = 0,

            //����ʱ�����ڵ�
            ReInsert = 1    
        };

    private:
        //�ĸ����޷���ö������
        enum Direct
        {
            //���Ϸ�
            LeftUp = 0,

            //���Ϸ�
            RightUp = 1,

            //���·�
            RightDown = 2,

            //���·�
            LeftDown = 3
        };

        typedef std::list<QTreePos<U>*> Entities;
    private:
        //�ڵ���������
        Rect        area;

        //�����entity����
        Entities    entitys;

        //���ڵ㣬����ɾ��֮�����
        QTreeNode   *parent;

        //�ڵ��������Ĳ���
        QuadTree<T> *tree;

        //������
        QTreeNode   *subAreas[4];

        //Ҷ�ӱ�־
        bool        isLeaf;

        //entitys������󳤶�
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

        //�ݹ����QTreePos<T>���ͽڵ㣬
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
            
            //�������������ֱ�ӷ���
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

        //ֱ��ɾ��T�ڵ㣬���QuadTreeʹ��
        //֧����ɾ����ɾ��ʱ����ɾ��QTreePos
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

        //������T�ڵ�������º���ã���������QuadTree
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

        //�ҵ�ĳ�������ڵ�����T�ڵ�
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
        //�Ƿ���Ҷ��
        bool IsLeaf() 
        {
            return isLeaf;
        }

        //Ҷ�ӽڵ��Ƿ�洢��T�ڵ�
        bool IsFull()
        {
            return count < entitys.size();
        }

        //�Ƿ��ǿ�Ҷ�ӽڵ�
        bool IsEmpty() 
        {
            return entitys.size() == 0;
        }

        //�ݹ�����Ĳ�����ÿ��ɾ��֮�����
        void Adjust(QTreeNode *ptr)
        {
            //Ҷ�ӽڵ㻹�洢��ʵ������Ѿ����������ˣ������ٽ�
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
            if(flag == true)//�м�ڵ㽵��ΪҶ�ӽڵ�
            {
                for(int dir = LeftUp; dir <= LeftDown; ++dir)
                {
                    p->isLeaf = true;
                }
                Adjust(p);
            }
        }

        //���Ҷ�ӽڵ�������ʵ��
        void ClearEntity()
        {
            for(auto it = entitys.begin(); it != entitys.end(); ++it)
            {
                delete *it;
            }
            entitys.clear();
        }

        //�����ĸ������򣬵�Ҷ�ӽڵ�洢��ʵ��ʱʹ�ã����ӽڵ�����Ͻ����
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
    //�Ĳ�������
    QTreeNode<T> *root;

    //entity���Ĳ����в��ұ�����֧����ɾ��
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

    //����T�ڵ�
    void Insert(T *ptr)
    {
        QTreePos<T> *pos = new QTreePos<T>(ptr);
        root->Insert(pos, QTreeNode<T>::InsertFlag::InsertPos);
    }

    //ɾ��T�ڵ�
    void Remove(T *ptr)
    {
        if(findTable.find(ptr) != findTable.end())
        {
            QTreeNode<T> *node = findTable[ptr];
            node->Remove(ptr);
        }
    }

    //�����Ĳ���
    void Update()
    {
        root->Update();
    }

    //�ҵ�ĳ�������ڵ�T�ڵ�
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