#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define n 20


void STRCAT(char s1[], char s2[]);

int main()
{
	char s1[2*n+1];
	char s2[n+1];
	s1[n] = '\0';
	s2[n] = '\0';
	int i, s1len, s2len;
	/*
	 *输入字符串
	 */ 
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
	
	STRCAT(s1, s2);
	
	//输出结果 
	printf("字符串连接结果：\n");
	puts(s1);
	return 0; 
}
//拼接
void STRCAT(char s1[], char s2[])
{
	int s1len = strlen(s1);
	int s2len = strlen(s2); 
	int i = 0;
	while(s2[i] != '\0')
	{
		s1[i + s1len] = s2[i];
		i++;
	}
	s1[i+s1len] = '\0';
}
