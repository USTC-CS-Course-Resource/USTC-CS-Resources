#include "basic.c"
#define N 20
void findPasser(LinkList *linklist);
void findStu(LinkList *linklist);
Student *nameGet(LinkList *linklist, char name[N]);
Student *IDGet(LinkList *linklist, char ID[N]);
Student *getStu(LinkList *linklist, int index);


/****************************************************************************************
Function: Student *getStu(LinkList *linklist, int index)
Description: 从linklist中获得第index个节点上的Student，并返回其地址 
Input:	linklist: 将要查找的链表
		index：将要获取的学生所在节点的序号数 
Return:	linklist上第index个节点上的Student的地址 
****************************************************************************************/
Student *getStu(LinkList *linklist, int index)
{
	int i;
	Student *stu = NULL;
	stu = (Student*)malloc(sizeof(Student));
	stu = linklist->head->next;
	if(index == 0) return linklist->head;
	for(i = 1; i < index; i++)
	{
		stu = stu->next;
	}
	return stu;
}

/****************************************************************************************
Function: Student *IDGet(LinkList *linklist, char ID[N])
Description: 从linklist中获得ID为ID的Student，并返回其地址 
Input:	linklist: 将要查找的链表
		ID：将要获取的学生的ID 
Return:	linklist上ID为ID的Student的地址 
****************************************************************************************/
Student *IDGet(LinkList *linklist, char ID[N])
{
	int flag = 0;
	Student *stu = linklist->head->next;
	while(stu != NULL)
	{
		if(strcmp(stu->ID, ID) == 0)
		{
			flag = 1;
			break;
		}
		if(flag == 1) break;
		stu = stu->next;
	}
	if(stu == NULL)
	{
		printf("\n找不到该学生\n");
		return NULL;
	}
	else
	{
		return stu;
	}
}

/****************************************************************************************
Function: Student *nameGet(LinkList *linklist, char name[N])
Description: 从linklist中获得name为name的Student，并返回其地址 
Input:	linklist: 将要查找的链表
		name：将要获取的学生的name 
Return:	linklist上name为name的Student的地址 
****************************************************************************************/
Student *nameGet(LinkList *linklist, char name[N])
{
	int flag = 0;
	Student *stu = linklist->head->next;
	while(stu != NULL)
	{
		if(strcmp(stu->name, name) == 0) 
		{
			flag = 1;
			break;
		}
		if(flag == 1) break;
		stu = stu->next;
	}
	if(stu == NULL)
	{
		printf("\n找不到该学生\n");
	}
	else
	{
		return stu;
	}
}

/****************************************************************************************
Function: void findStu(LinkList *linklist)
Description: 向用户提供选择来实现1.根据ID或姓名查找一个学生记录；2.查找平均分>60的学生，
并输出结果。 
Input:	linklist: 将要查找的链表
****************************************************************************************/
void findStu(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("链表内没有节点");
		return;
	}
	int choice;
	char temp[N];
	printf("想要哪个呢？输入序号\n\t1.根据ID或者姓名查找一个学生的记录\n\t2.查找平均分＞60的学生\n\t3.取消\n");
	scanf("%s", temp);
	choice = strToInt(temp);
	while(choice != 1 && choice != 2 && choice !=3)
	{
		printf("序号输入有误，请重新输入：");
		scanf("%s", temp);
		choice = strToInt(temp);
	}
	if(choice == 1)
	{
		char infor[N];
		int flag = 1; //如果infor纯数字则记为1，否则为0，1为初值
		int i;
		printf("请输入要寻找的学生的 ID 或 姓名: \n");
		scanf("%s", infor);
		for(i = 0; i < strlen(infor); i++)
		{
			if(infor[i] > '9' || infor[i] < '0')
			{
				flag = 0;
			}
			if(flag == 0) break;
		}
		if(flag == 1)
		{
			if(IDGet(linklist, infor) != NULL)
			{
				printf("\n所找学生信息如下：\n");
				printStu(IDGet(linklist, infor));
			}
		}
		else if(flag == 0)
		{
			if(nameGet(linklist, infor) != NULL)
			{
				printf("\n所找学生信息如下：\n");
				printStu(nameGet(linklist, infor));
			}
		}
		else
		{
			printf("输入有误");
		}
	}
	else if(choice == 2)
	{
		findPasser(linklist);
	}
	else if(choice == 3)
	{
		return;
	}
	
}


/****************************************************************************************
Function: findPasser
Description: 根据ID找到学生并打印其信息 
Calls:	NULL 
Called By:	;
Input:	linklist: 要找的链表
		ID: 要找的学生的ID 
Output: 输出要找的学生的信息 
Return:	无 
****************************************************************************************/
void findPasser(LinkList *linklist)
{
	Student *stu = linklist->head->next;
	int flag = 0, i;
	printf("\n以下是平均分>60的学生:\n");
	printf("序号\tID\t\t\t姓名\t语文\t数学\t英语\t平均分\t最高分\t最低分\n"); //输出表头
	for(i = 0; i < linklist->num; i++)
	{
		if(stu->grade[0] > 60) 
		{
			printf("%d\t", i+1);
			printStu(stu);
			flag = 1;
		}
		stu = stu->next;
	}
	if(flag == 0)
	{
		printf("\n哎呀，没有平均分>60的学生\n");
	}
} 
