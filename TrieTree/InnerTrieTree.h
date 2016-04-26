#pragma once
#include<string>
#include<list>
#include<functional>

namespace Charlotte
{

	class InnerTrieTree
	{
	private:

		struct TrieTreePare
		{
			TrieTreePare	*children = nullptr;
			InnerTrieTree	*tree = nullptr;		//指向所属的前缀树
			unsigned int	count = 0;

			TrieTreePare()
			{

			}

			TrieTreePare(const TrieTreePare &c)
			{
				if (c.children != nullptr)
				{
					children = new TrieTreePare[c.tree->scope];
					for (int i = 0; i < c.tree->scope; ++i)
					{
						children[i] = c.children[i];
					}
				}
				tree = c.tree;
				count = c.count;
			}

			TrieTreePare& operator = (const TrieTreePare &c)
			{
				if (c.children != nullptr)
				{
					children = new TrieTreePare[c.tree->scope];
					for (int i = 0; i < c.tree->scope; ++i)
					{
						children[i] = c.children[i];
					}
				}
				tree = c.tree;
				count = c.count;
				return *this;
			}

			void setTree(InnerTrieTree *tree)
			{
				this->tree = tree;
			}

			~TrieTreePare()
			{
				if (children != nullptr)
				{
					delete[] children;
				}
			}
		};

		friend TrieTreePare;

		TrieTreePare *root = nullptr;

		int scope = 0;	//字符集中的数量，对应为每个节点的数组长度

		std::function<int(char)> index;	//依据字符求数组的下标

	protected:
		InnerTrieTree(int scope, std::function<int(char)> index) : scope(scope), index(index)
		{
			root = new TrieTreePare[scope];
			initPairTree(root);
		}

		InnerTrieTree(const InnerTrieTree &c)
		{
			root = new TrieTreePare[c.scope];
			scope = c.scope;
			index = c.index;
			for (int i = 0; i < c.scope; ++i)
			{
				root[i] = c.root[i];	//此时root[i]会指向c所属的树
				root[i].setTree(this);	//恢复root[i]指向自身
			}
		}

		~InnerTrieTree()
		{
			delete[] root;
		}

		void buildTrieTree(std::list<std::string> words)
		{
			for (std::string word : words)
			{
				insertOne(word);
			}
		}

		int retrievalCount(const std::string &prefix)
		{
			if (prefix.length() != 0)
			{
				TrieTreePare *curr = root;
				TrieTreePare *pre = curr;

				for (const char &c : prefix)
				{
					if (curr == nullptr)
					{
						return 0;
					}
					pre = curr;
					curr = curr[index(c)].children;
				}
				return pre[index(prefix.back())].count;
			}
			return 0;
		}

		void insertOne(const std::string &word)
		{
			TrieTreePare *curr = root;
			for (const char &c : word)
			{
				curr[index(c)].count++;
				if (curr[index(c)].children == nullptr)
				{
					curr[index(c)].children = new TrieTreePare[scope];
					initPairTree(curr[index(c)].children);
				}
				curr = curr[index(c)].children;
			}
		}

	private:
		void initPairTree(TrieTreePare *curr)
		{
			for (int i = 0; i < scope; ++i)
			{
				curr[i].setTree(this);
			}
		}
	};
}
