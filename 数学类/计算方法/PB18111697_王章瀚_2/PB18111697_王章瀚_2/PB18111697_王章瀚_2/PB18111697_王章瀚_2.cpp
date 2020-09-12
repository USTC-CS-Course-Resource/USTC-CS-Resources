#include "pch.h"
#include <iostream>
#include <cmath>
using namespace std;

// 不同的n的取值
double ns[4] = {5, 10, 20, 40};
const double PI = 3.1415926536;

double inline ori_x(double i, double n, int which) {
	//第一组节点
	if (which == 1)
		return -5 + 10.0 * i / n;
	//第二组节点
	else if (which == 2)
		return -5 * cos((2 * i + 1)*PI / (2 * n + 2));
}

// 测试点
double inline test_x(double i) {
	return -5 + 10.0 * i / 500.0;
}

// 函数f
double inline f(double x) {
	return 1 / (1 + x * x);
}

//计算在第which组节点下的拉格朗日插值结果，其中节点数为n
double L(double x, double n, int which) {
	double ans = 0;
	for (int i = 0; i <= n; i++) {
		double temp = 1;
		for (int j = 0; j <= n; j++) {
			if (j != i) {
				temp *= ((x - ori_x(j, n, which)) / (ori_x(i, n, which) - ori_x(j, n, which)));
			}
		}
		ans += temp*f(ori_x(i, n, which));
	}
	return ans;
}

int main()
{
	// 对两组节点循环
	for (int which = 1; which <= 2; which++) {
		// 对四种n的取值循环
		for (int i = 0; i < 4; i++) {
			double n = ns[i];
			double maxError = 0;
			double error;
			double tempX;
			// 对501个测试点循环
			for (int j = 0; j <= 500; j++) {
				tempX = test_x(j);
				error = fabs(f(tempX) - L(tempX, n, which));
				if (error > maxError) maxError = error;
			}
			//输出结果
			cout <<"第"<<which<<"组节点, n="<< n << "，\t"
				<< "最大模误差为： " << maxError << endl;
		}
		cout << endl;
	}
}

