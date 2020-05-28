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
	//Ϊʹ�����ȶ��У�������У����ȼ���time>operation>label
	bool operator()(teacher a, teacher b)
	{
		if (a->time != b->time)
			return a->time > b->time;					//������ȼ����
		else
		{
			if (a->operation != b->operation)
				return a->operation > b->operation;	//������Ȼ����
			else
				return a->label > b->label;			//ʱ�����ȼ����
		}
	}
};
int main()
{
	int N, K;
	//N:Կ������		K:������
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
	cout << "���̣�" << endl;
	while (!Q.empty())
	{
		teacher tmp = new node;
		tmp = Q.top();
		Q.pop();
		//��Կ��
		if (tmp->operation)
		{
			for (vector<int>::iterator iter = keybox.begin(); iter != keybox.end(); iter++)
				if (tmp->label == *iter)
					*iter = 0;
		}
		//��Կ��
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

		cout << "ʱ��" << tmp->time << "Ϊ��";
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