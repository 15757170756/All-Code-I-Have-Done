#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define CHAR_STAR '*'
#define CHAR_SPACE ' '

#define EPS 1e-1

#define OUT_A 0.3
#define IN_A 0.6
#define IN_B 1.8
#define OUT_B 1.0

#define HEIGH 1.5
#define WIDTH 4.0

#define OFFSET_HEIGH 0.5
#define OFFSET_WIDTH 1.0

#define STRING_ONE "Dear LISIs"
#define STRING_TWO "I love you"

double pown(double x, int n)
{
	int i;
	double ret = 1.0;
	for (i = 0; i < n; i++)
		ret *= x;
	return ret;
}

double f(double ratioA, double ratioB, double x, double y)
{
	return pown(ratioA * pown(x, 2) + ratioB * pown(y, 2) - 1, 3) - ratioB * pown(x, 2) * pown(y, 3);
}

int main()
{
	int i, j;
	double x, y;

	int cnt_x = 2 * WIDTH * 10 - OFFSET_WIDTH * 10 + 1;
	int cnt_y = 2 * HEIGH * 10 - OFFSET_HEIGH * 10 + 1;

	int len = strlen(STRING_ONE);

	int pos_x = (cnt_x + 1 - 2 * len) / 2;
	int posA_y = cnt_y / 3;
	int posB_y = cnt_y * 2 / 3;

	char **buf;

	buf = (char **)malloc(cnt_y * sizeof(char *));
	for (i = 0; i < cnt_y; i++)
		buf[i] = (char *)malloc(cnt_x * sizeof(char) + 1);

	for (i = 0; i < cnt_y; i++)
		for (j = 0; j < cnt_x + 1; j++)
			buf[i][j] = 0;

	for (i = 0, y = HEIGH; y >= -(HEIGH - OFFSET_HEIGH); ++i, y -= EPS) {
		for (j = 0, x = -(WIDTH - OFFSET_WIDTH); x <= WIDTH; ++j, x += EPS)
			if (f(IN_A, IN_B, x, y) >= 0 && f(OUT_A, OUT_B, x, y) < 0)
				buf[i][j] = CHAR_STAR;
		//  putchar(CHAR_STAR); 
			else
				buf[i][j] = CHAR_SPACE;
		//  putchar(CHAR_SPACE);
		//puts("");
	}

	for (i = 0; i < len; i++)
		buf[posA_y][pos_x + i] = STRING_ONE[i],
		buf[posB_y][pos_x + i] = STRING_TWO[i];

	for (i = 0; i < cnt_y; i++)
		puts(buf[i]);

	for (i = 0; i < cnt_y; i++)
		free(buf[i]);

	free(buf);

	getchar();
}