/*
 * for Search Algorithm.
 */

#pragma once

#include <iostream>

namespace SearchSpace {
	int TestList[] = { 1,2,3,4,5,6,7,8,9 };
}

template<class T>
int Fibonacci_Search(T* Tlist, int len, T key) {
	static int f_array[] = { 1, 1, 2, 3, 5, 8, 13, 21, 35, 56 };
	int start = 0, end = len - 1, middle;
	int cur = -1;
	for (int i = 0; i < 10; i++) {
		if (f_array[i]-1 == len) {
			cur = i;
			break;
		}
	}
	if (cur == -1) return -1;
	while (start <= end) {
		middle = start + f_array[cur - 2] - 1;
		if ((cur == 0 || cur == 1) && Tlist[middle] != key) return -1;
		if (Tlist[middle] == key) return middle;
		else if (Tlist[middle] < key) {
			start = middle + 1;
			cur = cur - 1;
		}
		else if (Tlist[middle] > key) {
			end = middle - 1;
			cur = cur - 2;
		}
	}
	return -1;
}