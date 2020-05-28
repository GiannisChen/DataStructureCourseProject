#include <iostream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <vector>
#include <list>
#include "define.h"

using namespace std;


int main()
{
	list<member> family;
	wfstream resource;
	resource.open("���ϴ���.txt", ios::in);
	if (resource.fail())
	{
		cout << "�ļ���ʧ�ܣ�" << endl;
		exit(0);
	}

	wcin.imbue(locale("chs"));
	wcout.imbue(locale("chs"));
	resource.imbue(locale("chs"));
	int label, father;
	wstring name;
	Date birth;
	Date death;
	wstring address;
	wstring living;
	FamilyTree FT;

	while (!resource.eof())
	{
		resource >> father >> label >> name >> birth.year >> birth.month
			>> birth.day >> address >> living;
		member tmp = new node;
		if (living == L"��")
			tmp->living = true;
		else
		{
			tmp->living = false;
			resource >> death.year >> death.month >> death.day;
			tmp->death = death;
		}
			
		tmp->label = label;
		tmp->name = name;
		tmp->birth = birth;
		tmp->address = address;
		if (father != label)
			FT.insert(father, tmp);
		else
			FT.insertSpouse(label, tmp);
	}
	cout << "�������" << endl;
	cout << endl << endl;

	
	bool flag = 0;
	int choice;
	int level;
	wstring f;
	member tmp;
	member spouse;
	
	while (true)
	{
		cout << endl << "����ѡ��" << endl;
		cout << "===================================================" << endl;
		cout << "������ż------------------------------------1" << endl;
		cout << "�����Ա------------------------------------2" << endl;
		cout << "�鿴����------------------------------------3" << endl;
		cout << "��ӡ����------------------------------------4" << endl;
		cout << "�޸���Ϣ------------------------------------5" << endl;
		cout << "��ӡ������Ϣ--------------------------------6" << endl;
		cout << "ɾ����Ա------------------------------------7" << endl;
		cout << "ͨ�����ղ��ҳ�Ա----------------------------8" << endl;
		cout << "�˳�����------------------------------------0" << endl;
		cout << "===================================================" << endl;
		cout << "�����룺" << endl;
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			cout << "�����������Ϣ����ʽ������ ��������ż����ͬ�� ������ �� �� סַ��" << endl;
			spouse = new node;
			wcin >> name >> spouse->name >> spouse->birth.year >> spouse->birth.month
				>> spouse->birth.day >> spouse->address;
			if (!FT.insertSpouse(name, spouse))
				wcout << L"�Ҳ������׳�Ա " << name << endl;
			cout << "===================================================" << endl;
			break;

		case 2:
			cout << "�����������Ϣ����ʽ������ ���� ������ �� �� סַ��" << endl;
			tmp = new node;
			wcin>>f>> tmp->name >> tmp->birth.year >> tmp->birth.month
				>> tmp->birth.day >> tmp->address;
			if (!FT.insert(f, tmp))
				cout << "����ʧ�ܣ�" << endl;
			cout << "===================================================" << endl;
			break;

		case 3:
			cout << "��������Ҫ��ϸ��Ϣ��������" << endl;
			wcin >> name;
			if(!FT.print(name))
				wcout << L"�Ҳ������׳�Ա " << name << endl;
			cout << "===================================================" << endl;
			break;

		case 4:
			cout << endl << "��������" << endl;
			FT.traverse();
			break;

		case 5:
			while (!flag)
			{
				cout << "-----------------------------------------------" << endl;
				cout << "\t��������Ҫ�޸ĵ���ϸ���棺" << endl;
				cout << "\t1���޸�����" << endl;
				cout << "\t2���޸�����" << endl;
				cout << "\t3���޸Ļ���״��" << endl;
				cout << "\t4���޸�סַ" << endl;
				cout << "\t5���޸�����״��" << endl;
				cout << "\t0���˳��޸�" << endl;
				cout << "-----------------------------------------------" << endl;
				cout << "������ѡ��" << endl;
				cin >> choice;
				switch (choice)
				{
				case 0:
					flag = 1;
					cout << "===================================================" << endl;
					break;

				case 1:
					cout << "�����뱻�޸���������" << endl;
					wcin >> name;
					cout << "�����뱻�޸��������֣�" << endl;
					wcin >> f;
					if (!FT.modifyName(name, f))
						wcout << L"�Ҳ������׳�Ա " << name << endl;
					break;

				case 2:
					cout << "�����뱻�޸���������" << endl;
					wcin >> name;
					cout << "�����뱻�޸��������գ��� �� �գ���" << endl;
					wcin >> birth.year >> birth.month >> birth.day;
					if (!FT.modifyBirth(name, birth))
						wcout << L"�Ҳ������׳�Ա " << name << endl;
					break;

				case 3:
					cout << "�����뱻�޸���������" << endl;
					wcin >> name;
					cout << "�����뱻�޸��˻���״������/�� ����" << endl;
					wcin >> f;
					if (f == L"��")
					{
						cout << "�����뱻�޸�����ż����ʽ����������ż����ͬ�� ������ �� �� סַ��" << endl;
						spouse = new node;
						wcin >> spouse->name >> spouse->birth.year >> spouse->birth.month
							>> spouse->birth.day >> spouse->address;
						if (!FT.modifyMarriage(name, true, spouse))
							wcout << L"�Ҳ������׳�Ա " << name << endl;
					}
					else
						if (!FT.modifyMarriage(name, false))
							wcout << L"�Ҳ������׳�Ա " << name << endl;
					break;

				case 4:
					cout << "�����뱻�޸���������" << endl;
					wcin >> name;
					cout << "�����뱻�޸���סַ��" << endl;
					wcin >> address;
					if (!FT.modifyAddress(name, address))
						wcout << L"�Ҳ������׳�Ա " << name << endl;
					break;

				case 5:
					cout << "�����뱻�޸���������" << endl;
					wcin >> name;
					cout << "�����뱻�޸����Ƿ���������/�񣩣�" << endl;
					wcin >> f;
					if (f == L"��")
					{
						cout << "�����뱻�޸����������ڣ��� �� �գ���" << endl;
						spouse = new node;
						wcin >> death.year >> death.month >> death.day;
						if (!FT.modifyDeath(name, true, death))
							wcout << L"�Ҳ������׳�Ա " << name << endl;
					}
					else
						if (!FT.modifyDeath(name, false))
							wcout << L"�Ҳ������׳�Ա " << name << endl;
					break;

				default:
					break;
				}
			}
			break;

		case 6:
			cout << "�������n�������ˣ�" << endl;
			cin >> level;
			if (!FT.returnNLevelAll(level))
				cout << "�޵�" << level << "����" << endl;
			cout << "===================================================" << endl;
			break;

		case 7:
			cout << "��������Ҫɾ����������" << endl;
			wcin >> name;
			if (!FT.erase(name))
				wcout << L"�Ҳ������׳�Ա " << name << endl;
			else
				cout << "ɾ���ɹ���" << endl;
			break;

		case 8:
			cout << "���������ѯ��Ա�����գ��� �� �գ���" << endl;
			wcin >> birth.year >> birth.month >> birth.day;
			if(!FT.find(birth))
				wcout << L"�Ҳ������׳�Ա" << endl;
			break;

		case 0:
			exit(0);
			break;

		default:
			break;
		}
	}
	/*while (!family.empty())
	{
		wcout << family.front()->label << L"  " << family.front()->name << L"  ";
		cout << family.front()->birth.year << "--" << setfill('0') << setw(2)
			<< family.front()->birth.month << "--" << setfill('0') << setw(2)
			<< family.front()->birth.day << "  ";
		wcout << family.front()->address << endl;
		family.pop_front();
	}*/

	

	return 0;
}

