#include"AVLTree.h"
int main()
{
	AVLTree test;

	for(int i = 0; i < 10; ++i)
	{
		test.insert(i);
	}
	test.print();

	test.deleteNode(9);
	test.deleteNode(0);
	test.deleteNode(4);
	test.print();
	return 0;
}