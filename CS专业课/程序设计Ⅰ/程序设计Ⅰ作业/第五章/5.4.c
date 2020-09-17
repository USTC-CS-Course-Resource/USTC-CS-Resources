#include<stdio.h>

int main()
{
	char c;
	int letters = 0, space = 0, num = 0, others = 0;
	while((c = getchar()) != '\n'){
		if(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) letters++;
		else if(c == ' ') space++;
		else if('0' <= c  && c <= '9') num++;
		else others++;
	}
	printf("英文字母有 %d个\n",letters);
	printf("空格有 %d个\n", space);
	printf("数字有 %d个\n", num);
	printf("其他字符有 %d个\n", others);
	return 0;	
}
