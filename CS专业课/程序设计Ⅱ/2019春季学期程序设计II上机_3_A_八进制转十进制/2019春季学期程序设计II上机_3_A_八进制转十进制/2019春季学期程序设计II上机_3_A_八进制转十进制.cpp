// 2019春季学期程序设计II上机_3_A_八进制转十进制.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int oct, dec;
	cin >> oct;
	dec = 0;
	int i = 0;
	while (oct) {
		dec += (oct % 10) * pow(8, i++);
		oct /= 10;
	}
	cout << dec << endl;
}