/***************************************
���������� ��������Ǳ���ȵĵڼ���
****************************************/

#include <stdio.h>

struct Time {
	int year;
	int month;
	int day;
};

int main()
{
	struct Time t1;
	while (1) {
		scanf("%d%d%d", &t1.year, &t1.month, &t1.day);

		if (t1.month < 1 || t1.month > 12) {
			printf("error:month is between 1 to 12! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
		}

		int daysInFeb = ((t1.year % 400 == 0) ||
			(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;

		switch (t1.month)
		{
		case 1:while (t1.day < 1 || t1.day > 31) {
			printf("error:Jan has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 2:while (t1.day < 1 || t1.day > daysInFeb) {
			printf("error:%d Feb has %d days! Please input again:\n", t1.year, daysInFeb);
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 3:while (t1.day < 1 || t1.day > 31) {
			printf("error:Mar has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
		}; break;
		case 4:while (t1.day < 1 || t1.day > 30) {
			printf("error:Apr has 30 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 5:while (t1.day < 1 || t1.day > 31) {
			printf("error:May has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 6:while (t1.day < 1 || t1.day > 30) {
			printf("error:Jun has 30 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 7:while (t1.day < 1 || t1.day > 31) {
			printf("error:Jul has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 8:while (t1.day < 1 || t1.day > 31) {
			printf("error:Aug has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 9:while (t1.day < 1 || t1.day > 30) {
			printf("error:Sept has 30 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 10:while (t1.day < 1 || t1.day > 31) {
			printf("error:Oct has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 11:while (t1.day < 1 || t1.day > 30) {
			printf("error:Nov has 30 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;
		case 12:while (t1.day < 1 || t1.day > 31) {
			printf("error:Dec has 31 days! Please input again:\n");
			scanf("%d%d%d", &t1.year, &t1.month, &t1.day);
			daysInFeb = ((t1.year % 400 == 0) ||
				(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;
		}; break;

		default:
			break;
		}

		daysInFeb = ((t1.year % 400 == 0) ||
			(t1.year % 4 == 0 && t1.year % 100 != 0)) == 1 ? 29 : 28;

		int totalDays;
		switch (t1.month)
		{
		case 1:totalDays = 0; break;
		case 2:totalDays = 31; break;
		case 3:totalDays = 31 + daysInFeb; break;
		case 4:totalDays = 62 + daysInFeb; break;
		case 5:totalDays = 92 + daysInFeb; break;
		case 6:totalDays = 123 + daysInFeb; break;
		case 7:totalDays = 153 + daysInFeb; break;
		case 8:totalDays = 184 + daysInFeb; break;
		case 9:totalDays = 215 + daysInFeb; break;
		case 10:totalDays = 245 + daysInFeb; break;
		case 11:totalDays = 276 + daysInFeb; break;
		case 12:totalDays = 306 + daysInFeb; break;

		default:
			break;
		}

		totalDays += t1.day;
		printf("�ǵ�%d��\n", totalDays);
	}

	return 0;
}
/***************************************
��Ȼ˵���������򵥵� ͳ����һ������һ��ĵڼ��졣
���������ȷ������£����Ǵ��������кܶ��֣�
�����������뵽�Ĵ��������·ݳ���12��
���о���ÿ���µ����������ȶ��������������2�·��鷳һ�㡣
���ǳ����Ժ��������룬�����֮ǰ�����·���ȫ��һ����
Ȼ�����д������˵ʵ����Щ�Ѹ㡣
��������2012 2 30����ʾerror:2012 Feb has 29 days!Please input again :
Ȼ������2012 3 34�� ����error : 2012 Feb has 29 days!Please input again :
��Ϊ������whileѭ����
****************************************/