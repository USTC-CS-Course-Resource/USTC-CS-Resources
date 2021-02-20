// 2019春季学期程序设计II上机_5_A_闰年问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

int main()
{
	int year;
	cin >> year;
	if (year % 100 == 0) {
		if (year % 400 == 0) {
			cout << "YES"<<endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	else {
		if (year % 4 == 0) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
}
