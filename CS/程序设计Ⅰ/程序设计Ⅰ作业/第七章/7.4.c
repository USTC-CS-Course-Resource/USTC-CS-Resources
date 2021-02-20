#include<stdio.h>
#define n 3
int main()
{
	void matrixInversion(int a[n][n]);
	int a[n][n];
	int i,j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("请输入第%d行第%d列的数：", i+1, j+1);
			scanf("%d", &a[i][j]);
		}
	} 
	matrixInversion(a);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			printf("%d\t", a[i][j]);
		}
		printf("\n");
	} 
}

void matrixInversion(int a[n][n])
{
	int i,j;
	int c;
	for(i = 0; i < n; i++)
	{
		for(j = i+1; j < n; j++)
		{
			c = a[i][j];
			a[i][j] = a[j][i];
			a[j][i] = c;
		}
	}
}
