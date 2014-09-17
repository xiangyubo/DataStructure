#include"QTree.h"
QTree::Node::Node(const Rectangle rec, Node *p):
	area(rec), entity(nullptr), parent(p)	//构造出来的节点默认都是叶子
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

QTree::QTree(const Rectangle rec)	//四叉树需要地图大小（矩形）来初始化
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
	if(is_leaf(r) == false)	//若不是叶子，那么肯定不能插入，只能插入它其中一个子区域里面
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
	else if(r.entity != nullptr)	//叶子节点，但是已经存储了一个实体，需要把这个叶子升级成中间节点
	{								//然后再递归的插入原有的实体和新的实体
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
	else	//叶子节点，并且没有存储实体，直接存储实体
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
	if(p == nullptr)	//已经降级到根了，不能再降
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
	if(flag == true)		//中间节点降级为叶子节点
	{
		for(int dir = lu; dir <= ld; ++dir)
		{
			delete p->sub_area[dir];
			p->sub_area[dir] = nullptr;
		}
		adjust(*p);
	}
}