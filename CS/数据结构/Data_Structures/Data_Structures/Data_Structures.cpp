// Data_Structures.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include "TestCommand.h"
#include "BiTree.h"
#include "MGraph.h"
#include "Search.h"
#include "Sort.h"

using namespace std;

int main()
{
	//Test for Sort.h
	Print_Title("Test for Sort.h");
	QSort_Sub(SortSpace::TestList, 0, 10);
	Print_End();

	//Test for Search.h
	Print_Title("Test for Search.h");
	cout << Fibonacci_Search<int>(SearchSpace::TestList, 7, 3) << endl;
	Print_End();

	//Test for BiTree
	Print_Title("Test for BiTree.h");
	BiTree* t = &BiTree(BiTreeSpace::Test1);
	cout << "先序遍历：\n\t";
	BiTree::PreOrderTraverse(t, BiTree::printTree);
	cout << endl << endl;
	cout << "中序遍历：\n\t";
	BiTree::InOrderTraverse(t, BiTree::printTree);
	cout << endl << endl;
	cout << "后序遍历：\n\t";
	BiTree::PostOrderTraverse(t, BiTree::printTree);
	cout << endl << endl;
	t->PostOrderThreading(t);
	cout << "利用线索的后序遍历：\n\t";
	t->PostOrderThreadingTraverse(BiTree::printTree);
	Print_End();

	//Test for MGraph.h
	Print_Title("Test for MGraph.h");
	MGraph mg("optional_graph1.txt");
	mg.FindArticul();
	mg.PrintArticul();
	mg.FindMaxCircle();
	mg.PrintMaxCircle();
	mg.PrintGraphvizCode();
	Print_End();
}