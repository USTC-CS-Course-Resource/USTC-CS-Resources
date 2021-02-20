#include<stdio.h>
#include<stdlib.h>
#define n 5
int main()
{
	char s1[n];
	char s2[n];
	printf("字符串比较"); 
	printf("字符串连接\n请输入字符串s1(不超过%d个字符)： ", n);
	gets(s1);

	if(s1[n] != '\0')
	{
		printf("所输入的s1超过%d个字符\n", n);
		exit(-1); 
	}
	
	printf("请输入字符串s2(不超过%d个字符)： ", n);
	gets(s2);
	if(s2[n] != '\0')
	{
		printf("所输入的s2超过%d个字符\n", n);
		exit(-1); 
	}

	printf("比较的结果是：%d\n", STRCMP(s1, s2));
	return 0;
}

int STRCMP(char s1[], char s2[])
{
	int i = 0, j = 0, flag = 0;
	while(s1[j] != '\0' && i == 0)
	{
		i = s1[j] - s2[j];
		j++;
	}
	return i;
} 
