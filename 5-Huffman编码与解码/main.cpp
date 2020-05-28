#include "define.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>

#define ResFile "articlel.txt"
#define CodeFile "code.dat"
#define DecodeFile "decode.txt"

using namespace std;

int isCode(string word, array<string, 256> code);
string reverse(string a);

int main()
{
	//��ȡ����׼��
	fstream resource(ResFile, ios::in);
	char tmpc;
	string article = "";
	//�洢������ţ�8��char��
	string articleEnd;
	//���ֵ�ͳ���ַ�������
	int num = 0;
	//ͳ��0-1������
	int countNum = 0;
	//ascii�빲8bits����256����
	int count[256] = { 0 };
	//�Ƿ�ɹ���ȡ
	if (resource.fail())
	{
		cout << "Դ�ļ���ȡʧ�ܣ�" << endl;
		exit(0);
	}
	//������ͳ�Ƹ���
	while (resource.read(&tmpc, sizeof(char)))
	{
		if (tmpc >= 0 && tmpc <= 255)
		{
			count[tmpc]++;
			article.push_back(tmpc);
		}
		
	}
	if (article.size() >= 8)
		articleEnd = article.substr(article.size() - 8, 8);
	else
		articleEnd = article;
	//cout << articleEnd << endl; return 0;
	resource.close();
//����1���Ƿ���ȷͳ��
/*
	for (size_t i = 0; i < 256; i++)
	{
		if (count[i])
		{
			if (count[i] == ' ')
				cout << "�ո�\t" << count[i] << '\t' << endl;
			else if (count[i] == '\n')
				cout << "�س�\t" << count[i] << '\t' << endl;
			else if (count[i] == '\t')
				cout << "�Ʊ�\t" << count[i] << '\t' << endl;
			else
				cout << (char)i << "\t" << count[i] << '\t' << endl;
		}
	}
	//����1����
*/
	//���
	priority_queue<node,vector<node>,cmp> MinHeap;
	for (int i = 0; i < 256; i++)
	{
		if (count[i])
		{
			node tmpn = new HTNode;
			tmpn->num = i;
			tmpn->weight = count[i];
			tmpn->lchild = NULL;
			tmpn->rchild = NULL;
			tmpn->code = "";
			MinHeap.push(tmpn);
			num++;
		}
	}

//����2���Ƿ���������
/*
	while (!MinHeap.empty())
	{
		node tmpn = MinHeap.top();
		MinHeap.pop();
		cout << tmpn->weight << "\t" << (char)tmpn->num << "\t" << (int)tmpn->num << "\t" << endl;
	}
	//����2����
*/
//����3�����Ƿ��ȡ����
/*
	fstream test3("test1.txt", ios::out);
	test3 << article;
	//����3����
*/
	
	//���ѽ���
	while (MinHeap.size() > 1)
	{
		node tmpn = new HTNode;
		tmpn->code = "";

		tmpn->lchild = MinHeap.top();
		MinHeap.pop();
		tmpn->rchild = MinHeap.top();
		MinHeap.pop();
		tmpn->weight = tmpn->lchild->weight + tmpn->rchild->weight;
		MinHeap.push(tmpn);
	}
	//ȡ������
	node tmpn = MinHeap.top();

	//׼������
	std::array<string, 256> code;
	code.fill("");
	queue<node> Q;
	
	Q.push(tmpn);
	while (!Q.empty())
	{
		tmpn = Q.front();
		Q.pop();
		//����5�Ƿ����ɹ�
		//cout << (char)tmpn->num << "\t" << tmpn->weight << "\t" << endl;
		if (!tmpn->lchild && !tmpn->rchild)
			code.at(tmpn->num) = tmpn->code;
		else
		{
			if (tmpn->lchild)
			{
				tmpn->lchild->code = tmpn->code + '0';
				Q.push(tmpn->lchild);
			}
			if (tmpn->rchild)
			{
				tmpn->rchild->code = tmpn->code + '1';
				Q.push(tmpn->rchild);
			}
		}
	}
//����4�Ƿ�ɹ�����
///*
	for (size_t i = 0; i < 256; i++)
	{
		if (code.at(i) != "")
			cout << i << "\t" << (char)i << "\t" << code.at(i) << "\t" << endl;
	}
	//����4����
//*/
	//ת�������׼��
	queue<bool> byte;
	int tmpByte = 0;
	fstream codeFile(CodeFile, ios::out | ios::binary);
	if (codeFile.fail())
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(0);
	}

	
	//ת��
	string tmps("");
	for (string::iterator iter = article.begin(); iter != article.end(); iter++)
	{
		tmps = code.at(*(iter));
		//��תΪ�˱���pop
		tmps = reverse(tmps);	
		//string to binary
		while (!tmps.empty())
		{
			if (byte.size() == 8)
			{
				while (!byte.empty())
				{
					tmpByte *= 2;
					if (byte.front())
						tmpByte++;
					byte.pop();
				}
				codeFile << (char)tmpByte;
				countNum += 8;
				tmpByte = 0;
			}
			if (tmps.back() == '0')
				byte.push(0);
			else
				byte.push(1);
			tmps.pop_back();
		}
	}
	//�����8λ
	if (byte.size())
	{
		countNum += byte.size();
		while (byte.size() != 8)
			byte.push(0);
		while (!byte.empty())
		{
			tmpByte *= 2;
			if (byte.front())
				tmpByte++;
			byte.pop();
		}
		codeFile << (char)tmpByte;
		tmpByte = 0;
	}

	codeFile.close();
	cout << "���ܳɹ���" << endl;

	//���벿��
	string tmpCode;
	fstream codeResource(CodeFile, ios::in | ios::binary);
	if (codeResource.fail())
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(0);
	}
	fstream decodeFile(DecodeFile, ios::out | ios::in);
	if (decodeFile.fail())
	{
		cout << "�����ļ���ʧ�ܣ�" << endl;
		exit(0);
	}
	
	int tmpNum = 0;
	//char to binary_string
	while (codeResource.read(&tmpc, sizeof(char)))
	{
		tmps = "";
		tmpByte = (int)tmpc;
		if (tmpByte < 0)
			tmpByte = 256 + tmpByte;
		
		while (tmpByte)
		{
			if (tmpByte % 2)
				tmps.push_back('1');
			else
				tmps.push_back('0');
			tmpByte /= 2;
		}

		while (tmps.size() != 8)
			tmps.push_back(0);
		//tmps = reverse(tmps);
		while (!tmps.empty())
		{
			byte.push((tmps.back()=='1'));
			tmps.pop_back();
		}

		while (!byte.empty())
		{
			tmpCode.push_back((byte.front() == 1 ? '1' : '0'));
			tmpNum++;
			byte.pop();
			int tmpi = isCode(tmpCode, code);
			if (tmpi != -1)
			{
				decodeFile << (char)tmpi;
				tmpCode.clear();
			}
			if (tmpNum == countNum)
			{
				cout << "������ɣ�" << endl;
				exit(0);
			}
		}
	}
	
	/*int con = (int)articleEnd.size();
	int check;
	check = con;
	char* c = new char[con];
	decodeFile.seekg(-check, ios::end);
	decodeFile.read(c,con);
	
	cout << articleEnd << endl;
	cout << c << endl;
	while (articleEnd != c)
	{
		check++;
		decodeFile.seekg(-check, ios::end);
		decodeFile.read(c, con);
		cout << articleEnd << endl;
		
	}
	*/

	codeResource.close();
	decodeFile.close();

	return 0;
}

int isCode(string word, array<string, 256> code)
{
	for (size_t i = 0; i < code.size(); i++)
	{
		if (word == code.at(i))
			return i;
	}
	return -1;
}

string reverse(string a)
{
	string b;
	while(!a.empty())
	{
		b.push_back(a.back());
		a.pop_back();
	}
	return b;
}

