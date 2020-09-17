// HW3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cmath>

const int WIDTH = 3;
const int TIMES = 4;
using namespace std;

//int affected[WIDTH*WIDTH][5] = { {1, 2, 4, 5},{1,2,3},{2,3,5,6},{1,4,7},{2,4,5,6,8},{3,6,9},{4,5,7,8},{7,8,9},{5,6,8,9} };
int canAffected[WIDTH*WIDTH][5] = { {1,2,4},{1,2,3,5},{2,3,6},{1,4,5,7},{1,3,5,7,9},{3,5,6,9},{4,7,8},{5,7,8,9},{6,8,9} };
int status[WIDTH][WIDTH];
int answer[WIDTH*WIDTH];

bool isTwelve(int index) {
	int turnedTimes = 0;
	int temp;
	for (int i = 0; i < 5; i++) {
		if ((temp = canAffected[index][i] - 1) != -1) {
			turnedTimes += answer[temp];
		}
		else {
			break;
		}
	}
	if ((turnedTimes + status[index/WIDTH][index%WIDTH]) % TIMES == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool solve() {
	answer[3] = (4*TIMES - (answer[0] + answer[1] + status[0][0])) % TIMES;
	answer[4] = (4*TIMES - (answer[0] + answer[1] + answer[2] + status[0][1])) % TIMES;
	answer[5] = (4*TIMES - (answer[1] + answer[2] + status[0][2])) % TIMES;
	answer[6] = (4*TIMES - (answer[0] + answer[3] + answer[4] + status[1][0])) % TIMES;
	answer[7] = (4*TIMES - (answer[3] + answer[6] + status[2][0])) % TIMES;
	answer[8] = (4*TIMES - (answer[5] + answer[7] + status[2][2])) % TIMES;

	for (int index = 0; index < WIDTH*WIDTH; index++) {
		if (!isTwelve(index)) {
			return false;
		}
	}
	return true;
}

bool enumerate(int firstLine) {
	memset(answer, 0, sizeof(answer));
	for (int i = 0; i < WIDTH; i++) {
		answer[i] = (firstLine >> (2*i)) & 3;
	}
	bool isFirstPrint = true;
	if (solve()) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < answer[i]; j++) {
				if (isFirstPrint) {
					cout << i + 1;
					isFirstPrint = false;
				}
				else {
					cout << " " << i + 1;
				}
			}
		}
		return true;
	}
	return false;
}

int main() {
	int maxI = (int)pow((double)4, 3);
	for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < WIDTH; j++) {
			cin >> status[i][j];
		}
	}
	for (int i = 0; i < maxI; i++) {
		if (enumerate(i)) {
			cout << endl;
			break;
		}
	}
}
