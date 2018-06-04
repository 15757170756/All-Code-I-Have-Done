// 8_num.cpp : Defines the entry point for the console application.
//

#include "iostream"
using namespace std;

static int target[9]={1,2,3,4,5,6,7,8,0};
//class definition
class CEight
{
private:
	int num[9];
	int not_in_position_num;
	int deapth;
	int eva_function;

public:
	CEight* parent;
	CEight* leaf_next;
	CEight* leaf_pre;

	CEight(int init_num[9]);
//	CEight(int num1,int num2,int num3,int num4,int num5,int num6,int num7,int num8,int num9)
//	{
//		num[0]=num1;
//		num[1]=num2;
//		num[2]=num3;
//		num[3]=num4;
//		num[4]=num5;
//		num[5]=num6;
//		num[6]=num7;
//		num[7]=num8;
//		num[8]=num9;
//	}
	CEight(void)
	{
		for (int i=0;i<9;i++)
			num[i]=i;
	}

	void cul_para(void);

	void get_numbers_to(int other_num[9]);
	int get_nipn(void)
	{return not_in_position_num;}

	int get_deapth(void)
	{return deapth;}
	int get_evafun(void)
	{return eva_function;}
	void set_num(int other_num[9]);

	void show(void);
	
	CEight& operator=(CEight&);
	CEight& operator=(int other_num[9]);
	int operator==(CEight&);
	int operator==(int other_num[9]);
};

void CEight::cul_para(void)
{
	int i;
	int temp_nipn=0;
	for (i=0;i<9;i++)
		if (num[i]!=target[i])
			temp_nipn++;
	not_in_position_num=temp_nipn;
	if (this->parent==NULL)
		deapth=0;
	else
		deapth=this->parent->deapth+1;
	eva_function=not_in_position_num+deapth;
}


CEight::CEight(int init_num[9])
{
	for (int i=0;i<9;i++)
		num[i]=init_num[i];
}

void CEight::show()
{
       for (int i=0;i<9;i++)    {
             cout<<num[i];
             if ((i+1)%3)
                 cout<<" ";
             else
                 cout<<"\n";
       }
}

void CEight::get_numbers_to(int other_num[9])
{
	for (int i=0;i<9;i++)
		other_num[i]=num[i];
}

void CEight::set_num(int other_num[9])
{
	for (int i=0;i<9;i++)
		num[i]=other_num[i];
}

CEight& CEight::operator=(CEight& another_8num)
{
	for (int i=0;i<9;i++)
		num[i]=another_8num.num[i];
	not_in_position_num=another_8num.not_in_position_num;
	deapth=another_8num.deapth+1;
	eva_function=not_in_position_num+deapth;
	return *this;
}

CEight& CEight::operator=(int other_num[9])
{
	for (int i=0;i<9;i++)
		num[i]=other_num[i];
	return *this;
}

int CEight::operator==(CEight& another_8num)
{
	int match=1;
	for (int i=0;i<9;i++)
		if(num[i]!=another_8num.num[i])
		{
			match=0;
			break;
		}
	if (match==0)
		return 0;
	else 
		return 1;
}

int CEight::operator==(int other_num[9])
{
	int match=1;
	for (int i=0;i<9;i++)
		if(num[i]!=other_num[i])
		{
			match=0;
			break;
		}
	if (match==0)
		return 0;
	else 
		return 1;
}

//class definition over
//*************************


//空格向上移
int move_up(int num[9])
{
    int i;
	for (i=0;i<9;i++)
		if (num[i]==0)
			break;
	if (i<3)
		return 0;
	else
	{
		num[i]=num[i-3];
		num[i-3]=0;
		return 1;
	}
}

//空格向下移
int move_down(int num[9])
{
    int i;
	for (i=0;i<9;i++)
		if (num[i]==0)
			break;
	if (i>5)
		return 0;
	else
	{
		num[i]=num[i+3];
		num[i+3]=0;
		return 1;
	}
}
//空格向左移
int move_left(int num[9])
{
    int i;
	for (i=0;i<9;i++)
		if (num[i]==0)
			break;
	if (i==0||i==3||i==6)
		return 0;
	else
	{
		num[i]=num[i-1];
		num[i-1]=0;
		return 1;
	}
}
//空格向右移
int move_right(int num[9])
{
    int i;
	for (i=0;i<9;i++)
		if (num[i]==0)
			break;
	if (i==2||i==5||i==8)
		return 0;
	else
	{
		num[i]=num[i+1];
		num[i+1]=0;
		return 1;
	}
}

//判断可否解出
int icansolve(int num[9],int target[9])
{
	int i,j;
	int count_num = 0;
	int count_target = 0;
	for (i=0;i<9;i++)
		for (j=0;j<i;j++)
		{
			if(num[j]<num[i]&&num[j]!=0)
				count_num++;
			if(target[j]<target[i]&&target[j]!=0)
				count_target++;
		}
	count_num=count_num-2*(count_num/2);
	count_target=count_target-2*(count_target/2);
	if ((count_num==1&&count_target==1)||(count_num==0&&count_target==0))
		return 1;
	else
		return 0;
}

//判断有无重复
int existed(int num[9],CEight *where)
{
	CEight *p;
	for(p=where;p!=NULL;p=p->parent)
		if(*p==num)
			return 1;
	return 0;
}

//寻找估价函数最小的叶子节点
CEight* find_OK_leaf(CEight* start)
{
	CEight *p,*OK;
	p=OK=start;
	int min=start->get_evafun();
	for(p=start;p!=NULL;p=p->leaf_next)
		if(min>p->get_evafun())
		{
			OK=p;
			min=p->get_evafun();
		}
	return OK;
}

//主函数开始
int main(void)
{
	double  time;   
	clock_t Start,Finish;
	int memery_used=0,step=0;
	int num[9];
	int flag=0;//是否输入错误标志，1表示输入错误
	int bingo=0;//是否查找成功标志，1表示成功
	int i,j;
	cout<<"Please input the number(0 for the blank):\n";
	for (i=0;i<9;i++)
	{
		flag=0;
		cin>>num[i];
		for(j=0;j<i;j++)
			if(num[i]==num[j])
				flag=1;
		if (num[i]<0||num[i]>8||flag==1)
		{
			i--;
			cout<<"Illegle number!\tReinput!\n";
		}
	}
	cout<<"Do you want to modify the target(Y/N)?";
	char input;
	cin>>input;
	if (input=='y'||input=='Y')
	{
		cout<<"\nPlease input the new target:\n";
		for (i=0;i<9;i++)
		{
			flag=0;
			cin>>target[i];
			for(j=0;j<i;j++)
				if(target[i]==target[j])
					flag=1;
			if (target[i]<0||target[i]>8||flag==1)
			{
				i--;
				cout<<"Illegle number!\tReinput!\n";
			}
		}
	}

	CEight S(num),Target(target);
	S.parent=S.leaf_next=S.leaf_pre=NULL;
	S.cul_para();
	memery_used++;
	cout<<"Now the initial numbers are:\n";
	S.show();
	cout<<"And the Target is:\n";
	Target.show();
	
	if(!icansolve(num,target))
	{
		cout<<"No one can solve it!\n";
		cin>>i;
		return 1;
	}

	Start=clock( );

	CEight *OK_leaf=&S,*leaf_start=&S,*new_8num,*p;
	while(OK_leaf!=NULL&&bingo!=1)
	{
		OK_leaf=find_OK_leaf(leaf_start);
		if(*OK_leaf==Target)
		{
			bingo=1;
			break;
		}
		
		p=OK_leaf->leaf_pre;
		for (int i=0;i<4;i++)
		{
            OK_leaf->get_numbers_to(num);
            bool bRec = false;
           	switch(i) {
               case 0: bRec = move_up(num); break;
               case 1: bRec = move_down(num); break;
               case 2: bRec = move_left(num); break;
               case 3: bRec = move_right(num); break;
            }
            if(bRec&&!existed(num,OK_leaf))
		    {
    			new_8num=new CEight;			
    			new_8num->set_num(num);
    			new_8num->parent=OK_leaf;
    			new_8num->cul_para();
    			new_8num->leaf_pre=p;
    			if(p==NULL)
    				leaf_start=new_8num;
    			else
    				p->leaf_next=new_8num;
    			p=new_8num;
    			memery_used++;                                                  
            }		
        }
		
		
		
//		OK_leaf->get_numbers_to(num);
//		if(move_up(num)&&!existed(num,OK_leaf))
//		{
//			new_8num=new CEight;			
//			new_8num->set_num(num);
//			new_8num->parent=OK_leaf;
//			new_8num->cul_para();
//			new_8num->leaf_pre=p;
//			if(p==NULL)
//				leaf_start=new_8num;
//			else
//				p->leaf_next=new_8num;
//			p=new_8num;
//			memery_used++;
//		}
//		OK_leaf->get_numbers_to(num);
//		if(move_down(num)&&!existed(num,OK_leaf))
//		{
//			new_8num=new CEight;			
//			new_8num->set_num(num);
//			new_8num->parent=OK_leaf;
//			new_8num->cul_para();
//			new_8num->leaf_pre=p;
//			if(p==NULL)
//				leaf_start=new_8num;
//			else
//				p->leaf_next=new_8num;
//			p=new_8num;
//			memery_used++;
//		}
//		OK_leaf->get_numbers_to(num);
//		if(move_left(num)&&!existed(num,OK_leaf))
//		{
//			new_8num=new CEight;			
//			new_8num->set_num(num);
//			new_8num->parent=OK_leaf;
//			new_8num->cul_para();
//			new_8num->leaf_pre=p;
//			if(p==NULL)
//				leaf_start=new_8num;
//			else
//				p->leaf_next=new_8num;
//			p=new_8num;
//			memery_used++;
//		}
//		OK_leaf->get_numbers_to(num);
//		if(move_right(num)&&!existed(num,OK_leaf))
//		{
//			new_8num=new CEight;			
//			new_8num->set_num(num);
//			new_8num->parent=OK_leaf;
//			new_8num->cul_para();
//			new_8num->leaf_pre=p;
//			if(p==NULL)
//				leaf_start=new_8num;
//			else
//				p->leaf_next=new_8num;
//			p=new_8num;
//			memery_used++;
//		}


		p->leaf_next=OK_leaf->leaf_next;
		if(OK_leaf->leaf_next!=NULL)
			OK_leaf->leaf_next->leaf_pre=p;
		OK_leaf->leaf_next=OK_leaf->leaf_pre=NULL;
	}

	Finish=clock( ); 

	if(bingo==1)
	{
		time = (double)(Finish-Start)*1000/CLOCKS_PER_SEC;
		CEight *p;
		for (p=OK_leaf->parent;p!=NULL;p=p->parent)
		{
			cout<<"  ^\n";
			p->show();
			step++;
		}

		cout<<"Time cost:"<<time <<"ms\n";
		cout<<"Memery cost:"<<memery_used<<"blocks\n";
		cout<<"Totaly covered steps:"<<step<<"\n";
	}
	else
		cout<<"Fail to find!";

//	cin>>i;
    system("pause"); 
	return 0;
}

