#pragma once
#include <string>
#include "MyStack.h"
using namespace std;

/*���ȼ���ϵ��
	'.' > '*' = '/' > '(' = ')' > '+' = '-'
*/

/*��ʾ��ջϸ��*/
void detail(My_stack<char> oprt,My_stack<float> val)
{
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "|\t\t|" << endl;
	cout << "|�����ջ\t|";
	oprt.traverse();
	cout << "|\t\t|" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "|\t\t|" << endl;
	cout << "|������ջ\t|";
	val.traverse();
	cout << "|\t\t|" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

/*��ʾ�ַ���ʣ������*/
void showStr(string a, int begin, int size)
{
	cout << "ʣ���ַ�����";
	for (int i = begin; i < size; i++)
		cout << a.at(i);
	cout << endl;
}

/*ִ�о������*/
void operation(std::string a)
{
	//׼��
	My_stack<char> oprt;
	My_stack<float> val;
	int size = a.size(), index = 0;

	//stringΪ��
	if (size == 0)
	{
		cout << "���ʽΪ�գ�" << endl;
		return;
	}
	if (a.at(index) != '#')
	{
		cout << "ȱ��ǰ�߽��#" << endl;
		return;
	}
	//��#���������ջ
	oprt.push(a.at(index));
	index++;

	//����string
	float num = 0;
	bool isDecimal = false;
	float decimal = 0;
	int length = 0;
	bool flag = false;
	while (index < size)
	{
		//�������ִ�
		while (index < size && (a.at(index) >= '0' && a.at(index) <= '9') || a.at(index)=='.')
		{
			if (a.at(index) >= '0' && a.at(index) <= '9')
			{
				if (isDecimal)
				{
					length++;
					decimal += ((float)(a.at(index) - '0') / (float)pow(10, length));
					index++;
					flag = true;
				}
				else
				{
					num *= 10;
					num += (a.at(index) - '0');
					length++;
					index++;
					flag = true;
				}
			}
			else if (a.at(index) == '.')
			{
				if (isDecimal)
				{
					cout << "С�����ظ���" << endl;
					return;
				}
				else
					isDecimal = true;
				index++;
				length = 0;
			}
		}
		if (index == size)
		{
			cout << "ȱ�ٺ�߽����" << endl;
			return;
		}
		if (flag && (a.at(index) > '9' || a.at(index) < '0'))
		{
			val.push(num + decimal);
			cout << "��ǰ��������" << num + decimal << endl;
			flag = false;
			num = 0;
			length = 0;
			isDecimal = false;
			decimal = 0;
		}

		char tmp = a.at(index);
		//1.�߽������
		if (tmp == '#')
		{
			while ((oprt.size() >= 2) && (val.size() >= 2))
			{
				//n oprt m
				float m = val.top();
				val.pop();
				float n = val.top();
				val.pop();
				char tmp = oprt.top();
				oprt.pop();
				switch (tmp)
				{
				case '*':
					val.push(n * m);
					break;
				case '/':
					if (m == 0)
					{
						cout << "0Ϊ������" << endl;
						return;
					}
					else
						val.push(n / m);
					break;
				case '(':
					cout << "ȱ�٣���" << endl;
					return;
					break;
				case ')':
					cout << "����ģ���" << endl;
				case '+':
					val.push(n + m);
					break;
				case '-':
					val.push(n - m);
					break;
				default:
					cout << "�Ƿ��ַ���" << endl;
					break;
				}
			}
			if (oprt.size() == 1 && oprt.top() == '#' && val.size() == 1)
			{
				oprt.pop();
				cout << "���Ϊ��" << val.top() << endl;
				cout << "����ɹ���" << endl;
				
				return;
			}
			else if (oprt.size() >= 2)
			{
				cout << "ȱ����������" << endl;
				return;
			}
			else if (val.size() >= 2)
			{
				cout << "ȱ���������" << endl;
				return;
			}
			else
			{
				cout << "��������" << endl;
				return;
			}
		}
		//3.�˺Ŵ���
		else if (tmp == '*')
		{
			if (oprt.top() == '*')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n * m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '/')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					if (m == 0)
					{
						cout << "0��Ϊ������" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			oprt.push('*');
			index++;
		}
		//4.���Ŵ���
		else if (tmp == '/')
		{
			if (oprt.top() == '*')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n * m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '/')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					if (m == 0)
					{
						cout << "0��Ϊ������" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			oprt.push('/');
			index++;
		}
		//5.�ӺŴ���
		else if (tmp == '+')
		{
			if (oprt.top() == '*')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n * m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '/')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					if (m == 0)
					{
						cout << "0��Ϊ������" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '+')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n + m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '-')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n - m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			oprt.push('+');
			index++;
		}
		//6.���Ŵ���
		else if (tmp == '-')
		{
			if (oprt.top() == '*')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n * m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '/')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					if (m == 0)
					{
						cout << "0��Ϊ������" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '+')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n + m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			if (oprt.top() == '-')
			{
				oprt.pop();
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					val.push(n - m);
				}
				else
				{
					cout << "ȱ����������" << endl;
					return;
				}
			}
			oprt.push('-');
			index++;
		}
		//7.�����Ŵ���
		else if (tmp == '(')
		{
			oprt.push('(');
			index++;
		}
		//8.�����Ŵ���
		else if (tmp == ')')
		{
			while (!oprt.empty() && !(oprt.top() == '('))
			{
				if (oprt.top() == '#')
				{
					cout << "ȱ��(��" << endl;
					return;
				}
				//n oprt m
				if (val.size() >= 2)
				{
					float m = val.top();
					val.pop();
					float n = val.top();
					val.pop();
					char tmp = oprt.top();
					oprt.pop();
					switch (tmp)
					{
					case '*':
						val.push(n * m);
						break;
					case '/':
						if (m == 0)
						{
							cout << "0Ϊ������" << endl;
							return;
						}
						else
							val.push(n / m);
						break;
					case '(':
						cout << "ȱ�٣���" << endl;
						return;
						break;
					case ')':
						cout << "����ģ���" << endl;
					case '+':
						val.push(n + m);
						break;
					case '-':
						val.push(n - m);
						break;
					default:
						cout << "�Ƿ��ַ���" << endl;
						break;
					}
				}
			}
			if (oprt.empty())
			{
				cout << "ȱ�������ţ�" << endl;
				cout << "ȱ��ǰ�߽����" << endl;
				return;
			}
			if (oprt.top() == '(')
				oprt.pop();
			index++;
		}
		else
		{
			cout << "�Ƿ��ַ���" << endl;
			return;
		}
		cout << "��ǰ�������" << tmp << endl;
		detail(oprt, val);
	}
	cout << "ȱ�ٺ�߽��#��" << endl;
}