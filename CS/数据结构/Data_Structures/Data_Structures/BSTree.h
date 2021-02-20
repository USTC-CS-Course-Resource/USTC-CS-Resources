/*
 * BSTree: for Balance Searching Tree.
 */

#pragma once

#include <iostream>

#define LH +1
#define EH 0
#define RH -1

class BSTree {
public:
	int key;
	int bf;
	BSTree *left, *right;
	BSTree() : key(0), bf(0), left(nullptr), right(nullptr) {};
	BSTree(int key, int bf, BSTree* left, BSTree* right) : key(key), bf(bf), left(left), right(right) {};
};

void R_Rotate(BSTree *&p) {
	BSTree *lc = p->left;
	p->left = lc->right;
	lc->right = p;
	p = lc;
}

void L_Rotate(BSTree *&p) {
	BSTree* rc = p->right;
	p->right = rc->left;
	rc->left = p;
	p = rc;
}

void RightBalance(BSTree*& T) {
	BSTree* rc = T->right;
	switch (rc->bf) {
	case RH:
		T->bf = rc->bf = EH;
		L_Rotate(T); break;
	case LH:
		BSTree *rlc = rc->left;
		switch (rlc->bf) {
		case RH: T->bf = LH; rc->bf = EH; break;
		case EH: T->bf = rc->bf = EH; break;
		case LH: T->bf = EH; rc->bf = RH; break;
		}
		rlc->bf = EH;
		R_Rotate(T->right);
		L_Rotate(T);
	}
}

void LeftBalance(BSTree *&T) {
	BSTree *lc = T;
	switch (lc->bf) {
	case LH:
		T->bf = lc->bf = EH;
		R_Rotate(T); break;
	case RH:
		BSTree *lrc = lc->right;
		switch (lrc->bf) {
		case LH: T->bf = RH; lc->bf = EH; break;
		case EH: T->bf = lc->bf = EH; break;
		case RH: T->bf = EH; lc->bf = LH; break;
		
		}
		lrc = EH;
		L_Rotate(T->left);
		R_Rotate(T);
	}
}

bool InsertAVL(BSTree *&T, int key, bool& taller) {
	if (!T) {
		T = new BSTree(key, EH, nullptr, nullptr);
	}
	else {
		if (key == T->key) {
			taller = false; return false;
		}
		if (key < T->key) {
			InsertAVL(T->left, key, taller);
			if (taller) {
				switch (T->bf) {
				case LH: 
					LeftBalance(T); taller = false; break;
				case EH:
					T->bf = LH; taller = true; break;
				case RH:
					T->bf = EH; taller = false; break;
				default: 
					break;
				}
			}
		}
		else if (key > T->key) {
			InsertAVL(T->right, key, taller);
			if (taller) {
				switch (T->bf) {
				case RH:
					RightBalance(T); taller = false; break;
				case EH:
					T->bf = RH; taller = true; break;
				case LH:
					T->bf = EH; taller = false; break;
				default:
					break;
				}
			}
		}
	}
	return true;
}