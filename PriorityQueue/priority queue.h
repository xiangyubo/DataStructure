#include<vector>
class priority_queue
{
public:
	priority_queue();
	~priority_queue();
	void push_back(int val);
	int get_front();
	int pop();
	bool is_empty();
	void make_empyt();
	size_t cur_size();
	void print();
private:
	std::vector<int> buff;
	void modify();
	void print_node(size_t index, char * prefix);
};