// 2019春季学期程序设计II上机_10_B_八数码问题.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <cmath>
#include <map>
#include <queue>
using namespace std;

const int SIZE = 3;
const int AREA = SIZE * SIZE;
const int moveTo[4] = { -SIZE,1,SIZE,-1 };

class Status {
public:
	long value;
	short table[AREA];
	short zero;
	Status(long Eigenvalue) : value(Eigenvalue){
 		for (int i = AREA - 1; i >= 0; i--) {
			table[i] = Eigenvalue % 10;
			if (table[i] == 0) {
				zero = i;
			}
			Eigenvalue /= 10;
		}
	}
};

map<long, bool> tried[2];
queue<long> toCheck[2];

inline bool isIn(short zero, int position) {
	//0上，1右，2下，3左
	if (position == 0) {
		if (zero >= SIZE) return true;
		else return false;
	}
	else if (position == 1) {
		if (zero % SIZE < SIZE - 1) return true;
		else return false;
	}
	else if (position == 2) {
		if (zero < AREA - SIZE) return true;
		else return false;
	}
	else if (position == 3) {
		if (zero % SIZE > 0) return true;
		else return false;
	}
	return false;
}

int DBFS() {
	int times[2] = { 0 };
	while (true) {
		for (int i = 0; i < 2; i++) {
			times[i]++;
			int toCheckSize = toCheck[i].size();
			for (int j = 0; j < toCheckSize; j++) {
				Status cur = Status(toCheck[i].front());
				toCheck[i].pop();
				for (int pos = 0; pos < 4; pos++) {
					int next = cur.zero + moveTo[pos];
					if (isIn(cur.zero, pos)) {
						int curValue = cur.value -
							(int)(pow(10, 8 - next) - pow(10, 8 - cur.zero)) * cur.table[next];
						if (tried[!i].find(curValue) != tried[!i].end()) {
							return times[0] + times[1];
						}
						if (tried[i].find(curValue) == tried[i].end()) {
							toCheck[i].push(curValue);
							tried[i].insert(pair<long, bool>(curValue, true));
						}
					}
				}
			}
		}
	}
}

int main()
{
	long value = 0;
	for (int i = 0; i < AREA; i++) {
		short temp;
		cin >> temp;
		value += (int)pow(10, 8 - i)*temp;
	}
	tried[0].insert(pair<long, bool>(value, true));
	//tried[0].insert(map<long, bool>::value_type(value, true));
	tried[1].insert(pair<long, bool>(876543210L, true));
	toCheck[0].push(value);
	toCheck[1].push(876543210L);

	if (value == 876543210L) {
		cout << 0 << endl;
	}
	else {
		cout << DBFS() << endl;
	}
}