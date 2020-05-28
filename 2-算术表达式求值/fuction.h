#pragma once
#include <string>
#include "MyStack.h"
using namespace std;

/*优先级关系：
	'.' > '*' = '/' > '(' = ')' > '+' = '-'
*/

/*显示堆栈细节*/
void detail(My_stack<char> oprt,My_stack<float> val)
{
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "|\t\t|" << endl;
	cout << "|运算符栈\t|";
	oprt.traverse();
	cout << "|\t\t|" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
	cout << "|\t\t|" << endl;
	cout << "|运算数栈\t|";
	val.traverse();
	cout << "|\t\t|" << endl;
	cout << "--------------------------------------------------------------------------" << endl;
}

/*显示字符串剩余内容*/
void showStr(string a, int begin, int size)
{
	cout << "剩余字符串：";
	for (int i = begin; i < size; i++)
		cout << a.at(i);
	cout << endl;
}

/*执行具体操作*/
void operation(std::string a)
{
	//准备
	My_stack<char> oprt;
	My_stack<float> val;
	int size = a.size(), index = 0;

	//string为空
	if (size == 0)
	{
		cout << "表达式为空！" << endl;
		return;
	}
	if (a.at(index) != '#')
	{
		cout << "缺少前边界符#" << endl;
		return;
	}
	//将#加入操作符栈
	oprt.push(a.at(index));
	index++;

	//遍历string
	float num = 0;
	bool isDecimal = false;
	float decimal = 0;
	int length = 0;
	bool flag = false;
	while (index < size)
	{
		//处理数字串
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
					cout << "小数点重复！" << endl;
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
			cout << "缺少后边界符！" << endl;
			return;
		}
		if (flag && (a.at(index) > '9' || a.at(index) < '0'))
		{
			val.push(num + decimal);
			cout << "当前运算数：" << num + decimal << endl;
			flag = false;
			num = 0;
			length = 0;
			isDecimal = false;
			decimal = 0;
		}

		char tmp = a.at(index);
		//1.边界符处理
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
						cout << "0为除数！" << endl;
						return;
					}
					else
						val.push(n / m);
					break;
				case '(':
					cout << "缺少）！" << endl;
					return;
					break;
				case ')':
					cout << "多余的）！" << endl;
				case '+':
					val.push(n + m);
					break;
				case '-':
					val.push(n - m);
					break;
				default:
					cout << "非法字符！" << endl;
					break;
				}
			}
			if (oprt.size() == 1 && oprt.top() == '#' && val.size() == 1)
			{
				oprt.pop();
				cout << "结果为：" << val.top() << endl;
				cout << "计算成功！" << endl;
				
				return;
			}
			else if (oprt.size() >= 2)
			{
				cout << "缺少运算数！" << endl;
				return;
			}
			else if (val.size() >= 2)
			{
				cout << "缺少运算符！" << endl;
				return;
			}
			else
			{
				cout << "其他错误！" << endl;
				return;
			}
		}
		//3.乘号处理
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
					cout << "缺少运算数！" << endl;
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
						cout << "0作为除数！" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "缺少运算数！" << endl;
					return;
				}
			}
			oprt.push('*');
			index++;
		}
		//4.除号处理
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
					cout << "缺少运算数！" << endl;
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
						cout << "0作为除数！" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "缺少运算数！" << endl;
					return;
				}
			}
			oprt.push('/');
			index++;
		}
		//5.加号处理
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
					cout << "缺少运算数！" << endl;
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
						cout << "0作为除数！" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "缺少运算数！" << endl;
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
					cout << "缺少运算数！" << endl;
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
					cout << "缺少运算数！" << endl;
					return;
				}
			}
			oprt.push('+');
			index++;
		}
		//6.减号处理
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
					cout << "缺少运算数！" << endl;
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
						cout << "0作为除数！" << endl;
						return;
					}
					val.push(n / m);
				}
				else
				{
					cout << "缺少运算数！" << endl;
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
					cout << "缺少运算数！" << endl;
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
					cout << "缺少运算数！" << endl;
					return;
				}
			}
			oprt.push('-');
			index++;
		}
		//7.左括号处理
		else if (tmp == '(')
		{
			oprt.push('(');
			index++;
		}
		//8.右括号处理
		else if (tmp == ')')
		{
			while (!oprt.empty() && !(oprt.top() == '('))
			{
				if (oprt.top() == '#')
				{
					cout << "缺少(！" << endl;
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
							cout << "0为除数！" << endl;
							return;
						}
						else
							val.push(n / m);
						break;
					case '(':
						cout << "缺少）！" << endl;
						return;
						break;
					case ')':
						cout << "多余的）！" << endl;
					case '+':
						val.push(n + m);
						break;
					case '-':
						val.push(n - m);
						break;
					default:
						cout << "非法字符！" << endl;
						break;
					}
				}
			}
			if (oprt.empty())
			{
				cout << "缺少左括号！" << endl;
				cout << "缺少前边界符！" << endl;
				return;
			}
			if (oprt.top() == '(')
				oprt.pop();
			index++;
		}
		else
		{
			cout << "非法字符！" << endl;
			return;
		}
		cout << "当前运算符：" << tmp << endl;
		detail(oprt, val);
	}
	cout << "缺少后边界符#！" << endl;
}