#include <iostream>
#include <queue>
#include <vector>
using namespace std;
enum state { Return, Borrow };

typedef struct node
{
	int label;
	int time;
	state operation;
}*teacher;
struct cmp
{
	//为使用优先队列，反序进行，优先级：time>operation>label
	bool operator()(teacher a, teacher b)
	{
		if (a->time != b->time)
			return a->time > b->time;					//序号优先级最低
		else
		{
			if (a->operation != b->operation)
				return a->operation > b->operation;	//其次是先还后借
			else
				return a->label > b->label;			//时间优先级最高
		}
	}
};
int main()
{
	int N, K;
	//N:钥匙数量		K:操作数
	cin >> N >> K;
	vector<int> keybox;
	for (int i = 1; i <= N; i++)
		keybox.push_back(i);

	int w, s, c;
	priority_queue<teacher, vector<teacher>, cmp> Q;
	for (int i = 0; i < K; i++)
	{
		teacher tmpBorrow = new node;
		teacher tmpReturn = new node;
		cin >> w >> s >> c;
		tmpBorrow->label = w;
		tmpReturn->label = w;
		tmpBorrow->time = s;
		tmpReturn->time = s + c;
		tmpBorrow->operation = Borrow;
		tmpReturn->operation = Return;
		Q.push(tmpBorrow);
		Q.push(tmpReturn);
	}
	cout << "过程：" << endl;
	while (!Q.empty())
	{
		teacher tmp = new node;
		tmp = Q.top();
		Q.pop();
		//借钥匙
		if (tmp->operation)
		{
			for (vector<int>::iterator iter = keybox.begin(); iter != keybox.end(); iter++)
				if (tmp->label == *iter)
					*iter = 0;
		}
		//还钥匙
		else
		{
			for (vector<int>::iterator iter = keybox.begin(); iter != keybox.end(); iter++)
			{
				if (*iter == 0)
				{
					*iter = tmp->label;
					break;
				}
			}
		}

		cout << "时刻" << tmp->time << "为：";
		for (vector<int>::iterator iter = keybox.begin(); iter != keybox.end(); iter++)
		{
			if (iter == keybox.begin())
				cout << *iter;
			else
				cout << " " << *iter;
		}
		cout << endl;
	}

	for (vector<int>::iterator iter = keybox.begin(); iter != keybox.end(); iter++)
	{
		if (iter == keybox.begin())
			cout << *iter;
		else
			cout << " " << *iter;
	}
	cout << endl;

	return 0;
}