
#include<stdio.h>
#define STUNUM 10
#define SUBNUM 5

void averageOfStu(float grade[STUNUM+1][SUBNUM+1]);
void averageOfSub(float grade[STUNUM+1][SUBNUM+1]);
void getBest(char student[STUNUM][20], char subject[SUBNUM][20], float grade[STUNUM+1][SUBNUM+1]);
void printVariance(float grade[STUNUM+1][SUBNUM+1]);
int lessThanZero(int a);
int main()
{
	int i, j;
	float grade[STUNUM+1][SUBNUM+1];
	char student[STUNUM][20]; 
	char subject[SUBNUM][20];
	for(i = 0; i < SUBNUM; i++)
	{
		printf("输入科目%d名称：", i+1);
		gets(subject[i]);	
	//	printf("get %s\n", subject[i]);
	} 
	for(i = 0; i < STUNUM; i++)
	{
		printf("输入学生%d姓名：",i+1);
		fflush(stdin);
		gets(student[i]);
	//	printf("get %s\n", student[i]);
		for(j = 0; j < SUBNUM; j++)
		{
		/*	do
			{
				printf("输入该学生 科目%s 的分数：", subject[j]);
				scanf("%f", &(grade[i][j])); 
				fflush(stdin); 
			//	printf("%f", grade[i][j]);
			} while(lessThanZero(grade[i][j]));
*/
			grade[i][j] = i*SUBNUM + j;
		}
		printf("\n");
	}
	//get the average grades of students and print.
	averageOfStu(grade);
	for(i = 0; i < STUNUM; i++)
	{
		printf("学生%s的平均分为： %.2f\n", student[i], grade[i][SUBNUM]);
	}
	//get the average grades of subjects and print.
	averageOfSub(grade);
	for(i = 0; i < SUBNUM; i++)
	{
		printf("科目%s的平均分为： %.2f\n", subject[i], grade[STUNUM][i]);
	}
	//print the best grade
	getBest(student, subject, grade);
	//print the variance grade;
	printVariance(grade);
	
	return 0;
}

void averageOfStu(float grade[STUNUM+1][SUBNUM+1])
{
	int i,j;
	float total = 0;
	for(i = 0; i < STUNUM; i++)
	{
		for(j = 0; j < SUBNUM; j++)
		{
			total += grade[i][j];
		}
		grade[i][SUBNUM] = total/SUBNUM;
		total = 0;
	}
}

void averageOfSub(float grade[STUNUM+1][SUBNUM+1])
{
	int i,j;
	float total = 0;
	for(i = 0; i < SUBNUM; i++)
	{
		for(j = 0; j < STUNUM; j++)
		{
			total += grade[j][i];
		}
		grade[STUNUM][i] = total/STUNUM;
		total = 0;
	}
}

void getBest(char student[STUNUM][20], char subject[SUBNUM][20], float grade[STUNUM+1][SUBNUM+1])
{
	int i,j, index = 0;
	int order[STUNUM][SUBNUM];
	float max = 0;
	for(i = 0; i < STUNUM; i++)
	{
		for(j = 0; j < SUBNUM; j++)
		{
			if(max < grade[i][j])
			{
				index++;
				max = grade[i][j];
				order[i][j] = index;
			}
			else if(max == grade[i][j])
			{
				order[i][j] = index;
			}
			else
			{
				order[i][j] = -1;
			}
		}
	}
	printf("这%d个分数中最高的分数为：%.2f\n对应的学生\t课程有：\n", SUBNUM*STUNUM, max);
	for(i = 0; i < STUNUM; i++)
	{
		for(j = 0; j < SUBNUM; j++)
		{
			if(order[i][j] == index)
			{
				printf("\t%s\t%s\n", student[i], subject[j]);
			}
		}
	}
}

void printVariance(float grade[STUNUM+1][SUBNUM+1])
{
	float sum, squareSum;
	int i;
	averageOfStu(grade);
	for(i = 0; i < STUNUM; i++)
	{
		sum += grade[i][SUBNUM];
		squareSum += grade[i][SUBNUM]*grade[i][SUBNUM];
	}
	printf("学生平均分的方差为：%.2f", squareSum/STUNUM - (sum*sum)/(STUNUM*STUNUM));
	
}

int lessThanZero(int a)
{
	if(a < 0)
	{
		printf("输入的分数小于0\n");
		return 1;
	}
	else return 0;
}



