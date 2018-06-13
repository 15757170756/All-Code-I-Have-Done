/*
题目1 : 命名
时间限制:5000ms
单点时限:1000ms
内存限制:256MB
描述
有两个公司想要合并，第一个公司的名字是一个字符串S，第二个公司的名字是一个字符串T.

合并后的新公司是这样取名的：

1.先选一个S的子序列A，T的一个子序列B，要求-1 ≤ |A|-|B| ≤ 1

2.如果|A|=|B|，那么可以选择取名为A1B1A2B2..A|A|B|B|或者B1A1B2A2..B|B|A|A|，例如A=abc, B=def，则可以取名为adbecf或者daebfc.

3.如果|A|=|B|+1，那么只能取名为A1B1A2B2..A|B|B|B|A|B|+1

4.如果|B|=|A|+1，那么只能取名为B1A1B2A2..B|A|A|A|B|A|+1

现在第一个公司的老总想知道，是否存在一种取名方式，使得新的名字为S

定义字符串X是字符串Y的子序列，当且仅当X可以由Y删掉若干个位置得到。

输入
输入包含多组数据。第一行包含一个整数N，代表测试数据组数。

对于每组测试数据：

第一行一个小写字母字符串S

第二行一个小写字母字符串T

1 ≤ N ≤ 5, 1 ≤ |S|, |T| ≤ 103

输出
对于每组数据，如果存在一种取名方式使得新的名字为S的话，输出Yes，否则输出No

样例输入
3
hoge
moen
abcdefg
xacxegx
abcdef
ghijkl
样例输出
Yes
Yes
No
*/



#include <bits/stdc++.h>

using namespace std;

const int maxn = 1005;
char s[maxn],t[maxn];

bool check()
{
    int ls=strlen(s),lt=strlen(t);
    int i=0,j=0;
    while(i<ls&&j<lt)
    {
        if(s[i]==t[j]){
            i+=2;
        }
        j++;
    }
    if(i>=ls) return 1;
    i=1;j=0;
    while(i<ls&&j<lt)
    {
        if(s[i]==t[j]){
            i+=2;
        }
        j++;
    }
    if(i>=ls) return 1;
    return 0;
}
int main()
{
    int n;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%s%s",s,t);
        if(check()) printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
