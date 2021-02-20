#include<stdio.h>
#include<stdlib.h>
#define n 10

int main()
{
	//共n-1个数 将插入到n个 
	int i = 0, j = n-1,order = -1, total=0;//order为0表示逆序，为1表示顺序 ,为-1表示未确定 
	char c;
	float x;
	float a[n];
	printf("开始输入排好序的数组，最多%d个元素。\n", n-1);
	do
	{
		printf("请输入第%d个数(若为最后一个数则在其后加一空格)： ", total+1);
		scanf("%f", &a[total]);
		total++;
		if(total >= n-1)
		{
			printf("已达到数字数上限，结束输入。\n");
			break;
		}
	} while((c = getchar()) != ' ');
	
	
	
	//确定是否为逆序 
	order = 0;
	for(i = 0; i < total-1; i++)
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
		for(i = 0; i < total-1; i++)
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
	j=total;
	if(order == -1)
	{
		printf("数组未被排序\n");
		exit(-1);
	}
	else 
	{
		printf("输入要插入的数： ");
		scanf("%f", &x);
		if(order == 1)
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
			} 
		}
	}

	
	//将x应插入处之后的数全部顺延 
	for(i = total; i > j; i--)
	{
		a[i] = a[i-1];
	} 
	a[j] = x;
	
	//输出插入结果
	for(i = 0; i < total+1; i++)
	{
		printf("%f ", a[i]);
		if(i%5 == 4) printf("\n");
	}
	printf("\n");
	
	return 0;
} 
