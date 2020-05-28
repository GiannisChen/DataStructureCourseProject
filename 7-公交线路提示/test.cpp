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
//工作方式
#define LEAST_TRANSFER 0
#define LEAST_STATION 1
const int INF = 0x3f3f3f3f;

using namespace std;

/*****************************结构定义*******************************/
//站点信息
struct station
{
	wstring name;
	int label;
	list<int> bus_label;
};

//存放公交编号和站点
map<int, vector<int>> bus;
//存放站点——编号信息
map<int, wstring> number_station;
map<wstring, int> station_number;
//图<转乘参数,公交编号>
pair<int, int> Graph_1[STATION_NUM][STATION_NUM];
pair<int, int> Graph_2[STATION_NUM][STATION_NUM];
//路径
int dis[STATION_NUM], way[STATION_NUM];
bool vis[STATION_NUM];


/*****************************结构定义结束****************************/

/*****************************函数声明*******************************/
//int转wstring
void itow(int a, wstring& w);

//初始化存储结构
void init(wfstream& resource);

//测试输出bus（map）
void traverse(map<int, vector<int>> bus);

//测试输出stationList（map<wstring,int>）
void traverse(map<wstring, int> stationList);

//测试输出stationList（map<int,wstring>）
void traverse(map<int, wstring> stationList);

//测试文件输出stationList（map<int,wstring>）
void traverse(map<int, wstring> stationList,wfstream &output);

//G_1的逐行插入
void GraphInsert(int buNum,vector<int> l);

//指定开始节点的dijkstra算法（最少换乘）
void dijkstra(int start, int size, bool flag = LEAST_TRANSFER);

//输出路径（仅显示出发站、终点站以及换乘站和路线）
void PrintRoute(int start, int end, bool flag = LEAST_TRANSFER);

//集成
void implement(bool flag = LEAST_TRANSFER);
/*****************************函数声明结束****************************/

int main()
{
	cout << "===========================================" << endl;
	cout << endl;
	cout << "加载中，请稍后..." << endl;
	cout << endl;
	wfstream resource, output;
	resource.open("南京公交线路.txt", ios::in);
	
	//resource.open("test.txt", ios::in);
	resource.imbue(locale("chs"));
	wcout.imbue(locale("chs"));
	wcin.imbue(locale("chs"));
	if (resource.fail())
	{
		cout << "读取文件失败！" << endl;
		exit(0);
	}
	
	init(resource);
	cout << "读取成功！" << endl;
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
		cout << "选择工作方式：" << endl;
		
		cout << setw(10) << "换乘最少" << "\t\t0" << endl;
		cout << setw(10) << "站点最少" << "\t\t1" << endl;
		cout << setw(10) << "退出" << "\t\t-1" << endl;
		cout << "===========================================" << endl;
		cout << "您的选择是：";
		cin >> choice;
		if (choice == -1)
		{
			cout << "退出程序！" << endl;
			exit(0);
		}
		else if (choice > 1 || choice < -1)
			continue;
		else
			implement(choice);
	}
	return 0;
}

/*****************************函数定义*******************************/

//int转wstring
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

//初始化存储结构
void init(wfstream& resource)
{
	//初始化
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

	//读取
	resource >> second;
	while (!resource.eof())
	{
		first = second;
		resource >> second;
		//处理数字
		if (first >= '0' && first <= '9')
		{
			tmpN = tmpN * 10 + first - '0';
			//判断为公交编号
			if (second == L'路')
			{
				//cout << endl;
				//可能有遗漏的前一个站点未处理
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
				//cout << busNum << "路：" << endl;
				tmpN = 0;
				resource >> second;
			}
			//仍是数字
			else if (second >= '0' && second <= '9')
				continue;
			//是数字，但是是站点名称的数字（进行转化）
			else
			{
				itow(tmpN, s);//数字转换成字符串
				tmpN = 0;
			}
		}
		//处理文字和符号
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

//测试输出bus（map）
void traverse(map<int, vector<int>> bus)
{
	for (map<int, vector<int>>::iterator bus_iter = bus.begin(); bus_iter != bus.end(); bus_iter++)
	{
		wcout << (*bus_iter).first;
		cout << "路：" << endl;
		for (vector<int>::iterator iter = (*bus_iter).second.begin(); iter != (*bus_iter).second.end(); iter++)
			wcout << (*iter) << "  ";
		cout << endl;
	}
	wcout << endl;
}

//测试输出stationList（map<wstring,int>）
void traverse(map< wstring, int> stationList)
{
	for (map<wstring, int>::iterator iter = stationList.begin(); iter != stationList.end(); iter++)
		wcout << "[" << (*iter).second << "]\t" << (*iter).first << endl;
	wcout << endl;
}

//测试输出stationList（map<int,wstring>）
void traverse(map<int, wstring> stationList)
{
	for (map<int, wstring>::iterator iter = stationList.begin(); iter != stationList.end(); iter++)
		wcout << "[" << (*iter).first << "]\t" << (*iter).second << endl;
	wcout << endl;
}

//G的初始化
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

//测试文件输出stationList（map<int,wstring>）
void traverse(map<int, wstring> stationList, wfstream& output)
{
	output.open("站台编号.txt", ios::out);
	if (output.fail())
	{
		cout << "读取文件失败！" << endl;
		exit(0);
	}
	output.imbue(locale("chs"));
	for (map<int, wstring>::iterator iter = stationList.begin(); iter != stationList.end(); iter++)
		output << "[" << (*iter).first << "]\t" << (*iter).second << endl;

	wcout << endl;
}

/*	
	指定开始节点的dijkstra算法（最少换乘）
	flag=0（最少换乘）	flag=1（最少站）
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

//输出路径（仅显示出发站、终点站以及换乘站和路线）
void PrintRoute(int start, int end, bool flag)
{
	if (dis[end] == INF)
	{
		wcout << L"没有从" << number_station[start] << L"[" << start << L"]到" << number_station[end] << L"[" << end << L"]的直接换乘方案！" << endl << endl;
		return;
	}
	if (!flag)
	{
		cout << "换乘次数为：" << "\t" << dis[end] - 1 << endl << endl;
		wcout << L"换乘过程为：" << endl << endl;
		stack<int> S;
		S.push(end);
		while (S.top() != start)
			S.push(way[S.top()]);
		while (S.size() > 1)
		{
			int i = S.top();
			S.pop();
			int j = S.top();
			wcout << number_station[i] << L"[" << Graph_1[i][j].second << L"路]" << endl;
			cout << "  |\n  V" << endl;
		}
		wcout << number_station[S.top()] << endl << endl;
	}
	else
	{
		cout << "经过站数：" << "\t" << dis[end] + 1 << endl << endl;
		wcout << L"乘坐顺序为：" << endl << endl;
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

//集成
void implement(bool flag)
{
	wstring tmpStation;
	int start, end;
	map<wstring, int>::iterator i;
	cout << "===========================================" << endl;
	if (flag == LEAST_TRANSFER)
		cout << "您的选择为换乘最少..." << endl;
	else
		cout << "您的选择为换乘最少..." << endl;
	cout << endl << endl;
	cout << "请输入起始站点：" << endl << endl;
	wcin >> tmpStation;
	i = station_number.find(tmpStation);
	while (i == station_number.end())
	{
		cout << "不存在该站点！" << endl << endl;
		cout << "请输入起始站点：" << endl << endl;
		wcin >> tmpStation;
		i = station_number.find(tmpStation);
	}
	start = (*i).second;
	wcout << L"站台编号：" << "\t[" << start << "]" << endl << endl;
	dijkstra(start, station_number.size(), flag);
	cout << "请输入终点站点：" << endl << endl;
	wcin >> tmpStation;
	i = station_number.find(tmpStation);
	while (i == station_number.end())
	{
		cout << "不存在该站点！" << endl << endl;
		cout << "请输入终点站点：" << endl << endl;
		wcin >> tmpStation;
		i = station_number.find(tmpStation);
	}
	end = (*i).second;
	wcout << L"站台编号：" << "\t[" << end << "]" << endl << endl;

	PrintRoute(start, end, flag);

	//cout << "经过站点：" << endl;
	system("pause");

}
/*****************************函数定义结束****************************/


