#pragma once
#include <iostream>
#include <vector>
#include <string>
using std::string; using std::vector;
using std::cout; using std::initializer_list;
using std::endl;
class list
{
public:
	string error_line = "index out of range";
	int Int_Index = 0, String_Index = 0;
	vector<int> Int;
	vector<float> Float;
	vector<double> Double;
	vector<string> String;
	vector<vector<int>> dict;
	list(initializer_list<string> ini)
	{
		for (auto i : ini)
		{
			add(i);
		}
	}
	int query(int index)
	{
		if (dict[index][1] == 0)
		{
			return Int[dict[index][0]];
		}
		else
		{
			return -1;
		}
	}
	void add(string s)
	{
		if (s[0] == 'i')
		{
			Int.push_back(atoi(s.substr(1).c_str()));
			dict.push_back({ Int_Index,0 });
			Int_Index++;
		}
		if (s[0] == 's')
		{
			String.push_back(s.substr(1));
			dict.push_back({ String_Index,1 });
			String_Index++;
		}
	}
	string& operator[](unsigned int index)
	{
		if (index > dict.size())
		{
			return error_line;
		}
		else
		{
			return String[dict[index][0]];
		}
	}
	string& operator+(const string& str2)
	{
		string str1;
		str1 += str2.substr(1);
		return str1;
	}
};
