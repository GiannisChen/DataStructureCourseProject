#include "MyStack.h"
#include "fuction.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

#define RESOURCE "resource.txt"
#define PROCESS "process.txt"

int main()
{
	fstream resource, process;
	resource.open(RESOURCE, ios::in);
	process.open(PROCESS, ios::out);
	if (resource.fail())
	{
		cout << "源文件打开失败！" << endl;
		exit(0);
	}
	if (process.fail())
	{
		cout << "过程输出文件打开失败！" << endl;
		exit(0);
	}

	char line[1024];
	//string test_line("#6+15*(21-8/4)#");
	while(resource.getline(line, 1024))
	{
		cout << string(line) << endl;
		operation(line);
		system("pause");
		system("CLS");
		
	}
	//operation(test_line);
	return 0;
}