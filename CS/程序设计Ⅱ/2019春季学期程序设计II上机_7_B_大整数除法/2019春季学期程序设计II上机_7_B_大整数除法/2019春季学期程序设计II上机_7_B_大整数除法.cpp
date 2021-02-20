// 2019春季学期程序设计II上机_7_B_大整数除法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MAX = 100 + 5;
int num1[MAX];
int num2[MAX];
int answer[MAX];

bool subtract(int* n1, int* n2, int& len1, int len2) {
	if (len1 < len2)
		return 0;
	else if (len1 == len2) {
		for (int i = len1; i >= 0; i--) {
			if (n1[i] > n2[i]) {
				break;
			}
			else if (n1[i] < n2[i]) {
				return 0;
			}
		}
	}
	for (int i = len1 - 1; i >= 0; i--) {
		n1[i] -= n2[i];
	}
	int curLen1 = 1;
	for (int i = 0; i < len1; i++) {
		if (n1[i] < 0) {
			n1[i] += 10;
			n1[i + 1] -= 1;
		}
		if (n1[i + 1] != 0) {
			curLen1 = i + 2;
		}
	}
	if (curLen1 == 0 && n1[0] == 0) {
		len1 = 0;
	}
	else
		len1 = curLen1;
	return 1;
}

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	int len1 = s1.length();
	int len2 = s2.length();
	memset(num1, 0, sizeof(num1));
	memset(num2, 0, sizeof(num2));
	memset(answer, 0, sizeof(answer));
	for (int i = 0; i < len1; i++) {
		num1[i] = s1[len1 - i - 1] - '0';
	}
	for (int i = 0; i < len2; i++) {
		num2[i] = s2[len2 - i - 1] - '0';
	}
	if (len1 == len2) {
		for (int i = len1; i >= 0; i--) {
			if (num1[i] < num2[i]) {
				cout << 0 << endl << s1 << endl;
				return 0;
			}
		}
	}
	else if (len1 < len2) {
		cout << 0 << endl << s1 << endl;
		return 0;
	}
	int ansDigit = len1 - len2;
	int curDigit = ansDigit;
	int tempNum[MAX * 2];
	memset(tempNum, 0, sizeof(tempNum));
	for (int i = 0; i < len2; i++) {
		tempNum[i + curDigit] = num2[i];
	}
	for (; curDigit >= 0; curDigit--) {
		while (subtract(num1, tempNum + ansDigit - curDigit, len1, len2 + curDigit)) {
			answer[curDigit]++;
		}
	}
	int ansLen = 0;
	for (int i = MAX - 1; i >= 0; i--) {
		if (answer[i] != 0) {
			ansLen = i + 1;
			break;
		}
	}
	for (int i = ansLen - 1; i >= 0; i--) {
		printf("%d", answer[i]);
	}
	printf("\n");
	if (len1 != 0) {
		for (int i = len1 - 1; i >= 0; i--) {
			printf("%d", num1[i]);
		}
		printf("\n");
	}
	else {
		cout << 0 << endl;
	}
}