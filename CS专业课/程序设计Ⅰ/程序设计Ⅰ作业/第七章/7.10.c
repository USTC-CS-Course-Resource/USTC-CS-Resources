#include<stdio.h>
#include<string.h>
#define n 100
void printLongest(char str[]);

int main()
{
	char str[n];
	printf("请输入一行字符：");
	gets(str);
	printLongest(str);
	return 0;
} 

void printLongest(char str[n])
{
	int i,j;
	int flag[n] = {0};
	int longestIndex = 0;
	int longest, count;	
	int length = strlen(str);
	for(i = 0; i < length; i++)
	{
		if(str[i] == ' ')
		{
		//	continue;
		}
		else if(str[i] == '\0')
		{
			break;	
		}
		else
		{
			while(('z' >= str[i] && str[i] >= 'a') || ('Z' >= str[i] && str[i] >= 'A'))
			{
				count++;
				i++;
			}
			if(count > longest)
			{
				longestIndex = i - count;
				longest = count;
				flag[longestIndex] = longest;
			}
			else if(count == longest)
			{
				longestIndex = i - count;
				flag[longestIndex] = longest;
			}
			count = 0;
		}
	}
	
	
	printf("最长的单词是：\n");
	for(i = 0; i < length; i++)
	{
		if(flag[i] == longest)
		{
		//	printf("%d", longest);
			for(j = i; j < longest+i; j++) 
			{
				printf("%c", str[j]);
			}
			printf("\n");
		}
	//	break;
	}
/*	for(i = longestIndex; i < longest+longestIndex; i++) 
	{
		printf("%c", str[i]);
	}*/
}




