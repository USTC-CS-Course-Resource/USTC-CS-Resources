#include "pch.h"
#include <iostream>

using namespace std;

template <class ElemType>
class DulNode {
public:
	ElemType data;
	DulNode *pre, *next;
	int freq;
	DulNode(ElemType x) {
		data = x;
		freq = 0;
		pre = nullptr;
		next = nullptr;
	}
	DulNode(ElemType *A, int len) {
		DulNode *p = this;
		pre = nullptr;
		for (int i = 0; i < len; i++) {
			p->next = new DulNode(A[i]);
			p->next->pre = p;
			p = p->next;
		}
	}
	DulNode* Locate(ElemType x) {
		DulNode *p = this->next;
		while (p != nullptr) {
			if (p->data == x) {
				p->freq++;
				break;
			}
			p = p->next;
		}
		if (p != nullptr) {
			DulNode *toInsert = p->pre;
			while (toInsert != nullptr) {
				if (toInsert->freq >= p->freq || toInsert->pre == nullptr) {
					p->pre->next = p->next;
					p->next->pre = p->pre;
					p->next = toInsert->next; 
					p->pre = toInsert;
					toInsert->next->pre = p;
					toInsert->next = p;
					break;
				}
				toInsert = toInsert->pre;
			}
		}
		return p;
	}

	void printList() {
		DulNode *p = this->next;
		while (p != nullptr) {
			cout << p->data << '(' << p->freq << ')' << ' ';
			p = p->next;
		}
		cout << endl;
	}
};

int main()
{
	int a[15] = { 2, 3, 5, 6, 7, 8, 9, 10, 13, 14, 17, 18, 19, 21, 22};
	DulNode<int> *A = new DulNode<int>(a, 15);
	A->printList();
	A->Locate(6); A->printList();
	A->Locate(7); A->printList();
	A->Locate(7); A->printList();
	A->Locate(10); A->printList();
	A->Locate(13); A->printList();
	A->Locate(13); A->printList();
	A->Locate(13); A->printList();
	A->Locate(8); A->printList();
	A->Locate(18); A->printList();
	A->Locate(18); A->printList();
	A->Locate(18); A->printList();
	A->Locate(18); A->printList();
	A->Locate(18); A->printList();
}