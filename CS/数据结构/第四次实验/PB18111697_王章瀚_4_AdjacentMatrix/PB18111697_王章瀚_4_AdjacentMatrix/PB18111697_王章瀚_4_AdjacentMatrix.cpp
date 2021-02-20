// PB18111697_王章瀚_4_AdjacentMatrix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <climits>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Vertex {
public:
	int index;
};

// 图类，用邻接矩阵表示无向图
class MGraph {
private:
	int* visited = NULL;
	// 从顶k开始由DFS寻找最大圈。
	void FindMaxCircleThrough(int& k, int v, int weight, vector<int>* curCircle);
public:
	Vertex* vexs = NULL;
	int** arcs = NULL; //邻接矩阵，值直接是权，若为0，则表示不相邻
	bool edgeWeighted = false;
	int vexNum = 0, arcNum = 0;
	vector<int> Articul;
	
	bool hasCircle = false;
	int maxWeight = 0;
	vector<int> maxCircle;
	
	MGraph(string fileName);
	// 打印邻接矩阵
	void PrintMatrix();
	// 找关节点的启动函数，最终找到所有割顶放在Articul中
	void FindArticul();
	// 找割顶的DFS函数
	void DFSArticul(int v0, int& count, int* visited, int* low);
	// 找最大圈的函数
	void FindMaxCircle();
	// 打印最大圈
	void PrintMaxCircle();
	// 打印割顶
	void PrintArticul();
	// 打印可以用于生成Graphviz图的代码（）
	void PrintGraphvizCode();
};

void MGraph::FindMaxCircleThrough(int& k, int v, int weight, vector<int>* curCircle) {
	visited[v] = true;
	curCircle->push_back(v);
	for (int i = 0; i < vexNum; i++) {
		if (arcs[v][i] != 0) {
			if (i == k && curCircle->size() > 2) {
				//说明找到了一个圈
				if (weight + arcs[v][i] > maxWeight) {
					// 比之前找到的更长
					maxWeight = weight + arcs[v][i];
					maxCircle = *curCircle;
					continue;
				}
			}
			else if (!visited[i]) {
				// 未访问顶，则继续遍历
				FindMaxCircleThrough(k, i, weight + arcs[v][i], curCircle);
				continue;
			}
		}
	}
	curCircle->pop_back();
	visited[v] = false;
}

MGraph::MGraph(string fileName) {
	fstream fs(fileName, ios::in | ios::out);
	// 读入顶点数
	string line;
	fs >> vexNum;
	getline(fs, line);
	// 分配顶点的空间
	vexs = new Vertex[vexNum];
	if (vexs == NULL) return;
	for (int i = 0; i < vexNum; i++) {
		vexs[i].index = i;
	}
	// 分配visited的空间
	visited = new int[vexNum];
	if (visited == NULL) return;
	memset(visited, 0, sizeof(int) * vexNum);
	// 分配边矩阵空间
	arcs = new int* [vexNum];
	if (arcs == NULL) return;
	for (int i = 0; i < vexNum; i++) {
		arcs[i] = new int[vexNum];
		if (arcs[i] == NULL) return;
		memset(arcs[i], 0, sizeof(int)*vexNum);
	}
	// 读入数据
	while(!fs.eof()) {
		getline(fs, line);
		stringstream ss(line);
		int h, t;
		ss >> h >> t;
		// 看该行是否有第三个数，如果有说明输入了边权
		if (ss.eof()) {
			arcs[h][t] = 1;
			arcs[t][h] = 1;
		}
		else {
			edgeWeighted = true;
			ss >> arcs[h][t];
			arcs[t][h] = arcs[h][t];
		}
		arcNum++;
	}
	if (arcNum >= vexNum) hasCircle = true;
}

void MGraph::PrintMatrix() {
	for (int i = 0; i < vexNum; i++) {
		for (int j = 0; j < vexNum; j++) {
			cout << arcs[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
// 这里假设图连通
void MGraph::FindArticul() {
	// 全局计数
	int count = 1;
	// 定义访问过标记数组
	int* visited = new int[vexNum];
	if (visited == NULL) return;
	memset(visited, 0, sizeof(int) * vexNum);
	// 定义low数组
	int* low = new int[vexNum];
	if (low == NULL) return;
	memset(low, 0, sizeof(int) * vexNum);

	// 第一个结点vexs[0]已经访问
	visited[0] = 1;
	int v = -1;
	v++;
	while (v < vexNum && arcs[0][v] == 0) v++;
	DFSArticul(v, count, visited, low);
	if (count < vexNum) {
		// 说明生成树中至少有两棵子树，这时根vexs[0]是割顶
		Articul.push_back(0);
		// 继续访问其他子树
		v++;
		while (v < vexNum && arcs[0][v] == 0) v++;
		DFSArticul(v, count, visited, low);
	}
	// 对割顶进行排序
	sort(Articul.begin(), Articul.end(), less<int>());
}

void MGraph::DFSArticul(int v0, int& count, int* visited, int* low) {
	// 状态类
	class State {
	public:
		int v;
		int w;
		int min;
		State(int v, int w, int min) : v(v), w(w), min(min) {};
	};

	stack<State*> DFSStack;
	int w = -1;
	DFSStack.push(new State(v0, w, count+1));
	visited[v0] = ++count;

	State* s = DFSStack.top();
	while (!DFSStack.empty()) {
		s = DFSStack.top();
		// 找下一个邻顶（生成树的孩子）
		s->w++;
		while (s->w < vexNum && arcs[s->v][s->w] == 0) s->w++;
		if (s->w >= vexNum) {
			// 则说明所有孩子都访问过了，应pop
			// pop前设置好low
			low[s->v] = s->min;
			DFSStack.pop();
			if (DFSStack.empty())
				return;
			delete s;
			// 对前面的结果进行一些处理，更新min值或确认割顶
			s = DFSStack.top();
			if (low[s->w] < s->min) s->min = low[s->w];
			if (low[s->w] >= visited[s->v]) {
				bool isIn = false;
				for (auto a : Articul) {
					if (a == s->v) {
						isIn = true;
						break;
					}
				}
				if(!isIn) Articul.push_back(s->v);
			}
			continue;
		}
		if (!visited[s->w]) {
			// 如果没被访问过，则访问它
			State* nexts = new State(s->w, -1, -1);
			visited[nexts->v] = nexts->min = ++count;
			DFSStack.push(nexts);
			continue;
		}
		else if (visited[s->w] < s->min) {
			// 否则，尝试修改s->min（如果需要）
			s->min = visited[s->w];
		}
	}
}

void MGraph::FindMaxCircle() {
	for (int k = 0; k < vexNum; k++) {
		memset(visited, 0, sizeof(int) * vexNum);
		FindMaxCircleThrough(k, k, 0, new vector<int>);
	}
}

void MGraph::PrintMaxCircle()
{
	if (hasCircle) {
		cout << maxWeight << endl << maxCircle[0];
		int vsize = maxCircle.size();
		for (int i = 1; i < vsize; i++) {
			cout << "->" << maxCircle[i];
		}
		cout << "->" << maxCircle[0] << endl;
	}
	else {
		cout << "没有圈" << endl;
	}
}

void MGraph::PrintArticul() {
	for (auto e : Articul) {
		cout << e << ' ';
	}
	cout << endl;
}

void MGraph::PrintGraphvizCode() {
	if (!edgeWeighted) {
		// 非带权图
		cout << "graph g {" << endl;
		for (int i = 0; i < vexNum; i++) {
			for (int j = i; j < vexNum; j++) {
				if (arcs[i][j] != 0) {
					cout << "\t" << i << "--" << j << endl;
				}
			}
		}
		cout << "}" << endl;
	}
	else {
		// 带权图
		cout << "graph g {" << endl;
		for (int i = 0; i < vexNum; i++) {
			int a1 = -1;
			int a2 = -1;
			for (int k = 0; k < maxCircle.size(); k++) {
				// 确定k是否是最大圈路径上的顶，如果是，用a1,a2记录其邻顶。
				if (maxCircle[k] == i) {
					a1 = k == maxCircle.size() - 1 ? maxCircle[0] : maxCircle[k + 1];
					a2 = k == 0 ? maxCircle[maxCircle.size() - 1] : maxCircle[k - 1];
					break;
				}
			}
			for (int j = i; j < vexNum; j++) {
				if (arcs[i][j] != 0) {
					// 带颜色考虑的输出
					cout << "\t" << i << "--" << j
						<< "[label = \"" << arcs[i][j] << "\""
						<< ", color = \"" << (j == a1 || j == a2 ? "red" : "black") << "\"]" << endl;
				}
			}
		}
		cout << "}" << endl;;
	}
}

int main()
{
	MGraph mg("optional_input1.txt");
	mg.FindArticul();
	mg.PrintArticul();
	mg.FindMaxCircle();
	mg.PrintMaxCircle();
	mg.PrintGraphvizCode();
}