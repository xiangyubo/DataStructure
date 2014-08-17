#include"AVLTree.h"
int main()
{
	AVLTree test;

	for(int i = 0; i < 30; ++i)
	{
		test.insert(i);
	}
	test.print();
	return 0;
}