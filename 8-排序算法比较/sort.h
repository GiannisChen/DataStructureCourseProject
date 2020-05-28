#pragma once
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <stack>
#include <array>
#include <queue>
#include "heap.h"

/*
	直接插入排序
*/

//1.直接插入排序
void InsertSort(std::vector<int>& v)
{
	for (int i = 1; i < (int)v.size(); i++)
	{
		if (v.at(i) < v.at(i - 1))
		{
			int j = i - 1;
			int tmp = v.at(i);
			for (; j >= 0 && tmp < v.at(j); j--)
				v.at(j + 1) = v.at(j);
			v.at(j + 1) = tmp;
		}
	}
}
void TestInsertSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		InsertSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "直接插入排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "直接插入排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//2.希尔排序
void ShellsSort(std::vector<int>& v)
{
	//使用2^k-1作为步长
	int step = 16383;
	int tmp;
	for (; step >= 1; step = ((step + 1) / 2) - 1)
	{
		for (int i = step; i < (int)v.size(); i++)
		{
			tmp = v.at(i);
			int j = i - step;
			for (; j >= 0 && tmp < v.at(j); j -= step)
				v.at(j + step) = v.at(j);
			v.at(j + step) = tmp;
		}
	}
}
void TestShellsSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		ShellsSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "希尔排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;
		
		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "希尔排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//3.冒泡排序
void BubbleSort(std::vector<int>& v)
{
	for (int i = 0; i < (int)(v.size() - 1); i++)
	{
		bool flag = true;
		for (int j = 0; j < (int)(v.size() - 1 - i); j++)
		{
			if (v.at(j) > v.at(j + 1))
			{
				flag = false;
				std::swap(v.at(j), v.at(j + 1));
				
			}
			if (flag)
				break;
		}
	}
}
void TestBubbleSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		ShellsSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "冒泡排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "冒泡排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//4.快速排序
int Partiton(std::vector<int>& v, int low, int high)
{
	//法2：
	//法2：调整一次只需要0.06s左右，优化近两个数量级
	int mid = (low + high) / 2;
	if (v.at(low) > v.at(high))
		std::swap(v.at(low), v.at(high));
	if (v.at(mid) > v.at(high))
		std::swap(v.at(mid), v.at(high));
	if (v.at(mid) > v.at(low))
		std::swap(v.at(mid), v.at(low));
	int key = v.at(low);
	
	//法1：int index = low;
	//法1：较慢，完全有序调整一次要4s
	while (low != high)
	{
		while (low < high && v.at(high) >= key)
			high--;
		while (low < high && v.at(low) <= key)
			low++;
		if (low < high)
			std::swap(v.at(low), v.at(high));
	}
	//if (low != index)
	//	std::swap(v.at(index), v.at(low));
	return low;
}
void QuickSort(std::vector<int>& v)
{
	std::stack<std::pair<int, int>> Stack;
	int mid = Partiton(v, 0, v.size() - 1);
	if (mid > 1)
		Stack.push(std::make_pair(0, mid - 1));
	if (mid < int(v.size() - 2))
		Stack.push(std::make_pair(mid + 1, v.size() - 1));

	while (!Stack.empty())
	{
		std::pair<int,int> tmpP = Stack.top();
		Stack.pop();
		mid = Partiton(v, tmpP.first, tmpP.second);
		if (tmpP.first < (mid - 1))
			Stack.push(std::make_pair(tmpP.first, mid - 1));
		if (tmpP.second > mid + 1)
			Stack.push(std::make_pair(mid + 1, tmpP.second));
	}
}
void TestQuickSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		QuickSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if(i!=0 && i!=1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "快速排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "快速排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//5.选择排序
void SelectSort(std::vector<int>& v)
{
	int min;
	int index;

	for (size_t i = 0; i < (v.size() - 1); i++)
	{
		min = v.at(i);
		index = i;
		for (size_t j = i; j < v.size(); j++)
		{
			if (min > v.at(j))
			{
				min = v.at(j);
				index = j;
			}
		}
		if (index != i)
			std::swap(v.at(index), v.at(i));
	}
}
void TestSelectSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		InsertSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "选择排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "选择排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//6.堆排序
void HeapSort(std::vector<int>& v)
{
	MinHeap heap(-1);
	for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
		heap.push(*iter);
	for (std::vector<int>::iterator iter = v.begin(); iter != v.end(); iter++)
		(*iter) = heap.pop();
}
void TestHeapSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		HeapSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "堆排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "堆排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//7.归并排序
void sort(std::vector<int>& v, std::vector<int>& tmp, int left, int mid, int right)
{
	int i = left, j = mid + 1, k;
	for (k = i; i <= mid && j <= right; k++)
	{
		if (v.at(i) < v.at(j))
			tmp.at(k) = v.at(i++);
		else
			tmp.at(k) = v.at(j++);
	}
	if (i <= mid)
	{
		for (int h = 0; h <= mid - i; h++)
			tmp.at(k + h) = v.at(i + h);
	}
	else
	{
		for (int h = 0; h <= right - j; h++)
			tmp.at(k + h) = v.at(j + h);
	}
}
void Merge(std::vector<int>& v, std::vector<int>& tmp, int step)
{
	int i = 0, j;
	while (i <= (int)(v.size() - 2 * step))
	{
		sort(v, tmp, i, i + step - 1, i + 2 * step - 1);
		i += 2 * step;
	}
	if (i < (int)(v.size() - step + 1))
		sort(v, tmp, i, i + step - 1, v.size() - 1);
	else
		for (j = i; j < (int)v.size(); j++)
			tmp.at(j) = v.at(j);
	for (i = 0; i < (int)v.size(); i++)
		v.at(i) = tmp.at(i);
}
void MergeSort(std::vector<int>& v)
{
	int step = 1;
	std::vector<int> tmp(20000);
	while (step < (int)v.size())
	{
		Merge(v, tmp, step);
		step *= 2;
	}
}
void TestMergeSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		MergeSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "归并排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "归并排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}

//8.基数排序
void BaseSort(std::vector<int>& v)
{
	std::queue<int> Q[10];
	int count = 1;
	int base = 1;
	for (; count <= 5; count++, base *= 10)
	{
		for (size_t i = 0; i < v.size(); i++)
			Q[(v.at(i) / base) % 10].push(v.at(i));
		size_t j = 0;
		for (int i = 0; i < 10; i++)
		{
			while (!Q[i].empty())
			{
				v.at(j++) = Q[i].front();
				Q[i].pop();
			}
		}
	}
}
void TestBaseSort(std::vector<std::string>& resource)
{
	std::fstream text;
	clock_t start, end;
	std::vector<double> cost;
	std::vector<int> arr;
	int tmp;
	double average = 0;
	for (size_t i = 0; i < resource.size(); i++)
	{
		//预处理
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "文件打开失败！" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//排序并计数输出
		start = clock();
		BaseSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//测试排序
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//测试结束
*/
		std::cout << "基数排序\t" << resource.at(i) << "\t运行时间：" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

		//还原工作
		arr.clear();
		text.close();
	}
	std::cout << "基数排序\t" << "平均时间" << "\t运行时间：" << (average / 8) << "s\t" << std::endl;
}