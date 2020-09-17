#include<stdio.h>

int main(){
	int n = 1, i;
	for(i = 0; i < 9; i++)
	{
		n = (n + 1)*2; 
	}
	printf("第一天共摘了%d个桃子", n);
	return 0;
}
