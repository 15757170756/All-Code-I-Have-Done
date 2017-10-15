/***************************************
建立学生情况登记表，包括学号、姓名、5门课成绩与总分。
在主函数中调用以下函数实现指定的功能：
1、输入n个学生的数据（不包过总分）
2、计算每个学生的总分
3、按每个学生总分由高到低排序
4、有键盘输入一个学号，输出给定学号的学生的所有信息
****************************************/

#include <stdio.h>
#include <string.h>

#define N 5

struct stuInfo
{
	char stuNum[20];
	char stuName[20];
	int course[5];
	int totalScore;
};

int sumScorePerStu(struct stuInfo oneStu);
void getStuInfo(char stuNum[], struct stuInfo students[N]);
void sortByTotalScore(struct stuInfo students[N]);

int main()
{
	struct stuInfo stus[N];
	printf("请输入信息：\n");
	for (int i = 0; i < N; ++i) {
		scanf("%s%s%d%d%d%d%d", stus[i].stuNum, stus[i].stuName,
			&stus[i].course[0], &stus[i].course[1], &stus[i].course[2],
			&stus[i].course[3], &stus[i].course[4]);
	}

	getchar();

	for (int i = 0; i < N; ++i) {
		stus[i].totalScore = sumScorePerStu(stus[i]);
		printf("总分分别为：%d\n", stus[i].totalScore);
	}

	sortByTotalScore(stus);

	for (int i = 0; i < N; ++i) {
		printf("按每个学生总分由高到低排序：\n");
		printf("学号：%s 姓名：%s 5门功课成绩：%d %d %d %d %d 总分：%d\n",
			stus[i].stuNum, stus[i].stuName, stus[i].course[0],
			stus[i].course[1], stus[i].course[2], stus[i].course[3],
			stus[i].course[4], stus[i].totalScore);
	}

	printf("请输入一个学生的学号：\n");
	char stuNum[20];
	gets(stuNum);
	getStuInfo(stuNum, stus);

	return 0;
}

int sumScorePerStu(struct stuInfo oneStu)
{
	int sumScore = 0;
	for (int i = 0; i < 5; ++i)
		sumScore += oneStu.course[i];
	return sumScore;
}

void sortByTotalScore(struct stuInfo students[N])
{
	int i, j;
	for (i = 1; i < N; ++i) {
		struct stuInfo temp = students[i];
		int key = students[i].totalScore;
		for (j = i - 1; j >= 0 &&
			students[j].totalScore < key; --j) {
			students[j + 1] = students[j];
		}
		students[j + 1] = temp;
	}
}

void getStuInfo(char stuNum[], struct stuInfo students[N])
{
	int i;
	for (i = 0; i < N; ++i) {
		if (strcmp(students[i].stuNum, stuNum) == 0) {
			printf("学号为%s的学生的信息：\n", students[i].stuNum);
			printf("姓名：%s, 5门功课成绩：%d, %d, %d, %d, %d, 总分：%d\n",
				students[i].stuName, students[i].course[0], students[i].course[1],
				students[i].course[2], students[i].course[3],
				students[i].course[4], students[i].totalScore);
			return;
		}
	}
	if (i == N) {
		printf("没有相应学号的学生。\n");
		return;
	}

}