#include "pch.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;
const int LIST_INIT_SIZE = 100;
template <class ElemType>
class SqList {
public:
	ElemType *elem;
	int length; //当前长度
	int listsize;
	SqList(ElemType* a, int len) {
		length = len;
		listsize = LIST_INIT_SIZE;
		elem = new ElemType[listsize];
		for (int i = 0; i < len; i++) {
			elem[i] = a[i];
		}
	}
	~SqList() {
		delete elem;
	}

	void interWith(const SqList &B) {
		int i = 0, j = 0, insertTo = 0, last = -1;
		while (i < length && j < B.length) {
			while (elem[i] > B.elem[j] && j < B.length) j++;
			if (elem[i] == B.elem[j]) {
				if (last == -1 || elem[last] != elem[i])
					elem[insertTo++] = elem[i];
				last = i;
			}
			i++;
		}
		length = insertTo;
	}

	void printSqList() {
		for (int i = 0; i < length; i++) {
			cout << elem[i] << ' ';
		}
		cout << endl;
	}
};

int main()
{
	int a[13] = { 1, 3, 5, 6, 6, 7, 7, 13, 14, 14, 14, 18, 19};
	int b[15] = { 2, 3, 3, 6, 6, 7, 7, 10, 10, 12, 13, 13, 14, 17, 18};
	SqList<int> A = *new SqList<int>(a, 13);
	SqList<int> B = *new SqList<int>(b, 15);
	A.printSqList();
	B.printSqList();

	A.interWith(B);
	A.printSqList();
	

}