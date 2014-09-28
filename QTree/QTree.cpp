#include"QTree.h"
QTree::Node::Node(const Rectangle &rec, Node *p, Count c):
    area(rec), parent(p), count(c)	//��������Ľڵ�Ĭ�϶���Ҷ��
{
	sub_area[lu] = sub_area[ru] = sub_area[rd] = sub_area[ld] = nullptr;
}

QTree::Node::~Node()
{
	parent = nullptr;
	delete sub_area[lu];
	delete sub_area[ru];
	delete sub_area[rd];
	delete sub_area[ld];
}

QTree::QTree(const Rectangle &rec)	//�Ĳ�����Ҫ��ͼ��С�����Σ�����ʼ��
{
	root = new Node(rec, nullptr);
}

QTree::~QTree()
{
	delete root;
}

void QTree::insert(Position *pos)
{
	if(root->area.is_contain(*pos) == true)
	{
		insert(pos, *root);
	}
}

void QTree::insert(Position *pos, Node &r)
{
	if(r.is_leaf() == false)	//������Ҷ�ӣ���ô�϶����ܲ��룬ֻ�ܲ���������һ������������
	{
		for(int dir = lu; dir <= ld; ++dir)
		{
            if(r.sub_area[dir]->area.is_contain(*pos) == true)
			{
				insert(pos, *r.sub_area[dir]);
				break;
			}
		}
	}
    else	//Ҷ�ӽڵ㣬��ʵ���������
    {
        r.entitys.push_back(pos);
        if(r.is_full() == true)     //������Ҷ�ӽڵ�洢����
        {
            for(int dir = lu; dir <= ld; ++dir)
            {
                r.sub_area[dir] = new Node(cut_rect(r.area, static_cast<Direct>(dir)), &r);
                for(auto it = r.entitys.begin(); it != r.entitys.end(); )
                {
                    if(r.sub_area[dir]->area.is_contain(**it) == true)
                    {
                        insert(&**it, *r.sub_area[dir]);
                        it = r.entitys.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            r.entitys.clear();
        }
	}
}

void QTree::remove(Position *pos)
{
	remove(pos, *root);
}

void QTree::remove(Position *pos, Node &r)
{
    if(r.area.is_contain(*pos) == false)
    {
        return ;
    }
    auto it = r.find_entity(*pos);
    if(it != r.entitys.end())
	{
        r.erase_entity(it);
		adjust(r);
	}
	else if(r.is_leaf() == false)
	{
		for(int dir = lu; dir <= ld; ++dir)
		{
			if(r.sub_area[dir]->area.is_contain(*pos) == true)
			{
				remove(pos, *r.sub_area[dir]);
				break;
			}
		}
	}
}

std::vector<Position> QTree::findInRect(const Rectangle &rt)
{
    std::vector<Position> ret;
    find_in_node(*root, rt, ret);
    return ret;
}

void QTree::find_in_node(const Node &r, const Rectangle &rt, std::vector<Position> &ret)
{
    if(r.area.is_intersect(rt) == true)
    {
        if(r.is_leaf() == true)
        {
            for(auto it = r.entitys.begin(); it != r.entitys.end(); ++it)
            {
                if(rt.is_contain(**it) == true)
                {
                    ret.push_back(**it);
                }
            }
        }
        else
        {
            for(int i = lu; i <= ld; ++i)
            {
                find_in_node(*r.sub_area[i], rt, ret);
            }
        }
    }
}

void QTree::adjust(Node &r)
{
    if(r.parent == nullptr || r.is_empty() != true)	//Ҷ�ӽڵ㻹�洢��ʵ������Ѿ����������ˣ������ٽ�
	{
		return ;
	}
    Node *p = r.parent;
	bool flag = true;
	for(int dir = lu; dir <= ld; ++dir)
	{
        if(p->sub_area[dir]->is_leaf() != true || p->sub_area[dir]->is_empty() != true)
		{
			flag = false;
			break;
		}
	}
	if(flag == true)		//�м�ڵ㽵��ΪҶ�ӽڵ�
	{
		for(int dir = lu; dir <= ld; ++dir)
		{
			delete p->sub_area[dir];
			p->sub_area[dir] = nullptr;
		}
		adjust(*p);
	}
}