#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/time.h>

#define n 10
void sort(char *str[n]);

int main()
{
	int i;
/*	
	struct timeval start;
    struct timeval end;
    unsigned long timer;
*/	
	char *str[n] = {NULL};
	for(i = 0; i < n; i++)
	{ 
		printf("输入第%d个字符串(小于20个字符)", i);
		str[i] = calloc(21, sizeof(char));
		gets(str[i]);
	}
	
//	gettimeofday(&start, NULL);
	
	sort(str);
	for(i = 0; i < n; i++)
	{
		puts(str[i]);
	}
	
/*	gettimeofday(&end, NULL);
	timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
    printf("timer = %ld us\n", timer);
*/	
} 

void sort(char *str[n])
{
	//选择排序
	char *t;
	int i, j, k;
	for(i = 0; i < n-1; i++)
	{
		k = i;
		for(j = i + 1; j < n; j++)
		{
			if(strcmp(str[k], str[j]) > 0) k = j;
		}
		if(i != k)
		{
			t = str[i];
			str[i] = str[k];
			str[k] = t;
		}
	}
}



