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
		cout << "------------²Ëµ¥------------" << endl;
		cout << "ÌáÊ¾£º0.datºÍ1.dat·Ö±ðÎªÉýÐòºÍ½µÐòÅÅÁÐ£¬Æ½¾ùÊ±¼äÎªºó8¸öÎÄ¼þÆ½¾ùÊ±¼ä¡£" << endl;
		cout << "1.²âÊÔÖ±½Ó²åÈëÅÅÐò" << endl;
		cout << "2.²âÊÔÏ£¶ûÅÅÐò" << endl;
		cout << "3.²âÊÔÃ°ÅÝÅÅÐò" << endl;
		cout << "4.²âÊÔ¿ìËÙÅÅÐò" << endl;
		cout << "5.²âÊÔÑ¡ÔñÅÅÐò" << endl;
		cout << "6.²âÊÔ¶ÑÅÅÐò" << endl;
		cout << "7.²âÊÔ¹é²¢ÅÅÐò" << endl;
		cout << "8.²âÊÔ»ùÊýÅÅÐò" << endl;
		cout << "0.ÍË³ö" << endl;
		cout << "----------------------------" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Ö±½Ó²åÈëÅÅÐò£º" << endl;
			TestInsertSort(resource);
			system("pause");
			break;

		case 2:
			cout << "Ï£¶ûÅÅÐò£º" << endl;
			TestShellsSort(resource);
			system("pause");
			break;
		
		case 3:
			cout << "Ã°ÅÝÅÅÐò£º" << endl;
			TestBubbleSort(resource);
			system("pause");
			break;
		
		case 4:
			cout << "¿ìËÙÅÅÐò£º" << endl;
			TestQuickSort(resource);
			system("pause");
			break;
		
		case 5:
			cout << "Ñ¡ÔñÅÅÐò£º" << endl;
			TestSelectSort(resource);
			system("pause");
			break;
		
		case 6:
			cout << "¶ÑÅÅÐò£º" << endl;
			TestHeapSort(resource);
			system("pause");
			break;
		
		case 7:
			cout << "¹é²¢ÅÅÐò£º" << endl;
			TestMergeSort(resource);
			system("pause");
			break;
		
		case 8:
			cout << "»ùÊýÅÅÐò£º" << endl;
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