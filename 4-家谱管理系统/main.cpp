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
	resource.open("吕氏春秋.txt", ios::in);
	if (resource.fail())
	{
		cout << "文件打开失败！" << endl;
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
		if (living == L"生")
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
	cout << "输出测试" << endl;
	cout << endl << endl;

	
	bool flag = 0;
	int choice;
	int level;
	wstring f;
	member tmp;
	member spouse;
	
	while (true)
	{
		cout << endl << "输入选择：" << endl;
		cout << "===================================================" << endl;
		cout << "插入配偶------------------------------------1" << endl;
		cout << "插入成员------------------------------------2" << endl;
		cout << "查看详情------------------------------------3" << endl;
		cout << "打印家谱------------------------------------4" << endl;
		cout << "修改信息------------------------------------5" << endl;
		cout << "打印整代信息--------------------------------6" << endl;
		cout << "删除成员------------------------------------7" << endl;
		cout << "通过生日查找成员----------------------------8" << endl;
		cout << "退出测试------------------------------------0" << endl;
		cout << "===================================================" << endl;
		cout << "请输入：" << endl;
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			cout << "请输入相关信息（格式：人名 人名（配偶，下同） 出生年 月 日 住址）" << endl;
			spouse = new node;
			wcin >> name >> spouse->name >> spouse->birth.year >> spouse->birth.month
				>> spouse->birth.day >> spouse->address;
			if (!FT.insertSpouse(name, spouse))
				wcout << L"找不到家谱成员 " << name << endl;
			cout << "===================================================" << endl;
			break;

		case 2:
			cout << "请输入相关信息（格式：父亲 人名 出生年 月 日 住址）" << endl;
			tmp = new node;
			wcin>>f>> tmp->name >> tmp->birth.year >> tmp->birth.month
				>> tmp->birth.day >> tmp->address;
			if (!FT.insert(f, tmp))
				cout << "插入失败！" << endl;
			cout << "===================================================" << endl;
			break;

		case 3:
			cout << "请输入需要详细信息的人名：" << endl;
			wcin >> name;
			if(!FT.print(name))
				wcout << L"找不到家谱成员 " << name << endl;
			cout << "===================================================" << endl;
			break;

		case 4:
			cout << endl << "家谱树：" << endl;
			FT.traverse();
			break;

		case 5:
			while (!flag)
			{
				cout << "-----------------------------------------------" << endl;
				cout << "\t请输入需要修改的详细方面：" << endl;
				cout << "\t1）修改姓名" << endl;
				cout << "\t2）修改生日" << endl;
				cout << "\t3）修改婚姻状况" << endl;
				cout << "\t4）修改住址" << endl;
				cout << "\t5）修改死亡状况" << endl;
				cout << "\t0）退出修改" << endl;
				cout << "-----------------------------------------------" << endl;
				cout << "请输入选择：" << endl;
				cin >> choice;
				switch (choice)
				{
				case 0:
					flag = 1;
					cout << "===================================================" << endl;
					break;

				case 1:
					cout << "请输入被修改人姓名：" << endl;
					wcin >> name;
					cout << "请输入被修改人新名字：" << endl;
					wcin >> f;
					if (!FT.modifyName(name, f))
						wcout << L"找不到家谱成员 " << name << endl;
					break;

				case 2:
					cout << "请输入被修改人姓名：" << endl;
					wcin >> name;
					cout << "请输入被修改人新生日（年 月 日）：" << endl;
					wcin >> birth.year >> birth.month >> birth.day;
					if (!FT.modifyBirth(name, birth))
						wcout << L"找不到家谱成员 " << name << endl;
					break;

				case 3:
					cout << "请输入被修改人姓名：" << endl;
					wcin >> name;
					cout << "请输入被修改人婚姻状况（是/否 ）：" << endl;
					wcin >> f;
					if (f == L"是")
					{
						cout << "请输入被修改人配偶（格式：人名（配偶，下同） 出生年 月 日 住址）" << endl;
						spouse = new node;
						wcin >> spouse->name >> spouse->birth.year >> spouse->birth.month
							>> spouse->birth.day >> spouse->address;
						if (!FT.modifyMarriage(name, true, spouse))
							wcout << L"找不到家谱成员 " << name << endl;
					}
					else
						if (!FT.modifyMarriage(name, false))
							wcout << L"找不到家谱成员 " << name << endl;
					break;

				case 4:
					cout << "请输入被修改人姓名：" << endl;
					wcin >> name;
					cout << "请输入被修改人住址：" << endl;
					wcin >> address;
					if (!FT.modifyAddress(name, address))
						wcout << L"找不到家谱成员 " << name << endl;
					break;

				case 5:
					cout << "请输入被修改人姓名：" << endl;
					wcin >> name;
					cout << "请输入被修改人是否死亡（是/否）：" << endl;
					wcin >> f;
					if (f == L"是")
					{
						cout << "请输入被修改人死亡日期（年 月 日）：" << endl;
						spouse = new node;
						wcin >> death.year >> death.month >> death.day;
						if (!FT.modifyDeath(name, true, death))
							wcout << L"找不到家谱成员 " << name << endl;
					}
					else
						if (!FT.modifyDeath(name, false))
							wcout << L"找不到家谱成员 " << name << endl;
					break;

				default:
					break;
				}
			}
			break;

		case 6:
			cout << "请输入第n代所有人：" << endl;
			cin >> level;
			if (!FT.returnNLevelAll(level))
				cout << "无第" << level << "代！" << endl;
			cout << "===================================================" << endl;
			break;

		case 7:
			cout << "请输入需要删除的人名：" << endl;
			wcin >> name;
			if (!FT.erase(name))
				wcout << L"找不到家谱成员 " << name << endl;
			else
				cout << "删除成功！" << endl;
			break;

		case 8:
			cout << "请输入需查询成员的生日（年 月 日）：" << endl;
			wcin >> birth.year >> birth.month >> birth.day;
			if(!FT.find(birth))
				wcout << L"找不到家谱成员" << endl;
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

