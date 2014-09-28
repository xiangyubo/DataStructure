/*************************************
�����Ĳ���
��Ҷ�ӽڵ��⣬ÿ���ڵ㶼���ĸ����ӡ�
ֻ��Ҷ�ӽڵ��ܰ���ʵ��ڵ㣨���꣩��
�������������м�ڵ㣬���ĸ����Ӷ���û�б���ʵ���Ҷ�ӽڵ㡣
�˴���ʵ��ڵ���ecs������ʵ���������Ϣ��
ʵ�ֻ������������ɾ����
entity�ƶ�ʱ��������������������ʵ��λ�������еĸ��¡�
**************************************/

#include<vector>
#include"BasicType.h"
//�Ĳ�����
class QTree
{
private:
	struct Node
	{
		Rectangle area;
		Position *entity;	//ʵ������꣬������ʵ���ƶ�������ֻ�ǳ���һ�������ָ�룬��������������
		Node * sub_area[4];
		Node * parent;		//ָ���׵�ָ�룬���ڵ�ʱ����õ�
		Node(const Rectangle &, Node *);
		~Node();

        //������������ʾ���Ϊ��������
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
	void adjust(Node &);	//ɾ���������ܳ����ĸ�Ҷ�Ӷ�û�б���ʵ�壬�ô˺������� 
	
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