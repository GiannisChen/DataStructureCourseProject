/*                                    _
								   | |
 __      __ _   _ __      __ _ __  | |__
 \ \ /\ / /| | | |\ \ /\ / /| '_ \ | '_ \
  \ V  V / | |_| | \ V  V / | | | || |_) |
   \_/\_/   \__, |  \_/\_/  |_| |_||_.__/
			 __/ |
			|___/
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include <list>
#include <string>
#include <stack>
#include <map>
#include <locale>

#define STATION_NUM 5200
//������ʽ
#define LEAST_TRANSFER 0
#define LEAST_STATION 1
const int INF = 0x3f3f3f3f;

using namespace std;

/*****************************�ṹ����*******************************/
//վ����Ϣ
struct station
{
	wstring name;
	int label;
	list<int> bus_label;
};

//��Ź�����ź�վ��
map<int, vector<int>> bus;
//���վ�㡪�������Ϣ
map<int, wstring> number_station;
map<wstring, int> station_number;
//ͼ<ת�˲���,�������>
pair<int, int> Graph_1[STATION_NUM][STATION_NUM];
pair<int, int> Graph_2[STATION_NUM][STATION_NUM];
//·��
int dis[STATION_NUM], way[STATION_NUM];
bool vis[STATION_NUM];


/*****************************�ṹ�������****************************/

/*****************************��������*******************************/
//intתwstring
void itow(int a, wstring& w);

//��ʼ���洢�ṹ
void init(wfstream& resource);

//�������bus��map��
void traverse(map<int, vector<int>> bus);

//�������stationList��map<wstring,int>��
void traverse(map<wstring, int> stationList);

//�������stationList��map<int,wstring>��
void traverse(map<int, wstring> stationList);

//�����ļ����stationList��map<int,wstring>��
void traverse(map<int, wstring> stationList,wfstream &output);

//G_1�����в���
void GraphInsert(int buNum,vector<int> l);

//ָ����ʼ�ڵ��dijkstra�㷨�����ٻ��ˣ�
void dijkstra(int start, int size, bool flag = LEAST_TRANSFER);

//���·��������ʾ����վ���յ�վ�Լ�����վ��·�ߣ�
void PrintRoute(int start, int end, bool flag = LEAST_TRANSFER);

//����
void implement(bool flag = LEAST_TRANSFER);
/*****************************������������****************************/

int main()
{
	cout << "===========================================" << endl;
	cout << endl;
	cout << "�����У����Ժ�..." << endl;
	cout << endl;
	wfstream resource, output;
	resource.open("�Ͼ�������·.txt", ios::in);
	
	//resource.open("test.txt", ios::in);
	resource.imbue(locale("chs"));
	wcout.imbue(locale("chs"));
	wcin.imbue(locale("chs"));
	if (resource.fail())
	{
		cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
		exit(0);
	}
	
	init(resource);
	cout << "��ȡ�ɹ���" << endl;
	cout << endl;
	cout << "                                    _" << endl;
	cout << "                                   | |" << endl;
	cout << " __      __ _   _ __      __ _ __  | |__" << endl;
	cout << " \\ \\ /\\ / /| | | |\\ \\ /\\ / /|  _ \\ |  _ \\ " << endl;
	cout << "  \\ V  V / | |_| | \\ V  V / | | | || |_) |" << endl;
	cout << "   \\_/\\_/   \\__, |  \\_/\\_/  |_| |_||_.__/" << endl;
	cout << "             __/ |" << endl;
	cout << "            |___ /" << endl;
	cout << endl;
	cout << "===========================================" << endl;
	cout << endl;
	Sleep(1000);
	
	//traverse(number_station, output);
	int choice;
	while (1)
	{
		cout << "===========================================" << endl;
		cout << "ѡ������ʽ��" << endl;
		
		cout << setw(10) << "��������" << "\t\t0" << endl;
		cout << setw(10) << "վ������" << "\t\t1" << endl;
		cout << setw(10) << "�˳�" << "\t\t-1" << endl;
		cout << "===========================================" << endl;
		cout << "����ѡ���ǣ�";
		cin >> choice;
		if (choice == -1)
		{
			cout << "�˳�����" << endl;
			exit(0);
		}
		else if (choice > 1 || choice < -1)
			continue;
		else
			implement(choice);
	}
	return 0;
}

/*****************************��������*******************************/

//intתwstring
void itow(int a, wstring& w)
{
	wstring tmp;
	while (a)
	{
		tmp.push_back(wchar_t((a % 10) + '0'));
		a /= 10;
	}
	//reverse(tmp.begin(), tmp.end());
	while (!tmp.empty())
	{
		w.push_back(tmp.back());
		tmp.pop_back();
	}
}

//��ʼ���洢�ṹ
void init(wfstream& resource)
{
	//��ʼ��
	wstring s;
	wchar_t first, second;
	int times = 2;
	int tmpN = 0;
	int busNum = 0;
	int index = 1;
	bool flag = false;
	vector<int> tmpVector;
	for (int i = 0; i < STATION_NUM; i++)
	{
		for (int j = 0; j < STATION_NUM; j++)
		{
			Graph_1[i][j].first = INF;
			Graph_1[i][j].second = 0;
			Graph_2[i][j].first = INF;
			Graph_2[i][j].second = 0;
		}
	}

	//��ȡ
	resource >> second;
	while (!resource.eof())
	{
		first = second;
		resource >> second;
		//��������
		if (first >= '0' && first <= '9')
		{
			tmpN = tmpN * 10 + first - '0';
			//�ж�Ϊ�������
			if (second == L'·')
			{
				//cout << endl;
				//��������©��ǰһ��վ��δ����
				if (!s.empty())
				{
					//bus[busNum].push_back(s);
					map<wstring, int>::iterator i = station_number.find(s);
					if (i==station_number.end())
					{
						//wcout << "[" << index << "]\t" << s << endl;
						station_number.insert(map<wstring, int>::value_type(s, index));
						number_station.insert(map<int, wstring>::value_type(index, s));
						bus[busNum].push_back(index++);
					}
					else
					{
						bus[busNum].push_back((*i).second);
					}
					//wcout << s << "  ";
					s.clear();
				}
				if (busNum)
					GraphInsert(busNum,bus[busNum]);
				bus.insert(map<int, vector<int>>::value_type(tmpN, tmpVector));
				busNum = tmpN;
				//cout << busNum << "·��" << endl;
				tmpN = 0;
				resource >> second;
			}
			//��������
			else if (second >= '0' && second <= '9')
				continue;
			//�����֣�������վ�����Ƶ����֣�����ת����
			else
			{
				itow(tmpN, s);//����ת�����ַ���
				tmpN = 0;
			}
		}
		//�������ֺͷ���
		else
		{
			s.push_back(first);
			if (second == ',')
			{
				//bus[busNum].push_back(s);
				map<wstring, int>::iterator i = station_number.find(s);
				if (i == station_number.end())
				{
					//wcout << "[" << index << "]\t" << s << endl;
					station_number.insert(map<wstring, int>::value_type(s, index));
					number_station.insert(map<int, wstring>::value_type(index, s));
					bus[busNum].push_back(index++);
				}
				else
				{
					bus[busNum].push_back((*i).second);
				}
				//wcout << s << "  ";
				s.clear();
				resource >> second;
			}
		}
	}
}

//�������bus��map��
void traverse(map<int, vector<int>> bus)
{
	for (map<int, vector<int>>::iterator bus_iter = bus.begin(); bus_iter != bus.end(); bus_iter++)
	{
		wcout << (*bus_iter).first;
		cout << "·��" << endl;
		for (vector<int>::iterator iter = (*bus_iter).second.begin(); iter != (*bus_iter).second.end(); iter++)
			wcout << (*iter) << "  ";
		cout << endl;
	}
	wcout << endl;
}

//�������stationList��map<wstring,int>��
void traverse(map< wstring, int> stationList)
{
	for (map<wstring, int>::iterator iter = stationList.begin(); iter != stationList.end(); iter++)
		wcout << "[" << (*iter).second << "]\t" << (*iter).first << endl;
	wcout << endl;
}

//�������stationList��map<int,wstring>��
void traverse(map<int, wstring> stationList)
{
	for (map<int, wstring>::iterator iter = stationList.begin(); iter != stationList.end(); iter++)
		wcout << "[" << (*iter).first << "]\t" << (*iter).second << endl;
	wcout << endl;
}

//G�ĳ�ʼ��
void GraphInsert(int busNum,vector<int> l)
{
	for (size_t i = 0; i < l.size() - 1; i++)
	{
		Graph_2[l.at(i)][l.at(i)].first = 0;
		Graph_2[l.at(i)][l.at(i + 1)].first = Graph_2[l.at(i)][l.at(i + 1)].first = 1;
		Graph_2[l.at(i)][l.at(i + 1)].second = Graph_2[l.at(i)][l.at(i + 1)].second = busNum;
		Graph_1[l.at(i)][l.at(i)].first = 1;
		for (size_t j = i + 1; j < l.size(); j++)
		{
			Graph_1[l.at(i)][l.at(j)].first = Graph_1[l.at(j)][l.at(i)].first = 1;
			Graph_1[l.at(i)][l.at(j)].second = Graph_1[l.at(j)][l.at(i)].second = busNum;
		}
	}
}

//�����ļ����stationList��map<int,wstring>��
void traverse(map<int, wstring> stationList, wfstream& output)
{
	output.open("վ̨���.txt", ios::out);
	if (output.fail())
	{
		cout << "��ȡ�ļ�ʧ�ܣ�" << endl;
		exit(0);
	}
	output.imbue(locale("chs"));
	for (map<int, wstring>::iterator iter = stationList.begin(); iter != stationList.end(); iter++)
		output << "[" << (*iter).first << "]\t" << (*iter).second << endl;

	wcout << endl;
}

/*	
	ָ����ʼ�ڵ��dijkstra�㷨�����ٻ��ˣ�
	flag=0�����ٻ��ˣ�	flag=1������վ��
*/
void dijkstra(int start,int size,bool flag)
{
	for (int i = 0; i <= size; i++)
		vis[i] = false;
	for (int i = 0; i < STATION_NUM; i++)
		dis[i] = INF;
	dis[start] = 0;
	int cur = start;

	if(!flag)
	{
		while (!vis[cur])
		{
			vis[cur] = true;
			for (int i = 1; i <= size; i++)
			{
				if (!vis[i] && (dis[i] > dis[cur] + Graph_1[cur][i].first))
				{
					dis[i] = dis[cur] + Graph_1[cur][i].first;
					way[i] = cur;
				}
			}
			int min = INF;
			for (int i = 1; i <= size; i++)
			{
				if (!vis[i] && min > dis[i])
				{
					min = dis[i];
					cur = i;
				}
			}
		}
	}
	else
	{
		while (!vis[cur])
		{
			vis[cur] = true;
			for (int i = 1; i <= size; i++)
			{
				if (!vis[i] && (dis[i] > dis[cur] + Graph_2[cur][i].first))
				{
					dis[i] = dis[cur] + Graph_2[cur][i].first;
					way[i] = cur;
				}
			}
			int min = INF;
			for (int i = 1; i <= size; i++)
			{
				if (!vis[i] && min > dis[i])
				{
					min = dis[i];
					cur = i;
				}
			}
		}

	}
}

//���·��������ʾ����վ���յ�վ�Լ�����վ��·�ߣ�
void PrintRoute(int start, int end, bool flag)
{
	if (dis[end] == INF)
	{
		wcout << L"û�д�" << number_station[start] << L"[" << start << L"]��" << number_station[end] << L"[" << end << L"]��ֱ�ӻ��˷�����" << endl << endl;
		return;
	}
	if (!flag)
	{
		cout << "���˴���Ϊ��" << "\t" << dis[end] - 1 << endl << endl;
		wcout << L"���˹���Ϊ��" << endl << endl;
		stack<int> S;
		S.push(end);
		while (S.top() != start)
			S.push(way[S.top()]);
		while (S.size() > 1)
		{
			int i = S.top();
			S.pop();
			int j = S.top();
			wcout << number_station[i] << L"[" << Graph_1[i][j].second << L"·]" << endl;
			cout << "  |\n  V" << endl;
		}
		wcout << number_station[S.top()] << endl << endl;
	}
	else
	{
		cout << "����վ����" << "\t" << dis[end] + 1 << endl << endl;
		wcout << L"����˳��Ϊ��" << endl << endl;
		stack<int> S;
		S.push(end);
		while (S.top() != start)
			S.push(way[S.top()]);
		while (S.size() > 1)
		{
			int i = S.top();
			S.pop();
			int j = S.top();
			wcout << number_station[i] << endl;
			cout << "  |\n  V" << endl;
		}
		wcout << number_station[S.top()] << endl << endl;
	}
}

//����
void implement(bool flag)
{
	wstring tmpStation;
	int start, end;
	map<wstring, int>::iterator i;
	cout << "===========================================" << endl;
	if (flag == LEAST_TRANSFER)
		cout << "����ѡ��Ϊ��������..." << endl;
	else
		cout << "����ѡ��Ϊ��������..." << endl;
	cout << endl << endl;
	cout << "��������ʼվ�㣺" << endl << endl;
	wcin >> tmpStation;
	i = station_number.find(tmpStation);
	while (i == station_number.end())
	{
		cout << "�����ڸ�վ�㣡" << endl << endl;
		cout << "��������ʼվ�㣺" << endl << endl;
		wcin >> tmpStation;
		i = station_number.find(tmpStation);
	}
	start = (*i).second;
	wcout << L"վ̨��ţ�" << "\t[" << start << "]" << endl << endl;
	dijkstra(start, station_number.size(), flag);
	cout << "�������յ�վ�㣺" << endl << endl;
	wcin >> tmpStation;
	i = station_number.find(tmpStation);
	while (i == station_number.end())
	{
		cout << "�����ڸ�վ�㣡" << endl << endl;
		cout << "�������յ�վ�㣺" << endl << endl;
		wcin >> tmpStation;
		i = station_number.find(tmpStation);
	}
	end = (*i).second;
	wcout << L"վ̨��ţ�" << "\t[" << end << "]" << endl << endl;

	PrintRoute(start, end, flag);

	//cout << "����վ�㣺" << endl;
	system("pause");

}
/*****************************�����������****************************/


