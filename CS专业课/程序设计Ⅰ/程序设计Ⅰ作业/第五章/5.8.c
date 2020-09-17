#include<stdio.h>

int main(){
	int i, j, k, flag;
	printf("以下为所有水仙花数：\n");
	for(i = 1; i < 10; i++)
	{
		for(j = 0; j < 10; j++)
		{
			for(k = 0; k < 10; k++)
			{
				if(i*i*i + j*j*j + k*k*k == 100*i + 10*j + k)
				{
					if(flag = 9)
					{
						flag = 0;
					}
					flag++;
					printf("%d%d%d \n", i, j, k);	
				}
			}
		}
	}
	return 0; 
}
