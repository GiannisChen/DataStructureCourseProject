#define _CRT_SECURE_NO_WARNINGS
#include"BTree.h"
#include <iomanip>

using namespace std;

int main()
{
	//������������
	int scan = 0;  
	B_Tree T; 
	
	//B���п�   
	cout << "B��T�Ƿ�Ϊ�գ���" << endl;
	if (T.empty())
		cout << "true" << endl << endl;
	else
		cout << "false" << endl;
	int a[15];
	int b[15] = { 3,12,24,37,45,50,53,61,70,90,100,75,65,33,7};
	////ÿ�ζ�ʹ�ò�ͬ���������
	//srand((unsigned)time(NULL)); 
	////����15��С��1000���������
	//for (int i = 0; i < 15; i++)
	//	a[i] = rand()%100;

	cout << "��ʼ��������B���Ľڵ�ֵ����" << endl;
	for (int i = 0; i < 15; i++)
		cout << b[i] << " ";
	cout << endl << endl;

	cout << "����ؼ���������ԣ�" << endl;
	if (T.insert(b, 15) == true)
		cout << "ȫ������ɹ�" << endl;
	else
		cout << "�в��ֹؼ��ֵ�ֵ��ͬ������ʧ��" << endl;
	cout << endl << endl;

	cout << "��α���B������(ͬһ�ڵ�Ĺؼ���֮���ö�������������ö���ո��������ͬ��Ĺؼ����ڲ�ͬ����)��" << endl;
	bool(*visit)(KeyType e,bool flag) = visitValue;
	T.traverse(visit);
	cout << endl << endl;

	cout << "��B���Ĺؼ����ܸ������ԣ�" << endl;
	cout << "B���Ĺؼ����ܸ���Ϊ��" << T.keySum() << endl << endl;

	char choice;
	
	while (true)
	{
		cout << "===============================================" << endl;
		cout << "B������(ͬһ�ڵ�Ĺؼ���֮���ö�������������ö���ո��������ͬ��Ĺؼ����ڲ�ͬ����)��" << endl;
		cout << "===============================================" << endl;
		cout << left << setw(30) << "���ӹؼ���" << right << 1 << endl;
		cout << left << setw(30) << "���ҹؼ���" << right << 2 << endl;
		cout << left << setw(30) << "ɾ���ؼ���" << right << 3 << endl;
		cout << left << setw(30) << "�������߼��ؼ�������" << right << 4 << endl;
		cout << left << setw(30) << "�˳�" << right << "r" << endl;
		cin >> choice;
		switch (choice)
		{
		case '1':
			cout << "�������������ݣ�";
			cin >> scan;
			if (T.insert(scan))
				cout << "����ɹ�" << endl;
			else
				cout << "����ʧ�ܣ���ԭ�йؼ�����ͬ" << endl;
			cout << "===============================================" << endl;
			cout << "��α���B�����£�" << endl;
			T.traverse(visit);
			cout << endl << endl;
			system("pause");
			break;
		case '2':
			cout << "��������ҵ����ݣ�";
			cin >> scan;
			if (T.search(scan))
				cout << "���ҵ�" << endl;
			else
				cout << "δ�ҵ�" << endl;
			cout << "===============================================" << endl;
			cout << "��α���B�����£�" << endl;
			T.traverse(visit);
			cout << endl << endl;
			system("pause");
			break;

		case '3':
			cout << "�����ɾ�������ݣ�";
			cin >> scan;
			if (T.erase(scan))
				cout << "ɾ���ɹ�" << endl;
			else
				cout << "�����ڸùؼ���" << endl;
			cout << "===============================================" << endl;
			cout << "��α���B�����£�" << endl;
			T.traverse(visit);
			cout << endl << endl;
			system("pause");
			break;

		case '4':
			cout << "B�������Ϊ��" << endl << T.depth() << endl;
			cout << "B���Ĺؼ����ܸ���Ϊ��" << endl << T.keySum() << endl;
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