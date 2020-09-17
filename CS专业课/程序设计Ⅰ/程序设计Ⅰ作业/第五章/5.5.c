#include<stdio.h>
#include<math.h>
#include<stdlib.h>

int main()
{
	int i, n, sum, a;
	sum = 0;
	printf("请输入a: ");
	scanf("%d", &a);
	if(a < 0 || a > 9){
		printf("输入的a不是0到9的数字。");
		exit(-1);
	}
	printf("请输入n："); 
	scanf("%d", &n);
	if(!(n >= 1)){
		printf("输入的n不是正整数。");
		exit(-1);
	} 
	
	for(i = 0; i < n; i++)
	{
		sum += (n-i)*a*pow(10,i);//拆成n个a*10^i相加 
	}
	printf("S[n] = %d", sum);
	
	return 0;
}
