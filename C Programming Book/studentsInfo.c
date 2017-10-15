#include <stdio.h>
#include <string.h>

void getScoreinfo(int score[], int n, double info[]);
void getScoreinfo2(int score[], int n, double info[]);

int main()
{
	int score[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	double info[3] = { 0.0 };
	getScoreinfo(score, 10, info);
	printf("��ͷ֣�%.2f\n��߷֣�%.2f\nƽ���֣�%.2f\n", info[0], info[1], info[2]);

	return 0;
}

void getScoreinfo(int score[], int n, double info[])
{
	int minScore = score[0];
	int maxScore = score[0];
	int sum = 0;
	double avergeScore = 0.0;
	for (int i = 1; i < n; ++i) {
		sum += score[i];
		if (minScore > score[i])
			minScore = score[i];
		if (maxScore < score[i])
			maxScore = score[i];

	}

	avergeScore = (sum + score[0]) / 10.0;
	info[0] = minScore;
	info[1] = maxScore;
	info[2] = avergeScore;
}

/***************************************
����ıȽϳ����ֵ����Сֵ�ķ�����һ��Ҫ�Ƚ�2n-2�Σ�
�����µķ���ֻҪ�Ƚ�3n/2��
������Ԫ�سɶԵؽ��д���һ������Ԫ�ػ���Ƚϣ�
Ȼ��ѽ�С�ĺ͵�ǰ��Сֵ�Ƚϣ��ϴ�ĺ͵�ǰ���ֵ�Ƚ�
****************************************/
void getScoreinfo2(int score[], int n, double info[])
{
	int tempMinScore, tempMaxScore, currentMinScore, currentMaxScore;
	if (n % 2 == 0) {
		if (score[0] < score[1]) {
			currentMinScore = score[0];
			currentMaxScore = score[1];
		}
		else {
			currentMinScore = score[1];
			currentMaxScore = score[0];
		}

		for (int i = 2; i < n - 1; i += 2) {
			if (score[i] < score[i + 1]) {
				tempMinScore = score[i];
				tempMaxScore = score[i + 1];
			}
			else {
				tempMinScore = score[i + 1];
				tempMaxScore = score[i];
			}

			if (currentMinScore > tempMinScore)
				currentMinScore = tempMinScore;
			if (currentMaxScore < tempMaxScore)
				currentMaxScore = tempMaxScore;
		}
	}
	else {
		currentMaxScore = currentMinScore = score[0];
		for (int i = 1; i < n - 1; i += 2) {
			if (score[i] < score[i + 1]) {
				tempMinScore = score[i];
				tempMaxScore = score[i + 1];
			}
			else {
				tempMinScore = score[i + 1];
				tempMaxScore = score[i];
			}

			if (currentMinScore > tempMinScore)
				currentMinScore = tempMinScore;
			if (currentMaxScore < tempMaxScore)
				currentMaxScore = tempMaxScore;
		}
	}

	info[0] = currentMinScore;
	info[1] = currentMaxScore;
}