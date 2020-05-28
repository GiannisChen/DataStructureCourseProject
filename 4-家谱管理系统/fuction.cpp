#include "define.h"

//构造函数
FamilyTree::FamilyTree()
{
	ancestor = NULL;
}

//构造函数（指定始祖）
FamilyTree::FamilyTree(member m)
{
	m->label = 1;
	ancestor = new TreeNode;
	ancestor->father = NULL;
	ancestor->self = m;
	ancestor->spouse = NULL;
	familyMember_label.insert
	(std::map<int, TreeNode*>::value_type(1, ancestor));
	familyMember_name.insert
	(std::map<std::wstring, TreeNode*>::value_type(m->name, ancestor));
}

//插入
bool FamilyTree::insert(int father, member m)
{
	if (!ancestor)
	{
		if (father == 0)
		{
			m->label = 1;
			ancestor = new TreeNode;
			ancestor->father = NULL;
			ancestor->self = m;
			ancestor->spouse = NULL;
			familyMember_label.insert
			(std::map<int, TreeNode*>::value_type(1, ancestor));
			familyMember_name.insert
			(std::map<std::wstring, TreeNode*>::value_type(m->name, ancestor));
			return true;
		}
		else
			return false;
	}

	if (!familyMember_label.count(father))
		return false;
	for (std::vector<TreeNode*>::iterator iter = familyMember_label[father]->child.begin();
		iter != familyMember_label[father]->child.end(); iter++)
	{
		if ((*iter)->self->name == m->name)
		{
			(*iter)->self = m;
			return true;
		}
	}
	m->label = familyMember_label.size();
	while (familyMember_label.count(m->label))
		m->label++;
	TNode tmpNode = new TreeNode;
	tmpNode->father = familyMember_label[father];
	tmpNode->self = m;
	tmpNode->spouse = NULL;
	familyMember_label[father]->child.push_back(tmpNode);

	familyMember_label.insert(std::map<int, TreeNode*>::value_type(m->label, tmpNode));
	familyMember_name.insert(std::map<std::wstring, TreeNode*>::value_type(m->name, tmpNode));

	return true;
}

//插入
bool FamilyTree::insert(std::wstring father, member m)
{
	if (!ancestor)
	{
		if (father == L"")
		{
			m->label = 1;
			ancestor = new TreeNode;
			ancestor->father = NULL;
			ancestor->self = m;
			ancestor->spouse = NULL;
			familyMember_label.insert
			(std::map<int, TreeNode*>::value_type(1, ancestor));
			familyMember_name.insert
			(std::map<std::wstring, TreeNode*>::value_type(m->name, ancestor));
			return true;
		}
		else
			return false;
	}

	if (!familyMember_name.count(father))
		return false;
	for (std::vector<TreeNode*>::iterator iter = familyMember_name[father]->child.begin();
		iter != familyMember_name[father]->child.end(); iter++)
	{
		if ((*iter)->self->name == m->name)
		{
			(*iter)->self = m;
			return true;
		}
	}
	m->label = familyMember_label.size();
	while (familyMember_label.count(m->label))
		m->label++;
	TNode tmpNode = new TreeNode;
	tmpNode->father = familyMember_name[father];
	tmpNode->self = m;
	tmpNode->spouse = NULL;
	familyMember_name[father]->child.push_back(tmpNode);

	familyMember_label.insert(std::map<int, TreeNode*>::value_type(m->label, tmpNode));
	familyMember_name.insert(std::map<std::wstring, TreeNode*>::value_type(m->name, tmpNode));
	return true;
}

//测试层次顺序
bool FamilyTree::returnNLevelAll(int l)
{
	if (!ancestor)
		return false;

	std::queue<TNode> Q;
	Q.push(ancestor);
	int count = Q.size();
	int level = 1;
	while (count)
	{
		if (level == l)
			std::cout << "第" << level << "层所有人：" << std::endl;

		for (int c = 0; c < count; c++)
		{
			TNode tmp = Q.front();
			Q.pop();
			if (level == l)
				std::wcout << tmp->self->name << std::endl;

			for (std::size_t i = 0; i < tmp->child.size(); i++)
				Q.push(tmp->child.at(i));
		}
		count = Q.size();
		if (level == l)
			return true;
		level++;
	}
	return false;
}

//文件树形式输出
bool FamilyTree::traverse()
{
	if (!ancestor)
		return false;
	//std::stack<std::pair<int,TNode>> S;
	std::stack<TNode> S;
	std::stack<int> SL;
	int level = 1;
	TNode tmp;
	std::wcout << L"+--" << ancestor->self->name;
	if (ancestor->self->marriage)
	{
		if (ancestor->self->living)
			std::wcout << L"（" << NOW - ancestor->self->birth.year << L"岁 "
			<< ancestor->spouse->name << ")" << std::endl;
		else
			std::wcout << L"（卒 " << ancestor->spouse->name << ")" << std::endl;
	}
	else
	{
		if (ancestor->self->living)
			std::wcout << L"（" << NOW - ancestor->self->birth.year << L"岁 无配偶)" << std::endl;
		else
			std::wcout << L"（卒 无配偶)" << std::endl;
	}

	//S.push(std::make_pair(level,ancestor));
	S.push(ancestor);
	SL.push(level);
	while (!S.empty())
	{
		tmp = S.top(); S.pop();
		level = SL.top(); SL.pop();
		if (level != 1)
		{
			for (int i = 0; i < level - 1; i++)
				std::wcout << L"\t";
			std::wcout << L"|" << std::endl;
			for (int i = 0; i < level - 1; i++)
				std::wcout << L"\t";
			std::wcout << L"|--" << tmp->self->name;
			if (tmp->self->marriage)
			{
				if (tmp->self->living)
					std::wcout << L"（" << NOW - tmp->self->birth.year << L"岁 "
					<< tmp->spouse->name << ")" << std::endl;
				else
					std::wcout << L"（卒 " << tmp->spouse->name << ")" << std::endl;
			}
			else
			{
				if (tmp->self->living)
					std::wcout << L"（" << NOW - tmp->self->birth.year << L"岁 无配偶)" << std::endl;
				else
					std::wcout << L"（卒 无配偶)" << std::endl;
			}
		}
		for (int i = tmp->child.size() - 1; i >= 0; i--)
		{
			S.push(tmp->child.at(i));
			SL.push(level + 1);
		}
		//S.push(std::make_pair(level + 1, tmp->child.at(i)));
	}
	return true;
}

//插入配偶（仅供文件读入label）
bool FamilyTree::insertSpouse(int label, member mate)
{
	if (!familyMember_label.count(label))
		return false;
	else
	{
		familyMember_label[label]->spouse = mate;
		familyMember_label[label]->self->marriage = 1;
		return true;
	}
}

//插入配偶（按照姓名查询）
bool FamilyTree::insertSpouse(std::wstring name, member mate)
{
	if (!familyMember_name.count(name))
		return false;
	else
	{
		familyMember_name[name]->spouse = mate;
		familyMember_name[name]->self->marriage = 1;
		return true;
	}
}

//格式化输出
bool FamilyTree::print(std::wstring name)
{
	if (!familyMember_name.count(name))
		return false;
	else
	{
		std::cout << "（本人）";
		printMember(familyMember_name[name]->self);
		if (familyMember_name[name]->self->marriage)
		{
			std::cout << "（配偶）";
			printMember(familyMember_name[name]->spouse);
		}
		for (std::vector<TreeNode*>::iterator i = familyMember_name[name]->child.begin();
			i != familyMember_name[name]->child.end(); i++)
		{
			std::cout << "（孩子）";
			printMember((*i)->self);
		}
			
		return true;
	}
}

//删除本人及其所有后代
bool FamilyTree::erase(std::wstring name)
{
	if (!familyMember_name.count(name))
		return false;

	std::queue<TNode> Q;
	Q.push(familyMember_name[name]);

	TNode father = familyMember_name[name]->father;
	int count = Q.size();
	int label;
	for (std::vector<TreeNode*>::iterator iter = father->child.begin(); iter != father->child.end(); iter++)
	{
		if ((*iter)->self->name == name)
		{
			father->child.erase(iter);
			break;
		}
	}

	while (count)
	{
		for (int c = 0; c < count; c++)
		{
			TNode tmp = Q.front();
			Q.pop();
			std::vector<TreeNode*>::iterator i = tmp->child.begin();
			name = tmp->self->name;
			label = tmp->self->label;
			while (i != tmp->child.end())
			{
				Q.push(*i);
				i = tmp->child.erase(i);
			}
			delete tmp;

			familyMember_label.erase(label);
			familyMember_name.erase(name);
		}
		count = Q.size();
	}

	return true;
}

//修改名字
bool FamilyTree::modifyName(std::wstring oldname, std::wstring newname)
{
	if (!familyMember_name.count(oldname))
		return false;

	int label = familyMember_name[oldname]->self->label;
	familyMember_label[label]->self->name = newname;
	familyMember_name.erase(oldname);
	familyMember_name.insert(std::map<std::wstring, TNode>::value_type(newname, familyMember_label[label]));
	return true;
}

//修改生日
bool FamilyTree::modifyBirth(std::wstring name, Date birth)
{
	if (!familyMember_name.count(name))
		return false;

	familyMember_name[name]->self->birth = birth;
	return true;
}

//修改婚姻状况
bool FamilyTree::modifyMarriage(std::wstring name, bool isMarriage, member spouse)
{
	if (!familyMember_name.count(name))
		return false;

	familyMember_name[name]->self->marriage = isMarriage;
	delete familyMember_name[name]->spouse;
	familyMember_name[name]->spouse = spouse;
	return true;
}

//修改地址
bool FamilyTree::modifyAddress(std::wstring name, std::wstring address)
{
	if (!familyMember_name.count(name))
		return false;

	familyMember_name[name]->self->address = address;
	return true;
}

//修改死亡状况
bool FamilyTree::modifyDeath(std::wstring name, bool living, Date death)
{
	if (!familyMember_name.count(name))
		return false;

	familyMember_name[name]->self->living = living;
	familyMember_name[name]->self->death = death;
	return true;
}

//通过生日查找
bool FamilyTree::find(Date birth)
{
	for (std::map<int, TNode>::iterator i = familyMember_label.begin(); i != familyMember_label.end(); i++)
	{
		if ((*i).second->self->birth == birth)
		{
			printMember((*i).second->self);
			return true;
		}
	}
	return false;
}

//格式化输出
void printMember(member a)
{
	std::wcout << L"  " << a->name << L"  生于";
	std::cout << a->birth.year << "--" << std::setfill('0') << std::setw(2)
		<< a->birth.month << "--" << std::setfill('0') << std::setw(2)
		<< a->birth.day << "  ";
	if (!a->living)
		std::cout << "卒于" << a->death.year << "--" << std::setfill('0') << std::setw(2)
		<< a->death.month << "--" << std::setfill('0') << std::setw(2)
		<< a->death.day << "  ";
	std::wcout << a->address << std::endl;
}