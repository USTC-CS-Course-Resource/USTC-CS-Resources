#include<stdio.h>
#include "..\\Student.h"


int main()
{
	FILE *in = fopen("..\\10.6\\stu_sort", "r");
	printf("请输入要插入的学生的ID,name,sub1,sub2,sub3并以制表符隔开:\n");
	Student *stu = (Student*)malloc(sizeof(Student));
	scanf("%d\t%s\t%d\t%d\t%d", &stu->ID, stu->name, &stu->sub1, &stu->sub2, &stu->sub3);
	stu->average = (stu->sub1+stu->sub2+stu->sub3)/3;
	
	int i, j, flag = 0; 
	Student *stuArray[STUNUM+1] = {NULL};
	for(i = 0; i < STUNUM; i++)
	{
		stuArray[i] = fscanfStu(in);
	}
	fclose(in);
	FILE *out = fopen("..\\10.6\\stu_sort", "w");
	for(i = 0; i < STUNUM; i++)
	{
		if((stuArray[i]->average) < (stu->average))
		{
			for(j = STUNUM-1; j > i-1; j--)
			{
				stuArray[j+1] = stuArray[j];
			}
			stuArray[i] = stu;
			flag = 1;
			break;
		}
		if(flag == 1) break;
	}
	if(flag == 0) stuArray[STUNUM] = stu;
	for(i = 0; i < STUNUM+1; i++)
	{
		fprintf(out, "%d\t%s\t%d\t%d\t%d\t%f\n", stuArray[i]->ID, stuArray[i]->name, stuArray[i]->sub1, stuArray[i]->sub2, stuArray[i]->sub3, stuArray[i]->average);
	}
	
	printf("完成添加");
	fclose(out);
	
	return 0;
}

