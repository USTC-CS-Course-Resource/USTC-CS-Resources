#pragma once

#include  <iostream>

namespace SortSpace {
	int TestList[] = { 6,9,8,7,6,9,2,4,3,1,5 };
}

template<class T>
int QSort_Sub(T L[], int low, int high) {
	int i = low, j = high;
	while (i < j) {
		while (i < j && L[j] >= L[i]) j--;
		T temp = L[j];
		L[j] = L[i];
		L[i] = temp;
		while (i < j && L[j] >= L[i]) i++;
		temp = L[j];
		L[j] = L[i];
		L[i] = temp;
	}
	for (int i = low; i <= high; i++) {
		cout << L[i] << ' ';
	}
	cout << endl;
	for (int j = low; j < i; j++) {
		cout << ' ' << ' ';
	}
	cout << "¡ü" << endl;
	return i;
}