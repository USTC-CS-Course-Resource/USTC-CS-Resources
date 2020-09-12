// 6_2_二叉树.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <queue>
using namespace std;

typedef struct BiTree {
	int data;
	struct BiTree* left;
	struct BiTree* right;
} BiTree;

void InitBitree(BiTree& T);
void DestroyBiTree(BiTree& T);
// void CreateBiTree(BiTree& T, definition); // I am not sure what it is now.
void ClearBiTree(BiTree& T);
bool BiTreeEmpty(BiTree& T);
// int BiTreeDepth(BiTree& T);
BiTree& Root(BiTree& T);
int Value(BiTree& e);
void Assign(BiTree& e, int value);
BiTree* Parent(BiTree& T, BiTree& e);
BiTree* LeftChild(BiTree& e);
BiTree* RightChild(BiTree& e);
BiTree* LeftSibling(BiTree& T, BiTree& e);
BiTree* RightSibling(BiTree& T, BiTree& e);
void InsertChild(BiTree& p, bool LR, BiTree& c);
void DeleteChild(BiTree& p, bool LR);
void PreOrderTraverse(BiTree& T, void Visit(BiTree& T));
void InOrderTraverse(BiTree& T, void Visit(BiTree& T));
void PostOrderTraverse(BiTree& T, void Visit(BiTree& T));
void LevelOrderTraverse(BiTree& T, void Visit(BiTree& T));

// Initialize a BiTree.
void InitBitree(BiTree& T) {
	T.data = 0;
	T.left = NULL;
	T.right = NULL;
}

// Destroy the BiTree T by recursion.
void DestroyBiTree(BiTree& T) {
	if (T.left != NULL) {
		DestroyBiTree(*T.left);
	}
	if (T.right != NULL) {
		DestroyBiTree(*T.right);
	}
	if (T.left == NULL && T.right == NULL) {
		free(&T);
		return;
	}
}

// Clear a T into a NULL BiTree
void ClearBiTree(BiTree& T) {
	DestroyBiTree(*T.left);
	DestroyBiTree(*T.right);
	T.left = NULL; T.right = NULL;
}

// return whether BiTree T is empty.
bool BiTreeEmpty(BiTree& T) {
	return T.left == NULL && T.right == NULL && T.data == 0;
}

// return the root of T.
BiTree& Root(BiTree& T) {
	return T;
}

// return the data of e.
int Value(BiTree& e) {
	return e.data;
}

// Assign the data of e as value.
void Assign(BiTree& e, int value) {
	e.data = value;
}

// return the Parent of e in T.
BiTree* Parent(BiTree& T, BiTree& e) {
	BiTree* p;
	if (&T == &e)
		return &T;
	if (T.left != NULL) {
		p = Parent(*T.left, e);
		if (p != NULL) return p;
	}
	if (T.right != NULL) {
		p = Parent(*T.right, e);
		if (p != NULL) return p;
	}
	return NULL;
}

// return the left child of e.
BiTree* LeftChild(BiTree& e) {
	return e.left;
}

// return the right child of e.
BiTree* RightChild(BiTree& e) {
	return e.right;
}

BiTree* LeftSibling(BiTree& T, BiTree& e) {
	BiTree* p = Parent(T, e);
	if (p->left == &e) {
		return NULL;
	}
	else {
		return p->left;
	}
}

BiTree* RightSibling(BiTree& T, BiTree& e) {
	BiTree* p = Parent(T, e);
	if (p->right == &e) {
		return NULL;
	}
	else {
		return p->right;
	}
}

void InsertChild(BiTree& p, bool LR, BiTree& c) {
	if (LR) {
		p.left = &c;
	}
	else {
		p.right = &c;
	}
}

void DeleteChild(BiTree& p, bool LR) {
	if (LR) {
		DestroyBiTree(*(p.left));
		p.left = NULL;
	}
	else {
		DestroyBiTree(*(p.right));
		p.right = NULL;
	}
}

void PreOrderTraverse(BiTree& T, void Visit(BiTree& T)) {
	Visit(T);
	if (T.left != NULL)
		PreOrderTraverse(*T.left, Visit);
	if (T.right != NULL)
		PreOrderTraverse(*T.right, Visit);
}

void InOrderTraverse(BiTree& T, void Visit(BiTree& T)) {
	if (T.left != NULL)
		PreOrderTraverse(*T.left, Visit);
	Visit(T);
	if (T.right != NULL)
		PreOrderTraverse(*T.right, Visit);
}

void PostOrderTraverse(BiTree& T, void Visit(BiTree& T)) {
	if (T.left != NULL)
		PreOrderTraverse(*T.left, Visit);
	if (T.right != NULL)
		PreOrderTraverse(*T.right, Visit);
	Visit(T);
}

void LevelOrderTraverse(BiTree& T, void Visit(BiTree& T)) {
	queue<BiTree*> BTQ;
	BTQ.push(&T);
	while (BTQ.size()) {
		int size = BTQ.size();
		for (int i = 0; i < size; i++) {
			BiTree* cur = BTQ.front();
			BTQ.pop();
			Visit(*cur);
			if (cur->left != NULL) {
				BTQ.push(cur->left);
			}
			if (cur->right != NULL) {
				BTQ.push(cur->right);
			}
		}	
	}
}


int main()
{
	BiTree T[5];
	for (int i = 0; i < 5; i++) {
		InitBitree(T[i]);
		Assign(T[i], i + 1);
	}
	InsertChild(T[0], true, T[1]);
	InsertChild(T[1], false, T[2]);
	InsertChild(T[0], false, T[3]);
	InsertChild(T[3], true, T[4]);
	BiTree* parent = Parent(T[0], T[3]);

}
