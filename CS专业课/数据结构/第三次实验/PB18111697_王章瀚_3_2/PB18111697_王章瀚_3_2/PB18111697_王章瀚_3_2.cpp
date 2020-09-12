// PB18111697_王章瀚_3_2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <sstream>
#include "ExpressionTree.h"

using namespace std;

int main()
{
	string polish;
	getline(cin, polish);
	ExpressionTree* t = new ExpressionTree(polish, 1); //为0则波兰表达式，1则逆波兰
	cout << "波兰表达式：\n\t";
	ExpressionTree::printPolishExpression(t);
	cout << endl << endl;
	cout << "中缀表达式：\n\t";
	ExpressionTree::printInfixExpression(t);
	cout << endl << endl;
	cout << "逆波兰表达式：\n\t";
	ExpressionTree::printInversePolishExpression(t);
	cout << endl << endl;
	cout << "表达式值：\n\t" << ExpressionTree::getValue(t) << endl;
	return 0;
}

//测试数据
// 2 30 5 * +
// + 2 * 30 5

// 15 5 2 18 + * + 5 /
// / + 15 * 5 + 2 18 5

//15 2 7 - / 10 -
// - / 15 - 2 7 10

