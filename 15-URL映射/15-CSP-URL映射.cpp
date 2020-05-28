#include <iostream>
#include <cctype>
#include <vector>
using namespace std;

vector<string> ruleHand, ruleEnd;
string sentence;

bool isMatch(string& sentence, string& rule, bool flag)
{
	int url_index = 0, rule_index = 0;
	while (url_index < (int)sentence.size() && rule_index < (int)rule.size())
	{
		if (rule.at(rule_index) == sentence.at(url_index))
		{
			url_index++;
			rule_index++;
		}
		// Æ¥Åä²ÎÊý
		else
		{
			if (rule.at(rule_index++) != '<')
				return false;
			if (flag)
				cout << ' ';
			// Æ¥Åä<int>
			if (rule.at(rule_index) == 'i')
			{
				bool success = false;
				while (url_index < (int)sentence.size() && isdigit(sentence.at(url_index)))
				{
					if (sentence.at(url_index) != '0')
						success = true;
					if (flag && success)
						cout << sentence.at(url_index);
					url_index++;
				}
				if (!success)
					return false;
				rule_index += 4;
			}
			else if (rule.at(rule_index) == 's')
			{
				// Æ¥Åä<str>
				bool success = false;
				while (sentence[url_index] && sentence.at(url_index) != '/')
				{
					success = true;
					if (flag)
						cout << sentence.at(url_index);
					url_index++;
				}
				if (!success)
					return false;
				rule_index += 4;
			}
			// Æ¥Åä<path>
			else if (rule.at(rule_index) == 'p')
			{
				
				if (flag)
					while (sentence[url_index])
						cout << sentence.at(url_index++);
				return true;
			}
		}
	}

	return (rule_index == (int)rule.size() && url_index == (int)sentence.size());
}

int main()
{
	int ruleNum, urlNum;
	cin >> ruleNum >> urlNum;
	string tmpH, tmpE;
	for (int i = 0; i < ruleNum; i++)
	{
		cin >> tmpH >> tmpE;
		ruleHand.push_back(tmpH);
		ruleEnd.push_back(tmpE);
	}
	for (int i = 0; i < urlNum; i++)
	{
		cin >> sentence;

		bool flag = true;
		for (int j = 0; flag && j < ruleNum; j++)
			if (isMatch(sentence, ruleHand.at(j), false))
			{
				flag = false;
				cout << ruleEnd.at(j);
				isMatch(sentence, ruleHand.at(j), true);
			}

		if (flag)
			cout << "404";
		cout << endl;
	}

	return 0;
}