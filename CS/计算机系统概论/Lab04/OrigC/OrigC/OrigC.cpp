// OrigC.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using namespace std;

typedef int i16;
typedef unsigned int u16;

int counter = 0;

i16 func(i16 n, i16 a, i16 b, i16 c, i16 d, i16 e, i16 f)
{
	i16 t = getchar() - '0' + a + b + c + d + e + f;
	counter++;
	if (n > 1)
	{
		i16 x = func(n - 1, a, b, c, d, e, f);
		i16 y = func(n - 2, a, b, c, d, e, f);
		return x + y + t - 1;
	}
	else
	{
		return t;
	}
}

i16 main(void) {
	i16 n = getchar() - '0';
	printf("%d\n", func(n, 0, 0, 0, 0, 0, 0));
	cout << counter << endl;
}
// 0	1
// 1	1
// 2	3
// 3	5
// 4	9
// 5	15
// 6	25
