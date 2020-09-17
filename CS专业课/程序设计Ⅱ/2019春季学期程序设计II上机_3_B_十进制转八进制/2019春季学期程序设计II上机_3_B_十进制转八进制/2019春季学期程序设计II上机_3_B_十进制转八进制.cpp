// 2019春季学期程序设计II上机_3_B_十进制转八进制.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;
const int MAX = 50;
int main()
{
	int dec;
	cin >> dec;
	int oct[MAX];
	int len = 0;
	while (dec) {
		oct[len++] = dec % 8;
		dec /= 8;
	}
	if (len == 0) {
		cout << 0;
	}
	else {
		for (int i = len - 1; i >= 0; i--) {
			printf("%d", oct[i]);
		}
	}
	cout << endl;
}
