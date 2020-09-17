// HW4_B.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include<iostream>
#include<cstring>
using namespace std;
const int MAX_SIZE = 50;
short walls[MAX_SIZE+2][MAX_SIZE+2];
int marks[MAX_SIZE+2][MAX_SIZE+2];
int m, n;

int doMarks(int row, int col, int markIndex) {
	int count = 0;
	if (marks[row][col] == 0) {
		marks[row][col] = markIndex;
		// west
		if ((walls[row][col] & 1) != 1 && col > 0) {
			count += doMarks(row, col - 1, markIndex);
		}
		// north
		if ((walls[row][col] & 2) != 2 && row > 0) {
			count += doMarks(row - 1, col, markIndex);
		}
		// east
		if ((walls[row][col] & 4) != 4 && col < n - 1) {
			count += doMarks(row, col + 1, markIndex);
		}
		// south
		if ((walls[row][col] & 8) != 8 && row < m - 1) {
			count += doMarks(row + 1, col, markIndex);
		}
		count++;
	}
	else {
		return count;
	}
	return count;
}

int main() {
	int i, j, markIndex = 0, maxModule = 0, temp;
	memset(walls, 0, sizeof(walls));
	memset(marks, 0, sizeof(marks));
	cin >> m >> n;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			cin >> walls[i][j];
		}
	}

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (marks[i][j] == 0) {
				if ((temp = doMarks(i, j, ++markIndex)) > maxModule) {
					maxModule = temp;
				}
			}
		}
	}
	cout << markIndex << endl << maxModule << endl;
}