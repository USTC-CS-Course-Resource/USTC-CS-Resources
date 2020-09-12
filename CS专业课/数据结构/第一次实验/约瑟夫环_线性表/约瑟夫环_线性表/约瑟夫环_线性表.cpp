// 约瑟夫环_线性表.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// 约瑟夫结点
class JosephNode {
public:
	int index; //结点序号
	int code; // 结点密码
	int nextCur; //下一个结点的位置
	JosephNode(int index, int code, int nextCur) 
		: index(index), code(code), nextCur(nextCur) {};
};

// 从字符串s中读取正整数，存入dest中
bool tryReadNum(int* dest, char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (!isdigit(s[i])) {
			cout << "出现非正整数\n";
			return false;
		}
	}
	sscanf(s, "%d", dest);
	return true;
}

// 解约瑟夫问题
void solve(int num, int m, JosephNode** list) {
	FILE* f = fopen("answer.txt", "w");
	int beforeCur = num - 1;
	int cur = 0;
	while (num--) {
		m--;
		// 循环数人，直到达到m
		while (m--) {
			beforeCur = cur;
			cur = list[cur]->nextCur;
		}
		cout << list[cur]->index << ' ';
		fprintf(f, "%d ", list[cur]->index);
		m = list[cur]->code;
		list[beforeCur]->nextCur = list[cur]->nextCur;
		cur = list[cur]->nextCur;
	}
	cout << endl;
	fprintf(f, "\n");
	fclose(f);
}

int main(int argc, char* argv[])
{
	int num, m, code;
	JosephNode** list = nullptr;
	bool flag = true;
	// 对命令行参数的数量做分类，要满足题目要求，至少有4个参数
	if (argc >= 4) {
		// 读取人数
		if (!tryReadNum(&num, argv[1])) {
			flag = false;
		}
		// 判断人数和密码数是否一致
		if (num != argc - 3 && flag) {
			cout << "人数或密码数有误\n";
			flag = false;
		}
		// 读取初始密码
		if (!tryReadNum(&m, argv[2]) && flag) {
			flag = false;
		}
		if (flag) {
			list = new JosephNode*[num];
			// 读取所有密码
			for (int i = 0; i < num; i++) {
				if (!tryReadNum(&code, argv[i + 3])) {
					flag = false;
					break;
				}
				list[i] = new JosephNode(i + 1, code, i == num - 1 ? 0 : i + 1);
			}
			// 执行
			solve(num, m, list);
			return 0;
		}
	}
	if (flag) {
		// 命令行输入信息不完整
		cout << "命令行信息不完整，请重新输入，按照如下格式：\n"
			<< "〈人数n〉〈初始的报数上限m〉〈密码1〉 …… 〈密码n〉\n" << endl;
		// 重新读取人数和初始密码
		cin >> num >> m;
		list = new JosephNode*[num];
		// 重新读取密码
		for (int i = 0; i < num; i++) {
			cin >> code;
			list[i] = new JosephNode(i + 1, code, i == num - 1 ? 0 : i + 1);
		}
		// 执行
		solve(num, m, list);
	}
}
