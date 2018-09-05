/*
http://blog.csdn.net/acdreamers/article/details/16902023


0 1 2
1 2 3
2 3 4
3 1 3
4 4 1
5 1 5
6 4 5


struct Edge
{
int next;
int to;
int w;
};

其中
edge[i].to表示第i条边的终点,
edge[i].next表示与第i条边同起点的下一条边
（我怎么觉得是上一条边呀）的存储位置（在第几条边）,
edge[i].w为边权值.

另外还有一个数组head[],它是用来表示以i为起点的第一条边存储的位置,
实际上你会发现这里的第一条边存储的位置其实
在以i为起点的所有边的最后输入的那个编号.

head[]数组一般初始化为-1,对于加边的add函数是这样的:


void add(int u,int v,int w)
{
edge[cnt].w = w;
edge[cnt].to = v;
edge[cnt].next = head[u];
head[u] = cnt++;
}


初始化cnt = 0,这样,现在我们还是按照上面的图和输入来模拟一下:


edge[0].to = 2;     edge[0].next = -1;      head[1] = 0;
edge[1].to = 3;     edge[1].next = -1;      head[2] = 1;
edge[2].to = 4;     edge[2],next = -1;      head[3] = 2;
edge[3].to = 3;     edge[3].next = 0;       head[1] = 3;
edge[4].to = 1;     edge[4].next = -1;      head[4] = 4;
edge[5].to = 5;     edge[5].next = 3;       head[1] = 5;
edge[6].to = 5;     edge[6].next = 4;       head[4] = 6;


很明显,head[i]保存的是以i为起点的所有边中编号最大的那个,
而把这个当作顶点i的第一条起始边的位置.


这样在遍历时是倒着遍历的,也就是说与输入顺序是相反的,不过这样不影响结果的正确性.
比如以上图为例,以节点1为起点的边有3条,它们的编号分别是0,3,5   而head[1] = 5


我们在遍历以u节点为起始位置的所有边的时候是这样的:
for(int i=head[u];~i;i=edge[i].next)
那么就是说先遍历编号为5的边,也就是head[1],
然后就是edge[5].next,也就是编号3的边,然后继续edge[3].next,也
就是编号0的边,可以看出是逆序的.


*/

