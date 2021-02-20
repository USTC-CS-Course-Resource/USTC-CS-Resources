// PB18111697_王章瀚_3.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "BTreeNode.h"
using namespace std;

void printTree(BTreeNode* t)
{
	if(t != nullptr)
		cout << t->data;
}

int main()
{
	//Test for BiTree
	//测试数据
	//AB#C#D##E##
	//A#BC##DE##F##
	//ABCD##E##F###
	string input;
	cin >> input;
	BTreeNode* t = &BTreeNode(input);
	cout << "先序遍历：\n\t";
	BTreeNode::PreOrderTraverse(t, printTree);
	cout << endl << endl;
	cout << "中序遍历：\n\t";
	BTreeNode::InOrderTraverse(t, printTree);
	cout << endl << endl;
	cout << "后序遍历：\n\t";
	BTreeNode::PostOrderTraverse(t, printTree);
	cout << endl << endl;
	t->PostOrderThreading(t);
	cout << "利用线索的后序遍历：\n\t";
	t->PostOrderThreadingTraverse(printTree);
	cout << endl << endl;
}

//测试数据
//AB#C#D##E##
//A#BC##DE##F##
//ABCD##E##F###