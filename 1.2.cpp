#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

int max(int a, int b, int c, int d) {
    int max1, max2;
    a > b ? max1 = a : max1 = b;
    c > d ? max2 = c : max2 = d;
    max1 > max2 ? max1 = max1 : max1 = max2;
    return max1;
}//对四个数据比较
int max2(const vector<int>& vctr) //遍历比较
{
    int max = vctr[0];
    for (auto i : vctr)
    {
        i > max ? max = i : max;
    }
    return max;
}

int main() {
    //从键盘输入四个整数，并输出其中大的数
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    cout << max(a, b, c, d);
}
