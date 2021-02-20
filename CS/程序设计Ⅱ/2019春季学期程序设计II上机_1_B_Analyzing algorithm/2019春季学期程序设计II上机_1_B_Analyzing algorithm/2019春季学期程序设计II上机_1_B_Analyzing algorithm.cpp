// 2019春季学期程序设计II上机_1_B_Analyzing algorithm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

int getLen(int n) {
	int len = 1;
	while (true) {
		if (n == 1) break;
		else if (n % 2 == 0) n /= 2;
		else n = n * 3 + 1;
		len++;
	}
	return len;
}
int main()
{
	int i, j;
	while (cin >> i >> j) {
		int maxLen = 0;
		int tempi, tempj;
		tempi = i > j ? j : i;
		tempj = i > j ? i : j;
		for (int k = tempi; k <= tempj; k++) {
			int temp = getLen(k);
			maxLen = maxLen > temp ? maxLen : temp;
		}
		cout << i << ' ' << j << ' ' << maxLen << endl;
	}
}
