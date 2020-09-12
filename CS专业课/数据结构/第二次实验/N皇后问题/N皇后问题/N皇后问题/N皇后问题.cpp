// N皇后问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
using namespace std;


// Here we use a stack to store the information of 
// the layout.
class layout {
private:
	int cur;
	int size;
	int** layout_stack;

public:
	layout(int N) {
		size = 0;
		cur = -1;
		this->N = N;
		layout_stack = new int*[N];
		for (int i = 0; i < N; i++) {
			layout_stack[i] = new int[N];
		}
	}

	int N;
	inline int stack_size() {
		return cur + 1;
	}

	// get the top of stack
	int* top() {
		if (cur >= 0)
			return layout_stack[cur];
		return nullptr;
	}

	// pop the top of the stack
	void pop() {
		if (cur >= 0) 
			delete layout_stack[cur--];
	}

	// push cur_layout to the top of the stack
	void push(int* cur_layout) {
		layout_stack[++cur] = cur_layout;
	}

	// clone a layout and return it.
	int* clone(int* ori) {
		if (ori == nullptr)
			return nullptr;
		auto temp = new int[N];
		for (int i = 0; i < N; i++) {
			temp[i] = ori[i];
		}
		return temp;
	}

	// print the layout.
	void printLayout(int* lay) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (j == lay[i]) cout << 'Q';
				else cout << '#';
			}
			cout << endl;
		}
		cout << endl;
	}

	// to determine whether the last line in lay is ok.
	bool is_lastline_ok(int* lay, int row) {
		for (int j = 0; j < row; j++) {
			if (lay[j] == lay[row] || abs(lay[j] - lay[row]) == row - j) {
				return false;
			}
		}
		return true;
	}

	void solve() {
		LARGE_INTEGER start, nFreq, end;
		QueryPerformanceFrequency(&nFreq);
		QueryPerformanceCounter(&start);
		int counter = 0;
		int* cur_layout = new int[N];
		cur_layout[0] = 0;
		push(cur_layout);
		while (1) {
			cur_layout = clone(top());
			if (top() == nullptr)
				break;
			if (is_lastline_ok(cur_layout, stack_size() - 1)) {
				// no conflict here
				// whether finished
				if (stack_size() == N) {
					counter++;
					cout << counter << endl;
					printLayout(cur_layout);
				}
				else {
					cur_layout[stack_size()] = 0;
					push(cur_layout);
					continue;
				}
			}
			// need a recall
			delete[] cur_layout;
			cur_layout = top();
			if (cur_layout == nullptr)
				break;
			while (cur_layout[stack_size() - 1] == N - 1) {
				// tried all circumstance in this row
				pop();
				cur_layout = top();
				if (cur_layout == nullptr)
					break;
			}
			// found a row that the queen can be move rightward.
			if (cur_layout != nullptr) {
				top()[stack_size() - 1]++;
			}
		}
		QueryPerformanceCounter(&end);
		cout << "以上共" << counter << "种" << endl;
		cout << "耗时" << (double)(end.QuadPart - start.QuadPart) / (double)nFreq.QuadPart << "秒" << endl;

	}
	
};


// recursion method
int counter = 0;
void recursion(int* cur_layout, int row, const int N) {
	if (row == N) {
		counter++;
		// print the layout.
		cout << counter << endl;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (j == cur_layout[i]) cout << 'Q';
				else cout << "#";
			}
			cout << endl;
		}
		cout << endl;
		return;
	}
	for (int i = 0; i < N; i++) {
		cur_layout[row] = i;
		bool flag = true;
		// try all circumstances.
		for (int j = 0; j < row; j++) {
			if (cur_layout[j] == cur_layout[row] 
				|| abs(cur_layout[j] - cur_layout[row]) == row - j) {
				flag = false;
				break;
			}
		}
		// if ok, try next row. Here is the recursion.
		if(flag)
			recursion(cur_layout, row + 1, N);
	}
	return;
}


int main()
{
	int N;
	cin >> N;

	cout << "栈解法：\n";
	layout lay(N);
	lay.solve();

	cout << "\n递归解法：\n";
	int* cur_layout = new int[N];
	LARGE_INTEGER start, nFreq, end;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&start);
	recursion(cur_layout, 0, N);
	QueryPerformanceCounter(&end);
	cout << "以上共" << counter << "种" << endl;
	cout << "耗时" << (double)(end.QuadPart - start.QuadPart) / (double)nFreq.QuadPart << "秒" << endl;
}
