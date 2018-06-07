/*
链接：https://www.nowcoder.com/acm/contest/7/B
来源：牛客网

黑白树
时间限制：C/C++ 1秒，其他语言2秒
空间限制：C/C++ 32768K，其他语言65536K
64bit IO Format: %lld
题目描述 
一棵n个点的有根树，1号点为根，相邻的两个节点之间的距离为1。树上每个节点i对应一个值k[i]。每个点都有一个颜色，初始的时候所有点都是白色的。
你需要通过一系列操作使得最终每个点变成黑色。每次操作需要选择一个节点i，i必须是白色的，然后i到根的链上（包括节点i与根）所有与节点i距离小于k[i]的点都会变黑，已经是黑的点保持为黑。问最少使用几次操作能把整棵树变黑。
输入描述:
第一行一个整数n (1 ≤ n ≤ 10^5)
接下来n-1行，每行一个整数，依次为2号点到n号点父亲的编号。
最后一行n个整数为k[i] (1 ≤ k[i] ≤ 10^5)

样例解释:
对节点3操作，导致节点2与节点3变黑
对节点4操作，导致节点4变黑
对节点1操作，导致节点1变黑
输出描述:
一个数表示最少操作次数
示例1
输入
复制
4
1
2
1
1 2 2 1
输出
复制
3
*/



/*
作者：NotDeep
链接：https://www.nowcoder.com/discuss/29146
来源：牛客网

黑白树
思路
“每次操作选择的点必须是白色”这个条件其实是可以无视的，
因为这可以通过自顶向 下选择来避免。
通过观察发现最底层的叶子必须选择，
选完之后无视变黑的点，
剩下的叶子也必须通过选择其子树中某个节点来使自己变黑，
因此贪心选择能染层数最深(最上面被染到的点最接 近根)的点+模拟即可。
复杂度为线性。
*/


#include<bits/stdc++.h>
#define int64 long long
#define sqr(x) (x)*(x)
#define mk make_pair
#define pb push_back
#define fi first
#define se second
#define rep(i,x,y) for(int i=(x);i<=(y);++i)
#define VI vector<int>
#define VI64 vector<int64>
#define VS vector<string>
#define PII pair<int,int>
#define PDD pair<double,double>
#define VPII vector< PII >
#define SZ(x) ((int)(x).size())
#define N 120000
using namespace std;
const double pi=acos(-1);
VI E[N];
int dep[N],fa[N],ans,n,f[N],k[N],p[N];
void dfs(int x){
    f[x]=dep[x]-k[x]+1;
    p[x]=1e9;
    for(int i=0;i<E[x].size();++i){
        dep[E[x][i]]=dep[x]+1;
        dfs(E[x][i]);
        f[x]=min(f[x],f[E[x][i]]);
        p[x]=min(p[x],p[E[x][i]]);
    }
    if(p[x]>dep[x]){
        ans++;
        p[x]=f[x];
    }
}
int main(int argv,char **argc){
//    freopen("in","r",stdin);
//    freopen("out","w",stdout);
    freopen(argc[1],"r",stdin);
    freopen(argc[2],"w",stdout);
    scanf("%d",&n);
    rep(i,2,n){
        scanf("%d",&fa[i]);
        E[fa[i]].pb(i);
    }
    dep[1]=1;
    rep(i,1,n)scanf("%d",&k[i]);
    dfs(1);
    cerr<<ans<<endl;
    printf("%d\n",ans);
    fclose(stdin);
    fclose(stdout);
    return 0;
}