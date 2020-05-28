#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;
map<int,string> stationLabel;
map<string,int> stationName;
map<int,vector<int>> bus;

pair<int,int> Graph1[5200][5200];
pair<int,int> Graph2[5200][5200];

int main()
{
	fstream file;
	file.open("南京公交线路1.txt",ios::in);
	
	if(file.fail())
	{
		cout<<"File Open Error!"<<endl;
		exit(0);  
	}
	
	string s;
	int index=1;
	int num;
	while(!file.eof())
	{
		file>>s;
		if(s.substr(s.size()-2)=="路")
		{
			//system("pause");
			s.pop_back();
			s.pop_back();
			num=stoi(s,0,10);
			//cout<<num<<": ";
			vector<int> v;
			bus.insert(make_pair(num,v));
		}
		else
		{
			map<string,int>::iterator i=stationName.find(s);
			if(i==stationName.end())
			{
				stationName.insert(make_pair(s,stationName.size()+1));
				stationLabel.insert(make_pair(stationLabel.size()+1,s));
				bus[num].push_back(index++);
			}
			else
			{
				bus[num].push_back((*i).second);
			}
			
		}
		
		//cout<<s<<"  ";
	}
	
//	for(map<int,string>::iterator j=stationLabel.begin();j!=stationLabel.end();j++)
//	{
//		cout<<"["<<(*j).first<<"]\t"<<(*j).second<<endl;
//		 
//	}
	return 0;
}
