/*
链接：https://www.nowcoder.com/acm/contest/7/F
来源：牛客网

子串
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
给出一个正整数n，我们把1..n在k进制下的表示连起来记为s(n,k)，
例如s(16,16)=123456789ABCDEF10, s(5,2)=11011100101。
现在对于给定的n和字符串t，
我们想知道是否存在一个k(2 ≤ k ≤ 16)，使得t是s(n,k)的子串。
输入描述:
第一行一个整数n(1 ≤ n ≤ 50,000)。
第二行一个字符串t(长度 ≤ 1,000,000)
输出描述:
"yes"表示存在满足条件的k，否则输出"no"
示例1
输入
复制
8
01112
输出
复制
yes
*/





/*
作者：NotDeep
链接：https://www.nowcoder.com/discuss/29146
来源：牛客网

子串
思路
本题是一道简单的模拟题。直接对于 15 种可能的 k 枚举，
每种情况下直接使用 KMP 算 法进行匹配即可，
时间复杂度是 O(n log n + |t|), 其中|t|是 t 的长度。
可以进行一些简单的优化，例如 t 中出现数字 i 的话必然进制 k > i。
这样可以常数优化。
实际上通过对 t 的结构进行研究也许可以获得更好的结果(判断断点)，
但是对于本题 的范围没有必要。
*/


#include <iostream>
#include <cassert>
#include <cstdlib>
#include <cstdio> 
using namespace std;

const int maxn = 50000 + 10;
const int maxt = 1000000 + 1;

const char alphabet[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'}; 

char tmp[20]; 
string itoa(int n, int k) {
    int c;
    for (c = 0; n; c ++) tmp[c] = alphabet[n % k], n /= k; 
    tmp[c] = 0;
    for (int i = 0; i < c / 2; ++ i) swap(tmp[i], tmp[c-1-i]); 
    string str (tmp); 
    return str; 
}

string seq(int n, int k) {
    string str = ""; 
    for (int i = 1; i <= n; i ++)
        str = str + itoa(i, k);
    return str; 
}

string s, t; 
int nx[maxt]; 

int main() {
    int n;
    cin >> n;
    cin >> t; 
    nx[0] = 0;
    for (int i = 0; i < t.length() - 1; i ++) {
        int j = nx[i]; 
        while (j && t[i + 1] != t[j]) j = nx[j - 1];
        nx[i + 1] = (t[i + 1] == t[j]) ? j + 1 : 0; 
    }
    for (int k = 2; k <= 16; k ++)  {
        s = seq(n, k);
        int j = 0; 
        bool matched = false; 
        for (int i = 0; i < s.length(); i ++ ) {
            while (j && s[i] != t[j]) j = nx[j - 1];
            j = (s[i] == t[j]) ? j + 1 : 0; 
            if (j == t.length()) {
                matched = true;
                break; 
            }
        }
        if (matched) {
            cout << "yes\n";
            return 0; 
        }
    }
    cout << "no\n"; 
    return 0; 
}