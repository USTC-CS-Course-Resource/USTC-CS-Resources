#include<stdio.h>
#include<math.h>

int main(){
	double x, y;
	int h;
	printf("请输入点的横坐标： ");
	scanf("%lf", &x); 
	printf("请输入点的纵坐标： ");
	scanf("%lf", &y); 
	h = ( ((fabs(x)-2)*(fabs(x)-2) + (fabs(y)-2)*(fabs(y)-2)) <= 1 ) ? 10 : 0;
	printf("该点建筑高度为： %d", h);
}
