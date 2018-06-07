/*
链接：https://www.nowcoder.com/acm/contest/7/A
来源：牛客网

合并字符串的价值
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 65536K，其他语言131072K
64bit IO Format: %lld
题目描述 
输入两个字符串a和b，合并成一个串c，属于a或b的字符在c中顺序保持不变。如"ACG"和"UT"可以被组合成"AUCTG"或"ACUGT"等。
我们定义字符串c的价值如下：令n为字符串c的长度，分界线k(1<=k<=n-1)将c分为两个子串u=c[1..k]，v=c[k+1..n]。u、v中字符的任意排列，使得u、v的最长公共前缀最大，这就是分界线k的价值，而所有分界线k价值最大的一个为字符串c的价值。
比如，字符串c=ACGTTTGCAT的价值为5，因为将该串分成两半得到u=ACGTT，V=TGCAT，重新排列后可以使得u=v，即最长公共前缀为5。
你需要求出所有可能的c中价值最大的字符串，输出这个最大价值即可。
输入描述:
第一行一个整数T(T ≤ 500)。
接下来2T行，每行一个字符串，每两行代表一对字符串a和b（|a|,|b|<=100,000；∑(|a|+|b|)<=500,000），字符串的字符集为{A,C,G,T}。
输出描述:
对于每组数据输出一行，一个整数表示价值最大的c的价值。
示例1
输入
复制
2
ACGT
ACGT
AACCGGTT
ACACAGAT
输出
复制
4
7
*/


#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<iostream>
using namespace std;
const int maxn=500005;
int CtI[256],T;
int n,m,a[maxn],b[maxn];
char str[maxn];
int cnt[maxn][4],pos[4][maxn];

struct node
{
    int s[16];
    node *lc,*rc;

    int Max(int l,int r,const int &a,const int &b,const int &mask)
    {
        if(l>=a&&r<=b)return s[mask];
        int mid=l+r>>1;
        if(b<=mid)return lc->Max(l,mid,a,b,mask);
        if(a>mid)return rc->Max(mid+1,r,a,b,mask);
        return max(lc->Max(l,mid,a,b,mask),rc->Max(mid+1,r,a,b,mask));
    }

}ndl[maxn*2],*ns,*root;

node* build(int l,int r)
{
    node *x=++ns;
    if(l==r)
    {
        for(int mask=0;mask<16;mask++)
        {
            x->s[mask]=0;
            for(int c=0;c<4;c++)
                x->s[mask]+=(mask>>c&1)?cnt[l][c]:-cnt[l][c];
        }
    }
    else
    {
        int mid=l+r>>1;
        x->lc=build(l,mid);
        x->rc=build(mid+1,r);
        for(int mask=0;mask<16;mask++)
            x->s[mask]=max(x->lc->s[mask],x->rc->s[mask]);
    }
    return x;
}

void init()
{
    CtI['A']=0,CtI['C']=1,CtI['G']=2,CtI['T']=3; 
    scanf("%s",str+1);n=strlen(str+1);
    for(int i=1;i<=n;i++)a[i]=CtI[str[i]];
    scanf("%s",str+1);m=strlen(str+1);
    for(int i=1;i<=m;i++)b[i]=CtI[str[i]];

    for(int i=1;i<=n;i++)
    {
        memcpy(cnt[i],cnt[i-1],sizeof(cnt[0]));
        cnt[i][a[i]]++;
        pos[a[i]][cnt[i][a[i]]]=i;
    }
    ns=ndl;
    root=build(0,n);
}

void work()
{
    int bA[4],bL[4];
    memset(bA,0,sizeof(bA));
    memset(bL,0,sizeof(bL));
    for(int i=1;i<=m;i++)
        bA[b[i]]++;
    int ans=0,sl[6],cu[6];
    for(int l,r,d,k,mask,i=0;i<=m;i++)
    {
        if(i)bL[b[i]]++;
        for(int c=0;c<4;c++)
        {
            k=bA[c]-bL[c]-bL[c]+cnt[n][c];
            if(k<0)k=(k-1)/2;
            else k/=2;
            k++;
            if(k<=0)k=-1;
            else if(k>cnt[n][c])k=n;
            else k=pos[c][k]-1;
            sl[c]=cu[c]=k;
        }
        sort(sl,sl+4);
        sl[5]=n;
        for(int j=0;j<=4;j++)
        {
            if(j==0)l=0;
            else l=sl[j-1]+1;
            r=sl[j];
            l=max(l,0),r=min(r,n);
            if(l<=r)
            {
                d=mask=0;
                for(int c=0;c<4;c++)
                    if(r<=cu[c])d+=bL[c],mask|=1<<c;
                    else d+=bA[c]-bL[c]+cnt[n][c];
                ans=max(ans,d+root->Max(0,n,l,r,mask));
            }
        }
    }
    printf("%d\n",ans);
}

int main()
{
    freopen("2.in","r",stdin);
    freopen("2.out","w",stdout);
    for(scanf("%d",&T);T--;)
    {
        init();
        work();
    }
    return 0;
}