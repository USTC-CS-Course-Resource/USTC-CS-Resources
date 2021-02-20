// HW4_D.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
int dataSet = 0;
string retracts = "|     ";
int retractTimes;
bool firstIn;

void printLine(string cur, int times) {
	for (int i = 0; i < times; i++) {
		cout << retracts;
	}
	cout << cur << endl;
}

bool solve(string dir) {
	string temp;
	cin >> temp;
	if (firstIn) {
		if (temp[0] == '#') {
			return false;
		}
		else {
			cout << "DATA SET " << dataSet << ":" << endl;
			firstIn = false;
		}
	}
	printLine(dir, retractTimes);
	vector<string> fileNames;
	while (retractTimes >= 0) {
		if (temp[0] == 'd') {
			retractTimes++;
			solve(temp);
			cin >> temp;
		}
		else if (temp[0] == 'f') {
			fileNames.push_back(temp);
			cin >> temp;
		}
		else if (temp[0] == ']' || temp[0] == '*') {
			int fsize = fileNames.size();
			if (fsize > 1) {
				sort(fileNames.begin(), fileNames.end());
			}
			for (int i = 0; i < fsize; i++) {
				printLine(fileNames[i], retractTimes);
			}
			retractTimes--;
			break;
		}
	}
	return true;
}

int main()
{
	string temp;
	while (true) {
		++dataSet;
		retractTimes = 0;
		firstIn = true;
		if (!solve("ROOT")) {
			break;
		}
		cout << endl;
	}
	return 0;
}




/*int comp(const void* a, const void* b) {
	for (int i = 0;; i++) {
		if (!(((char*)a)[i] != '\0' && ((char*)b)[i] != '\0')) {
			if (((char*)a)[i] == ((char*)b)[i]) {
				continue;
			}
			else {
				return (((char*)a)[i] - ((char*)b)[i]);
			}
		}
		else {
			return 0;
		}
	}
}

void sortNames(vector<string> names) {
	int maxIndex;
	int size = names.size();
	for (int i = 0; i < size; i++) {
		maxIndex = i;
		for (int j = i + 1; j < size; j++) {

		}
	}
}
*/