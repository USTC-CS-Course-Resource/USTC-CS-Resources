// 2019春季学期程序设计II上机补交_8_B_ 一元三次方程求解.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

double a, b, c, d;
int places[3];
double roots[3];
inline double f(double x) {
	return a * x * x * x + b * x * x + c * x + d;
}

inline bool isEqual(double x, double y) {
	return fabs(x - y) <= 1e-5 ? true : false;
}

inline short getSymbol(const double x) {
	if (isEqual(x, 0))
		return 0;
	else if (x < 0)
		return -1;
	else if (x > 0)
		return 1;
}


double getRoot(double left, double right) {
	short fms;
	double middle, fl, fr, fm;
	fl = f(left); fr = f(right);
	short fls = getSymbol(fl); 
	short frs = getSymbol(fr);
	while (true) {
		middle = (left + right) / 2;
		fm = f(middle);
		fms = getSymbol(fm);
		if (getSymbol(fm) == 0) {
			return middle;
		}
		else if (fms == fls) {
			left = middle;
			fl = fm;
			fls = fms;
		}
		else if (fms == frs) {
			right = middle;
			fr = fm;
			frs = fms;
		}
	}
}

int main()
{
	cin >> a >> b >> c >> d;
	int order = 0;
	for (int i = 0; i < 3; i++) {
		roots[i] = 200;
	}
	short last = getSymbol(f(-101));
	for (int i = -100; i < 102; i++) {
		double answer = f(i);
		short cur = getSymbol(answer);
		if (cur == 0) {
			roots[order++] = i;
			last = 0;
			continue;
		}
		if (cur != last && last != 0) {
			places[order++] = i;
		}
		last = cur;
	}
	//100 -900 1700 600
	//-0.0125 1 125 -10000
	//0.01030715316 -3.06122449 303.0509173 -10000
	for (int i = 0; i < 3; i++) {
		if (roots[i] == 200) {
			roots[i] = getRoot(places[i] - 1, places[i]);
		}
	}
	sort(roots, roots + 2);
	for (int i = 0; i < 3; i++) {
		if (i == 2) {
			printf("%.2f\n", roots[i]);
		}
		else {
			printf("%.2f ", roots[i]);
		}
	}
}
