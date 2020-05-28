#define _CRT_SECURE_NO_WARNINGS
#include"BTree.h"
#include <iomanip>

using namespace std;

int main()
{
	//用于输入数据
	int scan = 0;  
	B_Tree T; 
	
	//B树判空   
	cout << "B树T是否为空？：" << endl;
	if (T.empty())
		cout << "true" << endl << endl;
	else
		cout << "false" << endl;
	int a[15];
	int b[15] = { 3,12,24,37,45,50,53,61,70,90,100,75,65,33,7};
	////每次都使用不同的随机因子
	//srand((unsigned)time(NULL)); 
	////生成15个小于1000的随机整数
	//for (int i = 0; i < 15; i++)
	//	a[i] = rand()%100;

	cout << "初始化：插入B树的节点值如下" << endl;
	for (int i = 0; i < 15; i++)
		cout << b[i] << " ";
	cout << endl << endl;

	cout << "插入关键字数组测试：" << endl;
	if (T.insert(b, 15) == true)
		cout << "全部插入成功" << endl;
	else
		cout << "有部分关键字的值相同，插入失败" << endl;
	cout << endl << endl;

	cout << "层次遍历B树如下(同一节点的关键字之间用逗号相隔，否则用多个空格相隔，不同层的关键字在不同的行)：" << endl;
	bool(*visit)(KeyType e,bool flag) = visitValue;
	T.traverse(visit);
	cout << endl << endl;

	cout << "求B树的关键字总个数测试：" << endl;
	cout << "B树的关键字总个数为：" << T.keySum() << endl << endl;

	char choice;
	
	while (true)
	{
		cout << "===============================================" << endl;
		cout << "B树测试(同一节点的关键字之间用逗号相隔，否则用多个空格相隔，不同层的关键字在不同的行)：" << endl;
		cout << "===============================================" << endl;
		cout << left << setw(30) << "增加关键字" << right << 1 << endl;
		cout << left << setw(30) << "查找关键字" << right << 2 << endl;
		cout << left << setw(30) << "删除关键字" << right << 3 << endl;
		cout << left << setw(30) << "返回树高及关键词总数" << right << 4 << endl;
		cout << left << setw(30) << "退出" << right << "r" << endl;
		cin >> choice;
		switch (choice)
		{
		case '1':
			cout << "输入待插入的内容：";
			cin >> scan;
			if (T.insert(scan))
				cout << "插入成功" << endl;
			else
				cout << "插入失败，与原有关键词相同" << endl;
			cout << "===============================================" << endl;
			cout << "层次遍历B树如下：" << endl;
			T.traverse(visit);
			cout << endl << endl;
			system("pause");
			break;
		case '2':
			cout << "输入待查找的内容：";
			cin >> scan;
			if (T.search(scan))
				cout << "已找到" << endl;
			else
				cout << "未找到" << endl;
			cout << "===============================================" << endl;
			cout << "层次遍历B树如下：" << endl;
			T.traverse(visit);
			cout << endl << endl;
			system("pause");
			break;

		case '3':
			cout << "输入待删除的内容：";
			cin >> scan;
			if (T.erase(scan))
				cout << "删除成功" << endl;
			else
				cout << "不存在该关键字" << endl;
			cout << "===============================================" << endl;
			cout << "层次遍历B树如下：" << endl;
			T.traverse(visit);
			cout << endl << endl;
			system("pause");
			break;

		case '4':
			cout << "B树的深度为：" << endl << T.depth() << endl;
			cout << "B树的关键字总个数为：" << endl << T.keySum() << endl;
			break;

		case 'r':
			exit(0);
			break;

		default:
			break;
		}
	}

	return 0;
}