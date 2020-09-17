#include<stdio.h>

int main(){
	int x;
	char level;
	printf("请输入百分制成绩：");
	scanf("%d", &x);
	if(x > 100 || x < 0) printf("成绩输入有误，不是百分制成绩。");
	else {
		if(x < 60) level = 'E';
			else if(x <= 69) level = 'D';
			else if(x <= 79) level = 'C';
			else if(x <= 89) level = 'B';
			else level = 'A';
		printf("成绩等级为： %c", level);
	}
	return 0;
} 
