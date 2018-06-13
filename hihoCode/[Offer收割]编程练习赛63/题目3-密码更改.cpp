/*
题目3 : 密码更改
时间限制:20000ms
单点时限:1000ms
内存限制:256MB
描述
小 C 有一个由数字构成的密码 S，例如："123" , "3211" ,"111111"，"0123"

定义数字密码的大小为：这个数字密码代表的十进制数字的大小。

现在小 C 想改成一个更强的密码，新密码需要满足以下条件：

1.为了保证强度，每个数字在新密码中必须最多只出现一次。

2.旧密码和新密码的长度一样。

3.新密码和旧密码的距离尽量大。

4.如果有多个距离相同的，则取大小比较小的密码。

定义两个长度相同的数字密码 a , b的距离为min(|a-b|,10N-|a-b|)

其中 N 是数字密码 a,b 的长度。

例如 "012" 和 "987" 的距离为 25。

现在给定S，小 C 想知道满足条件的新密码是啥。

输入
第一行读入一个由数字构成的字符串 S

保证 1 ≤ |S| ≤ 10，其中|S|表示 S 的串长。

输出
输出一个长度和 S 相同的由数字构成的字符串，表示新密码。

额外样例
样例输入	样例输出
512
012
99999
49876
765876346
265874931
样例输入
201
样例输出
701
*/


#include <bits/stdc++.h>

using namespace std;
const long long INF = 1000000000000000LL;
char s[15];
int a[19];
int b[20];
int l;
long long num=0;
long long ten;
long long check()
{
    long long tnum=0;
    for(int i=0;i<l;i++)
    {
        tnum=tnum*10+a[i];
    }
    return min(abs(tnum-num),ten-abs(tnum-num));
}
int main()
{
    scanf("%s",s);
    num=0;
    ten=1;
    l=strlen(s);
    for(int i=0;i<l;i++)
    {
        num=num*10+(s[i]-'0');
        ten=ten*10;
    }
    for(int i=0;i<10;i++)
        a[i]=b[i]=i;
    long long ans=check();
    while(next_permutation(a,a+10))
    {
        long long tans = check();
        if(tans>ans){
            ans=tans;
            for(int i=0;i<l;i++)
                b[i]=a[i];
        }
    }
    for(int i=0;i<l;i++)
        printf("%c",b[i]+'0');
    printf("\n");
    return 0;
}
