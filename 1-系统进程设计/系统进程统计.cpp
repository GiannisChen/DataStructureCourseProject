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
		//��ȡ���ݵĸ�ʽ:"ӳ������","PID","�Ự��","�Ự#","�ڴ�ʹ��"
		//��ӳ������
		while (index < len && str.at(index) != '"')
			imageName.push_back(str.at(index++));
		//����","
		index += 3;
		//��PID
		while (index < len && str.at(index) != '"')
			PID = 10 * PID + str.at(index++) - '0';
		index += 3;
		//���Ự��
		while (index < len && str.at(index) != '"')
			sessionName.push_back(str.at(index++));
		index += 3;
		//���Ự#
		while (index < len && str.at(index) != '"')
			sessionID = 10 * sessionID + str.at(index++) - '0';
		index += 3;
		//���ڴ�ʹ��
		while (index < len && str.at(index) != ' ')
		{
			//�����ָ���','
			if (str.at(index) != ',')
				memory = 10 * memory + str.at(index) - '0';
			index++;
		}
	}
};

//�Զ�������
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
		//��ʽ�����
		cout << setw(70) << left << "ӳ������" << setw(10) << right << "PID"
			<< setw(15) << left << "   �Ự��" << setw(5) << "�Ự#"
			<< setw(10) << right << "        �ڴ�ʹ��" << endl;
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
		cout << "��ǰ���κν��̣�" << endl;
		return;
	}
}

void printClosedTaskList(list<task> l)
{
	if (!l.empty())
	{
		//��ʽ�����
		cout << setw(70) << left << "�ѹر�ӳ������" << setw(20) << right << "ʹ��ʱ��" << endl;
		cout << setw(70) << left << "======================" << setw(20) << right << "=========" << endl;
		for (list<task>::iterator iter = l.begin(); iter != l.end(); iter++)
		{
			cout << setw(70) << left << (*iter).imageName << setw(20) << right
				<< (double)((*iter).endTime - (*iter).startTime) / CLOCKS_PER_SEC <<"s"<<endl;
		}
	}
	else
	{
		cout << "��ǰ���κν��̣�" << endl;
		return;
	}
}
//��ʼ����Ľ��̶�ȡ
void getTask(FILE* pipe, list<task>& cur, list<task>& closed)
{
	char buffer[128];
	double timeTick;
	//���ļ���һ��Ϊ������ʾ���ƣ������Ǻ���
	fgets(buffer, 128, pipe);
	//����һ�εĽ��������������
	while (fgets(buffer, 128, pipe))
	{
		bool flag = false;
		//cout << buffer << endl;
		task* tmp = new task(string(buffer));
		for (list<task>::iterator iter = cur.begin(); iter != cur.end(); iter++)
		{
			//ͬʱ�����ڱ��κ��ϴν�����
			if (tmp->imageName == (*iter).imageName)
			{
				(*iter) = *tmp;
				(*iter).isExistNow = true;
				flag = true;
				break;
			}
		}
		//�������ڵ�ǰ������
		if (!flag)
		{
			tmp->isExistNow = true;
			cur.push_back(*tmp);
		}
		//�����ڹرս��������У�������
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
	//�������ǰ�ν��̵������ڱ��ν����е�����
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
//��ʼ����ȡ
void getTask(FILE* pipe, list<task>& cur)
{
	double timeTick;
	char buffer[128];
	//���ļ���һ��Ϊ������ʾ���ƣ������Ǻ���
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
	//����
	cur.sort(cmp);
}

int main()
{
	list<task> curTaskList;
	list<task> closedTaskList;
	//cmd����tasklist���Կ������ļ�����
	/*char buffer[128];*/
	//ʹ��_popen�򿪣�Ŀǰû���ļ����滻����
	FILE* pipe = _popen(cmd, "r");
	if (!pipe)
		return -1;
	getTask(pipe, curTaskList);
	//printTaskList(curTaskList);
	
	//�ر��ļ�
	_pclose(pipe);
	
	//��ʽ�����
	/*cout << setw(70) << left << "ӳ������" << setw(10) << right << "PID"
		<< setw(15) << left << "   �Ự��" << setw(5) << "�Ự#"
		<< setw(10) << right << "        �ڴ�ʹ��" << endl;
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
		cout <<left<< "��ѡ�������" << endl;
		cout << left << "==========================================================" << endl;
		cout << left << setw(50) << "��ȡ���̲���ʾ�ѽ������̺�ʹ��ʱ��" << right << 1 << endl;
		cout << left << setw(50) << "��ʾ��ǰ�����Ľ����б�" << right << 2 << endl;
		cout << left << setw(50) << "�˳�����" << right << "ESC" << endl;
		cout << left << "==========================================================" << endl;
		cout << "��ѡ��";
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