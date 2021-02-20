// 2019春季学期程序设计II上机_6_A_花生采摘.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

const int MAX = 20 + 5;
int field[MAX*MAX];
int order[MAX*MAX];
int M, N, K, AREA;

inline int distance(int x, int y) {
	return abs(x / N - y / N) + abs(x % N - y % N);
}

inline int getX(int x) {
	return x / N;
}

inline int getY(int x) {
	return x % N;
}


int main()
{
	cin >> M >> N >> K;
	AREA = M * N;
	memset(field, 0, sizeof(field));
	memset(order, 0, sizeof(order));
	for (int i = 0; i < AREA; i++) {
		order[i] = i;
		cin >> field[i];
	}
	for (int i = 0; i < AREA; i++) {
		for (int j = AREA - 1; j > i; j--) {
			if (field[order[j - 1]] < field[order[j]]) {
				int temp = order[j];
				order[j] = order[j - 1];
				order[j - 1] = temp;
			}
		}
	}
	int toPick = 0;
	int nuts = 0;
	//第一颗
	if (K >= (1 + getX(order[0]) + 1 + getX(order[0]) + 1)) {
		K -= (1 + getX(order[0]) + 1);
		nuts += field[order[toPick]];
		toPick++;
	}
	else {
		cout << 0 << endl;
		return 0;
	}
	while (true) {
		if (toPick >= AREA || field[order[toPick]] == 0) {
			cout << nuts << endl;
			break;
		}
		int temp1 = distance(order[toPick - 1], order[toPick]) + 1;
		//int temp2 = getX(order[toPick - 1]) + 1 + 1 + getX(order[toPick]) + 1;
		int temp2 = temp1 + 1;
		int temp = temp1 < temp2 ? temp1 : temp2;
		if (K >= (temp + getX(order[toPick]) + 1)) {
			K -= temp;
			nuts += field[order[toPick]];
			toPick++;
		}
		else {
			cout << nuts << endl;
			break;
		}
	}
}
