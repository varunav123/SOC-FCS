#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
using namespace std;
string rleencoder(string& s)
{
	string s1 = "";
	int j = 1;
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == s[i + 1])
		{
			j = j + 1;
		}
		else
		{
			if (j > 1)
			{
				string num = to_string(j);
				s1 = s1 + s[i] + num;
				/*fileout << s[i] << j;*/



				j = 1;
			}
			else
			{
				s1 = s1+ s[i];
				j = 1;
			}

		}
	}
	return s1;

}

string rledecoder(string& s)
{
	string s1 = "";
	
	int i = 0;
	while (i < s.size())
	{
		int j = 0;
		for (; i+j +1< s.size(); j++)
		{
			
				if (isdigit(s[i + j+1]))
				{
					continue;
				}
				else break;
			
		}
		string sub = s.substr(i + 1, j);
		int len;
		if (j != 0)
		{
			 len = stoi(sub);
		}
		if(j!=0)
		{
			for (; len > 0; len--)
			{
				s1 = s1 + s[i];

			}
		}
		if (j == 0)
			s1 = s1 + s[i];
		i= i + j+1;
	}
	return s1;
}

int main()
{
	ofstream filedecoded;
	filedecoded.open("filedecoded.txt");

	ofstream fileout;
	fileout.open("fileout.txt");
	ifstream file;
	file.open("file.txt"); 
	string s;
	stringstream ss;
	ss << file.rdbuf(); 
	s = ss.str();
	file.close();
	string s1 = rleencoder(s);
	string s2 = rledecoder(s1);
	cout << s1;
	fileout << s1;
	fileout.close();
	filedecoded << s2;
	filedecoded.close();
}