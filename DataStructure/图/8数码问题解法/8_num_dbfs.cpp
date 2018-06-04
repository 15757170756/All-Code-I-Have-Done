#include<iostream>
using namespace std;

#define MAXN 400000

#define SWAP(a, b) {char t = a; a = b; b = t;}

typedef struct _Node Node;

struct _Node
{
        char tile[10]; // represent the tile as a string ending with '\0'
        char pos;   // the position of 'x'
        char dir;  //the moving direction of 'x'
        int parent; //index of parent node
};

int head[2], tail[2];
Node queue[2][MAXN];// two queues for double directoin BFS

//shift of moving up, down, left ,right
int shift[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

//for output direction!
char dir[4][2] = {{'u', 'd'}, {'d', 'u'}, {'l', 'r'}, {'r', 'l'}};

//test case
char start[10] = "234150768";
char end[10] = "123456780";

//read a tile 3 by 3
void readtile()
{
        int i;
        char temp[10];
        for(i = 0; i < 9; ++i)
        {
                scanf("%s", temp);
                start[i] = temp[0];
        }
        start[9] = '\0';
}

//print result
void print_backward(int i)
{
        if(queue[0][i].parent != -1)
        {
                print_backward(queue[0][i].parent);
                printf("%c", queue[0][i].dir);
        }
}
void print_forward(int j)
{
        if(queue[1][j].parent != -1)
        {
                printf("%c", queue[1][j].dir);
                print_forward(queue[1][j].parent);
        }
}
void print_result(int i, int j)
{
        //printf("%d,%d\n", i, j);
        print_backward(i);
        print_forward(j);
        printf("\n");
}

//init the queue
void init(int qi, const char* state)
{
        strcpy(queue[qi][0].tile, state);
        queue[qi][0].pos = strchr(state, '0') - state;
        queue[qi][0].parent = -1;

        head[qi] = tail[qi]  = 0;
}

//check if there are duplicates in the queue
//time comlexity:O(n)
//We can optimise this function using HashTable
int isduplicate(int qi)
{
        int i;
        for(i = 0; i < tail[qi]; ++i)
        {
                if(strcmp(queue[qi][tail[qi]].tile, queue[qi][i].tile) == 0)
                {
                        return 1;
                }
        }
        return 0;
}

//check if the current node is in another queue!
//time comlexity:O(n)
//We can optimise this function using HashTable
int isintersect(int qi)
{
        int i;
        for(i = 0 ; i < tail[1 - qi]; ++i)
        {
                if(strcmp(queue[qi][tail[qi]].tile, queue[1 - qi][i].tile) == 0)
                {
                        return i;
                }
        }

        return -1;
}

//expand nodes
int expand(int qi)
{
        int i, x, y, r;

        Node* p = &(queue[qi][head[qi]]);
        head[qi]++;

        for(i = 0; i < 4; ++i)
        {
                x = p->pos / 3 + shift[i][0];
                y = p->pos % 3 + shift[i][1];
                if(x >= 0 && x <= 2 && y >= 0 && y <= 2)
                {
                        tail[qi]++;
                        Node* pNew = &(queue[qi][tail[qi]]);
                        strcpy(pNew->tile, p->tile);
                        SWAP(pNew->tile[ 3 * x + y], pNew->tile[p->pos]);
                        pNew->pos = 3 * x + y;
                        pNew->parent = head[qi] - 1;
                        pNew->dir = dir[i][qi];
                        if(isduplicate(qi))
                        {
                                tail[qi]--;
                        }
                        else
                        {
                                if((r = isintersect(qi)) != -1)
                                {
                                        if(qi == 1)
                                        {
                                                print_result(r, tail[qi]);
                                        }
                                        else
                                        {
                                                print_result(tail[qi], r);
                                        }
                                        return 1;
                                }
                        }
                }
        }
        return 0;
}

//call expand to generate queues
int solve()
{
        init(0, start);
        init(1, end);
       
        while(head[0] <= tail[0] && head[1] <= tail[1])
        {
                //expand the shorter queue firstly
                if(tail[0] - head[0] >= tail[1] - head[1])
                {
                        if(expand(1)) return 1;
                }
                else
                {
                        if(expand(0)) return 1;
                }
        }
       
        while(head[0] <= tail[0]) if(expand(0)) return 1;
        while(head[1] <= tail[1]) if(expand(1)) return 1;
        return 0;
}

int main(int argc, char** argv)
{
        readtile();
        if(!solve())
        {
                printf("unsolvable\n");
        }
        system("pause"); //pause
        return 0;
}

