#include <iostream>
#include <ctime>
#include <fstream>
#include "AVLTree.h"

using namespace std;

int main()
{
	AVLTree testT;
	ElementType x;
	BT pTemp;
	char flag;
	int i;

	string fileName = "tree.txt";
	fstream inf(fileName, ios::in);
	if (!inf.is_open())
		std::cout << "Error opening file!" << endl;

	while (!inf.eof())
	{
		ElementType n;
		inf >> n;
		testT.Insert(n);
	}

	while (true)
	{
		cout << "-----------------------***-----------------------" << endl;
		cout << "test:递归和非递归前序遍历--------------a" << endl;
		cout << "test:递归和非递归中序遍历--------------b" << endl;
		cout << "test:递归和非递归后序遍历--------------c" << endl;
		cout << "test:层序遍历--------------------------d" << endl;
		cout << "test:返回树高--------------------------e" << endl;
		cout << "test:查找某个节点----------------------f" << endl;
		cout << "test:返回树的根节点--------------------g" << endl;
		cout << "test:删除某个节点----------------------h" << endl;
		cout << "test:清空此树--------------------------i" << endl;
		cout << "test:恢复最初的二叉搜索树--------------j" << endl;
		cout << "test:插入某个节点----------------------k" << endl;
		
		cout << "exit--------------------z" << endl;
		cout << "-----------------------***-----------------------" << endl;
		cin >> flag;
		cout << "--------------------------------------------------" << endl;
		switch (flag)
		{
		case 'a':
			cout << "递归前序遍历：" << endl;
			testT.R_PreOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "非递归前序遍历：" << endl;
			testT.N_PreOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'b':
			cout << "递归中序遍历：" << endl;
			testT.R_InOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "非递归中序遍历：" << endl;
			testT.R_InOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'c':
			cout << "递归后序遍历：" << endl;
			testT.R_PostOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "非递归后序遍历：" << endl;
			testT.R_PostOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'd':
			cout << "层序遍历：" << endl;
			testT.LevelOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'e':
			cout << "返回树高：";
			cout << testT.Height() << endl;
			system("pause");
			break;

		case 'f':
			cout << "请输入需要查找的值：";
			cin >> x;
			cout << "查找结果：" << endl;
			pTemp = testT.Find(x);
			if (!pTemp)
				cout << "该内容不存在！" << endl;
			else
			{
				cout << "找到了！" << endl;
				while (1)
				{
					cout << "1. 查找:内容为" << x << "的父节点;" << endl;
					cout << "2. 查找:内容为" << x << "的左孩子;" << endl;
					cout << "3. 查找:内容为" << x << "的右孩子;" << endl;
					cout << "4. 查找:内容为" << x << "的左兄弟;" << endl;
					cout << "5. 查找:内容为" << x << "的右兄弟;" << endl;
					cout << "-1.返回。" << endl;
					cin >> i;

					switch (i)
					{
					case 1:
						cout << "父节点查找结果：" << endl;
						pTemp = testT.FindParent(x);
						if (!pTemp)
							cout << "未找到父节点，为根节点！" << endl;
						else
							cout << "父节点为：" << pTemp->data << endl;
						system("pause");
						break;

					case 2:
						cout << "左孩子查找结果：" << endl;
						pTemp = testT.FindLeftChild(x);
						if (!pTemp)
							cout << "未找到左孩子！" << endl;
						else
							cout << "左孩子为：" << pTemp->data << endl;
						system("pause");
						break;

					case 3:
						cout << "右孩子查找结果：" << endl;
						pTemp = testT.FindRightChild(x);
						if (!pTemp)
							cout << "未找到右孩子！" << endl;
						else
							cout << "右孩子为：" << pTemp->data << endl;
						system("pause");
						break;

					case 4:
						cout << "左兄弟查找结果：" << endl;
						pTemp = testT.FindLeftSibling(x);
						if (!pTemp || x==pTemp->data)
							cout << "未找到左兄弟！" << endl;
						else
							cout << "左兄弟为：" << pTemp->data << endl;
						system("pause");
						break;

					case 5:
						cout << "右兄弟查找结果：" << endl;
						pTemp = testT.FindRightSibling(x);
						if (!pTemp || x==pTemp->data)
							cout << "未找到右兄弟！" << endl;
						else
							cout << "右兄弟为：" << pTemp->data << endl;
						system("pause");
						break;

					case -1:
						break;
					default:
						break;
					}
					if (i == -1)
						break;
				}

			}
				
			pTemp = NULL;
			delete pTemp;
			break;

		case 'g':
			pTemp = testT.ReturnTreeRoot();
			if (pTemp)
				cout << "该树根节点为：" << pTemp->data << endl;
			else
				cout << "树为空！" << endl;
			system("pause");
			break;

		case 'h':
			cout << "请输入需要删除的值：";
			cin >> x;
			testT.Delete(x);
			system("pause");
			break;

		case 'i':
			testT.Clear();
			cout << "清空成功！" << endl;
			system("pause");
			break;

		case 'j':
			if (testT.TreeRoot)
				testT.Clear();
			inf.seekg(0, ios::beg);
			while (!inf.eof())
			{
				char tmp[8];
				inf.getline(tmp, 8);
				testT.Insert(atoi(tmp));
			}
			cout << "平衡二叉搜索树恢复！" << endl;
			system("pause");
			break;
		
		case 'k':
			int insert;
			cout << "请输入需要插入的值：";
			cin >> insert;
			testT.Insert(insert);
			cout << "插入成功！" << endl;
			system("pause");
			break;

		case 'z':
			exit(0);
			testT.Clear();
			break;

		default:
			break;
		}
	}

	return 0;
}