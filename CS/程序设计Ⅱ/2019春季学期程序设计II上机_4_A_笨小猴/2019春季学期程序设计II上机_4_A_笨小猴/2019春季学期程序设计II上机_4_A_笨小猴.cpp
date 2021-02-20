// 2019春季学期程序设计II上机_4_A_笨小猴.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstring>;
using namespace std;

const int stranges[25] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97 };

int main()
{
	int times[26];
	memset(times, 0, sizeof(times));
	char c;
	while (cin>>c) {
		times[c - 'a']++;
	}
	int maxn = 0, minn = 200;
	for (int i = 0; i < 26; i++) {
		if (times[i] == 0) continue;
		maxn = maxn > times[i] ? maxn : times[i];
		minn = minn > times[i] ? times[i] : minn;
	}
	int luckNum = maxn - minn;
	bool lucky = false;
	for (int i = 0; i < 25; i++) {
		if (luckNum == stranges[i]) {
			cout << "Lucky Word" << endl << luckNum << endl;
			lucky = true;
			break;
		}
	}
	if (!lucky) {
		cout << "No Answer" << endl << 0 << endl;
	}
}
