// KMP.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <cstring>
#include <cstdarg>
#include <queue>

using namespace std;

int* KMP_get_next(char*  T) {
	int* next = new int[strlen(T)];
	next[0] = -1;
	int i = 0, j = -1;

	while (i < strlen(T)) {
		if (j == -1 || T[i] == T[j]) next[++i] = ++j;
		else j = next[j];
	}
	return next;
}

int KMP_Index(char*  s, char*  t, int start) {
	int i = start, j = 0;
	int* next = KMP_get_next(t);
	while (j == -1 || i < strlen(s) && j < strlen(t)) {
		if (j == -1 || s[i] == t[j]) { i++; j++; }
		else j = next[j];
	}
	if (j >= strlen(t))
		return i - strlen(t);
	else 
		return -1;
}

int main() {
	char str[] = "abaabc";
	char t[] = "abc";
	KMP_get_next(t);
	int indexs = KMP_Index(str, t, 0);
	cout << indexs;
}