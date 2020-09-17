#include<stdio.h>
int main(){
	int x0, x1, x2, x3, i;
	x0 = 5;
	x1 = 8;
	x2 = 16;
	x3 = 498;
	printf("请输入四个整数(以一个空格分开)：\n");
	scanf("%d %d %d %d", &x0, &x1, &x2, &x3);
	if(x0 > x1){
		i = x1;
		x1 = x0;
		x0 = i;
	}
	if(x1 > x2){
		i = x2;
		x2 = x1;
		x1 = i;
	}
	if(x2 > x3){
		i = x3;
		x3 = x2;
		x2 = i;
	}
	if(x0 > x1){
		i = x1;
		x1 = x0;
		x0 = i;
	}
	if(x1 > x2){
		i = x2;
		x2 = x1;
		x1 = i;
	}
	if(x0 > x1){
		i = x1;
		x1 = x0;
		x0 = i;
	}

	printf("按从小到大的顺序为： %d %d %d %d", x0, x1, x2, x3);
	return 0;
}



