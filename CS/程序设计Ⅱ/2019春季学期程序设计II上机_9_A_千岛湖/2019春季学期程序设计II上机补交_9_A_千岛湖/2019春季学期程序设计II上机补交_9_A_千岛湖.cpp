// 2019春季学期程序设计II上机补交_9_A_千岛湖.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

const int MAX_N = 1000 + 5;
int n;
char islandMap[MAX_N][MAX_N];
int markMap[MAX_N][MAX_N];
int counter;
const int position[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };


void makeMark(int row, int col) {
	int nextRow, nextCol;
	for (int i = 0; i < 4; i++) {
		nextRow = row + position[i][0]; nextCol = col + position[i][1];
		if (nextRow >= 0 && nextRow < n && nextCol >= 0 && nextCol < n){
			if (markMap[nextRow][nextCol] == -1) {
				markMap[nextRow][nextCol] = counter;
				makeMark(nextRow, nextCol);
			}
			else
				continue;
		}
	}
}

int main()
{
	n = 0;
	while (cin >> islandMap[n]) {
		n++;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (islandMap[i][j] == '.') markMap[i][j] = 0;
			else markMap[i][j] = -1;
		}
	}
	counter = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (markMap[i][j] != -1) continue;
			else {
				markMap[i][j] = ++counter;
				makeMark(i, j);
			}
		}
	}
	cout << counter << endl;
}
