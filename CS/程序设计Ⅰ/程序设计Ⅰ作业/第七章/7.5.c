#include<stdio.h>
#include<string.h>

void reverseString(char str[]);

int main()
{
	char str[20];
	printf("ÇëÊäÈë×Ö·û´®");
	gets(str);
	reverseString(str);
	puts(str);
}

void reverseString(char str[])
{
	int length = strlen(str);
	char c;
	int i;
	for(i = 0; i < length/2; i++)
	{
		c = str[i];
		str[i] = str[length-i-1];
		str[length-i-1] = c;
	}
}
