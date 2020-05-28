#ifndef DEFINE_H
#define DEFINE_H

#include <string>

struct HTNode
{
	int num;
	int weight;
	std::string code;
	struct HTNode* lchild, * rchild;
	friend bool operator<(const HTNode& a,const HTNode& b)
	{
		if (a.weight < b.weight)
			return true;
		else
			return false;
	}
	friend bool operator>(const HTNode& a,const HTNode& b)
	{
		if (a.weight > b.weight)
			return true;
		else
			return false;
	}
};
typedef HTNode* node;

struct cmp
{
	bool operator()(node a, node b)
	{
		if (a->weight > b->weight)
			return true;
		return false;
	}
};

#endif // !DEFINE_H
