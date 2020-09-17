#include<stdio.h>
#include<math.h> 
#define N 100
int main()
{
	int a[N];
	int i, j, n = sqrt(N);
	for(i = 0; i < N; i++)
	{
		a[i] = i+1;
	}
	a[0] = 0; //由于1特殊，先赋值为0； 
	//将非素数赋值为0 
	for(i = 1; i < n; i++)
	{
		if(a[i] != 0)
		{
			for(j = i + 1; j < N; j++)
			{
				if(a[j] % a[i] == 0) a[j] = 0;
			}
		}
	}
	
	//输出素数 
	printf("%d之内的素数有：\n", N);
	for(i = 0; i < 100; i++)
	{
		if(a[i] != 0) printf("%d\n", a[i]);
	} 
	return 0; 
} 
