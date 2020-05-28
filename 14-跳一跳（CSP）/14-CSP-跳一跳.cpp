#include <iostream>
using namespace std;
int main()
{
	int bonus = 2, sum = 0, pre = 1, cur;
	cin >> cur;
	while (cur)
	{
		if (cur == 1)
		{
			sum++;
			bonus = 2;
		}
		else
		{
			sum += bonus;
			bonus += 2;
		}
		cin >> cur;
	}
	cout << sum << endl;

	return 0;
}