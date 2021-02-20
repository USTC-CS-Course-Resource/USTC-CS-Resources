#include<stdio.h>

int main(){
	int n = 1;
	int i, sum = 0,flag, j;
	for(;n <=1000; n++)
	{
		for(i = 1; i < n; i++)
		{
			if(n%i == 0) sum += i;
		}
		if(sum == n) 
		{
		/*	if(flag > 9){
				printf("\n");
				flag = 0;
			}
			flag++;*/
			printf("%d its factors are 1", n);
			for(j = 2; j < n; j++) 
			{
				if(n % j == 0)
				{
					printf(",%d", j);
				}
			}
			printf("\n");
		}
		sum = 0;
	}
	return 0; 
}

