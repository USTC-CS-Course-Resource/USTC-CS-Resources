// 2019春季学期程序设计II上机_4_B_潜伏者.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	int len = s1.length();
	char codeToLetter[26];
	char letterToCode[26];
	bool checkAll[2][26];
	memset(codeToLetter, 0, sizeof(codeToLetter));
	memset(letterToCode, 0, sizeof(letterToCode));
	memset(checkAll, 0, sizeof(checkAll));
	for (int i = 0; i < len; i++) {
		checkAll[0][s1[i] - 'A'] = true;
		checkAll[1][s2[i] - 'A'] = true;
		if (codeToLetter[s1[i] - 'A'] != 0 && codeToLetter[s1[i] - 'A'] != s2[i]) {
			cout << "Failed" << endl;
			return 0;
		}
		else {
			codeToLetter[s1[i] - 'A'] = s2[i];
		}
		if (letterToCode[s2[i] - 'A'] != 0 && letterToCode[s2[i] - 'A'] != s1[i]) {
			cout << "Failed" << endl;
			return 0;
		}
		else {
			letterToCode[s2[i] - 'A'] = s1[i];
		}
	}

	for (int i = 0; i < 26; i++) {
		if (checkAll[0][i] == false || checkAll[1][i] == false) {
			cout << "Failed" << endl;
			return 0;
		}
	}
	string s3;
	cin >> s3;
	int len3 = s3.length();
	for (int i = 0; i < len3; i++) {
		s3[i] = codeToLetter[s3[i] - 'A'];
	}
	cout << s3 << endl;
	return 0;
}
