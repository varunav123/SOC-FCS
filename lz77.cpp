#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;
string LZ77encoder(string &s)
{
	
	int match = 0;
	int match1 = 0;
	int offset = 0;
	int offset1 = 0;
	string s1="";
	string sout = "";
	for (int i = 0; i < s.size(); )
	{
		int j = 0;
		if (s1.size() == 0)
		{
			s1 = s1 + s[j];
		}
		else
		{
			int k = s1.size();
			for (; i+j < s.size()+1; j++)
			{
				if (j == 0)
				{
					for (k = k - 1; k > -1; k--)
					{
						if (s[i + j] == s1[k])
						{
							if (match1 == 0)
							{
								offset = s1.size() - k;
								match = 1;
								offset1 = s1.size() - k;
								match1 = 1;
							}
							else
							{
								offset1 = s1.size() - k;
								match1 = 1;
							}
							break;
						}
					}
					if (match1==1)
						continue;
					else
						break;
				}
				else
				{
					if (k == -1)
						break;
					else
					{
						if (j + k < s1.size())
						{
							if (s1[j + k] == s[i + j])
							{
								match1++;
								continue;
							}
						else
						{
								if (match1 > match )
								{
									match = match1;
									offset = offset1;
									match1 = 0;
									offset1 = 0;
								}
								j = -1;
								continue;
							}
						}
						else
						{
							if (match1 > match)
							{
								match = match1;
								offset = offset1;
							}
							/*else if (match1 == match)
							{
								if (offset1 < offset)
								{
									match = match1;
									offset = match1;
								}
							}*/
							j = -1;
							continue;
						}
						
					}
				}
			}
			
			
			
			
		}
		if (i != 0)
		{
		
			if (match>3)
			{
				for (int l = 0; l < match; l++)
				{
					s1 = s1 + s[i + l];
				}
			}
			else
			{
				s1 = s1 + s[i];
			}
		}

		/*if (i == 3)
		{
			for (int m = 0; m < s1.size(); m++)
				cout << s1[m];
		}*/
	if (match == 0 && offset == 0)
	{
		sout = sout+s[i];
		i = i + 1;
	}
	else
	{
		if (match>3)
		{	
			sout = sout + "(" + to_string(offset) + "," + to_string(match) + ")";
			i = i + match;
			match = 0;
			match1 = 0;
			offset = 0;
			offset1 = 0;
		}
		else
		{
		/*	for (int k = 0; k < match; k++)
			{
				sout = sout + s[i + k];
			}*/
			sout = sout + s[i]; 
			i = i + 1;
			match = 0;
			match1 = 0;
			offset = 0;
			offset1 = 0;
		}

	}
	}
	
	return sout;
}

string LZ77decoder(string& s)
{
	int i2=0;
	int offset;
	int match;
	string s2="";
	string s1 = "";
	string sout = "";
	for (int i = 0; i < s.size();)
	{
		
		if (s[i]=='(')
		{
			int k = 0;
			s1 = "";
			for (; isdigit(s[i+1 + k]); k++)
			{
				s1 = s1 + s[i+1 + k];
			}
			offset = stoi(s1);
			/*cout << offset << "\n";*/
			k = k +1 ;
			s1 = "";
			for (; isdigit(s[i+1+ k]); k++)
			{
				s1 = s1 + s[i+1 + k];
			}
			match = stoi(s1);
			int match1 = match;
			/*cout << match << "\n";*/
			for (int p = offset; match > 0; match--)
			{
				s2 = s2 + s2[i2 - p];
				p--;
			}
			i2 = i2 + match1;
			i = i + k + 2;
		}
		else
		{
			s2 =s2+s[i];
			i = i + 1;
			i2++;
		}
	}
	sout = s2;
	return sout;
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
	string sout=LZ77encoder(s);
	fileout << sout;
	fileout.close();
	string sdecoded = LZ77decoder(sout);
	filedecoded << sdecoded;
	filedecoded.close();
}