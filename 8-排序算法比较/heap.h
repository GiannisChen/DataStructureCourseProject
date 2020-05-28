#ifndef HEAP_H
#define HEAP_H
#include <array>
#include <iostream>
class MinHeap
{
private:
	std::array<int,20001> Elements;
	int HeapSize = 0;
	int Capacity = 20001;
public:
	MinHeap(int MIN)
	{
		HeapSize = 0;
		Capacity = 20001;
		Elements.at(0) = MIN;
	}
	bool empty()
	{
		return (0 == HeapSize);
	}
	bool full()
	{
		return (HeapSize == Capacity);
	}
	void push(int node)
	{
		if (full())
		{
			std::cout << "HEAP IS FULL CANT PUSH..." << std::endl;
			return;
		}
		int i = ++HeapSize;
		for (; Elements.at(i / 2) > node && i >= 1; i /= 2)
			Elements.at(i) = Elements.at(i / 2);
		Elements.at(i) = node;
		return;
	}
	int pop()
	{
		if (empty())
		{
			std::cout << "MINHEAP IS EMPTY CANT PUSH..." << std::endl;
			return NULL;
		}
		int parent, child;
		int Min, tmp;
		Min = Elements.at(1);
		tmp = Elements.at(HeapSize--);
		for (parent = 1; parent * 2 <= HeapSize; parent = child)
		{
			child = parent * 2;
			if ((child != HeapSize) && Elements.at(child) > Elements.at(child + 1))
				child++;
			if (Elements.at(child) >= tmp)
				break;
			else
				Elements.at(parent) = Elements.at(child);
		}
		Elements.at(parent) = tmp;
		return Min;
	}
	int size()
	{
		return HeapSize;
	}
};
#endif // !HEAP_H