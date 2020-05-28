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
	ֱ�Ӳ�������
*/

//1.ֱ�Ӳ�������
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		InsertSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "ֱ�Ӳ�������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "ֱ�Ӳ�������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//2.ϣ������
void ShellsSort(std::vector<int>& v)
{
	//ʹ��2^k-1��Ϊ����
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		ShellsSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "ϣ������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;
		
		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "ϣ������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//3.ð������
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		ShellsSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "ð������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "ð������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//4.��������
int Partiton(std::vector<int>& v, int low, int high)
{
	//��2��
	//��2������һ��ֻ��Ҫ0.06s���ң��Ż�������������
	int mid = (low + high) / 2;
	if (v.at(low) > v.at(high))
		std::swap(v.at(low), v.at(high));
	if (v.at(mid) > v.at(high))
		std::swap(v.at(mid), v.at(high));
	if (v.at(mid) > v.at(low))
		std::swap(v.at(mid), v.at(low));
	int key = v.at(low);
	
	//��1��int index = low;
	//��1����������ȫ�������һ��Ҫ4s
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		QuickSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if(i!=0 && i!=1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "��������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "��������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//5.ѡ������
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		InsertSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "ѡ������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "ѡ������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//6.������
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		HeapSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//7.�鲢����
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		MergeSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "�鲢����\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "�鲢����\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}

//8.��������
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
		//Ԥ����
		text.open(resource.at(i), std::ios::in);
		if (text.fail())
		{
			std::cout << resource.at(i) << "�ļ���ʧ�ܣ�" << std::endl;
			exit(0);
		}
		for (int j = 0; j < 20000; j++)
		{
			text >> tmp;
			arr.push_back(tmp);
		}

		//���򲢼������
		start = clock();
		BaseSort(arr);
		end = clock();
		cost.push_back((double)(end - start) / CLOCKS_PER_SEC);
		if (i != 0 && i != 1)
			average += cost.back();

		//��������
/*
		for (std::vector<int>::iterator iter = arr.begin(); iter != arr.end(); iter++)
			std::cout << *iter << " ";
		std::cout << std::endl;
		//���Խ���
*/
		std::cout << "��������\t" << resource.at(i) << "\t����ʱ�䣺" << cost.at(i) << "s\t" << std::endl;

		//system("pause");

		//��ԭ����
		arr.clear();
		text.close();
	}
	std::cout << "��������\t" << "ƽ��ʱ��" << "\t����ʱ�䣺" << (average / 8) << "s\t" << std::endl;
}