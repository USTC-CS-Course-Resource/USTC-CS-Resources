// 2019春季学期程序设计II上机（附加题）_A_杀蚂蚁.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <stack>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;
const int MAP_MAX = 8;

class Coordinate {
public:
	int col;
	int row;
	Coordinate(int col, int row) : row(row), col(col) {}
	Coordinate() {};
	friend Coordinate operator+(const Coordinate c1, const Coordinate c2) {
		Coordinate* newc = new Coordinate(c1.col + c2.col, c1.row + c2.row);
		return *newc;
	}
	friend bool operator==(const Coordinate c1, const Coordinate c2) {
		if (c1.col == c2.col && c1.row == c2.row) return true;
		else return false;
	}
	double distanceToPoint(Coordinate c) {
		return pow((c.row - this->row)*(c.row - this->row) + (c.col - this->col)*(c.col - this->col), 0.5);
	}
	double distanceToLine(Coordinate c1, Coordinate c2) {
		return abs((c1.col - c2.col)*this->row - (c1.row - c2.row)*this->col + c1.row*c2.col - c2.row*c1.col)
			/ pow((c1.col - c2.col)*(c1.col - c2.col) + (c1.row - c2.row)*(c1.row - c2.row), 0.5);
	}
};

const Coordinate POSI_ORDER[4] = { Coordinate(1, 0), Coordinate(0, 1), Coordinate(-1, 0), Coordinate(0, -1) };

class Ant {
public:
	Coordinate location;
	bool isCarryingCake;
	int age;
	int level;
	int HP;
	int maxHP;
	Ant(int level) : level(level) {
		location = Coordinate(0, 0);
		age = 0;
		maxHP = (int)(4 * pow(1.1, level));
		HP = maxHP;
		isCarryingCake = false;
	};

};

class Cannon {
public:
	Coordinate location;
	const int fireRate = 1;
	int d; //攻击伤害为d/次
	int r; //攻击范围为r(直线距离)
	Cannon() {}
	Cannon(int col, int row, int d, int r) :d(d), r(r) {
		this->location = Coordinate(col, row);
	}
};

class GameMap {
public:
	int n, m;
	int pheromone[MAP_MAX][MAP_MAX];
	bool occupied[MAP_MAX][MAP_MAX];
	int bornedAntsNum;
	int cannonsNum;
	Ant* target;
	queue<Ant*> ants;
	Cannon** cannons;
	void antBorn();
	void antsBehave();
	void attack();
	bool check();
	GameMap(int m, int n, int cannonsNum){
		this->m = m;
		this->n = n;
		this->cannonsNum = cannonsNum;
		cannons = new Cannon* [cannonsNum];
		target = NULL;
		memset(pheromone, 0, sizeof(pheromone));
		memset(occupied, 0, sizeof(occupied));
	}
};

void GameMap::antBorn() {
	//1秒的最初，如果地图上蚂蚁数不足6，一只蚂蚁就会在洞口出生。
	if (ants.size() < 6) {
		ants.push(new Ant((int)(bornedAntsNum/6+1)));
		occupied[0][0] = true;
	}
}

void GameMap::antsBehave() {
	int antNum = ants.size();
	for (int i = 0; i < antNum; i++) {
		Ant* curAnt = ants.front();
		ants.pop();
		//接着，蚂蚁们在自己所在点留下一些信息素后，
		if (curAnt->isCarryingCake) {
			pheromone[curAnt->location.col][curAnt->location.row] += 5;
		}
		else {
			pheromone[curAnt->location.col][curAnt->location.row] += 2;
		}
		curAnt->age++;
		ants.push(curAnt);
	}
	//考虑移动。先出生的蚂蚁先移动。
	antNum = ants.size();
	for (int i = 0; i < antNum; i++) {
		Ant* curAnt = ants.front();
		ants.pop();
		int nextPosition = -1;
		const Coordinate curLocation = curAnt->location;
		int maxPheromone = -1;
		int firstPosiblePosition = -1;
		bool maxDoubled = false;
		for (int i = 0; i < 4; i++) {
			if ((curLocation.row + POSI_ORDER[i].row) < 0 || (curLocation.row + POSI_ORDER[i].row) >= (m - 1)) {
				continue;
			}
			if ((curLocation.col + POSI_ORDER[i].col) < 0 || (curLocation.col + POSI_ORDER[i].col) >= (n - 1)) {
				continue;
			}
			if (occupied[curLocation.col + POSI_ORDER[i].col][curLocation.row + POSI_ORDER[i].row]) {
				continue;
			}
			else {
				if(firstPosiblePosition == -1) firstPosiblePosition = i;
				if (maxPheromone == pheromone[curLocation.col + POSI_ORDER[i].col][curLocation.row + POSI_ORDER[i].row]) {
					//出现两个最大信息素位置
					maxDoubled = true;
				}
				else if (maxPheromone < pheromone[curLocation.col + POSI_ORDER[i].col][curLocation.row + POSI_ORDER[i].row]) {
					maxPheromone = pheromone[curLocation.col + POSI_ORDER[i].col][curLocation.row + POSI_ORDER[i].row];
					nextPosition = i;
					maxDoubled = false;
				}
			}
		}
		if (firstPosiblePosition != -1)
		{
			if (curAnt->age % 5 != 0) {
				if (maxDoubled == false) {
					occupied[curLocation.col][curLocation.row] = false;
					curAnt->location = POSI_ORDER[nextPosition] + curLocation;
					occupied[curAnt->location.col][curAnt->location.row] = true;
				}
				else {
					if (firstPosiblePosition != -1) {
						occupied[curLocation.col][curLocation.row] = false;
						curAnt->location = POSI_ORDER[firstPosiblePosition] + curLocation;
						occupied[curAnt->location.col][curAnt->location.row] = true;
					}
				}
			}
			else {
				//活动时间秒数为5的倍数，考虑逆时针旋转
				int trueNextPosition = -1;
				for (int i = -1; i > -5; i--) {
					trueNextPosition = (nextPosition + 4 + i) % 4;
					if ((curLocation.row + POSI_ORDER[trueNextPosition].row) < 0
						|| (curLocation.row + POSI_ORDER[trueNextPosition].row) >= (m - 1)) {
						continue;
					}
					if ((curLocation.col + POSI_ORDER[trueNextPosition].col) < 0
						|| (curLocation.col + POSI_ORDER[trueNextPosition].col) >= (n - 1)) {
						continue;
					}
					if (occupied[curLocation.col + POSI_ORDER[trueNextPosition].col][curLocation.row + POSI_ORDER[trueNextPosition].row]) {
						continue;
					}
					else {
						break;
					}
				}
				occupied[curLocation.col][curLocation.row] = false;
				curAnt->location = POSI_ORDER[trueNextPosition] + curLocation;
				occupied[curAnt->location.col][curAnt->location.row] = true;
			}
			//确定target，为NULL表示没有蚂蚁搬动着蛋糕
			if (target == NULL && (curAnt->location.row == m && curAnt->location.col == n)) {
				curAnt->isCarryingCake = true;
				curAnt->HP += (int)(curAnt->maxHP / 2);
				if (curAnt->HP > curAnt->maxHP) curAnt->HP = curAnt->maxHP;
				target = curAnt;
			}
		}
		ants.push(curAnt);
	}
	//移动完毕后，如果有蚂蚁在蛋糕的位置上并且蛋糕没被拿走，它把蛋糕扛上，血量增加，并在这时被所有塔设成target。

}

void GameMap::attack() {
	//然后所有塔同时开始攻击。如果攻击结束后那只扛着蛋糕的蚂蚁挂了，蛋糕瞬间归位。
	for (int i = 0; i < cannonsNum; i++) {
		//考虑有蚂蚁拿着蛋糕
		if (target != NULL) {
			double cannon_ant_distance;
			if ((cannon_ant_distance = cannons[i]->location.distanceToPoint(target->location)) <= cannons[i]->r) {
				//遍历每只蚂蚁
				int antNum = ants.size();
				for (int j = 0; j < antNum; j++) {
					Ant* curAnt = ants.front();
					ants.pop();
					if (curAnt->location.distanceToLine(target->location, cannons[i]->location) <= 1
						&& cannons[i]->location.distanceToPoint(curAnt->location) <= cannons[i]->location.distanceToPoint(target->location)) {
						curAnt->HP -= cannons[i]->d;
					}
					if (curAnt->HP >= 0 || curAnt == target) {
						ants.push(curAnt);
					}
					else {
						if (target != curAnt) {
							delete curAnt;
							curAnt = NULL;
						}
					}
				}
				if (target->HP < 0) {
					delete target;
					target = NULL;
				}
			}
			else {
				//TODO 激光塔没法攻击到target的情况
				queue<Ant*> antsToAttack;
				double minDistance = pow(MAP_MAX*MAP_MAX*2, 0.5) + 10;
				int antNum = ants.size();
				for (int j = 0; j < antNum; j++) {
					Ant* curAnt = ants.front();
					ants.pop();
					double tempDistance = curAnt->location.distanceToPoint(cannons[i]->location);
					if (tempDistance < minDistance) {
						while (!antsToAttack.empty()) {
							antsToAttack.pop();
						}
						antsToAttack.push(curAnt);
						minDistance = tempDistance;
					}
					else if (tempDistance == minDistance) {
						antsToAttack.push(curAnt);
					}
					ants.push(curAnt);
				}
				Ant* curAnt = ants.front();
				curAnt->HP -= cannons[i]->d;
				if (curAnt->HP < 0) {
					ants.pop();
					delete curAnt;
				}
			}
		}
		//没有蚂蚁拿着蛋糕
		else {
			//TODO 激光塔没法攻击到target的情况
			queue<Ant*> antsToAttack;
			double minDistance = pow(MAP_MAX*MAP_MAX * 2, 0.5) + 10;
			int antNum = ants.size();
			for (int j = 0; j < antNum; j++) {
				Ant* curAnt = ants.front();
				ants.pop();
				double tempDistance = curAnt->location.distanceToPoint(cannons[i]->location);
				if (tempDistance < minDistance) {
					while (!antsToAttack.empty()) {
						antsToAttack.pop();
					}
					antsToAttack.push(curAnt);
					minDistance = tempDistance;
				}
				else if (tempDistance == minDistance) {
					antsToAttack.push(curAnt);
				}
				ants.push(curAnt);
			}
			Ant* curAnt = ants.front();
			curAnt->HP -= cannons[i]->d;
			if (curAnt->HP < 0) {
				ants.pop();
				delete curAnt;
			}
		}
	}
}

bool GameMap::check() {
	//攻击结束后，如果发现扛蛋糕的蚂蚁没死并在窝的位置，就认为蚂蚁抢到了蛋糕。游戏也在此时结束。
	if (target != NULL && target->location.distanceToPoint(Coordinate(0, 0)) == 0) {
		return true;
	}
	//最后，地图上所有点的信息素损失1单位。所有蚂蚁的年龄加1。
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (pheromone[i][j] > 0) {
				pheromone[i][j]--;
			}
		}
	}
	return false;
}

int main() {
	int n, m, s, d, r, t;
	cin >> n >> m >> s >> d >> r;
	GameMap gm = GameMap(m, n, s);
	for (int i = 0; i < s; i++) {
		int row, col;
		cin >> col >> row;
		gm.cannons[i] = new Cannon(col, row, d, r);
	}
	cin >> t;
	for (int i = 1; i <= t; i++) {
		gm.antBorn();
		gm.antsBehave();
		gm.attack();
		if (gm.check()) {
			cout << "Game over after " << i << " seconds" << endl;
			int antsNum = gm.ants.size();
			cout << antsNum << endl;
			for (int j = 0; j < antsNum; j++) {
				Ant* curAnt = gm.ants.front();
				cout << curAnt->age << curAnt->level << curAnt->HP << curAnt->location.col << curAnt->location.row << endl;
			}
			return 0;
		}
	}
	cout << "The game is going on" << endl;
	int antsNum = gm.ants.size();
	cout << antsNum << endl;
	for (int j = 0; j < antsNum; j++) {
		Ant* curAnt = gm.ants.front();
		cout << curAnt->age << curAnt->level << curAnt->HP << curAnt->location.col << curAnt->location.row << endl;
	}

}