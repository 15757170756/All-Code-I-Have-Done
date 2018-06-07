/*
链接：https://www.nowcoder.com/acm/contest/7/D
来源：牛客网

模
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
给定四个正整数a,b,c,k，回答是否存在一个正整数n，使得a*n在k进制表示下的各位的数值之和模b为c。
输入描述:
第一行一个整数T(T <= 5,000)。 

接下来T行，每行四个正整数a,b,c,k（1 ≤ a ≤ 10^18; 2 ≤ k ≤ 10^18; 0 ≤ c < b ≤ 10^18）表示一个询问，所有输入都是十进制的。
输出描述:
对于每组数据输出一行，Yes表示存在，No表示不存在。
示例1
输入
复制
2
3 9 5 10
7 3 1 10
输出
复制
No
Yes
*/


#include<cstdio>
#include<iostream>

using namespace std;

typedef long long LL;
int T;
LL a,b,c,k;
LL gcd(LL a,LL b)
{
	return b?gcd(b,a%b):a;
}

int main()
{
    for(scanf("%d",&T);T--;)
    {
        scanf("%lld%lld%lld%lld",&a,&b,&c,&k);
        if(c%gcd(b,gcd(a,k-1))==0)
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}