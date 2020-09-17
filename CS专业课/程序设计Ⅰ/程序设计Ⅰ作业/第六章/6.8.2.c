#include<stdio.h>
#define m 10
#define n 10
int main()
{
	int a[m][n] = {0};
	int i, j, k, x, index_j,num = 0, totalM = 0, totalN = 0,N=0;
	char c;
	
	 //输入数组元素
	printf("以下输入过程中，若为一行最后一个数则加一个空格，\n\t\t若为最后一行最后一个数则加两个空格.\n"); 
	do
	{
		do
		{
			printf("请输入第%d行，第%d列的数(若为最后一个数则加一空格)： ", totalM+1, N+1);
			scanf("%d", &a[totalM][N]);
			N++;
			if(N >= n)
			{
				printf("已达到列数上限，结束输入。\n");
				break;
			}
		} while((c = getchar()) != ' '); 
		totalN = totalN>N ? totalN : N;
		N=0;
		totalM++;
		if(totalM >= m)
		{
			printf("已达到行数上限，结束输入。\n");
			break;
		}
	} while((c = getchar()) != ' ');
	
	
	 //寻找鞍点 
	for(i = 0; i < totalM; i++)
	{
		x = a[i][0];
		for(j = 0; j < totalN; j++)
		{
			if(a[i][j] > x) 
			{
				x = a[i][j];
				index_j = j;
			} 
		}//使x为第i+1行最大 
		//检测x是否为第index_j+1列最小 
		for(k = 0; k < totalM; k++)
		{
			if(a[k][index_j] < x) break;
		}
		if(k == totalM)
		{
			printf("%d 为一鞍点, 位于第%d行第%d列\n", a[i][index_j], i+1, index_j + 1);
			num++;
		}
	}
	
	if(num == 0) printf("该二维数组不存在鞍点");
	return 0;
}
