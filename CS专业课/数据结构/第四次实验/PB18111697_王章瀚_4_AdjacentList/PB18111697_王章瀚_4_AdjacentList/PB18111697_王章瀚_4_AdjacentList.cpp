// PB18111697_王章瀚_4_AdjacentList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <string>
#include <queue>
#include <stack>

using namespace std;

// 弧结点类。认为弧权均为1，故不设多余信息成员变量
class ArcNode {
public:
	int adjVex; // 该弧指向的顶点索引
	ArcNode* nextArc; // 指向下一条弧

	ArcNode(int av, ArcNode* na) : adjVex(av), nextArc(na) {};
};

// 顶类。
class VNode {
public:
	int index; // 顶点序号
	ArcNode* firstArc; //第一条邻边

	// 默认构造方法
	VNode() : index(-1), firstArc(nullptr) {};
	// 由序号和第一条邻边构造顶
	VNode(int index, ArcNode* fa) : index(index), firstArc(fa) {};
	// 添加一条关联边
	void addAdjArc(ArcNode* arcnode);
};

class ALGraph {
public:
	VNode* vexs; //顶
	int vexNum = 0, arcNum = 0; //顶数，边数
	int* distance = NULL; // 由Dijkstra算法得到的最短路径距离
	int* front = NULL; // 由Dijkstra算法得到的前驱结点

	// 构造函数：通过文件名构造
	ALGraph(string fileName);
	// Dijkstra算法实现
	void ShortestPath_DIJ();
	// 通过front数组来寻找到0的最短路径
	void printShortestPath(int i);
	// 通过front数组来寻找到0的最短路径
	void printAllShortestPath();
	// 打印邻接表
	void printAdjacentList();
};

void VNode::addAdjArc(ArcNode* arcnode)
{
	if (firstArc == NULL) {
		firstArc = arcnode;
		return;
	}
	ArcNode* p = firstArc;
	while (p->nextArc != NULL) p = p->nextArc;
	p->nextArc = arcnode;
	return;
}

void ALGraph::ShortestPath_DIJ()
{
	// 一些初始化
	bool* defined = new bool[vexNum];
	for (int i = 0; i < vexNum; i++) {
		distance[i] = INT_MAX;
		defined[i] = false;
	}
	// 先考虑0顶
	int v = 0;
	ArcNode* an = vexs[v].firstArc;
	while (an != NULL) {
		distance[an->adjVex] = 1;
		front[an->adjVex] = v;
		an = an->nextArc;
	}
	// 遍历所有顶
	for (int i = 0; i < vexNum; i++) {
		int minD = INT_MAX;
		// 找最短路径顶
		for (int j = 0; j < vexNum; j++) {
			if (!defined[j]) {
				if (distance[j] < minD) {
					v = j; minD = distance[j];
				}
			}
		}
		defined[v] = true;
		// 更新最短路径
		an = vexs[v].firstArc;
		while (an != NULL) {
			if (distance[an->adjVex] > minD + 1) {
				distance[an->adjVex] = minD + 1;
				front[an->adjVex] = v;
			}
			an = an->nextArc;
		}
	}
}

ALGraph::ALGraph(string fileName) {
	fstream fs(fileName, ios::in | ios::out);
	// 读入顶点数
	string line;
	fs >> vexNum;
	getline(fs, line);
	// 分配顶点的空间
	vexs = new VNode[vexNum];
	if (vexs == NULL) return;
	for (int i = 0; i < vexNum; i++) {
		vexs[i].index = i;
	}
	// 分配distance空间
	distance = new int[vexNum];
	if (distance == NULL) return;
	memset(distance, 0, sizeof(int) * vexNum);
	// 分配front空间
	front = new int[vexNum];
	if (front == NULL) return;
	memset(front, 0, sizeof(int) * vexNum);

	// 读入数据
	while (!fs.eof()) {
		getline(fs, line);
		stringstream ss(line);
		int h, t;
		ss >> h >> t;
		vexs[h].addAdjArc(new ArcNode(t, nullptr));
		vexs[t].addAdjArc(new ArcNode(h, nullptr));
		arcNum++;
	}
}

void ALGraph::printShortestPath(int i)
{
	int t = i;
	stack<int> s;
	while (t != 0) {
		s.push(t);
		t = front[t];
	}
	int ssize = s.size();
	cout << distance[i] << " 0";
	for (int t = 0; t < ssize; t++) {
		cout << "->" << s.top();
		s.pop();
	}
	cout << endl;
}

void ALGraph::printAllShortestPath()
{
	for (int i = 1; i < vexNum; i++) {
		printShortestPath(i);
	}
}

void ALGraph::printAdjacentList()
{
	for (int i = 0; i < vexNum; i++) {
		cout << i << ":";
		ArcNode* p = vexs[i].firstArc;
		while (p != NULL) {
			cout << p->adjVex << " ";
			p = p->nextArc;
		}
		cout << endl;
	}
}



int main()
{
	ALGraph alg("input2.txt");
	alg.ShortestPath_DIJ();
	alg.printAllShortestPath();
}

