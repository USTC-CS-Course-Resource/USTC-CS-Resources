#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define N 20
#define IDLen 4
#define SUBNUM 3

struct Student{
	char ID[N];
	char name[N];
	float grade[SUBNUM+3];
	struct Student *next;
};
typedef struct Student Student;

struct LinkList{
	Student *head;
	int num;
};
typedef struct LinkList LinkList;


LinkList *newLinkList();
Student *newStu();
void printStu(Student *stu);
void printLinkList(LinkList *linklist);
void calculate(Student *stu);
void swap(LinkList *linklist, int index1, int index2);
int strToInt(char str[N]);
float strToPFloat(char str[N]);


/****************************************************************************************
Function: newLinkList
Description: 新建一个LinkList并返回其指针，若新建失败则返回NULL
Return:	该函数返回新建的链表的指针，若新建失败则返回NULL 
****************************************************************************************/
LinkList *newLinkList()
{
	LinkList *linklist = (LinkList*)malloc(sizeof(LinkList));
	if(linklist == 0)
	{
		printf("内存空间不足,无法创建链表");
		return NULL;
	}
	linklist->head = (Student*)malloc(sizeof(Student));
	linklist->head->next = NULL;
	linklist->num = 0;
	return linklist;
}

/****************************************************************************************
Function: newStu
Description: 新建一个学生并返回其指针，若新建失败则返回NULL。 
Return:	该函数返回该学生的指针，若新建失败则返回NULL
****************************************************************************************/
Student *newStu()
{
	int i;
	int flag = 1;
	Student *stu = NULL;
	stu = (Student*)malloc(sizeof(Student));
	stu->next = NULL;
	if(stu == 0)
	{
		printf("内存空间不足,无法创建学生");
		return NULL;
	}
	else
	{
		char subject[SUBNUM][N] = {"语文", "数学", "英语"}; 
		char grade[SUBNUM][N] = {0};
		stu->next = NULL;
		printf("请分别输入要插入的新学生的ID 姓名 语文成绩 数学成绩 英语成绩(以空格隔开)：\n");
		scanf("%s\t%s\t%s\t%s\t%s", stu->ID, stu->name, grade[0], grade[1], grade[2]);//这里要求ID为4位纯数字，name不应为纯数字,三个grade应为非负数 
		while(strlen(stu->ID) != 4)
		{
			printf("读到学生ID非法，应为%d位.请重新输入ID：", IDLen);
			scanf("%s", stu->ID);
		}//检查ID格式合法性结束 
		
		do
		{
			for(i = 0; i < strlen(stu->name); i++)
			{
				if((stu->name)[i] > '9' || (stu->name)[i] < '0')
				{
					flag = 0;
				}
				if(flag == 0) break;
			}
			if(flag == 1)
			{
				printf("读到学生姓名非法，不应为纯数字.请重新输入姓名：");
				scanf("%d", stu->name); 
			}
		}while(flag == 1);//检查姓名格式合法性结束 
		for(i = 0; i < SUBNUM; i++)
		{
			while(strToPFloat(grade[i]) == -1)
			{
				printf("检测到该学生 %s 的成绩非法，应为非负数. 请重新输入: ", subject[i]);
				scanf("%s", grade[i]);
			}
		}//检查成绩格式合法性结束 
		
		for(i = 0; i < SUBNUM; i++)
		{
			stu->grade[i+3] = strToPFloat(grade[i]);
		}
		calculate(stu); 
		return stu;
	}
}

/****************************************************************************************
Function: printLinkList
Description: 打印链表中所有节点的信息 
Input:	linklist: 将打印的链表
Return:	打印链表中所有节点的信息 
****************************************************************************************/
void printLinkList(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("链表内没有节点");
		return;
	}
	int i;
	Student *stu = linklist->head;
	printf("序号\tID\t\t\t姓名\t语文\t数学\t英语\t平均分\t最高分\t最低分\n"); //输出表头
	for(i = 0; i < linklist->num; i++)
	{
		stu = stu->next;
		printf("%d\t",i+1);
		printStu(stu);
	}
} 

/****************************************************************************************
Function: printStu
Description: 打印stu的信息 
Input:	stu: 将打印信息的学生 
Return:	打印stu的信息 
****************************************************************************************/
void printStu(Student *stu)
{
	printf("%4s\t%20s\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\t%4.2f\n", 
		stu->ID, stu->name, stu->grade[3], stu->grade[4], stu->grade[5], stu->grade[0], stu->grade[1], stu->grade[2]);
} 


/****************************************************************************************
Function: void calculate(Student *stu)
Description: 对学生stu求平均，最高，最低分 
Input:	stu: 将要求平均，最高，最低分的学生 
Return:	无 
****************************************************************************************/
void calculate(Student *stu)
{
	int i;
	float max, min;
	if(stu != NULL)
	{
		stu->grade[0] = (stu->grade[3] + stu->grade[4] + stu->grade[5]) /3;
		max = stu->grade[3];
		min = stu->grade[3];
		for(i = 3; i < SUBNUM+3; i++)
		{
			if(stu->grade[i] > max) max = stu->grade[i];
			if(stu->grade[i] < min) min = stu->grade[i];
		}
		stu->grade[1] = max;
		stu->grade[2] = min;
	}
} 



/****************************************************************************************
Function: int strToInt(char str[N])
Description: 若str可表示非负整数，则返回该整数，否则返回-1 
Input:	str: 将要转化的字符串 
Return:	若str可表示非负整数，则返回该整数，否则返回-1 
****************************************************************************************/
int strToInt(char str[N]) 
{
	int i, result = 0,flag = 1;
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] > '9' || str[i] < '0')
		{
			flag = 0;
		}
		if(flag == 0) break;
	}
	if(flag == 1)
	{
		for(i = strlen(str) - 1; i >= 0; i--)
		{
			result += (str[i]-48)*pow(10, strlen(str) - i - 1);	
		}
		return result;
	}
	else if(flag == 0)
	{
		return -1;
	}
}

/****************************************************************************************
Function: float strToPFloat(char str[N])
Description: 若str可表示非负浮点数，则返回该浮点数(以float类型)，否则返回-1 
Input:	str: 将要转化的字符串 
Return:	若str可表示非负浮点数，则返回该浮点数(以float类型)，否则返回-1 
****************************************************************************************/
float strToPFloat(char str[N])
{
	float result = 0;
	int i, flag = 1, point = strlen(str);
	for(i = 0; i < strlen(str); i++)
	{
		if((str[i] > '9' || str[i] < '0') )
		{
			if(str[i] == 46)
			{
				point = i;
			}
			else
			{
				flag = 0;
			}
		}
		if(flag == 0) break;
	}
	if(flag == 1)
	{
		for(i = point - 1; i >= 0; i--)
		{
			result += (str[i]-48)*pow(10, point - i - 1);	
		}
		for(i = point + 1; i < strlen(str); i++)
		{
			result += (str[i]-48)*pow(10, -(i-point));	
		}
		return result;
	}
	else if(flag == 0)
	{
		return -1;
	}
}







