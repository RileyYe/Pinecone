#include <vector>
#include <ostream>
using std::vector; using std::ostream;
class matrix
{
private:
	vector<vector<double>> v1;

public:
	matrix(vector<vector<double>> v1)	//构造函数
	{ 
		this->v1 = v1;
	}
	int row = int(), column = int();	//行，列
	auto operator+=(const matrix& m2)	//矩阵自加
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
				os1 << j << "\t";
			}
			os1 << "\n\n";
		}
		return os1;
	}
	auto operator+(const matrix& m2)	//重载+
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
	auto operator[](const int& ele)	//重载[]
	{
		return v1[ele];
	}
	void operator*=(const double& num)
	{
		for (auto &i :	v1)
		{
			for (auto &j : i)
			{
				j *= num;
			}
		}
	}
	matrix operator*(const double& num)        
	{
		matrix temp(this->v1);
		for (auto& i : temp.v1)
		{
			for (auto& j : i)
			{
				j *= num;
			}
		}
		return temp;
	}
};
