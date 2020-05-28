#include <iostream>
#include<list>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <iomanip>
#include <queue>
#include <ctime>
#include <conio.h>
#define cmd "tasklist /FO CSV"
using namespace std;
struct task
{
	string imageName;
	int PID;
	string sessionName;
	int sessionID;
	int memory;
	bool isExistNow;
	double startTime;
	double endTime;
	task(string str) : PID(0), memory(0), sessionID(0), isExistNow(false), startTime(0), endTime(0)
	{
		int index = 1;
		int len = str.size();
		//读取内容的格式:"映像名称","PID","会话名","会话#","内存使用"
		//读映像名称
		while (index < len && str.at(index) != '"')
			imageName.push_back(str.at(index++));
		//跳过","
		index += 3;
		//读PID
		while (index < len && str.at(index) != '"')
			PID = 10 * PID + str.at(index++) - '0';
		index += 3;
		//读会话名
		while (index < len && str.at(index) != '"')
			sessionName.push_back(str.at(index++));
		index += 3;
		//读会话#
		while (index < len && str.at(index) != '"')
			sessionID = 10 * sessionID + str.at(index++) - '0';
		index += 3;
		//读内存使用
		while (index < len && str.at(index) != ' ')
		{
			//跳过分隔符','
			if (str.at(index) != ',')
				memory = 10 * memory + str.at(index) - '0';
			index++;
		}
	}
};

//自定义排序
bool cmp(const task& a, const task& b)
{
	if (a.memory == b.memory)
		return a.PID < b.PID;
	return a.memory < b.memory;
}

void printTaskList(list<task> l)
{
	if (!l.empty())
	{
		//格式化输出
		cout << setw(70) << left << "映像名称" << setw(10) << right << "PID"
			<< setw(15) << left << "   会话名" << setw(5) << "会话#"
			<< setw(10) << right << "        内存使用" << endl;
		cout << setw(70) << left << "======================" << setw(10) << right << "========="
			<< setw(15) << left << "   =================" << setw(5) << "==="
			<< setw(10) << right << "=======" << endl;
		for (list<task>::iterator iter = l.begin(); iter != l.end(); iter++)
		{
			cout << setw(70) << left << (*iter).imageName << setw(10) << right << (*iter).PID << "   "
				<< setw(15) << left << (*iter).sessionName << setw(5) << (*iter).sessionID
				<< setw(10) << right << (*iter).memory << " K" << endl;
		}
	}
	else
	{
		cout << "当前无任何进程！" << endl;
		return;
	}
}

void printClosedTaskList(list<task> l)
{
	if (!l.empty())
	{
		//格式化输出
		cout << setw(70) << left << "已关闭映像名称" << setw(20) << right << "使用时间" << endl;
		cout << setw(70) << left << "======================" << setw(20) << right << "=========" << endl;
		for (list<task>::iterator iter = l.begin(); iter != l.end(); iter++)
		{
			cout << setw(70) << left << (*iter).imageName << setw(20) << right
				<< (double)((*iter).endTime - (*iter).startTime) / CLOCKS_PER_SEC <<"s"<<endl;
		}
	}
	else
	{
		cout << "当前无任何进程！" << endl;
		return;
	}
}
//初始化后的进程读取
void getTask(FILE* pipe, list<task>& cur, list<task>& closed)
{
	char buffer[128];
	double timeTick;
	//该文件第一行为中文提示名称，读但是忽略
	fgets(buffer, 128, pipe);
	//对上一次的进程链表进行搜索
	while (fgets(buffer, 128, pipe))
	{
		bool flag = false;
		//cout << buffer << endl;
		task* tmp = new task(string(buffer));
		for (list<task>::iterator iter = cur.begin(); iter != cur.end(); iter++)
		{
			//同时存在于本次和上次进程中
			if (tmp->imageName == (*iter).imageName)
			{
				(*iter) = *tmp;
				(*iter).isExistNow = true;
				flag = true;
				break;
			}
		}
		//仅存在于当前进程中
		if (!flag)
		{
			tmp->isExistNow = true;
			cur.push_back(*tmp);
		}
		//存在于关闭进程链表中，重启型
		list<task>::iterator iter = closed.begin();
		while (iter != closed.end())
		{
			if (tmp->imageName == (*iter).imageName)
				iter = closed.erase(iter);
			else
				iter++;
		}
	}
	list<task>::iterator iter = cur.begin();
	//处理存在前次进程但不存在本次进程中的数据
	while (iter != cur.end())
	{
		timeTick = clock();
		(*iter).endTime = timeTick;
		if (!(*iter).isExistNow)
		{
			closed.push_back(*iter);
			iter = cur.erase(iter);
		}
		else
		{
			(*iter).isExistNow = false;
			iter++;
		}
	}
	cur.sort(cmp);
}
//初始化读取
void getTask(FILE* pipe, list<task>& cur)
{
	double timeTick;
	char buffer[128];
	//该文件第一行为中文提示名称，读但是忽略
	fgets(buffer, 128, pipe);
	//cout << buffer << endl;
	while (fgets(buffer, 128, pipe))
	{
		//cout << buffer << endl;
		timeTick = clock();
		cur.push_back(task((string)buffer));
		cur.back().startTime = timeTick;
		cur.back().isExistNow = false;
	}
	//排序
	cur.sort(cmp);
}

int main()
{
	list<task> curTaskList;
	list<task> closedTaskList;
	//cmd里输tasklist可以看见该文件内容
	/*char buffer[128];*/
	//使用_popen打开，目前没有文件流替换方案
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return -1;
	getTask(pipe, curTaskList);
	//printTaskList(curTaskList);
	
	//关闭文件
	_pclose(pipe);
	
	//格式化输出
	/*cout << setw(70) << left << "映像名称" << setw(10) << right << "PID"
		<< setw(15) << left << "   会话名" << setw(5) << "会话#"
		<< setw(10) << right << "        内存使用" << endl;
	cout << setw(70) << left << "======================" << setw(10) << right << "========="
		<< setw(15) << left << "   =================" << setw(5) << "==="
		<< setw(10) << right << "=======" << endl;
	for (list<task>::iterator iter = q.begin(); iter != q.end(); iter++)
	{
		cout << setw(70) << left << (*iter).imageName << setw(10) << right << (*iter).PID << "   "
			<< setw(15) << left << (*iter).sessionName << setw(5) << (*iter).sessionID
			<< setw(10) << right << (*iter).memory << " K" << endl;
	}*/
	//printTaskList(curTaskList);

	char choice;
	while (true)
	{
		cout <<left<< "请选择操作：" << endl;
		cout << left << "==========================================================" << endl;
		cout << left << setw(50) << "读取进程并显示已结束进程和使用时间" << right << 1 << endl;
		cout << left << setw(50) << "显示当前保留的进程列表" << right << 2 << endl;
		cout << left << setw(50) << "退出程序" << right << "ESC" << endl;
		cout << left << "==========================================================" << endl;
		cout << "请选择：";
		cin >> choice;

		switch (choice)
		{
		case '1':
			pipe = _popen(cmd, "r");
			if (!pipe)
				return -1;
			getTask(pipe, curTaskList, closedTaskList);
			_pclose(pipe);
			printClosedTaskList(closedTaskList);
			system("pause");
			break;

		case '2':
			printTaskList(curTaskList);
			system("pause");
			break;

		case 27:
			exit(0);
			break;
		default:
			break;
		}
		

	}

	return 0;
}