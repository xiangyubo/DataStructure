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
#include<memory>
#include"BasicType.h"
//�Ĳ�����
class QTree
{
private:
	struct Node
	{
        typedef std::vector<Position*> Entities;
        typedef std::size_t Count;
        
        Count count;
		Rectangle area;
        Entities entitys;   //ʵ������꣬������ʵ���ƶ�������ֻ�ǳ���һ�������ָ�룬��������������
        Node * sub_area[4];
		Node * parent;		//ָ���׵�ָ�룬���ڵ�ʱ����õ�
		
        Node(const Rectangle &, Node *, Count c = 4);
		~Node();

        //������������ʾ���Ϊ��������
        inline bool is_leaf() const
        {
            return sub_area[lu] == nullptr &&
                sub_area[ru] == nullptr &&
                sub_area[rd] == nullptr &&
                sub_area[ld] == nullptr;
        }

        inline bool is_full() const
        {
            return count < entitys.size();
        }

        inline bool is_empty() const
        {
            return entitys.size() == 0;
        }

        inline Entities::iterator find_entity(const Position &pos)
        {
            for(auto it = entitys.begin(); it != entitys.end(); ++it)
            {
                if(pos == **it)
                {
                    return it;
                }
            }
            return entitys.end();
        }

        inline void erase_entity(const Entities::iterator &it)
        {
            entitys.erase(it);
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
    //void move(Position *);
    void find_in_node(const Node &, const Rectangle &, std::vector<Position> &);
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