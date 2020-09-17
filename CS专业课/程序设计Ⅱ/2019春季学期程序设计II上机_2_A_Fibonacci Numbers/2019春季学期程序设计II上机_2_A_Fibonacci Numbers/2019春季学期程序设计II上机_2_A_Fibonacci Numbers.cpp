// 2019春季学期程序设计II上机_2_A_Fibonacci Numbers.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	int n;
	while (cin >> n) {
		if (n == 0) {
			cout << "The Fibonacci number for " << 0 << " is " << 0 <<endl;
			continue;
		}
		else if (n == 1) {
			cout << "The Fibonacci number for " << 1 << " is " << 1 << endl;
			continue;
		}
		else if (n == 2) {
			cout << "The Fibonacci number for " << 2 << " is " << 1 << endl;
			continue;
		}
		else {
			int a, b;
			a = 0, b = 1;
			for (int i = 1; i < n; i++) {
				a = a + b;
				a = a + b;
				b = a - b;
				a = a - b;
			}
			cout << "The Fibonacci number for " << n << " is " << b <<endl;
		}
	}
}
