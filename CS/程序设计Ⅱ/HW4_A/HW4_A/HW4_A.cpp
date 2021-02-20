// HW4_A.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//2*1+(4+3)*6	21*43++6*

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;
string equation;
string answer;
int len;
int equIndex;

// mode==0表示不加括号，mode==1表示上一式为加减且求右式，mode==2表示上一式为乘除,mode==3上一式为乘除且须求右式
string solve(int mode) {
	if (equIndex < 0) {
		return "";
	}
	string cur = " ";
	cur[0] = equation[equIndex--];
	if (cur[0] >= '0' && cur[0] <= '9') {
		return cur;
	}
	else {
		string right; string left;
		if (mode == 0) {
			if (cur[0] == '+' || cur[0] == '-') {
				right = solve(1);
				left = solve(0);
			}
			else if (cur[0] == '*' || cur[0] == '/') {
				right = solve(3);
				left = solve(2);
			}
			return left + cur + right;
		}
		else if (mode == 1) {
			if (cur[0] == '+' || cur[0] == '-') {
				right = solve(1);
				left = solve(0);
				return "(" + left + cur + right + ")";
			}
			else if (cur[0] == '*' || cur[0] == '/') {
				right = solve(3);
				left = solve(2);
				return left + cur + right;
			}
		}
		else if (mode == 2) {
			if (cur[0] == '+' || cur[0] == '-') {
				right = solve(1);
				left = solve(0);
				return "(" + left + cur + right + ")";
			}
			else if (cur[0] == '*' || cur[0] == '/') {
				right = solve(3);
				left = solve(2);
				return left + cur + right;
			}
		}
		else if (mode == 3) {
			if (cur[0] == '+' || cur[0] == '-') {
				right = solve(1);
				left = solve(0);
				return "(" + left + cur + right + ")";
			}
			else if (cur[0] == '*' || cur[0] == '/') {
				right = solve(3);
				left = solve(2);
				return "(" + left + cur + right + ")";
			}
		}
	}
}


int main()
{
	cin >> equation;
	equIndex = equation.length() - 1;
	cout << solve(0) << endl;
}


/*int findNextBracket(int start) {
	int leftNum = 0, rightNum = 0;
	for (int i = start; i < len - 1; i++) {
		if (answer[i] == '(') {
			leftNum++;
		}
		else if (answer[i] == ')') {
			rightNum++;
		}
		if (leftNum == rightNum) {
			return i;
		}
	}
}

void cancelBrackets(int start) {
	int leftIndex = -1, rightIndex = -1;

	if (answer[start] == '(') {
		int leftNum = 1, rightNum = 0, i;
		for (i = start + 1; i < len - 1; i++) {
			if (answer[i] == '(') {
				leftNum++;
			}
			else if (answer[i] == ')') {
				rightNum++;
			}
			if (leftNum == rightNum) {
				break;
			}
		}
		if (answer[i + 1] == '+' || answer[i + 1] == '-' || answer[i + 1] == '(') {
			answer[1] = ' '; answer[i] = ' ';
		}
	}

	for (int i = start; i < len - 1; i++) {
		if (answer[i] == '(') {
			leftIndex = i;
			rightIndex = findNextBracket(i);
			i = rightIndex + 1;
			cancelBrackets(leftIndex + 1);
			bool can = true;
			for (int j = leftIndex + 1; j <= rightIndex; j++) {
				if (answer[j] == '(') {
					j = findNextBracket(j) + 1;
				}
				if ((j >= '0' && j <= '9') || answer[j] == ' ') {
					continue;
				}
				else {
					if (answer[j] != '*' && answer[j] != '/' && answer[j] != ')') {
						can = false;
						break;
					}
				}
			}
			if (can) {
				answer[leftIndex] = ' '; answer[rightIndex] = ' ';
			}
		}
	}
}*/


//彻底去掉多余括号
/*int cancelBrackets(int start) {
	int leftIndex = -1, rightIndex = -1;
	for (int i = start; i < len - 1; i++) {
		if (answer[i] == '(') {
			leftIndex = i;
			rightIndex = cancelBrackets(leftIndex + 1);
			if (((answer[leftIndex - 1] == '+' || answer[leftIndex - 1] == '-') &&
				(answer[rightIndex + 1] == '+' || answer[rightIndex + 1] == '-'))
				) {
				answer[leftIndex] = ' '; answer[rightIndex] = ' ';
			}
			else {
				bool can = true;
				for (int j = leftIndex; j <= rightIndex; j += 2) {
					if (answer[j] != '*' && answer[j] != '/') {
						can = false;
						break;
					}
				}
				if (can) {
					answer[leftIndex] = ' '; answer[rightIndex] = ' ';
				}
			}
			i = rightIndex + 1;
		}
		else if (answer[i] == ')') {
			return i;
		}
	}
}*/

