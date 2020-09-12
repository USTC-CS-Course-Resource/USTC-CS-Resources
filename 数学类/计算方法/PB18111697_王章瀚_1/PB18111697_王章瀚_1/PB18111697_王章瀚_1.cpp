#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;

// 设置允许截断误差值
const double TRUNCATION_ERROR = 1e-13;
// 计算在允许截断误差下的k应计算到多少位
const double MAX_K = 1/pow(2*TRUNCATION_ERROR, 0.5) + 1;

// x及x的个数
const int X_NUM = 7;
const double array_x[] = { 0.0, 0.5, 1.0, pow(2, 0.5), 10.0, 100.0, 300.0 };


double psi(double x) {
	double answer = 0;
	double k = 1;
	// 先计算(psi(x)-psi(1))/(1-x)，其收敛速度更快
	while (k <= MAX_K) {
		answer += 1/(k*(k+x)*(k+1));
		k++;
	}
	return 1 + (answer)*(1 - x);
}

int main()
{
	for (int i = 0; i < X_NUM; i++) {
		printf("x=%lf,y=%.15e\n", array_x[i], psi(array_x[i]));
	}
}