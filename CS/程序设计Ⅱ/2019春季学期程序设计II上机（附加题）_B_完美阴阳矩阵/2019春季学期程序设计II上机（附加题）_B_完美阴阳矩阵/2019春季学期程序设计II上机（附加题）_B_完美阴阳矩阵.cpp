// 2019春季学期程序设计II上机（附加题）_B_完美阴阳矩阵.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stack>
#include <cstring>
#include <cmath>
#include <algorithm>
#pragma warning(disable:4996)
using namespace std;

const int MAX = 2005;
int n, m;
int max_inRow = 0;
int max_inCol = 0;

class MaxValue
{
public:
	int max_squ;
	int max_rect;
	MaxValue(int ms, int mr) : max_squ(ms), max_rect(mr) {}
};
class Rect
{
public:
	int height;
	int pos;
	Rect(int height, int pos) : height(height), pos(pos) {}
	Rect(){}
};


MaxValue getMax_Line(int* line)
{
	stack<Rect> sr;
	int maxValue_rect = 0;
	int maxValue_squ = 0;
 	for (int i = n-2; i >= 0; i--)
	{
		Rect curRect = Rect(line[i], i);
		if (sr.empty())
		{
			sr.push(curRect);
		}
		else
		{
			if (sr.top().height < curRect.height)
			{
				sr.push(curRect);
			}
			else if (sr.top().height >= curRect.height)
			{
				Rect r;
				int d_pos = 0;
				while (!sr.empty() && sr.top().height >= curRect.height)
				{
					r = sr.top();
					sr.pop();
					d_pos = r.pos - i + 1;
					maxValue_squ = max(maxValue_squ, (int)pow(min(d_pos, r.height + 1), 2));
					maxValue_rect = max(maxValue_rect, (r.height + 1)*(d_pos));
				}
				curRect.pos = r.pos;
				sr.push(curRect);
			}
		}
	}
	Rect r;
	int d_pos = 0;
	while (!sr.empty())
	{
		r = sr.top();
		sr.pop();
		d_pos = r.pos + 2;
		maxValue_squ = max(maxValue_squ, (int)pow(min(d_pos, r.height + 1), 2));
		maxValue_rect = max(maxValue_rect, (r.height + 1)*(d_pos));
	}
	return MaxValue(maxValue_squ, maxValue_rect);
}

MaxValue getMax(int** simpleRect)
{
	MaxValue mv = MaxValue(1, max(max_inRow, max_inCol));
	for (int i = m - 2; i >= 0; i--)
	{
		MaxValue mv_Line = getMax_Line(simpleRect[i]);
		mv.max_rect = max(mv.max_rect, mv_Line.max_rect);
		mv.max_squ = max(mv.max_squ, mv_Line.max_squ);
	}
	return mv;
}

int main()
{
	cin >> n >> m;
	int line[2][MAX];
	int** simpleRect = new int*[m - 1];
	for (int i = 0; i < m - 1; i++)
	{
		simpleRect[i] = new int[n - 1];
		memset(simpleRect[i], 0, sizeof(simpleRect[i]));
	}
	int flag = 0;
	bool special = true;//false表示存在2*1或1*2，则只要考虑2*2以上的；不存在2*1或1*2的完美子矩阵则赋值为true，此时答案为m*n；
	int max_1[2][MAX] = { 0 };
	int max_inRow_counter = 1;
	memset(line, 0, sizeof(line));
	scanf("%d", &line[0][0]);
	for (int i = 1; i < m; i++)
	{
		scanf("%d", &line[flag][i]);
		if (line[flag][i] != line[flag][i - 1])
		{
			special = false;
		}
	}
	flag = !flag;
	for (int i = 1; i < n; i++)
	{
		scanf("%d", &line[flag][0]);
		if (line[flag][0] != line[!flag][0])
		{
			max_1[1][0]++;
		}
		else
		{
			max_1[0][0] = max(max_1[0][0], max_1[1][0]);
			max_1[1][0] = 0;
		}
		for (int j = 1; j < m; j++)
		{
			scanf("%d", &line[flag][j]);
			if (line[flag][j] != line[!flag][j])
			{
				max_1[1][j]++;
			}
			else
			{
				max_1[0][j] = max(max_1[0][j], max_1[1][j]);
				max_1[1][j] = 0;
			}

			if (line[flag][j] != line[flag][j - 1])
			{
				special = false;
				max_inRow_counter++;
			}

			if (line[flag][j] != line[flag][j - 1] && 
				line[flag][j] != line[!flag][j] && 
				line[flag][j] == line[!flag][j - 1])
			{
				simpleRect[j - 1][i - 1] = (j == 1 ? 1 : simpleRect[j - 2][i - 1] + 1);
			}
			else
			{
				simpleRect[j - 1][i - 1] = 0;
			}
			max_inRow = max(max_inRow, max_inRow_counter);
		}
		flag = !flag;
		max_inRow_counter = 1;
	}

	for (int i = 0; i < m; i++)
	{
		max_inCol = max(max_inRow, max(max_1[0][i], max_1[1][i]));
	}
	
	/*for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			cout << simpleRect[i][j] << " ";
		}
		cout << endl;
	}*/

	if (special == true)
	{
		printf("%d\n%d\n", (m > n ? n : m)*(m > n ? n : m), m*n);
	}
	else
	{
		MaxValue mv = getMax(simpleRect);
		printf("%d\n%d\n",  mv.max_squ, mv.max_rect);
	}
}
