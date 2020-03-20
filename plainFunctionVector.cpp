#include <iostream>
template <class T>
class vector
{
private:
	size_t _capacity = 1;
	T* ptr1 = new T[_capacity];
	T* cursor = ptr1;
	bool _empty = true;
	void allocateAndMove(size_t size, size_t cursorMove)
	{
		T* tempPtr = new T[size];	
		size_t distance;
		for (auto i = this->ptr1; i != cursor; ++i)	//将原来的数据拷贝到新内存中
		{
			distance = i - ptr1;
			*(tempPtr + distance) = *i;
		}
		delete[] ptr1; //释放原内存空间
		ptr1 = tempPtr;//指针指向新内存空间
		cursor = ptr1 + cursorMove;//cursor指向第一个无数据内存
		tempPtr = nullptr;
		delete[] tempPtr;
		_capacity = size;
	}
public:
	void reserve(const size_t& size)
	{
		if (size > _capacity)
		{
			_capacity = size;
			T* temp = new T[_capacity];
			delete[] ptr1;
			ptr1 = temp;
			cursor = ptr1;
			temp = nullptr;
		}
	}
	size_t& capacity()
	{
		return _capacity;
	}
	size_t size()
	{
		return cursor - ptr1;
	}
	bool& empty()
	{
		return _empty;
	}
	T* begin()
	{
		return ptr1;
	}
	T* end()
	{
		return cursor;
	}
	void push_back(const T& data)
	{
		_empty = false;
		if (cursor != (ptr1 + _capacity))
		{
			*cursor = data;
			++cursor;
		}
		else
		{
			allocateAndMove(2 * _capacity, _capacity);
			push_back(data);
		}
	}
	void shrink_to_fit()
	{
		allocateAndMove(size(),size());
	}
public:
	T& operator[](size_t index)
	{
		if (ptr1 + index >= cursor) //如果越界
			return *(cursor -1); //返回最后一个元素;
		return *(ptr1 + index);
	}
	
	vector(std::initializer_list<T> lst)
	{
		_empty = false;
		reserve(lst.size());
		for (auto& i : lst)
		{
			push_back(i);
		}
	}
	vector() = default;
	~vector()
	{
		delete[] ptr1;
		ptr1 = nullptr;
		cursor = nullptr;
	}
};
int main()
{
	vector<int> array { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	array.push_back(18);
	//array.shrink_to_fit();
	for (auto iter = array.begin(); iter != array.end(); ++iter)
	{
		std::cout << *iter << std::endl;
	}
	if (!array.empty())
	{
		std::cout << "capicity is : " << array.capacity() << "\n"
			<< "size is : " << array.size() << std::endl;
	}
}
