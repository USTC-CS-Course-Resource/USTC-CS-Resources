// 2019春季学期程序设计II上机_8_A_数字方格.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

const int FACTOR1 = 2;
const int FACTOR2 = 3;
const int FACTOR3 = 5;

int main()
{
	int n;
	cin >> n;
	int tryMax = 3 * n - (3 * n) % FACTOR3;
	for (; tryMax >= 0; tryMax -= FACTOR3) {
		for (int i = n; i >= 0; i--) {
			if ((tryMax - i) % FACTOR2 == 0) {
				for (int k = n; k >= 0; k--) {
					int j = tryMax - i - k;
					if (j >= 0 && j <= n && (tryMax - k) % FACTOR1 == 0) {
						cout << tryMax << endl;
						return 0;
					}
				}
			}
		}
	}
}