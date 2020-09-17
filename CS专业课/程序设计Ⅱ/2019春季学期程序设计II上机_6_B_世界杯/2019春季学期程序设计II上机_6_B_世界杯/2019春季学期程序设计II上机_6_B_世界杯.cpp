// 2019春季学期程序设计II上机_6_B_世界杯.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
using namespace std;

class Team {
public:
	int rank;
	int scores;
	int goals;
	int get;
	int lose;
	Team(){
		scores = 0; goals = 0; get = 0; lose = 0;
	}
};

Team teams[4];

void solve(int x, int y) {
	int xGet, yGet;
	cin >> xGet;
	getchar();
	cin >> yGet;
	if (xGet > yGet) {
		teams[x].scores += 3;
	}
	else if (xGet < yGet) {
		teams[y].scores += 3;
	}
	else {
		teams[x].scores++; teams[y].scores++;
	}
	teams[x].get += xGet; teams[y].get += yGet;
	teams[x].lose += yGet; teams[y].lose += xGet;
	teams[x].goals = teams[x].get - teams[x].lose;
	teams[y].goals = teams[y].get - teams[y].lose;
}

int teamCompare(int x, int y) {
	if (teams[x].scores > teams[y].scores) {
		return 1;
	}
	else if (teams[x].scores < teams[y].scores) {
		return -1;
	}
	else {
		if (teams[x].goals > teams[y].goals) {
			return 1;
		}
		else if (teams[x].goals < teams[y].goals) {
			return -1;
		}
		else {
			if (teams[x].get > teams[y].get) {
				return 1;
			}
			else if (teams[x].get < teams[y].get) {
				return -1;
			}
			else {
				return 0;
			}
		}
	}
}

int main()
{
	solve(0, 1);
	solve(2, 3);
	solve(0, 2);
	solve(3, 1);
	solve(1, 2);
	solve(3, 0);
	int rank[4] = { 0, 1, 2, 3 };
	for (int i = 0; i < 4; i++) {
		for (int j = 3; j > i; j--) {
			if (teamCompare(rank[j - 1], rank[j]) < 0) {
				int temp = rank[j - 1];
				rank[j - 1] = rank[j];
				rank[j] = temp;
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		teams[rank[i]].rank = i + 1;
	}
	for (int i = 0; i < 4; i++) {
		if (teams[i].goals < 0) {
			printf("%d %d %d %d %d %c\n", teams[i].rank, teams[i].scores, 
				teams[i].goals, teams[i].get, teams[i].lose, teams[i].rank <= 2 ? 'Y' : 'N');
		}
		else {
			printf("%d %d +%d %d %d %c\n", teams[i].rank, teams[i].scores, 
				teams[i].goals, teams[i].get, teams[i].lose, teams[i].rank <= 2 ? 'Y' : 'N');
		}
	}

}
