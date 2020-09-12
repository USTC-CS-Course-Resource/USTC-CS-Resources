#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#pragma once

using namespace std;

class ExpressionTree {
private:
	//由波兰表达式建树
	ExpressionTree* createTree_P(stringstream& ss, ExpressionTree* t);
	//由逆波兰表达式建树
	ExpressionTree* createTree_IP(stringstream& ss, ExpressionTree* t);
public:
	string op = IMAGE_NODE; //结点的运算符（若为运算符）
	string operand; //结点的数值（若为数）
	bool isOperand = false;
	ExpressionTree* left = nullptr, * right = nullptr;
	const string IMAGE_NODE = "#";
	bool isValueGetted = false;
	int value; //子树值

	//通过data和是否是操作数来创建一个结点
	ExpressionTree(string data, bool isOperand);
	//by为1则通过波兰表达式建树，by为0则通过逆波兰表达式建树
	ExpressionTree(string polish, int by);

	//打印中缀表达式
	static void printInfixExpression(ExpressionTree* t);
	//打印波兰表达式
	static void printPolishExpression(ExpressionTree* t);
	//打印逆波兰表达式
	static void printInversePolishExpression(ExpressionTree* t);
	//计算各子树的值
	static int getValue(ExpressionTree* t);
};

ExpressionTree::ExpressionTree(string data, bool isOperand) {
	this->isOperand = isOperand;
	if (isOperand) {
		operand = data;
		stringstream ss(data);
		ss >> value;
		isValueGetted = true;
	}
	else {
		isValueGetted = false;
		op = data[0];
	}
}

ExpressionTree* ExpressionTree::createTree_P(stringstream& ss, ExpressionTree* t) {
	string polish;
	ss >> polish;
	if (polish[0] == '+' || polish[0] == '-'
		|| polish[0] == '*' || polish[0] == '/') {
		if (t != this)
			t = new ExpressionTree(polish, false);
		else {
			t->isOperand = false;
			t->isValueGetted = false;
			t->op = polish[0];
		}
		if (!ss.eof()) {
			t->left = createTree_P(ss, t->left);
			t->right = createTree_P(ss, t->right);
		}
	}
	else {
		t = new ExpressionTree(polish, true);
	}
	return t;
}

ExpressionTree* ExpressionTree::createTree_IP(stringstream& ss, ExpressionTree* t) {
	string polish;
	ss >> polish;
	if (polish[0] == '+' || polish[0] == '-'
		|| polish[0] == '*' || polish[0] == '/') {
		if (t != this)
			t = new ExpressionTree(polish, false);
		else {
			t->isOperand = false;
			t->isValueGetted = false;
			t->op = polish[0];
		}
		if (!ss.eof()) {
			t->right = createTree_IP(ss, t->right);
			t->left = createTree_IP(ss, t->left);
		}
	}
	else {
		t = new ExpressionTree(polish, true);
	}
	return t;
}

ExpressionTree::ExpressionTree(string polish, int by) {
	if (by) {
		stringstream ss(polish);
		createTree_P(ss, this);
	}
	else {
		int len = polish.length();
		stringstream ss(polish);
		string inversed;
		while (!ss.eof()) {
			string temp;
			ss >> temp;
			inversed = temp + " " + inversed;
		}
		stringstream iss(inversed);
		createTree_IP(iss, this);
	}
}

void ExpressionTree::printInfixExpression(ExpressionTree* t) {
	if (t != nullptr) {
		//处理左子树
		if (t->left->isOperand) {
			cout << t->left->operand;
		}
		else {
			if ((t->left->op == "+" || t->left->op == "-")
				&& (t->op == "*" || t->op == "/")) {
				cout << '(';
				printInfixExpression(t->left);
				cout << ')';
			}
			else
				printInfixExpression(t->left);
		}

		//处理当前结点
		if (t->isOperand) {
			cout << t->operand;
		}
		else {
			cout << t->op;
		}

		//处理右子树
		if (t->right->isOperand) {
			cout << t->right->operand;
		}
		else {
			if ((t->right->op == "*" || t->right->op == "/")
				&& (t->op == "+" || t->op == "-")) {
				printInfixExpression(t->right);
			}
			else {
				cout << '(';
				printInfixExpression(t->right);
				cout << ')';
			}
		}
	}
}

void ExpressionTree::printPolishExpression(ExpressionTree* t)
{
	if (t != nullptr) {
		if (t->isOperand)
			cout << t->operand << ' ';
		else
			cout << t->op << ' ';
		printPolishExpression(t->left);
		printPolishExpression(t->right);
	}
}

void ExpressionTree::printInversePolishExpression(ExpressionTree* t)
{
	if (t != nullptr) {
		printInversePolishExpression(t->left);
		printInversePolishExpression(t->right);
		if (t->isOperand)
			cout << t->operand << ' ';
		else
			cout << t->op << ' ';
	}
}

int ExpressionTree::getValue(ExpressionTree* t) {
	if (t->isValueGetted)
		return t->value;
	else {
		if (t->op == "+") {
			t->value = getValue(t->left) + getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
		else if (t->op == "-") {
			t->value = getValue(t->left) - getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
		else if (t->op == "*") {
			t->value = getValue(t->left) * getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
		else if (t->op == "/") {
			t->value = getValue(t->left) / getValue(t->right);
			t->isValueGetted = true;
			return t->value;
		}
	}
}


