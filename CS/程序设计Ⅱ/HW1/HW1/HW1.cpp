// HW1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
	int n = 0;
	char words[1000 + 5][20 + 5] = { '\0' };
	char prefix[1000 + 5][20 + 5] = { '\0' };
	while (cin >> words[n++]);
	n--;
	for (int i = 0; i < n-1; i++) {
		for (int j = i + 1; j < n; j++) {
			int k = 0;
			while (true) {
				prefix[i][k] = words[i][k];
				prefix[j][k] = words[j][k];

				if ((words[i][k] == '\0')||(words[j][k] == '\0')
					||(words[j][k] != words[i][k])) {
					break;
				}
				k++;
			}
		}
	}


	for (int i = 0; i < n; i++) {
		cout << words[i] << " " << prefix[i] << endl;
	}
}