#pragma once
#include <iostream>
#include <vector>

enum type { OPRT, NUM };

template <class _My_Type>
class My_stack
{
public:
	void push(_My_Type a);
	_My_Type top();
	void pop();
	int size();
	bool empty();
	void traverse();
private:
	std::vector<_My_Type> content;
};
template <class _My_Type>
void My_stack<_My_Type>::push(_My_Type a)
{
	content.push_back(a);
	std::cout << "ÈëÕ»£º" << a << std::endl << std::endl;
}

template <class _My_Type>
_My_Type My_stack<_My_Type>::top()
{
	if (content.empty())
		return NULL;
	else
		return content.at(content.size() - 1);
}

template <class _My_Type>
void My_stack<_My_Type>::pop()
{
	std::cout << "³öÕ»£º" << content.back() << std::endl << std::endl;
	content.pop_back();
}

template <class _My_Type>
int My_stack<_My_Type>::size()
{
	return content.size();
}

template <class _My_Type>
bool My_stack<_My_Type>::empty()
{
	return (content.size() == 0);
}


template <class _My_Type>
void My_stack<_My_Type>::traverse()
{
	for (size_t i = 0; i < content.size(); i++)
	{
		if (i == 0)
			std::cout << content.at(i);
		else
			std::cout << "  " << content.at(i);
	}
	std::cout << std::endl;
}