/*
泛型缓冲池，用于存储各种类型的数据
*/
#include<hash_map>
#include<vector>

const static int USE_UP = -1;
const static int NO_COMP = -1;

//缓冲池类
template<typename T, int _size = 128>
class Pool
{
private:
	struct ValusType
	{
		T data;
		int next;
	};
	std::hash_map<int, int> ic_table;	//id到component(index)的映射表
	std::vector<int> ci_table;		//component(index)到id的映射表
	std::vector<ValusType> components;		//component的缓冲区
	int next_free;					//下一个可用内存的索引
public:
	Pool();
	void add_with_id(int , const T&);
	void remove_by_id(int );
	T get_by_id(int );
	void set_by_id(int , const T&);
private:
	int get_index_by_id(int id);
};

template<typename T, int _size>
Pool<T, _size>::Pool():components(_size), ci_table(_size, -1)
{
	for(int i = 0; i < _size; ++i)
	{
		components[i].next = i + 1;
	}
	components[_size - 1].next = -1;
	next_free = 0;
}

template<typename T, int _size>
void Pool<T, _size>::add_with_id(int id, const T& t)
{
	if(get_index_by_id(id) != NO_COMP)
	{
		return;
	}
	ci_table[next_free] = id;
	ic_table[id] = next_free;
	components[next_free].data = t;
	next_free = components[next_free].next;
	if(next_free == USE_UP)			//缓冲池用光了
	{
		components.resize(2 * components.size());
		ci_table.resize(2 * ci_table.size());
		components[components.size()/2-1].next = components.size()/2;
		for(int i = components.size()/2; i < components.size(); ++i)
		{
			components[i].next = i + 1;
		}
		components[components.size() - 1].next = -1;
		next_free = components.size()/2;
	}
}

template<typename T, int _size>
void Pool<T, _size>::remove_by_id(int id)
{
	int index = get_index_by_id(id);
	if(index == NO_COMP)		//没有这个id的component
	{
		return ;
	}
	components[index].next = next_free;
	next_free = index;
	ci_table[index] = -1;
	ic_table.erase(id);
}

template<typename T, int _size>
T Pool<T, _size>::get_by_id(int id)
{
	int index = get_index_by_id(id);
	if(index != NO_COMP)
	{
		return components[index].data;
	}
	//return T();		//如果没有此id对应的component，就让他错误吧
}

template<typename T, int _size>
void Pool<T, _size>::set_by_id(int id, const T& t)
{
	int index = get_index_by_id(id);
	if(index == NO_COMP)
	{
		return ;
	}
	components[index].data = t;
}

template<typename T, int _size>
int Pool<T, _size>::get_index_by_id(int id)
{
	if(ic_table.find(id) != ic_table.end())
	{
		return ic_table[id];
	}
	return NO_COMP;
}