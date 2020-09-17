// 2019春季学期程序设计II上机_2_B_2的n次方问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		unsigned long long int answer;
		answer = 1;
		for (int i = 0; i < n; i++) {
			answer *= 2;
		}
		cout << answer << endl;
	}
}
