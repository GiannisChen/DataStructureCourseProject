#pragma once
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

#define GRAPH_MAXSIZE 100
#define MAX (float)sqrt(INT_MAX)

struct edge
{
	float weight;
	int from;
	int to;
	friend bool operator>(const edge& a, const edge& b)
	{
		if (a.weight > b.weight)
			return true;
		else
			return false;
	}
};

class graph
{
private:
	float G[GRAPH_MAXSIZE][GRAPH_MAXSIZE] = { 0 };
	int VexNum = 0;

	struct GNode
	{
		string data = "";
		bool isVisited = false;
	}Vex[GRAPH_MAXSIZE];

private:
	bool isAllVisited();
	int isVex(std::string start);
public:
	void print();
	graph(int N)
	{
		VexNum = N;
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				if (i != j)
					G[i][j] = MAX;
	};
	~graph() {};
	void EdgeInsert(int v_start, int v_end, float weight = MAX);
	void vexData(int v, string data);

	//�㷨��
	bool Kruskal();
	bool Prim(string start="default");
};

/*==================================================================
	���ƣ�print
	���ã�����ڽӾ���
	��������
====================================================================*/
void graph::print()
{
	for (int i = 0; i < VexNum; i++)
	{
		for (int j = 0; j < VexNum; j++)
		{
			if (G[i][j] == MAX)
				std::cout << "*\t";
			else
				std::cout << G[i][j] << "\t";
		}

		std::cout << std::endl;
	}
	for (int i = 0; i < VexNum; i++)
	{
		std::cout << i << "\t" << Vex[i].data << "\t" << endl;
	}
}

/*==================================================================
	���ƣ��趨��
	���ã���ɾ�Ĳ��
	������ʼ���ձ�Ȩֵ
====================================================================*/
void graph::EdgeInsert(int v_start, int v_end, float weight)
{
	if (v_start >= 0 && v_start < GRAPH_MAXSIZE &&
		v_end >= 0 && v_end < GRAPH_MAXSIZE)
	{
		G[v_start][v_end] = weight;
		G[v_end][v_start] = weight;
		Vex[v_start].isVisited = false;
		Vex[v_end].isVisited = false;
	}
	else
		std::cout << "ERROR!ILLEGAL INDEX!" << std::endl;
	return;
}

/*==================================================================
	���ƣ�Prim
	���ã���С��������ѡ�㷨��
	���������
====================================================================*/
bool graph::Prim(std::string start)
{
	//��ʼ����
	int VexLabel = isVex(start);
	if (VexLabel == -1)
	{
		cout << "�ڵ㲻�Ϸ���" << endl;
		return false;
	}
	float lowest_weight = 0;

	std::vector<float> dist;
	std::vector<int> way;
	for (int i = 0; i < VexNum; i++)
	{
		dist.push_back(G[VexLabel][i]);
		if (G[VexLabel][i] == MAX)
			way.push_back(i);
		else
			way.push_back(VexLabel);
	}

	//���£�
	Vex[VexLabel].isVisited = true;


	while (true)
	{
		int min = VexNum;
		for (int i = 0; i < VexNum; i++)
		{
			if (!Vex[i].isVisited)
				if ((min == VexNum) || dist[i] > 0 && dist[i]<MAX && dist[min] > dist[i])
					min = i;
		}
		if (min == VexNum)
			break;
		Vex[min].isVisited = true;
		lowest_weight += dist[min];

		for (int i = 0; i < VexNum; i++)
		{
			if (Vex[i].isVisited)
				dist[i] = 0;
			else
			{
				if (dist[i] > G[min][i])
				{
					dist[i] = G[min][i];
					way[i] = min;
				}
			}
		}
	}

	if (lowest_weight >= MAX)
	{
		std::cout << "����ͨͼ��" << std::endl;
		return false;
	}
	int index = 0;
	for (int i = 0; i < VexNum; i++)
	{
		if (G[i][way[i]] == 0)
			index++;
		if (index == 2)
		{
			std::cout << "����ͨͼ��" << std::endl;
			return false;
		}
	}

	std::cout << "��С������ȨֵΪ��" << lowest_weight << endl;
	std::cout << "������ѡ��Ϊ��" << std::endl;
	for (int i = 0; i < VexNum; i++)
	{
		std::cout << Vex[i].data << " to " << Vex[way[i]].data << "��" << G[i][way[i]] << ")" << endl;
	}

	for (int i = 0; i < VexNum; i++)
		Vex[i].isVisited = false;

	return true;
}
int graph::isVex(string start)
{
	if (start == "default")
		return 0;
	for (int i = 0; i < VexNum; i++)
	{
		if (Vex[i].data == start)
			return i;
	}
	return -1;
}
/*==================================================================
	���ƣ�Kruskal
	���ã���С��������ѡ�߷���
	��������
====================================================================*/
bool graph::isAllVisited()
{
	for (int i = 0; i < VexNum; i++)
		if (!Vex[i].isVisited)
			return false;
	return true;
}
int FindRoot(int i, std::vector<int> way)
{
	if (way[i] == -1)
		return -1;
	else if (way[i] == i)
		return i;
	else
		return FindRoot(way[i], way);
}
bool graph::Kruskal()
{
	if (!VexNum)
		return false;


	priority_queue<edge, vector<edge>, greater<edge>> minHeap;
	float lowest_weight = 0;
	edge* tmpE = new edge;
	vector<int> way;

	for (int i = 0; i < VexNum; i++)
	{
		for (int j = i + 1; j < VexNum; j++)
		{
			if (G[i][j] > 0 && G[i][j] < MAX)
			{
				tmpE->weight = G[i][j];
				tmpE->from = i;
				tmpE->to = j;
				minHeap.push(*tmpE);
			}
		}
		way.push_back(i);
	}

	int edgeCount = 0;
	while (!minHeap.empty() && (edgeCount!=(VexNum-1)))
	{
		*tmpE = minHeap.top();	minHeap.pop();
		if (FindRoot(tmpE->from, way) != FindRoot(tmpE->to, way))
		{
			lowest_weight += tmpE->weight;
			if (Vex[tmpE->from].isVisited)
				way.at(tmpE->to) = tmpE->from;
			else
				way.at(tmpE->from) = tmpE->to;
			Vex[tmpE->from].isVisited = true;
			Vex[tmpE->to].isVisited = true;
			edgeCount++;
		}
	}

	if (minHeap.empty())
	{
		std::cout << "����ͨͼ��" << std::endl;
		for (int i = 0; i < VexNum; i++)
			Vex[i].isVisited = false;
		return false;
	}

	std::cout << "��С������ȨֵΪ��" << lowest_weight << endl;
	std::cout << "������ѡ��Ϊ��" << std::endl;
	for (int i = 0; i < VexNum; i++)
	{
		std::cout << Vex[i].data << " to " << Vex[way[i]].data << "��" << G[i][way[i]] << ")" << endl;
	}

	for (int i = 0; i < VexNum; i++)
		Vex[i].isVisited = false;
	return true;
}
/*==================================================================
	���ƣ�vevData
	���ã�������
	���������ţ�����
====================================================================*/
void graph::vexData(int v, string data)
{
	if (v >= 0 && v < VexNum)
	{
		Vex[v].data = data;
		Vex[v].isVisited = false;
	}
}