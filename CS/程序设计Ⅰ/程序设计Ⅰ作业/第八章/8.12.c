#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define n 10
void sort(char *str[n]);

int main()
{
	int i, length;
	char *temp = NULL;
	char *str[n] = {NULL};
	for(i = 0; i < n; i++)
	{ 
		printf("输入第%d个字符串(小于100个字符)", i);
		temp = calloc(101, sizeof(char));
		gets(temp);
		length = strlen(temp);
		str[i] = calloc(length + 1, sizeof(char));
		strcpy(str[i], temp);
		free(temp);
	}
	
	sort(str);
	//输出 
	for(i = 0; i < n; i++)
	{
		puts(str[i]);
	}

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



