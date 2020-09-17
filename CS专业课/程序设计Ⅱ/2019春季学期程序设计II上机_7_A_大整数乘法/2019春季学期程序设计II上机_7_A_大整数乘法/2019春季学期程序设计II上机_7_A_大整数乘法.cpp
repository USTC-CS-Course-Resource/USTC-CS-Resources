// 2019春季学期程序设计II上机_7_A_大整数乘法.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const int MAX = 200 + 10;
int answer[MAX];
int num1[MAX];
int num2[MAX];
int len1, len2, lenAns, finalLen;

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	len1 = s1.length();
	len2 = s2.length();
	lenAns = len1 + len2;
	finalLen = 0;
	memset(num1, 0, sizeof(num1));
	memset(num2, 0, sizeof(num2));
	memset(answer, 0, sizeof(answer));
	for (int i = 0; i < len1; i++) {
		num1[i] = s1[len1 - i - 1] - '0';
	}
	for (int i = 0; i < len2; i++) {
		num2[i] = s2[len2 - i - 1] - '0';
	}
	for (int i = 0; i < len2; i++) {
		for (int j = 0; j < len1; j++) {
			answer[i + j] += num1[j] * num2[i];
		}
	}
	
	for (int i = 0; i < lenAns; i++) {
		answer[i + 1] += answer[i] / 10;
		answer[i] = answer[i] % 10;
		if (answer[i + 1] != 0)
			finalLen = i + 2;
	}
	for (int i = finalLen - 1; i >= 0; i--) {
		printf("%d", answer[i]);
	}
	cout << endl;
}