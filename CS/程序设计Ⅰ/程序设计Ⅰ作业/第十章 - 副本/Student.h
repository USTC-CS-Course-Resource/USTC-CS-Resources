#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#define N 20

int STUNUM = 3

struct Student{
	int ID;
	char name[N];
	int sub1;
	int sub2;
	int sub3;
	float average;
	struct Student *next;
};
typedef struct Student Student;

struct LinkList{
	int num;
	Student *head;
};
typedef struct LinkList LinkList;

void scanfStu(FILE *out);
Student *fscanfStu(FILE *in);
void sort(FILE *in, FILE *out, int STUNUM);
void add(FILE *in, FILE *out, Student *stu, int STUNUM);

//要求用户输入学生信息并返回该学生的指针 
void scanfStu(FILE *out)
{
	int ID; char *name[N]; int sub1, sub2, sub3;
	scanf("%d\t%s\t%d\t%d\t%d", &ID, name, &sub1, &sub2, &sub3);
	fprintf(out, "%d\t%s\t%d\t%d\t%d\t%f\n", ID, name,sub1, sub2, sub3,(sub1+sub2+sub3)/3.0);
}

//从文件中读取数据 
Student *fscanfStu(FILE *in)
{
	Student *stu = (Student*)malloc(sizeof(Student));
	fscanf(in, "%d\t%s\t%d\t%d\t%d\t%f\n", &stu->ID, stu->name, &stu->sub1, &stu->sub2, &stu->sub3, &stu->average);
	return stu;
}


//排序
void sort(FILE *in, FILE *out, int STUNUM)
{
	int i, j;
	Student **stuArray = (Student**)calloc(STUNUM, sizeof(Student*));
	Student *temp = (Student*)malloc(sizeof(Student));
	Student *stu = (Student*)malloc(sizeof(Student));
	for(i = 0; i < STUNUM; i++)
	{
		stuArray[i] = fscanfStu(in);
	}
	for(i = 0; i < STUNUM-1; i++)
	{
		for(j = STUNUM-1; j > i; j--)
		{
			if(stuArray[j-1]->average < stuArray[j]->average)
			{
				temp = stuArray[j-1];
				stuArray[j-1] = stuArray[j];
				stuArray[j] = temp;
			}
		}
	}
	
	fprintf(out,"%d\n", STUNUM);
	for(i = 0; i < STUNUM; i++)
	{
		fprintf(out, "%d\t%s\t%d\t%d\t%d\t%f\n", stuArray[i]->ID, stuArray[i]->name, stuArray[i]->sub1, stuArray[i]->sub2, stuArray[i]->sub3, stuArray[i]->average);
	}
}
//添加 
void add(FILE *in, FILE *out, Student *stu, int STUNUM)
{
	int i, j, flag = 0;
	Student **stuArray = (Student**)calloc(STUNUM+1, sizeof(Student*));
	for(i = 0; i < STUNUM; i++)
	{
		stuArray[i] = fscanfStu(in);
	}
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
	
	
	fprintf(out,"%d\n", STUNUM+1);
	for(i = 0; i < STUNUM+1; i++)
	{
		fprintf(out, "%d\t%s\t%d\t%d\t%d\t%f\n", stuArray[i]->ID, stuArray[i]->name, stuArray[i]->sub1, stuArray[i]->sub2, stuArray[i]->sub3, stuArray[i]->average);
	}
}




