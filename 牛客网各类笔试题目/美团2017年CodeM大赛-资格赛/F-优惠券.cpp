/*
链接：https://www.nowcoder.com/acm/contest/5/F
来源：牛客网

优惠券
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
美团点评上有很多餐馆优惠券，用户可以在美团点评App上购买。
每张优惠券有一个唯一的正整数编号。
当用户在相应餐馆就餐时，可以在餐馆使用优惠券进行消费。
优惠券的购买和使用按照时间顺序逐行记录在日志文件中，
运营人员会定期抽查日志文件看业务是否正确。
业务正确的定义为：一个优惠券必须先被购买，然后才能被使用。

某次抽查时，发现有硬盘故障，历史日志中有部分行损坏，
这些行的存在是已知的，但是行的内容读不出来。
假设损坏的行可以是任意的优惠券的购买或者使用。

现在问这次抽查中业务是否正确。
若有错，输出最早出现错误的那一行，即求出最大s，
使得记录1到s-1满足要求；若没有错误，输出-1。
输入描述:
m 分别表示 m (1 ≤ m ≤ 5 * 10^5) 条记录。

下面有m行，格式为：

I x （I为Input的缩写，表示购买优惠券x）；

O x（O为Output的缩写，表示使用优惠券x）；

? （表示这条记录不知道）。

这里x为正整数，且x ≤ 10^5 。
输出描述:
-1 或 x(1 ≤ x ≤ m) 其中x为使得1到x-1这些记录合法的最大行号。
示例1
输入
复制
0
1
O 1
2
？
O 1
3
I 1
？
O 1
2
I 2
O 1
输出
复制
-1
1
-1
-1
2
*/







/*
作者：toraoh
链接：https://www.nowcoder.com/discuss/28562
来源：牛客网

Prob C：把问号放到平衡树/set里，
记录并维护一下?（问号）出现的下标。
开几个数组，记录手上有几张第x种优惠券，
上次买入变成1张是什么时候，上次卖出变成0张是什么时候。
买入的时候，如果之前手里有1张了，
那么找出买入上1张后，到现在，中间的最早的？，
把这个？改成卖出操作，这样这个买入就合理了。
卖出的时候，之前已经没了的情况处理类似。
（现在看看代码，感觉实现有bug：如果真实记录里，
就只有1~10w这10万种优惠券、只有I和O两种操作，不允许空操作的话，那：
1
2
3
4
5
6
7
8
9
10
11
I 1
I 2
I 3
...
I 100000
?
O 1
O 2
O 3
...
O 100000
我的程序会觉得没问题，但实际上有：买入10万张以后，
这个？不可以再买入，只能随便卖出1张。
但是随便卖出谁，都会导致后面10万条不同的卖出操作中，
有谁实际上卖不出去了。
那个问号，要不可以代表任何操作，
要不可以是I 100001，不然我的程序是错的……
UPD：根据红q（quailty，http://codeforces.com/profile/quailty ，
 http://osu.ppy.sh/u/6423914 ）的意思，是允许有I 100001，那就没问题了
*/


#include <stdio.h>
#include <algorithm>
#include <set>
using namespace std;
int cnt[100005];
int lasto[100005];
int lasti[100005];
int maxid,err;
set<int> left;
char str[2];
int id,m;
int main(){
    while(~scanf("%d",&m)){
        fill(cnt,cnt+maxid+1,0);
        fill(lasto,lasto+maxid+1,0);
        fill(lasti,lasti+maxid+1,0);
        maxid=0;
        err=-1;
        left.clear();
        for(int i=1;i<=m;i++){
            scanf("%s",str);
            if(str[0]=='?'){
                left.insert(i);
            }else{
                scanf("%d",&id);
                maxid=max(maxid,id);
                if(str[0]=='I'){
                    cnt[id]++;
                    if(cnt[id]>=2){
                        auto it=left.lower_bound(lasti[id]);
                        if(it!=left.end()){
                            left.erase(it);
                            --cnt[id];
                        }else{
                            if(err==-1)err=i;
                        }
                    }
                    lasti[id]=i;
                }else{
                    cnt[id]--;
                    if(cnt[id]<0){
                        auto it=left.lower_bound(lasto[id]);
                        if(it!=left.end()){
                            left.erase(it);
                            ++cnt[id];
                        }else{
                            if(err==-1)err=i;
                        }
                    }
                    lasto[id]=i;
                }
            }
        }
        printf("%d\n",err);
         
    }
    return 0;
}