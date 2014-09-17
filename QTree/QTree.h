/*************************************
�����Ĳ���
��Ҷ�ӽڵ��⣬ÿ���ڵ㶼���ĸ����ӡ�
ֻ��Ҷ�ӽڵ��ܰ���ʵ��ڵ㣨���꣩��
�������������м�ڵ㣬���ĸ����Ӷ���û�б���ʵ���Ҷ�ӽڵ㡣
�˴���ʵ��ڵ���ecs������ʵ���������Ϣ��
ʵ�ֻ������������ɾ����
entity�ƶ�ʱ��������������������ʵ��λ�������еĸ��¡�
**************************************/

enum Direct
{
	lu = 0,
	ru = 1,
	rd = 2,
	ld = 3
};

//��������
struct Position
{
	double x;
	double y;
	Position(double _x = 0.0, double _y = 0.0):x(_x), y(_y){}
	inline bool operator = (const Position &pos) const
	{
		return x == pos.x && y == pos.y;
	}
};

//����
struct Rectangle
{
	Position lu;
	Position rd;
	Rectangle(const Position _lu, const Position _rd):lu(_lu), rd(_rd){}
};

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
		Node(const Rectangle , Node *);
		~Node();
	};

	Node *root;
public:
	QTree(const Rectangle );
	~QTree();
	void insert(Position *);
	void remove(Position *);
private:
	void insert(Position *, Node &);
	void remove(Position *, Node &);
	void adjust(Node &);	//ɾ���������ܳ����ĸ�Ҷ�Ӷ�û�б���ʵ�壬�ô˺�������

	//������������ʾ���Ϊ��������
	inline bool is_leaf(const Node &r)
	{
		return r.sub_area[lu] == nullptr &&
			r.sub_area[ru] == nullptr &&
			r.sub_area[rd] == nullptr &&
			r.sub_area[ld] == nullptr;
	}

	inline bool is_contain(const Rectangle &rec, const Position *pos)
	{
		return rec.lu.x <= pos->x && 
			rec.lu.y >= pos->y &&
			rec.rd.x >= pos->x && 
			rec.rd.y <= pos->y;
	}
	
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