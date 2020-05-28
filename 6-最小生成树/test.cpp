#include "Graph.h"
#include <fstream>

using namespace std;

#define GraphData "graph.txt"


int main()
{
	fstream graphData(GraphData, ios::in);
	if (graphData.fail())
	{
		cout << "数据文件打开失败！" << endl;
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
		cout << "----------菜单----------" << endl;
		cout << "请选择操作：" << endl;
		cout << "1.Prim算法；" << endl;
		cout << "2.Kruskal算法；" << endl;
		cout << "3.退出。" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Prim算法(输入起始点名)：" << endl;
			cin >> start;
			G.Prim(start);
			break;

		case 2:
			cout << "Kruskal算法：" << endl;
			G.Kruskal();
			break;

		case 3:
			cout << "退出程序！" << endl;
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