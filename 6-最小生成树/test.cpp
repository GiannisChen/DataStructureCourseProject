#include "Graph.h"
#include <fstream>

using namespace std;

#define GraphData "graph.txt"


int main()
{
	fstream graphData(GraphData, ios::in);
	if (graphData.fail())
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(0);
	}

	int N;
	char tmp[1024];
	graphData.getline(tmp, 1024);
	sscanf_s(tmp, "%d", &N);
	graph G(N);
	cout << N << endl;

	for (int i = 0; i < N; i++)
	{
		graphData.getline(tmp, 1024);
		G.vexData(i, string(tmp));
	}

	int from, to;
	float weight;
	while (!graphData.eof())
	{
		graphData >> from >> to >> weight;
		G.EdgeInsert(from, to, weight);
	}

	G.print();
	string start;
	while (true)
	{
		int choice;
		cout << "----------�˵�----------" << endl;
		cout << "��ѡ�������" << endl;
		cout << "1.Prim�㷨��" << endl;
		cout << "2.Kruskal�㷨��" << endl;
		cout << "3.�˳���" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Prim�㷨(������ʼ����)��" << endl;
			cin >> start;
			G.Prim(start);
			break;

		case 2:
			cout << "Kruskal�㷨��" << endl;
			G.Kruskal();
			break;

		case 3:
			cout << "�˳�����" << endl;
			exit(0);

		default:
			break;
		}
	}

	cout << "Kruskal:" << endl;
	G.Kruskal();

	graphData.close();
	return 0;
}