#pragma once
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>

#define NOW 2057

struct Date
{
	int year;
	int month;
	int day;
	Date(int y = 1999, int m = 4, int d = 1)
	{
		year = y; month = m; day = d;
	}
	bool operator==(Date& a)
	{
		if (a.year == this->year && a.month == this->month && a.day == this->day)
			return true;
		return false;
	}
};

typedef struct node
{
	int label;
	std::wstring name;
	Date birth;
	Date death;
	std::wstring address;
	bool marriage;
	bool living;
	node() : label(0), name(L"无名氏"), birth(Date()), death(Date()),
		address(L"天庭"), marriage(0), living(1) {}
}*member;

typedef struct TreeNode
{
	member self;
	member spouse;
	TreeNode* father;
	std::vector<TreeNode*> child;
	/*TreeNode(member a)
	{
		self = a;
	}
	TreeNode(member m, member w)
	{
		self = m;
		spouse = w;
	}*/
}*TNode;

//格式化输出
void printMember(member a);

class FamilyTree
{
private:
	TNode ancestor;
	std::map<int, TNode> familyMember_label;
	std::map<std::wstring, TNode> familyMember_name;
public:
	FamilyTree();
	FamilyTree(member a);

	bool insert(int father, member m);
	bool insert(std::wstring father, member m);

	bool returnNLevelAll(int level);
	bool traverse();

	bool insertSpouse(int label, member mate);
	bool insertSpouse(std::wstring name, member mate);

	bool modifyName(std::wstring oldname, std::wstring newname);
	bool modifyBirth(std::wstring name, Date birth);
	bool modifyMarriage(std::wstring name, bool isMarriage = 0, member spouse = NULL);
	bool modifyAddress(std::wstring name, std::wstring address);
	bool modifyDeath(std::wstring name, bool living = 1, Date death = Date(0, 0, 0));

	bool erase(std::wstring name);

	bool find(Date birth);

	bool print(std::wstring a);
};