#include<stdio.h>
#include<stdlib.h>
#define n 10

int main()
{
	//共n-1个数 将插入到n个 
	int i = 0, j = n-1,order = -1;//order为0表示逆序，为1表示顺序 ,为-1表示未确定 
	float x;
	float a[n] = {10,9,9,6,5,4,3,2,1};//题目未描述清楚已知数组，此处自定义一个 
	printf("请输入将要插入的数: ");
	scanf("%f", &x);
	
	//确定是否为逆序 
	order = 0;
	for(i = 0; i < n-2; i++)
	{
		if(a[i] < a[i+1]) 
		{
			order = -1;
			break; 
		}
	} 
	if(order == -1)//此时不为逆序，判断是否为顺序 
	{
		order = 1;
		for(i = 0; i < n-2; i++)
		{
			if(a[i] > a[i+1])
			{
				order = -1;
				break;
			}
		}
	} 
	//找到 x应处位置 
	i=0;
	if(order == -1)
	{
		printf("数组未被排序\n");
		exit(-1);
	}else if(order == 1)
	{
		while((j - i)*(j - i) >= 1)
		{
			if(a[(i+j)/2] == x) 
			{
				i = (i + j)/2;
				j = i;
			}
			else if(a[(i+j)/2] > x) j = (i + j)/2-1;
			else i = (i + j)/2+1;
		} 
	}else if(order == 0)
	{
		while((j - i)*(j - i) >= 1)
		{
			if(a[(i+j)/2] == x) 
			{
				i = (i + j)/2;
				j = i;
			}
			else if(a[(i+j)/2] < x) j = (i + j)/2-1;
			else i = (i + j)/2+1;
			printf("i = %d  j = %d\n", i , j);
		} 
	}

	
	//将x应插入处之后的数全部顺延 
	for(i = n-1; i > j; i--)
	{
		a[i] = a[i-1];
	} 
	a[j] = x;
	
	//输出插入结果
	for(i = 0; i < n; i++)
	{
		printf("%f ", a[i]);
		if(i%5 == 4) printf("\n");
	}
	printf("\n");
	
	return 0;
} 
