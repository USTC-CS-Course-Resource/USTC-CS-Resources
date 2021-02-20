/*********************************************************************
Copyright: 2018-9999, Zhanghan Wang
File name: StuGradeManager.c
Description: 
这是一个学生成绩管理系统，它能够实现
	读取：读取历史成绩文件（格式为.txt)
	插入：插入新记录 
	删除：删除记录 
	查找：(1)根据ID或姓名查找一个学生的记录(2)查找平均分>60的学生 
	修改：修改某个学生的成绩 
	排序：按照某个学生属性对学生进行排序 
	保存：按照ID对学生排序，并保存成绩表为txt文件 
Author:王章瀚	PB18111697
Version:1.0.0
Date: 2018/12/5
*********************************************************************/
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
	float grade[SUBNUM+3]; //为了提高可扩展性，并方便后面的排序，用数组来记录各科成绩及最高最低平均分
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
void findPasser(LinkList *linklist);
void findStu(LinkList *linklist);
Student *nameGet(LinkList *linklist, char name[N]);
Student *IDGet(LinkList *linklist, char ID[N]);
Student *getStu(LinkList *linklist, int index);
void addToLinkList(LinkList *linklist, Student *stu, int index);
void editGrade();
void deleteStu(LinkList *linklist, int index, int mode);
void sortStu(LinkList *linklist);
void strSort(LinkList *linklist, int item);
void gradeSort(LinkList *linklist, int item);
void swapStu(LinkList *linklist, int index1, int index2);
LinkList *getStuInfor();
Student *readStu(FILE *in);
void writeStu(LinkList *linklist);
void printMenu();
void exitSystem(LinkList *linklist);

int main()
{	
	char choice[N];
	LinkList *linklist = newLinkList();
	while(1)
	{
		printMenu();
		scanf("%s", choice);
		switch(strToInt(choice))
		{
			case 1: linklist = getStuInfor(); break;
			case 2: addToLinkList(linklist, newStu(), -1); break;
			case 3: deleteStu(linklist, 0, 1); break;
			case 4: findStu(linklist); break;
			case 5: editGrade(linklist); break;
			case 6: sortStu(linklist); break;
			case 7: writeStu(linklist); break;
			case 8: printLinkList(linklist); break;
			case 9: system("cls"); break;
			case 10: exitSystem(linklist); break;
			default: printf("没有这个选项噢!"); break;
			
		}
	}
//	writeStu(linklist);
	//LinkList *linklist = getStuInfor();
	//printLinkList(linklist);
	return 0;
}

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
	int flag = 1; //后续检查输入合法性需要用flag作标记 
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
Function: void findPasser(LinkList *linklist)
Description: 查找linklist中average大于60的Student，并输出
Input:	linklist: 要找的链表
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

/****************************************************************************************
Function: addtoLinkList
Description: 将学生stu加入到链表linklist的指定位置 
Input:	linklist: 待添加学生的链表
		stu: 待插入的学生
		index: 若index = -1 表示询问用户插入到哪；若0 <= index && index <= linklist->num的时候则直接插入第index个节点之后
Return:	无 
****************************************************************************************/
void addToLinkList(LinkList *linklist, Student *stu, int index) 
{
	if(linklist->head->next == NULL)
	{
		linklist->head->next = stu;
		stu->next = NULL;
		linklist->num++;
	}
	else
	{
		if(index >= 0 && index <= linklist->num)
		{
			Student *tstu = (Student*)malloc(sizeof(Student));
			if(index > 0 && index <= linklist->num)
			{
				tstu = (getStu(linklist, index))->next;
				(getStu(linklist, index))->next = stu;
				stu->next = tstu;
			}
			else if(index == 0)
			{
				stu->next = linklist->head->next;
				linklist->head->next = stu;
			}
			linklist->num++;
		}
		else if(index == -1)
		{
			char temp[N];
			printLinkList(linklist);
			printf("在第几位的后面插入呢(0表示插入到首位噢)？");
			scanf("%s", temp);
			index = strToInt(temp);
			while(index < 0 || index > linklist->num)
			{
				printf("位次输入有错噢.请重新输入: ");
				scanf("%s", temp);
				index = strToInt(temp);
			} 
			Student *tstu = (Student*)malloc(sizeof(Student));
			if(index > 0 && index <= linklist->num)
			{
				tstu = (getStu(linklist, index))->next;
				(getStu(linklist, index))->next = stu;
				stu->next = tstu;
			}
			else if(index == 0)
			{
				stu->next = linklist->head->next;
				linklist->head->next = stu;
			}
			linklist->num++;
			printf("\n插入结果是酱紫：\n");
			printLinkList(linklist);
		}
	}
}

/****************************************************************************************
Function: void deleteStu(LinkList *linklist, int index, int mode) 
Description: 将linklist中第index个节点从链表中移除。 
Input:	linklist: 待添加学生的链表
		mode：若mode为1，才会释放第index个节点的内存 
Return:	无 
****************************************************************************************/
void deleteStu(LinkList *linklist, int index, int mode) 
{
	if(linklist->head->next == NULL)
	{
		printf("链表内没有节点");
		return;
	}
	if(index > 0 && index <= linklist->num)
	{
		Student *stu1 = getStu(linklist, index-1);
		Student *stu2 = getStu(linklist, index);
		stu1->next = stu2->next;
		if(mode == 1) free(stu2); 
		linklist->num--;
	}
	else
	{
		printLinkList(linklist);
		printf("要删除的记录序号是什么呢？(输入0取消删除噢)\n");
		scanf("%d", &index);
		while(index < 0 && index > linklist->num)
		{
			printf("序号不在范围内噢.请重新输入(如果要取消删除,输入0)：");
			scanf("%d", &index); 
		}
		if(index == 0)
		{
			return;
		} 
		Student *stu1 = getStu(linklist, index-1);
		Student *stu2 = getStu(linklist, index);
		stu1->next = stu2->next;free(stu2);
		linklist->num--;
		printf("删除成功,删除后结果如下：\n");
		printLinkList(linklist);
	}
}

/****************************************************************************************
Function: void editGrade(LinkList *linklist)
Description: 修改某个学生的成绩 
Input:	linklist: 该学生所在链表
Return:	无 
****************************************************************************************/
void editGrade(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("链表内没有节点");
		return;
	}
	int sub = 0;
	float grade;
	Student *stu = (Student*)malloc(sizeof(Student));
	char infor[N];
	char temp[N];
	int index;
	printLinkList(linklist);
	printf("请输入要修改的学生的序号(输入0取消修改): ");
	scanf("%s", temp);
	index = strToInt(temp);
	while(index < 1 || index > linklist->num)
	{
		printf("序号输入有误.请重新输入：");
		scanf("%s", temp);
		index = strToInt(temp);
	}
	if(index == 0)
	{
		return;
	}
	stu = getStu(linklist, index);
	if(stu != NULL)
	{
		printf("请输入要修改的科目序号数字:\n\t1.语文\n\t2.数学\n\t3.英语\n");
		scanf("%s", temp);
		sub = strToInt(temp);
		while(sub < 1 || sub > SUBNUM)
		{
			printf("科目输入有误,请重新输入:");
			scanf("%s", temp);
			sub = strToInt(temp);
		} 
		printf("请输入修改后的成绩应为: ");
		scanf("%s", temp);
		grade = strToPFloat(temp);
		while(grade == -1)
		{
			printf("成绩输入非法，应为非负数.请重新输入修改后的成绩: ");
			scanf("%s", temp);
			grade = strToPFloat(temp);
		}
		if(sub == 1 || sub == 2 || sub == 3)
		{
			switch(sub)
			{
				case 1: stu->grade[3] = grade; break;
				case 2: stu->grade[4] = grade; break;
				case 3: stu->grade[5] = grade; break;
			}
			calculate(stu);
			printf("\n修改结果：\n");
			printStu(stu);
		}
		else
		{
			printf("\n科目选择错误\n"); 
		}
	}
	else
	{
		printf("\n序号输入有误\n");
	}
}

/****************************************************************************************
Function: void sortStu(LinkList *linklist)
Description: 根据用户选择的排序依据对linklist的各个节点进行排序，然后输出链表中每个节点 
Input:	linklist: 待排序的链表 
Return:	无 
****************************************************************************************/
void sortStu(LinkList *linklist)
{
	if(linklist->head->next == NULL)
	{
		printf("链表内没有节点");
		return;
	}
	int choice;
	char temp[N]; 
	printf("\n请输入排序根据的序号:\n\t1.ID\n\t2.姓名\n\t3.平均分\n\t4.最高分\n\t5.最低分\n\t6.语文\n\t7.数学\n\t8.英语\n\t9.取消排序\n");
	while(1)
	{
		scanf("%s", temp);
		choice = strToInt(temp);
		switch(choice)
		{
			case 1: 
			case 2: strSort(linklist, choice); break;
			case 3: 
			case 4: 
			case 5:
			case 6:
			case 7: 
			case 8: gradeSort(linklist, choice); break;
			case 9: return; break;
			default: printf("输入有误，请重新输入:"); break;
		}
		if(choice >=1 && choice <= 8) break;
		else if(choice == 9) return;
	}
	printLinkList(linklist);
}

/****************************************************************************************
Function: void sortStu(LinkList *linklist)
Description: 实现排序，若item为1，则排序的依据是ID；若item为2，则排序的依据是姓名 
Input:	linklist: 待排序的链表 
		item：该函数需要根据item的值，按不同属性对linklist排序 
Return:	无 
****************************************************************************************/
void strSort(LinkList *linklist, int item)
{
	int i, j;
	int max_index;
	char max[N];
	Student *stu1 = linklist->head;
	Student *stu2 = NULL;
	if(item == 1)
	{
		for(i = 1; i < linklist->num; i++)
		{
			stu1 = getStu(linklist, i);
			max_index = i;
			stu2 = stu1;
			strcpy(max, stu1->ID);
			for(j = i+1; j <= linklist->num; j++)
			{
				stu2 = stu2->next;
				if(strcmp(stu2->ID, max) < 0)
				{
					strcpy(max, stu2->ID);
					max_index = j;
				}
			}
			if(max_index != i) swapStu(linklist, i, max_index);
		}
	}
	else if(item == 2)
	{
		for(i = 1; i < linklist->num; i++)
		{
			stu1 = getStu(linklist, i);
			max_index = i;
			stu2 = stu1;
			strcpy(max, stu1->name);
			for(j = i+1; j <= linklist->num; j++)
			{
				stu2 = stu2->next;
				if(strcmp(stu2->name, max) < 0)
				{
					strcpy(max, stu2->ID);
					max_index = j;
				}
			}
			if(max_index != i) swapStu(linklist, i, max_index);
		}
	}
}

/****************************************************************************************
Function: void sortStu(LinkList *linklist)
Description: 按照成绩排序，根据用户选择的排序依据对linklist的各个节点进行排序
Input:	linklist: 待排序的链表 
		item：该函数需要根据item的值，按不同属性对linklist排序  
Return:	无 
****************************************************************************************/
void gradeSort(LinkList *linklist, int item)
{
	int i, j;
	int max, max_index;
	Student *stu1 = linklist->head;
	Student *stu2 = NULL;
	for(i = 1; i < linklist->num; i++)
	{
		stu1 = getStu(linklist, i);
		max_index = i;
		stu2 = stu1;
		max = stu1->grade[item-3];
		for(j = i+1; j <= linklist->num; j++)
		{
			stu2 = stu2->next;
			if(stu2->grade[item-3] > max)
			{
				max = stu2->grade[item-3];
				max_index = j;
			}
		}
		if(max_index != i) swapStu(linklist, i, max_index);
	}
}

/****************************************************************************************
Function: void swapStu(LinkList *linklist, int index1, int index2)
Description: 交换linklist中第index1和第index2个节点的学生 
Input:	linklist: 待交换学生的链表 
		index1：第一个要交换的学生
		index2：第二个要交换的学生 
Return:	无 
****************************************************************************************/
void swapStu(LinkList *linklist, int index1, int index2)
{
	if(index1 > index2)
	{
		index2 = index1 + index2;
		index1 = index2 - index1;
		index2 = index2 - index1;
	}
	else if(index1 == index2) return;//保证index1<index2
	if(index1 <= 0 || index2 > linklist->num)
	{
		printf("索引错误");
		return;
	}
	Student *stu1 = (Student*)malloc(sizeof(Student));
	Student *stu2 = (Student*)malloc(sizeof(Student));
	
	stu1 = getStu(linklist, index1);
	stu2 = getStu(linklist, index2);
	deleteStu(linklist, index1, 0);
	deleteStu(linklist, index2-1, 0);
	addToLinkList(linklist, stu2, index1-1);
	addToLinkList(linklist, stu1, index2-1);
}

/****************************************************************************************
Function: LinkList *getStuInfor()
Description: 获取文件"Information.txt"内学生信息，并返回由学生作为节点的链表的指针
Return:	返回储存学生信息的链表的指针 
****************************************************************************************/ 
LinkList *getStuInfor()
{
	FILE *in = fopen("Information.txt", "r");
	LinkList *linklist = newLinkList();
	if(linklist == 0)
	{
		fclose(in);
		printf("内存空间不足，链表创建失败.\n");
		char c;
		printf("是否保存最新修改？(Y/N)(其他任意字符表示不保存)");
		fflush(stdin);
		scanf("%c", &c);
		if(c == 89 || c ==121)
		{
			writeStu(linklist);
		}
		exit(-1);
		return NULL;
	}
	else
	{
		while(!feof(in))
		{
			addToLinkList(linklist, readStu(in), linklist->num);
		}
		fclose(in);
		printf("读取信息如下：\n");
		printLinkList(linklist); 
		return linklist;
	}
}

/****************************************************************************************
Function: readStu
Description: 通过文件指针in，获取下一个学生的信息，并返回指向该学生的指针 
Input:	in:将要进行读取的文件的文件指针 
Return:	返回该学生的指针 
****************************************************************************************/
Student *readStu(FILE *in)
{
	Student *stu = (Student*)malloc(sizeof(Student));
	fscanf(in, "%s\t%s\t%f\t%f\t%f\t%f\t%f\t%f\n", 
		stu->ID, stu->name, &stu->grade[3], &stu->grade[4], &stu->grade[5], &stu->grade[0], &stu->grade[1], &stu->grade[2]);
	return stu;
}

/****************************************************************************************
Function: writeStu
Description: 将当前linklist中的信息保存到文件"Information.txt"中 
Input:	linklist: 将要保存的链表 
Return:	无 
****************************************************************************************/
void writeStu(LinkList *linklist)
{
	FILE *out = fopen("Information.txt", "w");
	Student *stu = stu = (Student*)malloc(sizeof(Student));
	stu = getStu(linklist, 1);
	while(stu != NULL)
	{
		fprintf(out, "%s\t%20s\t%f\t%f\t%f\t%f\t%f\t%f\n", 
			stu->ID, stu->name, stu->grade[3], stu->grade[4], stu->grade[5], stu->grade[0], stu->grade[1], stu->grade[2]);
		stu = stu->next;
	}
	fclose(out);
	printf("写入成功啦！"); 
}

/****************************************************************************************
Function: void printMenu()
Description: 输出菜单 
Input:	linklist: 将要保存的链表 
Return:	无 
****************************************************************************************/
void printMenu()
{
	printf("\n请输入需要执行的操作的序号：\n\
	1. 读取：读取历史成绩表文件 \n\
	2. 插入：插入新记录 \n\
	3. 删除：删除记录 \n\
	4. 查找 \n\
	5. 修改学生成绩 \n\
	6. 按照某个属性对学生排序 \n\
	7. 保存:按照ID对学生排序，并保存成绩表为txt文件 \n\
	8. 列表:列出现在链表中的数据 \n\
	9. 清屏\n\
	10.退出：退出系统\n");
}

/****************************************************************************************
Function: void exitSystem(LinkList *linklist)
Description: 退出系统，并询问用户是否保存linklist 
Input:	linklist: 可能被保存的linklist 
Return:	无 
****************************************************************************************/
void exitSystem(LinkList *linklist)
{
	char c;
	printf("是否保存最新修改？(Y/N)(其他任意字符表示取消退出)");
	fflush(stdin);
	scanf("%c", &c);
	if(c == 89 || c ==121)
	{
		writeStu(linklist);
		exit(-1);
	}
	else if(c == 78 || c == 110)
	{
		exit(-1);
	}
	else
	{
		printf("已取消退出!");
		return;
	}
}






