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
		cout << "test:�ݹ�ͷǵݹ�ǰ�����--------------a" << endl;
		cout << "test:�ݹ�ͷǵݹ��������--------------b" << endl;
		cout << "test:�ݹ�ͷǵݹ�������--------------c" << endl;
		cout << "test:�������--------------------------d" << endl;
		cout << "test:��������--------------------------e" << endl;
		cout << "test:����ĳ���ڵ�----------------------f" << endl;
		cout << "test:�������ĸ��ڵ�--------------------g" << endl;
		cout << "test:ɾ��ĳ���ڵ�----------------------h" << endl;
		cout << "test:��մ���--------------------------i" << endl;
		cout << "test:�ָ�����Ķ���������--------------j" << endl;
		cout << "test:����ĳ���ڵ�----------------------k" << endl;
		
		cout << "exit--------------------z" << endl;
		cout << "-----------------------***-----------------------" << endl;
		cin >> flag;
		cout << "--------------------------------------------------" << endl;
		switch (flag)
		{
		case 'a':
			cout << "�ݹ�ǰ�������" << endl;
			testT.R_PreOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "�ǵݹ�ǰ�������" << endl;
			testT.N_PreOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'b':
			cout << "�ݹ����������" << endl;
			testT.R_InOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "�ǵݹ����������" << endl;
			testT.R_InOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'c':
			cout << "�ݹ���������" << endl;
			testT.R_PostOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			cout << "�ǵݹ���������" << endl;
			testT.R_PostOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'd':
			cout << "���������" << endl;
			testT.LevelOrderTravel();
			cout << endl;
			cout << "--------------------------------------------------" << endl;
			system("pause");
			break;

		case 'e':
			cout << "�������ߣ�";
			cout << testT.Height() << endl;
			system("pause");
			break;

		case 'f':
			cout << "��������Ҫ���ҵ�ֵ��";
			cin >> x;
			cout << "���ҽ����" << endl;
			pTemp = testT.Find(x);
			if (!pTemp)
				cout << "�����ݲ����ڣ�" << endl;
			else
			{
				cout << "�ҵ��ˣ�" << endl;
				while (1)
				{
					cout << "1. ����:����Ϊ" << x << "�ĸ��ڵ�;" << endl;
					cout << "2. ����:����Ϊ" << x << "������;" << endl;
					cout << "3. ����:����Ϊ" << x << "���Һ���;" << endl;
					cout << "4. ����:����Ϊ" << x << "�����ֵ�;" << endl;
					cout << "5. ����:����Ϊ" << x << "�����ֵ�;" << endl;
					cout << "-1.���ء�" << endl;
					cin >> i;

					switch (i)
					{
					case 1:
						cout << "���ڵ���ҽ����" << endl;
						pTemp = testT.FindParent(x);
						if (!pTemp)
							cout << "δ�ҵ����ڵ㣬Ϊ���ڵ㣡" << endl;
						else
							cout << "���ڵ�Ϊ��" << pTemp->data << endl;
						system("pause");
						break;

					case 2:
						cout << "���Ӳ��ҽ����" << endl;
						pTemp = testT.FindLeftChild(x);
						if (!pTemp)
							cout << "δ�ҵ����ӣ�" << endl;
						else
							cout << "����Ϊ��" << pTemp->data << endl;
						system("pause");
						break;

					case 3:
						cout << "�Һ��Ӳ��ҽ����" << endl;
						pTemp = testT.FindRightChild(x);
						if (!pTemp)
							cout << "δ�ҵ��Һ��ӣ�" << endl;
						else
							cout << "�Һ���Ϊ��" << pTemp->data << endl;
						system("pause");
						break;

					case 4:
						cout << "���ֵܲ��ҽ����" << endl;
						pTemp = testT.FindLeftSibling(x);
						if (!pTemp || x==pTemp->data)
							cout << "δ�ҵ����ֵܣ�" << endl;
						else
							cout << "���ֵ�Ϊ��" << pTemp->data << endl;
						system("pause");
						break;

					case 5:
						cout << "���ֵܲ��ҽ����" << endl;
						pTemp = testT.FindRightSibling(x);
						if (!pTemp || x==pTemp->data)
							cout << "δ�ҵ����ֵܣ�" << endl;
						else
							cout << "���ֵ�Ϊ��" << pTemp->data << endl;
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
				cout << "�������ڵ�Ϊ��" << pTemp->data << endl;
			else
				cout << "��Ϊ�գ�" << endl;
			system("pause");
			break;

		case 'h':
			cout << "��������Ҫɾ����ֵ��";
			cin >> x;
			testT.Delete(x);
			system("pause");
			break;

		case 'i':
			testT.Clear();
			cout << "��ճɹ���" << endl;
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
			cout << "ƽ������������ָ���" << endl;
			system("pause");
			break;
		
		case 'k':
			int insert;
			cout << "��������Ҫ�����ֵ��";
			cin >> insert;
			testT.Insert(insert);
			cout << "����ɹ���" << endl;
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