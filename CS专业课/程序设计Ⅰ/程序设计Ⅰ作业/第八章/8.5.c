#include<stdio.h>
#include<stdlib.h>

int main()
{
	int i, n, left, count3 = 0, count = 0;
	//输入n 
	printf("输入n；");
	scanf("%d", &n);
	if(n <= 0)
	{
		printf("输入了非正整数");
		exit(-1);
	}
	left = n;
	
	//开辟空间 
	int *p = calloc(n, sizeof(int));
	
	//初始化 
	for(i = 0; i < n; i++)
	{
		*(p + i) = i + 1;
	}
	//开始报数逢3退出 
	while(1)
	{
		//是否已退出 
		if(*p != 0)
		{
			count3++;
		}
	
		//是否到第三个了 
		if(count3 == 3)
		{
			count3 = 0;
			left--;
			if(left != 0) 
			{
				*p = 0;	
			}
		}
		
		if(left == 0) 
		{
			printf("最后剩下的是原来的第%d个", *p);
			break;
		}
		
		//使p指向下一个人 
		if(count == n-1)
		{
			p = p - n + 1;
			count = 0;
		}
		else
		{
			p++;
			count++;
		}
	}
	
	free(p-*p);
} 
