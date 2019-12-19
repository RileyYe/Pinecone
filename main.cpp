#include<iostream>

using namespace std;
int main() {
    //从键盘输入两个正整数 a 和 b ，计算并输出 a/ b 的商和余数
    int a, b;
    cin >> a >> b;
    cout << (a - a % b) / b << " " << a % b;
}
