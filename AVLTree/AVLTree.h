#include<string>
class AVLTree
{
public:
	AVLTree();
	void print();
	~AVLTree();
	void insert(int v);
	void deleteNode(int val);
private:
	struct AVLNode
	{
		int val;
		int high;
		AVLNode *lc;
		AVLNode *rc;
		AVLNode(int v, int h = 0, AVLNode *ll =  nullptr, AVLNode *rr = nullptr):
			val(v), high(h), lc(ll), rc(rr)
		{}
	};

	AVLNode *root;
	int height(AVLNode *p);
	void rotateWithLeftChild(AVLNode *& r);
	void rotateWithRightChild(AVLNode *& r);
	void doubleRotateLeftChild(AVLNode *& r);
	void doubleRotateRightChild(AVLNode *& r);  
	void insert(int v, AVLNode *& r);
	void print(AVLNode *r, std::string ff);
	AVLNode *& findMax(AVLNode *r);
	AVLNode *& findMin(AVLNode *r);
	void adjHeigh(AVLNode *&r);
	void deleteNode(AVLNode *&r, int val);
	void destory(AVLNode *& r);
};