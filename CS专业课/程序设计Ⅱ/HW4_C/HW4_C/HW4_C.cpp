// HW4_C.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int N = 100;
int n, initialDirection, steps;
int sx, sy, ex, ey;
bool first = true;
bool maze[N][N]; //用true表示墙
int dealNum1[4][2] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };
int dealNum2[4][2] = { {-1, -1}, {1, -1}, {1, 1}, {-1, 1} };
string answer;

// direction为0，1, 2, 3分别表示N, W, S, E
void setInitialDirection(int sx, int sy) {
	if (sx == 0 && sy == 0) {
		initialDirection = 3;
	}
	else if (sx == 0 && sy == n - 1) {
		initialDirection = 2;
	}
	else if (sx == n - 1 && sy == 0) {
		initialDirection = 0;
	}
	else if (sx == n - 1 && sy == n - 1) {
		initialDirection = 1;
	}
}

bool findWay(int x, int y, int direction) {
	if (x == ex && y == ey) {
		return true;
	}
	else if (x == sx && y == sy && direction == initialDirection) {
		if (first) {
			first = false;
		}
		else {
			return false;
		}
	}
	else if (steps > 10000) {
		return false;
	}
	/*for (int i = 0; i < 4; i++) {
		if (direction == i) {
			if ((x + dealNum1[i][0] < 0 || maze[x + dealNum1[i][0]][y + dealNum1[i][1]]) == true) {
				direction = (direction + 3) % 4;
				return findWay(x, y, direction);
			}
			else if (y + dealNum2[i][1] < 0 || maze[x + dealNum2[i][0]][y + dealNum2[i][1]] == true) {
				answer.append("N");
				steps++;
				return findWay(x + dealNum1[i][0], y, direction);
			}
			else {
				answer.append("N");
				steps++;
				if (x + dealNum1[i][0] == ex && y == ey) {
					return true;
				}
				answer.append("W");
				steps++;
				return findWay(x + dealNum2[i][0], y + dealNum2[i][1], (direction + 1) % 4);
			}
			break;
		}
	}*/
	if (direction == 0){
		if ((x - 1 < 0 || maze[x - 1][y]) == true) {
			direction = (direction + 3) % 4;
			return findWay(x, y, direction);
		}
		else if (y - 1 < 0 || maze[x - 1][y - 1] == true) {
			answer.append("N");
			steps++;
			return findWay(x - 1, y, direction);
		}
		else {
			answer.append("N");
			steps++;
			if (x - 1 == ex && y == ey) {
				return true;
			}
			answer.append("W");
			steps++;
			return findWay(x - 1, y - 1, (direction + 1) % 4);
		}
	}
	else if (direction == 1) {
		if ((y - 1 < 0 || maze[x][y - 1]) == true) {
			direction = (direction + 3) % 4;
			findWay(x, y, direction);
		}
		else if (x + 1 > n - 1 || maze[x + 1][y - 1] == true) {
			answer.append("W");
			steps++;
			return findWay(x, y - 1, direction);
		}
		else {
			answer.append("W");
			steps++;
			if (x == ex && y - 1== ey) {
				return true;
			}
			answer.append("S");
			steps++;
			return findWay(x + 1, y - 1, (direction + 1) % 4);
		}
	}
	else if (direction == 2) {
		if ((x + 1 > n - 1 || maze[x + 1][y]) == true) {
			direction = (direction + 3) % 4;
			findWay(x, y, direction);
		}
		else if (y + 1 > n - 1 || maze[x + 1][y + 1] == true) {
			answer.append("S");
			steps++;
			return findWay(x + 1, y, direction);
		}
		else {
			answer.append("S");
			steps++;
			if (x + 1 == ex && y == ey) {
				return true;
			}
			answer.append("E");
			steps++;
			return findWay(x + 1, y + 1, (direction + 1) % 4);
		}
	}
	else if (direction == 3) {
		if ((y + 1 > n - 1 || maze[x][y + 1]) == true) {
			direction = (direction + 3) % 4;
				findWay(x, y, direction);
		}
		else if (x - 1 < 0 || maze[x - 1][y + 1] == true) {
			answer.append("E");
			steps++;
				return findWay(x, y + 1, direction);
		}
		else {
			answer.append("E");
			steps++;
			if (x == ex && y + 1 == ey) {
				return true;
			}
			answer.append("N");
			steps++;
			return findWay(x - 1, y + 1, (direction + 1) % 4);
		}
	}
}

int main()
{
	int T, caseNum, i, j;
	char temp;
	cin >> T;
	for (caseNum = 1; caseNum <= T; caseNum++) {
		cin >> n;
		steps = 0;
		first = true;
		memset(maze, 0, sizeof(maze));
		answer.clear();
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				cin >> temp;
				if (temp == '#') {
					maze[i][j] = true;
				}
			}
		}
		cin >> sx >> sy >> ex >> ey;
		sx--; sy--; ex--; ey--;
		setInitialDirection(sx, sy);
		if (findWay(sx, sy, initialDirection)) {
			int len = answer.length();
			if (len == 0) {
				cout << "Case #" << caseNum << ": " << answer.length() << endl << endl;
			}
			else {
				cout << "Case #" << caseNum << ": " << answer.length() << endl << answer << endl;
			}
		}
		else {
			cout << "Case #" << caseNum << ": Edison ran out of energy." << endl;
		}
	}
}
/*
1
5x
.##.#
.....
...#.
.###.
...#.
1 1 5 3

*/
