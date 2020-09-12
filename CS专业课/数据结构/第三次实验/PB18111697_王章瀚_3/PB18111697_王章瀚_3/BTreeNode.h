#include <iostream>
#include <string>
#include <queue>
#pragma once

using namespace std;

class BTreeNode {
private:
	BTreeNode* pre = nullptr; //前一个遍历的结点
public:
	static const char IMAGE_NODE = '#'; //表示虚节点的字符
	char data;
	BTreeNode* left = nullptr, * right = nullptr, * parent = nullptr;
	bool LTag, RTag;

	//构建一个结点，其中数据为data，左、右、双亲节点为left, right, parent
	BTreeNode(char data, BTreeNode* left, BTreeNode* right, BTreeNode* parent);
	//参数为题述字符串，构建对应树
	BTreeNode(string layerIter);
	//先序遍历
	static void PreOrderTraverse(BTreeNode* t, void function(BTreeNode*));
	//中序遍历
	static void InOrderTraverse(BTreeNode* t, void function(BTreeNode*));
	//后序遍历
	static void PostOrderTraverse(BTreeNode* t, void function(BTreeNode*));
	//后序线索化子程序
	void PostThreading(BTreeNode* t);
	//后序线索化
	void PostOrderThreading(BTreeNode* t);
	//利用后序线索化的遍历
	void PostOrderThreadingTraverse(void function(BTreeNode*));
};


BTreeNode::BTreeNode(char data, BTreeNode* left, BTreeNode* right, BTreeNode* parent)
	: data(data), left(left), right(right), parent(parent),
	LTag(false), RTag(false) {};

BTreeNode::BTreeNode(string layerIter) : LTag(false), RTag(false) {
	if (layerIter[0] == IMAGE_NODE) {
		data = IMAGE_NODE;
		cout << "Not a tree!" << endl;
	}
	else {
		//先做好根节点
		data = layerIter[0];
		queue<BTreeNode*> lastLayer;
		lastLayer.push(this);
		int nodeNum = 2;
		int index = 1;
		int strlen = layerIter.length();
		//用index逐一访问字符串layerIter
		while (index < strlen) {
			int qSize = lastLayer.size();
			for (int i = 0; i < qSize; i++) {
				BTreeNode* curNode = lastLayer.front();
				lastLayer.pop();
				if (layerIter[index] != IMAGE_NODE) {
					//如果下一个字符不表示虚节点
					curNode->left =
						new BTreeNode(layerIter[index], nullptr, nullptr, curNode);
					lastLayer.push(curNode->left);
				}
				else //否则是虚节点
					curNode->left = nullptr;
				index++;
				if (layerIter[index] != IMAGE_NODE) {
					//如果下一个字符不表示虚节点
					curNode->right =
						new BTreeNode(layerIter[index], nullptr, nullptr, curNode);
					lastLayer.push(curNode->right);
				}
				else //否则是虚节点
					curNode->right = nullptr;
				index++;
			}
		}
	}
};

void BTreeNode::PreOrderTraverse(BTreeNode* t, void function(BTreeNode*)) {
	if (t != nullptr)
	{
		function(t);
		if (t->LTag == 0)
			PreOrderTraverse(t->left, function);
		if (t->RTag == 0)
			PreOrderTraverse(t->right, function);
	}
}

void BTreeNode::InOrderTraverse(BTreeNode* t, void function(BTreeNode*)) {
	if (t != nullptr)
	{
		if (t->LTag == 0)
			InOrderTraverse(t->left, function);
		function(t);
		if (t->RTag == 0)
			InOrderTraverse(t->right, function);
	}
}

void BTreeNode::PostOrderTraverse(BTreeNode* t, void function(BTreeNode*)) {
	if (t != nullptr)
	{
		if (t->LTag == 0)
			PostOrderTraverse(t->left, function);
		if (t->RTag == 0)
			PostOrderTraverse(t->right, function);
		function(t);
	}
}

void BTreeNode::PostThreading(BTreeNode* t) {
	if (t == nullptr)
		return;
	//对左子树线索化
	PostThreading(t->left);
	//对右子树线索化
	PostThreading(t->right);
	//对本结点和pre线索化
	if (t->left == nullptr) {
		t->left = pre;
		t->LTag = true;
	}
	if (pre != nullptr && pre->right == nullptr) {
		pre->RTag = true;
		pre->right = t;
	}
	pre = t;
}

void BTreeNode::PostOrderThreading(BTreeNode* t) {
	PostThreading(t);
	if (pre != nullptr && pre->right == nullptr) {
		pre->RTag = true;
		pre->right = t;
	}
}

void BTreeNode::PostOrderThreadingTraverse(void function(BTreeNode*)) {
	BTreeNode* temp = this;
	// 找后序遍历的第一个结点
	while (!temp->LTag || !temp->RTag) {
		while (!temp->LTag)
			temp = temp->left;
		while (!temp->RTag)
			temp = temp->right;
	}
	function(temp);

	while (temp != nullptr && temp->parent != nullptr) {
		//如果该结点是双亲结点的右孩子或双亲节点没有右孩子
		if (temp->parent->right == temp
			|| temp->parent->RTag) {
			temp = temp->parent;
		}
		else {
			//否则后继结点是双亲节点的右子树中后序遍历第一个结点
			temp = temp->parent->right;
			// 找后序遍历的第一个结点
			while (!temp->LTag || !temp->RTag) {
				while (!temp->LTag)
					temp = temp->left;
				while (!temp->RTag)
					temp = temp->right;
			}
		}
		function(temp);
	}
}