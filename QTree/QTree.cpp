#include"QTree.h"
QTree::Node::Node(const Rectangle rec, Node *p):
	area(rec), entity(nullptr), parent(p)	//��������Ľڵ�Ĭ�϶���Ҷ��
{
	sub_area[lu] = sub_area[ru] = sub_area[rd] = sub_area[ld] = nullptr;
}

QTree::Node::~Node()
{
	entity = nullptr;
	parent = nullptr;
	delete sub_area[lu];
	delete sub_area[ru];
	delete sub_area[rd];
	delete sub_area[ld];
}

QTree::QTree(const Rectangle rec)	//�Ĳ�����Ҫ��ͼ��С�����Σ�����ʼ��
{
	root = new Node(rec, nullptr);
}

QTree::~QTree()
{
	delete root;
}

void QTree::insert(Position *pos)
{
	if(is_contain(root->area, pos) == true)
	{
		insert(pos, *root);
	}
}

void QTree::insert(Position *pos, Node &r)
{
	if(is_leaf(r) == false)	//������Ҷ�ӣ���ô�϶����ܲ��룬ֻ�ܲ���������һ������������
	{
		for(int dir = lu; dir <= ld; ++dir)
		{
			if(is_contain(r.sub_area[dir]->area, pos) == true)
			{
				insert(pos, *r.sub_area[dir]);
				break;
			}
		}
	}
	else if(r.entity != nullptr)	//Ҷ�ӽڵ㣬�����Ѿ��洢��һ��ʵ�壬��Ҫ�����Ҷ���������м�ڵ�
	{								//Ȼ���ٵݹ�Ĳ���ԭ�е�ʵ����µ�ʵ��
		for(int dir = lu; dir <= ld; ++dir)
		{
			r.sub_area[dir] = new Node(cut_rect(r.area, static_cast<Direct>(dir)), &r);
			if(is_contain(r.sub_area[dir]->area, pos) == true)
			{
				insert(pos, *r.sub_area[dir]);
			}
			if(is_contain(r.sub_area[dir]->area, r.entity) == true)
			{
				insert(r.entity, *r.sub_area[dir]);
			}
		}
		r.entity = nullptr;
	}
	else	//Ҷ�ӽڵ㣬����û�д洢ʵ�壬ֱ�Ӵ洢ʵ��
	{
		r.entity = pos;
	}
}

void QTree::remove(Position *pos)
{
	remove(pos, *root);
}

void QTree::remove(Position *pos, Node &r)
{
	if(r.entity != nullptr && r.entity == pos)
	{
		r.entity = nullptr;
		adjust(r);
	}
	else if(is_leaf(r) == false)
	{
		for(int dir = lu; dir <= ld; ++dir)
		{
			if(is_contain(r.sub_area[dir]->area, pos) == true)
			{
				remove(pos, *r.sub_area[dir]);
				break;
			}
		}
	}
}

void QTree::adjust(Node &r)
{
	Node *p = r.parent;
	if(p == nullptr)	//�Ѿ����������ˣ������ٽ�
	{
		return ;
	}
	bool flag = true;
	for(int dir = lu; dir <= ld; ++dir)
	{
		if(is_leaf(*p->sub_area[dir]) != true || p->sub_area[dir]->entity != nullptr)
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