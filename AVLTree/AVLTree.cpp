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
				rotateWithRightCHild(p);
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

void AVLTree::rotateWithRightCHild(AVLNode *& r)
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
	rotateWithRightCHild(r->lc);
	rotateWithLeftChild(r);
}

void AVLTree::doubleRotateRightChild(AVLNode *& r)
{
	rotateWithLeftChild(r);
	rotateWithRightCHild(r->lc);
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