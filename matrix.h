#pragma once
#include <iostream>
#include <vector>
#include <ostream>
using std::cout; using std::endl;
using std::vector; using std::ostream;
class matrix
{
private:
	vector<vector<int>> v1;

public:
	matrix(vector<vector<int>> v1)	//构造函数
	{
		this->v1 = v1;
	}
	int row = int(), column = int();	//行，列
	auto& operator+=(matrix m2)	//矩阵自加
	{
		auto v2 = m2.v1;
		row = v1.size();
		column = v1[0].size();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				v1[i][j] += v2[i][j];
			}
		}
		return v1;
	}
	friend ostream& operator<<(ostream& os1, const matrix& m2)	//重载<<
	{
		for (auto i : m2.v1)
		{
			for (auto j : i)
			{
				os1 << j << " ";
			}
			os1 << endl;
		}
		return os1;
	}
	auto& operator+(const matrix& m2)	//重载+
	{
		auto temp = this->v1;
		row = temp.size();
		column = temp[0].size();
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < column; j++)
			{
				temp[i][j] += m2.v1[i][j];
			}
		}
		return temp;
	}
	auto& operator[](const int& ele)	//重载[]
	{
		return v1[ele];
	}
	//matrix operator*(const matrix& m2)
	//{
	//	auto temp = this->v1;
	//	row = temp.size();
	//}
};
//int main()
//{
//	matrix m1({ {1,2},{3,4} });
//	matrix m2 = m1;
//	m2 += m1;
//	cout << m2;
//}