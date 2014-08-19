#include"AVLTree.h"
#include<iostream>
#include<algorithm>
AVLTree::AVLTree():root(nullptr)
{}

AVLTree::~AVLTree()
{
	destory(root);
}

void AVLTree::insert(int v)
{
	insert(v, root);
}

void AVLTree::insert(int v, AVLNode * &p)
{
	if(p == nullptr)
	{
		p = new AVLTree::AVLNode(v);
	}
	else if(v < p->val)
	{
		insert(v, p->lc);
		if(height(p->lc) - height(p->rc) == 2)
		{
			if(v < p->lc->val)
			{
				rotateWithLeftChild(p);
			}
			else
			{
				doubleRotateLeftChild(p);
			}
		}
	}
	else if(v > p->val)
	{
		insert(v, p->rc);
		if(height(p->rc) - height(p->lc) == 2)
		{
			if(v < p->rc->val)
			{
				doubleRotateRightChild(p);
			}
			else
			{
				rotateWithRightChild(p);
			}
		}
	}
	p->high = std::max(height(p->lc), height(p->rc)) + 1;
}

void AVLTree::destory(AVLNode * &p)
{
	if(p != nullptr)
	{
		destory(p->lc);
		destory(p->rc);
		delete p;
		p = nullptr;
	}
}

int AVLTree::height(AVLNode * p)
{
	return p != nullptr ? p->high : -1;
}

void AVLTree::rotateWithLeftChild(AVLNode *& r)
{
	AVLNode * temp = r->lc;
	r->lc = temp->rc;
	temp->rc = r;
	r->high = std::max(height(r->rc), height(r->lc)) + 1;
	temp->high = std::max(height(temp->rc), height(temp->lc)) + 1;
	r = temp;
}

void AVLTree::rotateWithRightChild(AVLNode *& r)
{
	AVLNode * temp = r->rc;
	r->rc = temp->lc;
	temp->lc = r;
	r->high = std::max(height(r->rc), height(r->lc)) + 1;
	temp->high = std::max(height(temp->rc), height(temp->lc)) + 1;
	r = temp;
}

void AVLTree::doubleRotateLeftChild(AVLNode *& r)
{
	rotateWithRightChild(r->lc);
	rotateWithLeftChild(r);
}

void AVLTree::doubleRotateRightChild(AVLNode *& r)
{
	rotateWithLeftChild(r);
	rotateWithRightChild(r->lc);
}

void AVLTree::print()
{
	std::cout<<root->val<<std::endl;
	print(root->lc, std::string("---"));
	print(root->rc, std::string("---"));
}

void AVLTree::print(AVLNode *r, std::string ff)
{
	if(r != nullptr)
	{
		std::cout<<ff<<r->val<<std::endl;
		print(r->lc, ff + "---");
		print(r->rc, ff + "---");
	}
}

AVLTree::AVLNode *& AVLTree::findMax(AVLNode *r)
{
	AVLNode *temp = r->rc;
	while(temp->rc != nullptr)
	{
		temp = temp->rc;
	}
	return temp;
}

AVLTree::AVLNode *& AVLTree::findMin(AVLNode *r)
{
	AVLNode *temp = r->lc;
	while(temp->lc != nullptr)
	{
		temp = temp->lc;
	}
	return temp;
}

void AVLTree::adjHeigh(AVLNode *&r)
{
	if(r == nullptr)
	{
		return ;
	}
	else
	{
		adjHeigh(r->lc);
		adjHeigh(r->rc);
		r->high = std::max(height(r->lc), height(r->rc)) + 1;
	}
}

void AVLTree::deleteNode(int val)
{
	deleteNode(root, val);
}

void AVLTree::deleteNode(AVLNode *&r, int val)
{
	if(r == nullptr)
	{
		return ;
	}
	if(r->val < val)
	{
		deleteNode(r->rc, val);
	}
	else if(r->val > val)
	{
		deleteNode(r->lc, val);
	}
	else		//找到了，交换到叶子，删除叶子
	{
		if(r->rc != nullptr)
		{
			AVLNode *&temp = findMin(r->rc);
			r->val = temp->val;
			deleteNode(r->rc, r->val);
		}
		else if(r->lc != nullptr)
		{
			AVLNode *&temp = findMax(r->lc);
			r->val = temp->val;
			deleteNode(r->lc, r->val);
		}
		else
		{
			delete r;
			r = nullptr;
		}
	}
	if(r != nullptr)
	{
		adjHeigh(r);
		if(height(r->lc) - height(r->rc) == 2)
		{
			if(height(r->lc->lc) > height(r->lc->rc))
			{
				rotateWithLeftChild(r);
			}
			else
			{
				doubleRotateLeftChild(r);
			}
		}
		else if(height(r->rc) - height(r->lc) == 2)
		{
			if(height(r->rc->rc) > height(r->rc->lc))
			{
				rotateWithRightChild(r);
			}
			else
			{
				doubleRotateRightChild(r);
			}
		}
	}
}