#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using std::vector; using std::string;
using std::next_permutation;
using std::ostream;
class arrange
{
private:
	vector<string> original_vec;
	vector<string> copied;
	vector<vector<string>> final_vec;
public:
    explicit arrange(const vector<string> &v)
	{
		this->original_vec = v;
		this->copied = v;
		auto* ptr_begin = &copied[0], * ptr_end = &copied[copied.size() - 1];
		std::sort(ptr_begin, ptr_end + 1);
		do {
			final_vec.push_back(copied);
		} while (next_permutation(ptr_begin, ptr_end + 1));
	}
	vector<vector<string>> getArranged()
	{
		return final_vec;
	}
	vector<string> getOriginal()
	{
		return original_vec;
	}
	friend ostream& operator<<(ostream& out, const arrange& arr)
	{
		for (auto &i : arr.final_vec)
		{
			for (auto &j : i)
			{
				out << j << " ";
			}
			out << "\n";
		}
		return out;
	}
};