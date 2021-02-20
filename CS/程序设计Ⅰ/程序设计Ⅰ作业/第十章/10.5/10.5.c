#include<stdio.h>
#include "..\\Student.h"


int main()
{
	int i;
	FILE *out = fopen("stud", "w");
	for(i = 0; i < STUNUM; i++)
	{
		printf("分别输入第%d位学生的ID,name,sub1,sub2,sub3并以制表符隔开:\n", i); 
		scanfStu(out);
	}
	printf("写入完成");
	fclose(out);
} 



