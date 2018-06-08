/*
链接：https://www.nowcoder.com/acm/contest/5/A
来源：牛客网

时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
给定两个整数 l 和 r ，对于所有满足1 ≤ l ≤ x ≤ r ≤ 10^9 的 x ，
把 x 的所有约数全部写下来。对于每个写下来的数，
只保留最高位的那个数码。求1～9每个数码出现的次数。
输入描述:
一行，两个整数 l 和 r (1 ≤ l ≤ r ≤ 10^9)。
输出描述:
输出9行。

第 i 行，输出数码 i 出现的次数。
示例1
输入
复制
1 4
输出
复制
4
2
1
1
0
0
0
0
0
*/



/*
作者：toraoh
链接：https://www.nowcoder.com/discuss/28562
来源：牛客网

Prob E：
这个问题，经典起手式：求[a,b]的问题，拆成求[1,b]-[1,a-1]的问题，
而处理[1,x]的问题一般容易搞定不少。
OK，[1,x]怎么处理？
首先要意识到：在[1,x]中，有约数y的数有x/y个。
那么，假设x为常数，对函数f(y)=x/y，
在y=1,2,3...n上的点用曲线近似，是反比例函数在第一象限的图像。
（图就靠大家自己画了~）
特点：前半段很陡峭，差个1，函数值都差远了；
后半段很平坦，n/2个数的函数值都为1……
根据这两段的不同情况，我们采取不同的处理策略：
对前半段（比如，1到10万），
我们直接算有多少个数包含这个约数x，直接加到答案上。
对后半段（10万以上），我们计算有多少个约数，
只有1个、2个....个数的约数中包含他，这些数的取值范围是多少。
然后我们统计出这些约数中，有多少是以1、2、3...9开头的数，
乘上相应的约数个数，加到答案中。
这样搞定了~基本是一个sqrt(n)*log(n)的时间复杂度。
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef long long ll;
 
ll a[10],b[10],out[10];
int highest[100001];
 
void cnt(int l,int r) {
    memset(out,0,sizeof(out));
    char tmp[15];
    while(l<=r) {
        sprintf(tmp,"%d",r);
        int t2=tmp[0]-'0';
        for(int i=1;tmp[i];i++)
			t2=t2*10;
        if(t2<l)
			t2=l;
        out[tmp[0]-'0']+=r-t2+1;
        r=t2-1;
    }
}
 
void get(int x,ll* a){
    if(x==0)
        return;
    for(int i=1;i<=100000;i++){
        a[highest[i]]+=x/i;
    }
    if(x<=100000)
        return;
    int last=x;
    for(int i=1;;i++){
        int p2=x/(i+1);
        ++p2;
        if(p2<=100000)
            p2=100001;
        cnt(p2,last);
        for(int j=1;j<=9;j++)
            a[j]+=out[j]*i;
        last=x/(i+1);
        if(last<=100000)
            break;
    }
}
 
 
int main()
{
    for(int i=1;i<=9;i++){
        for(int j=1;j<=10000;j*=10){
            for(int k=0;k<j;k++){
                highest[i*j+k]=i;
            }
        }
    }
    highest[100000]=1;
    int l,r;
    scanf("%d%d",&l,&r);
    get(r,b);get(l-1,a);
    for(int i=1;i<=9;i++)
        printf("%lld\n",b[i]-a[i]);
}