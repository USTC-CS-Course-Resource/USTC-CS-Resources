// 2019春季学期程序设计II上机补交_N皇后Ⅱ.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX_N = 15;
int n, counter;
int places[MAX_N];

inline bool canPut(int row, int col) {
	for (int i = 0; i < row; i++) {
		if ((row - i) == abs((places[i] - col)) || col == places[i])
			return false;
	}
	return true;
}

void putQueen(int row) {
	if (row == n) {
		counter++;
		return;
	}
	for (int col = 0; col < n; col++) {
		if (canPut(row, col)) {
			places[row] = col;
			putQueen(row + 1);
		}
	}
	return;
}

int main()
{
	memset(places, 0, sizeof(places));
	while (cin >> n) {
		counter = 0;
		putQueen(0);
		cout << counter << endl;
	}
}