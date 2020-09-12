#include "pch.h"
#include <iostream>

using namespace std;

// 带头结点的链表
template <class ElemType>
class LinkList {
public:
	ElemType data;
	LinkList *next;
	LinkList(ElemType e) {
		data = e;
		next = nullptr;
	}
	LinkList(ElemType *A, int lenA) {
		LinkList *p = this;
		for (int i = 0; i < lenA; i++) {
			p->next = new LinkList(A[i]);
			p = p->next;
		}
	}

	void eraseSame(LinkList *B, LinkList *C) {
		B = B->next;
		C = C->next;
		auto beforeP = this;
		auto p = this->next;
		while (p != nullptr) {
			while (B->data < p->data && B->next != nullptr) B = B->next;
			while (C->data < p->data && C->next != nullptr) C = C->next;
			if (B->data == p->data && C->data == p->data) {
				beforeP->next = p->next;
				delete p;
				p = beforeP->next;
			}
			else {
				beforeP = p;
				p = p->next;
			}
		}
	}

	void printList() {
		LinkList* p = this->next;
		while (p != nullptr) {
			cout << p->data<<' ';
			p = p->next;
		}
		cout << endl;
	}
	
};

int main()
{
	int a[14] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 18 };
	int b[15] = { 2, 3, 3, 5, 6, 6, 6, 7, 10, 12, 13, 13, 14, 17, 18 };
	int c[10] = { 2, 3, 6, 6, 7, 7, 13, 14, 17, 18 };
	LinkList<int> *A = new LinkList<int>(a, 14);
	LinkList<int> *B = new LinkList<int>(b, 15);
	LinkList<int> *C = new LinkList<int>(c, 10);
	A->printList();
	B->printList();
	C->printList();
	A->eraseSame(B, C);
	A->printList();
}