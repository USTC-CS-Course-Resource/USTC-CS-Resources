// 2019春季学期程序设计II上机_5_B_日历问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

int monthDays[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
int main()
{
	int month[2];
	int day[2];
	for (int i = 0; i < 2; i++) {
		cin >> month[i] >> day[i];
	}
	int days = 0;
	for (int i = month[0]; i < month[1]; i++) {
		days += monthDays[i - 1];
	}
	days = days - day[0] + day[1];
	cout << days << endl;
}
