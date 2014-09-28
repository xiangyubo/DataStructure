/*************************************
简易四叉树
除叶子节点外，每个节点都有四个孩子。
只有叶子节点能包含实体节点（坐标）。
不存在这样的中间节点，其四个孩子都是没有保存实体的叶子节点。
此处的实体节点是ecs中真正实体的坐标信息。
实现基本操作插入和删除。
entity移动时候利用这两个基本操作实现位置在树中的更新。
**************************************/

#include<vector>
#include"BasicType.h"
//四叉树类
class QTree
{
private:
	struct Node
	{
		Rectangle area;
		Position *entity;	//实体的坐标，会随着实体移动，所以只是持有一个坐标的指针，不拷贝，不析构
		Node * sub_area[4];
		Node * parent;		//指向父亲的指针，调节的时候会用到
		Node(const Rectangle &, Node *);
		~Node();

        //辅助函数，显示标记为内联函数
        inline bool is_leaf() const
        {
            return sub_area[lu] == nullptr &&
                sub_area[ru] == nullptr &&
                sub_area[rd] == nullptr &&
                sub_area[ld] == nullptr;
        }
    };

	Node *root;
public:
	QTree(const Rectangle &);
	~QTree();
	void insert(Position *);
	void remove(Position *);
    std::vector<Position> findInRect(const Rectangle &rt);
private:
	void insert(Position *, Node &);
	void remove(Position *, Node &);
    void findInNode(const Node &, const Rectangle &, std::vector<Position> &);
	void adjust(Node &);	//删除操作可能出现四个叶子都没有保存实体，用此函数调整 
	
	inline Rectangle cut_rect(const Rectangle &rec, const Direct dir)
	{
		Position center((rec.lu.x + rec.rd.x)/2, (rec.lu.y + rec.rd.y)/2);
		switch (dir)
		{
		case lu:
			return Rectangle(rec.lu, center);
		case ru:
			return Rectangle(Position(center.x, rec.lu.y), Position(rec.rd.x, center.y));
		case rd:
			return Rectangle(center, rec.rd);
		case ld:
			return Rectangle(Position(rec.lu.x, center.y), Position(center.x, rec.rd.y));
		}
	}
};