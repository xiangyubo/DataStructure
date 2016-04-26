#pragma once
#include<list>
#include<string>
#include "InnerTrieTree.h"
namespace Charlotte
{
	//前缀树，模板中的参数指定字符集的规模
	//构造函数的参数用于转化字符到数组下标
	template<int SCOPE = 10>
	class TrieTree : private InnerTrieTree
	{

	public:
		TrieTree(std::function<int (char)> index) : InnerTrieTree::InnerTrieTree(SCOPE, index)
		{
			
		}

		TrieTree(const TrieTree &c) : InnerTrieTree::InnerTrieTree(c)
		{
			
		}

		void buildTrieTree(std::list<std::string> words)
		{
			InnerTrieTree::buildTrieTree(words);
		}

		int retrievalCount(const std::string &prefix)
		{
			return InnerTrieTree::retrievalCount(prefix);
		}

		void insertOne(const std::string &word)
		{
			InnerTrieTree::insertOne(word);
		}
	};
}
