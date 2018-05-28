#include<stdio.h>
#include<string.h>
#include<math.h>
#include<conio.h>
#define SIZE 4
typedef char board[SIZE][SIZE];
board target = { 1, 2, 3, 4,
12, 13, 14, 5,
11, 0, 15, 6,
10, 9, 8, 7 };
board start;
long add[4][2] = { -1, 0, 0, 1, 1, 0, 0, -1 };
long targetplace[SIZE*SIZE][2]; // 这个估价函数是用来剪枝的
long CAL_H(board & node) {
	long i, j;
	long re = 0;
	for (i = 0; i < SIZE; i++) for (j = 0; j < SIZE; j++) if (node[i][j]) {
		re += abs(i - targetplace[node[i][j]][0])
			+ abs(j - targetplace[node[i][j]][1]);
	}
	return re;
}
bool can_solve() { // 搜索前判断是否可解
	long i, j, k1, k2;
	for (i = 0; i < SIZE; i++) for (j = 0; j < SIZE; j++) {
		if (start[i][j] == 0) {
			start[i][j] = SIZE*SIZE;
			k1 = (SIZE - 1 - i) + (SIZE - 1 - j);
		}
		if (target[i][j] == 0){
			target[i][j] = SIZE*SIZE;
			k2 = (SIZE - 1 - i) + (SIZE - 1 - j);
		}
	}
	for (i = 0; i<SIZE*SIZE; i++) for (j = i + 1; j < SIZE*SIZE; j++) {
		if (start[i / SIZE][i%SIZE] > start[j / SIZE][j%SIZE]) k1++;
		if (target[i / SIZE][i%SIZE] > target[j / SIZE][j%SIZE]) k2++;
	}
	for (i = 0; i < SIZE; i++) for (j = 0; j < SIZE; j++) {
		if (start[i][j] == SIZE*SIZE) start[i][j] = 0;
		if (target[i][j] == SIZE*SIZE) target[i][j] = 0;
	}
	return (k1 % 2) == (k2 % 2);
}
void out_board(board state, long step) {
	long i, j;
	printf("STEP %ld:\n", step);
	for (i = 0; i < SIZE; i++){
		for (j = 0; j < SIZE; j++){
			printf("%ld ", state[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void output(long dep, char path[]) { // 输出答案
	long i, j, x1, y1, x0, y0;
	board state;
	memcpy(state, start, sizeof(state));
	out_board(state, 0);
	for (i = 0; i < SIZE; i++)for (j = 0; j < SIZE; j++)if (state[i][j] == 0)x0 = i, y0 = j;
	for (i = 0; i < dep; i++) {
		x1 = x0 + add[path[i]][0];
		y1 = y0 + add[path[i]][1];
		state[x0][y0] = state[x1][y1];
		state[x1][y1] = 0;
		x0 = x1, y0 = y1;
		out_board(state, i + 1);
	}
	printf("The minimum number of steps is %ld.\n", dep);
}
long ans;
char path[100000];
bool ida(board & node, long x0, long y0, long dep, long d, long h) {
	long i, j, k, x1, y1, h1;
	if (memcmp(node, target, sizeof(target)) == 0) {
		output(dep, path);
		return 1;
	}
	if (dep == ans) return 0;
	board node1;
	for (i = 0; i < 4; i++) {
		if (((i % 2) == (d % 2)) && i != d) continue;
		x1 = x0 + add[i][0];
		y1 = y0 + add[i][1];
		if (x1 < 0 || y1 < 0 || x1 == SIZE || y1 == SIZE) continue;
		memcpy(node1, node, sizeof(node1));
		node1[x1][y1] = 0;
		node1[x0][y0] = node[x1][y1];
		if (i == 3 && y1<targetplace[node[x1][y1]][1]) h1 = h - 1;
		else if (i == 1 && y1>targetplace[node[x1][y1]][1]) h1 = h - 1;
		else if (i == 0 && x1 < targetplace[node[x1][y1]][0]) h1 = h - 1;
		else if (i == 2 && x1 > targetplace[node[x1][y1]][0]) h1 = h - 1;
		else h1 = h + 1;
		if (h1 + dep + 1 > ans) continue; // 根据估价值(h1+dep)
		// 和假定的解的步数(ans)来剪枝
		path[dep] = i;
		if (ida(node1, x1, y1, dep + 1, i, h1)) return 1;
	}
	return 0;
}
int main() {
	long i, j, k, x0, y0;
	long cs;
	//scanf("%ld", &cs);
	cs = 1;
	printf("input=\n");
	while (cs--) {
		for (i = 0; i < SIZE; i++)for (j = 0; j < SIZE; j++) {
			scanf("%ld", &k);
			start[i][j] = k;
			if (k == 0) { x0 = i; y0 = j; }
		}
		for (k = 1, i = 0; i < SIZE; i++) for (j = 0; j < SIZE; j++) {
			targetplace[target[i][j]][0] = i;
			targetplace[target[i][j]][1] = j;
		}
		if (!can_solve()) { printf("This puzzle is not solvable.\n"); continue; }
		i = -1;
		j = CAL_H(start);
		for (ans = j;; ans += 1) {
			if (ida(start, x0, y0, 0, i, j)) {
				break;
			}
		}
		getch();
	}
	return 0;
}