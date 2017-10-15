/***************************************
����ѧ������ǼǱ�����ѧ�š�������5�ſγɼ����ܷ֡�
���������е������º���ʵ��ָ���Ĺ��ܣ�
1������n��ѧ�������ݣ��������ܷ֣�
2������ÿ��ѧ�����ܷ�
3����ÿ��ѧ���ܷ��ɸߵ�������
4���м�������һ��ѧ�ţ��������ѧ�ŵ�ѧ����������Ϣ
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
	printf("��������Ϣ��\n");
	for (int i = 0; i < N; ++i) {
		scanf("%s%s%d%d%d%d%d", stus[i].stuNum, stus[i].stuName,
			&stus[i].course[0], &stus[i].course[1], &stus[i].course[2],
			&stus[i].course[3], &stus[i].course[4]);
	}

	getchar();

	for (int i = 0; i < N; ++i) {
		stus[i].totalScore = sumScorePerStu(stus[i]);
		printf("�ֱַܷ�Ϊ��%d\n", stus[i].totalScore);
	}

	sortByTotalScore(stus);

	for (int i = 0; i < N; ++i) {
		printf("��ÿ��ѧ���ܷ��ɸߵ�������\n");
		printf("ѧ�ţ�%s ������%s 5�Ź��γɼ���%d %d %d %d %d �ܷ֣�%d\n",
			stus[i].stuNum, stus[i].stuName, stus[i].course[0],
			stus[i].course[1], stus[i].course[2], stus[i].course[3],
			stus[i].course[4], stus[i].totalScore);
	}

	printf("������һ��ѧ����ѧ�ţ�\n");
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
			printf("ѧ��Ϊ%s��ѧ������Ϣ��\n", students[i].stuNum);
			printf("������%s, 5�Ź��γɼ���%d, %d, %d, %d, %d, �ܷ֣�%d\n",
				students[i].stuName, students[i].course[0], students[i].course[1],
				students[i].course[2], students[i].course[3],
				students[i].course[4], students[i].totalScore);
			return;
		}
	}
	if (i == N) {
		printf("û����Ӧѧ�ŵ�ѧ����\n");
		return;
	}

}