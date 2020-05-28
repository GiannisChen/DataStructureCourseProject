#include <iostream>
#include <algorithm>
using namespace std;

#define maxn  30001

int father[maxn];

//找根节点，非递归
int Find(int x)
{
	int r = x, t;
	while (father[r] != r)
		r = father[r];
	while (father[x] != r)
	{
		t = father[x];
		father[x] = r;
		x = t;
	}
	return r;
}
//加入集合
void join(int x, int y)
{
	int a = Find(x), b = Find(y);
	if (a != b)
		father[b] = a;
}
int main()
{
	int n, m, k, t;
	for (int i = 1; i < maxn; i++)
		father[i] = i;
	cin >> n >> m;
	while (m--)
	{
		int r;
		cin >> k;
		cin >> r;
		while (--k)
		{
			cin >> t;
			join(r, t);
		}
	}
	int Max = 1, count[maxn];
	memset(count, 0, sizeof(count));
	for (int i = 1; i <= n; i++)
	{
		int r = Find(i);
		count[r]++;
		Max = max(Max, count[r]);
	}
	cout << Max;
	return 0;
}