#pragma once
#include <vector>
#include <string>
#include <sstream>
class list
{
private:
    std::vector<std::vector<int>> data_base = {};
    std::vector<int> Int = {};	// 0
    std::vector<double> Float = {};		// 1
    std::vector<std::string> String = {};		// 2
    int current_index = int(), Int_index = int(), Float_index = int(),
        String_index = int();
public:
    int& length = current_index;
    list(std::initializer_list<std::string> init)
    {
        for (auto i : init)
        {
            if (i[0] == 'i')
            {
                append(std::stoi(i.substr(1)));
            }
            if (i[0] == 'f')
            {
                append(std::stod(i.substr(1)));
            }
            if (i[0] == 's')
            {
                append(i.substr(1));
            }
        }
    }
    void append(std::string i)
    {
        String.push_back(i);
        data_base.push_back({ 2,String_index });
        String_index += 1;
        current_index += 1;
    }
    void append(int i)
    {
        Int.push_back(i);
        data_base.push_back({ 0,Int_index });
        Int_index += 1;
        current_index += 1;
    }
    void append(double i)
    {
        Float.push_back(i);
        data_base.push_back({ 1, Float_index });
        Float_index += 1;
        current_index += 1;
    }
    void pop()
    {
        switch (data_base[length -1][0])
        {
        case 0:
            Int.pop_back();
            break;
        case 1:
            break;
        case 2:
            String.pop_back();
            break;
        }
        current_index -= 1;
        data_base.pop_back();
    }
    double sum()
    {
        double temp = double();
        if (String.empty())
        {
            for (auto i : Int)
            {
                temp += (double)i;
            }
            for (auto i : Float)
            {
                temp += (double)i;
            }
        }
        return temp;
    }
    double query(int index)
    {
        if (data_base[index][0] == 0)
        {
            return (double)Int[data_base[index][1]];
        }
        if (data_base[index][0] == 1)
        {
            return Float[data_base[index][1]];
        }
        else
        {
            return -1.0;
        }
    }
    friend std::ostream& operator<<(std::ostream& os1, list lst)	//重载<<
    {
        os1 << "[";
        for (auto ele : lst.data_base)
        {
            switch (ele[0])
            {
            case 0:
                os1 << lst.Int[ele[1]] << " ,";
                break;
            case 1:
                os1 << lst.Float[ele[1]] << " ,";
                break;
            case 2:
                os1 << "\"" << lst.String[ele[1]] << "\"" << " ,";
                break;
            }
        }
        os1 << "]";
        return os1;
    }
    std::string operator[](const int& index)
    {
        std::string str;
        std::stringstream sstream;
        if (index >= 0 && index < length)
        {
            switch (data_base[index][0])
            {
            case 0:
                sstream << Int[data_base[index][1]];
                break;
            case 1:
                sstream << Float[data_base[index][1]];
                break;
            case 2:
                sstream << String[data_base[index][1]];
                break;
            }
            sstream >> str;
            return str;
        }
        else
        {
            return "[error] : index out of range";
        }

    }
};
/*
初始化 ：   1. list lst = list({});
	        2. list lst = list({"i100","f3.14","sHello"});
类属性 ：length(int)，此list的长度.
类方法 ：append()， 往list中添加元素(string, double, int)
	    query(int index)，获取list中索引为index的数字元素.
	    pop()， 弹出list中最后一位元素.
操作符 ：list[int]，获取list[int]的元素，元素类型为string；
                    如果int >= length || int < 0，显示 index out of range.
	    std::cout << list， 按次序打印出list中所有元素.
*/
