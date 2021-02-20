#include<stdio.h>
#define m 3
#define n 4
int main()
{
	int a[m][n] = {{1,2,5,4}, {6,3,6,9}, {5,9,8,3}};
	int i, j, k, x, index_j,num = 0;
	
	 
	
	for(i = 0; i < m; i++)
	{
		x = a[i][0];
		for(j = 0; j < n; j++)
		{
			if(a[i][j] > x) 
			{
				x = a[i][j];
				index_j = j;
			} 
		}//使x为第i+1行最大 
		//检测x是否为第index_j+1列最小 
		for(k = 0; k < m; k++)
		{
			if(a[k][index_j] < x) break;
		}
		if(k == m)
		{
			printf("%d 为一鞍点, 位于第%d行第%d列\n", a[i][index_j], i+1, index_j + 1);
			num++;
		}
	}
	
	if(num == 0) printf("该二维数组不存在鞍点");
	return 0;
}
