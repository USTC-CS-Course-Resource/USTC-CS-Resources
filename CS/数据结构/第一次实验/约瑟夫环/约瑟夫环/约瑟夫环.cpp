// 约瑟夫环.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

// 约瑟夫循环链表结点
class JosephNode {
public:
	int index; // 结点序号
	int code; //结点密码
	JosephNode* next; // 下一个结点

	JosephNode(int index, int code) : index(index), code(code), next(nullptr) {};
};

// 约瑟夫循环链表
class JosephRing {
public:
	int num; // 总结点数
	int sup; //计数上限
	JosephNode* cur; //当前指向结点
	JosephNode* beforeCur; //当前指向结点的前一个结点
	JosephRing(int num, int sup, int* codes) : num(num), sup(sup){
		cur = new JosephNode(1, codes[0]);
		JosephNode* p = cur;
		for (int i = 1; i < num; i++) {
			p->next = new JosephNode(i + 1, codes[i]);
			p = p->next;
		}
		beforeCur = p;
		p->next = cur;
	}

	// 输出结果
	void printAnswer() {
		FILE* f = fopen("answer.txt", "w");
		while (num--) {
			sup--;
			//不断数下去，直到数完了上限
			while (sup--) {
				beforeCur = cur;
				cur = cur->next;
			}
			cout << cur->index << ' ';
			fprintf(f, "%d ", cur->index);
			sup = cur->code;
			beforeCur->next = cur->next;
			JosephNode* toDelete = cur;
			cur = cur->next;
			delete toDelete; //删除去掉了的节点占用的内存空间
		}
		cout << endl;
		fprintf(f, "\n");
		fclose(f);
	}
};

//从字符串中读取一个正整数
bool tryReadNum(int* dest, char* s) {
	int len = strlen(s);
	for (int i = 0; i < len; i++) {
		if (!isdigit(s[i])) {
			cout << "出现非正整数\n";
			return false;
		}
	}
	sscanf(s, "%d", dest);
}

int main(int argc, char* argv[])
{
	bool flag = true;
	// 对命令行参数的数量做分类，要满足题目要求，至少有4个参数
	if (argc >= 4) {
		int* codes = new int[argc - 1];
		// 将命令行参数转化为int类型数据存储在code中
		for (int i = 1; i < argc; i++) {
			if (!tryReadNum(codes + i - 1, argv[i])) {
				flag = false;
				break;
			}
		}
		// 判断人数和密码数是否对应
		if (codes[0] != argc - 3 && flag) {
			cout << "人数或密码数有误\n";
			flag = false;
		}
		if (flag) {
			// 实例化JosephRing,调用其printAnswer()方法以完成题目
			JosephRing* jr = new JosephRing(codes[0], codes[1], codes + 2);
			jr->printAnswer();
		}
	}
	if(!flag) {
		// 命令行参数格式不正确，要求重新输入。
		int num, m;
		cout << "命令行信息不完整，请重新输入，按照如下格式：\n"
			<< "〈人数n〉〈初始的报数上限m〉〈密码1〉 …… 〈密码n〉\n" << endl;
		cin >> num >> m;
		int* codes = new int[num]; 
		for (int i = 0; i < num; i++) {
			cin >> codes[i];
		}
		// 实例化JosephRing,调用其printAnswer()方法以完成题目
		JosephRing* jr = new JosephRing(num, m, codes);
		jr->printAnswer();
	}
}