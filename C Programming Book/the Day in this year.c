/***************************************
输入年月日 输出改日是本年度的第几日
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
		printf("是第%d天\n", totalDays);
	}

	return 0;
}
/***************************************
虽然说问题是蛮简单的 统计这一天是这一年的第几天。
这个是在正确的情况下，但是错误的情况有很多种，
比如我这里想到的错误：首先月份超出12，
还有就是每个月的天数超出既定的天数，这里就2月份麻烦一点。
但是出错以后重新输入，如果和之前的年月份完全不一样，
然后又有错误，这个说实话有些难搞。
比如输入2012 2 30，提示error:2012 Feb has 29 days!Please input again :
然后输入2012 3 34， 又是error : 2012 Feb has 29 days!Please input again :
因为那里是while循环。
****************************************/