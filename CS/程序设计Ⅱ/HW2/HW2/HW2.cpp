// HW2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

#define MAX_LEN 210

void add(int an1[MAX_LEN], int an2[MAX_LEN], int dot1, int moreDot, int an1Len, int an2Len) {
	int minIndex = 0, maxIndex = MAX_LEN-1, i;
	//小数部分相加
	for (i = 0; i < an2Len; i++) {
		an1[moreDot + i] += an2[i];
		if (an1[moreDot + i] >= 10) {
			an1[moreDot + i] -= 10;
			an1[moreDot + i + 1]++;
		}
	}
	for (i = an2Len; i < an1Len; i++) {

		if (an1[moreDot + i] >= 10) {
			an1[moreDot + i] -= 10;
			an1[moreDot + i + 1]++;
			continue;
		}
		else {
			break;
		}
	}
	while (an1[maxIndex] == 0 && maxIndex > dot1) {
		maxIndex--;
	}
	while (an1[minIndex] == 0 && minIndex <= dot1) {
		minIndex++;
	}
	if (maxIndex == dot1 && minIndex == dot1+1) {
		cout << 0 << endl;
		return;
	}
	for (i = maxIndex; i >= minIndex; i--) {
		if (i == (dot1 - 1)) {
			cout << ".";
		}
		cout << an1[i];
	}
}

int main()
{
	int i, dot1 = 0, dot2 = 0, maxLen, maxIndex; //dot1表示小数点在从最左边开始第dot1位前面
	string str1, str2;
	int an1[MAX_LEN];
	int an2[MAX_LEN];
	cin >> str1 >> str2;
	int an1Len = str1.length();
	int an2Len = str2.length();
	if (an1Len > an2Len) {
		maxLen = an1Len;
	}
	else {
		maxLen = an2Len;
	}
	maxIndex = maxLen + 2;
	memset(an1, 0, sizeof(an1));
	memset(an2, 0, sizeof(an2));
	for (i = an1Len - 1; i >= 0; i--) {
		if (str1[i] == '.') {
			dot1 = an1Len - 1 - i;
			continue;
		}
		if (dot1 == 0) {
			an1[an1Len - 1 - i] = str1[i] - '0';
		}
		else {
			an1[an1Len - 2 - i] = str1[i] - '0';
		}
	}
	for (i = an2Len - 1; i >= 0; i--) {
		if (str2[i] == '.') {
			dot2 = an2Len - 1 - i;
			continue;
		}
		if (dot2 == 0) {
			an2[an2Len - 1 - i] = str2[i] - '0';
		}
		else {
			an2[an2Len - 2 - i] = str2[i] - '0';
		}
	}

	if (dot1 >= dot2) {
		add(an1, an2, dot1, dot1 - dot2, an1Len, an2Len);
	}
	else {
		add(an2, an1, dot2, dot2 - dot1, an2Len, an1Len);
	}
	cout << endl;
	
}