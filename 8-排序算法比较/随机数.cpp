#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
int main()
{
	fstream text;
	vector<string> index;
	index.push_back("0.dat");
	index.push_back("1.dat");
	index.push_back("2.dat");
	index.push_back("3.dat");
	index.push_back("4.dat");
	index.push_back("5.dat");
	index.push_back("6.dat");
	index.push_back("7.dat");
	index.push_back("8.dat");
	index.push_back("9.dat");

	text.open(index.at(0), ios::out | ios::binary);
	text << (int)1;
	for (int i = 2; i <= 20000; i++)
		text << " " << i;
	text.close();

	text.open(index.at(1), ios::out | ios::binary);
	text << (int)20000;
	for (int i = 19999; i >= 1; i--)
		text << " " << i;
	text.close();

	for (int i = 2; i <= 9; i++)
	{
		
		text.open(index.at(i), ios::out | ios::binary);
		if (text.fail())
		{
			cout << index.at(i) << "文件打开失败！" << endl;
			continue;
		}
		text << (int)(rand() % 20000);
		for (int j = 2; j <= 20000; j++)
			text << " " << (int)(rand() % 20000);
		text.close();
	}
	cout << "随机数结束！" << endl;

	text.close();
	return 0;
}