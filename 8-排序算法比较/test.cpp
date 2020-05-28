#include "sort.h"

using namespace std;

int main()
{
	vector<string> resource;
	resource.push_back("0.dat");
	resource.push_back("1.dat");
	resource.push_back("2.dat");
	resource.push_back("3.dat");
	resource.push_back("4.dat");
	resource.push_back("5.dat");
	resource.push_back("6.dat");
	resource.push_back("7.dat");
	resource.push_back("8.dat");
	resource.push_back("9.dat");
	int times = 10;
	
	while (true)
	{
		int choice;
		cout << "------------�˵�------------" << endl;
		cout << "��ʾ��0.dat��1.dat�ֱ�Ϊ����ͽ������У�ƽ��ʱ��Ϊ��8���ļ�ƽ��ʱ�䡣" << endl;
		cout << "1.����ֱ�Ӳ�������" << endl;
		cout << "2.����ϣ������" << endl;
		cout << "3.����ð������" << endl;
		cout << "4.���Կ�������" << endl;
		cout << "5.����ѡ������" << endl;
		cout << "6.���Զ�����" << endl;
		cout << "7.���Թ鲢����" << endl;
		cout << "8.���Ի�������" << endl;
		cout << "0.�˳�" << endl;
		cout << "----------------------------" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "ֱ�Ӳ�������" << endl;
			TestInsertSort(resource);
			system("pause");
			break;

		case 2:
			cout << "ϣ������" << endl;
			TestShellsSort(resource);
			system("pause");
			break;
		
		case 3:
			cout << "ð������" << endl;
			TestBubbleSort(resource);
			system("pause");
			break;
		
		case 4:
			cout << "��������" << endl;
			TestQuickSort(resource);
			system("pause");
			break;
		
		case 5:
			cout << "ѡ������" << endl;
			TestSelectSort(resource);
			system("pause");
			break;
		
		case 6:
			cout << "������" << endl;
			TestHeapSort(resource);
			system("pause");
			break;
		
		case 7:
			cout << "�鲢����" << endl;
			TestMergeSort(resource);
			system("pause");
			break;
		
		case 8:
			cout << "��������" << endl;
			TestBaseSort(resource);
			system("pause");
			break;
		
		case 0:
			exit(0);
			system("pause");
			break;

		default:
			break;
		}
	}
	
	return 0;
}