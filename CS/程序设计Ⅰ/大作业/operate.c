#include "find.c"

void addToLinkList(LinkList *linklist, Student *stu, int index);
void editGrade();
void deleteStu(LinkList *linklist, int index, int mode);
void sortStu(LinkList *linklist);
void strSort(LinkList *linklist, int item);
void gradeSort(LinkList *linklist, int item);
void swapStu(LinkList *linklist, int index1, int index2);


/****************************************************************************************
Function: addtoLinkList
Description: 将学生stu加入到链表linklist的尾部 
Calls:	getStu();
		printLinkList();
Called By:	getStuInfor(); 
Input:	linklist: 待添加学生的链表
		stu: 待插入的学生
		index: 若index = -1 表示询问用户插入到哪；若0 <= index && index <= linklist->num的时候则直接插入第index个节点之后
Return:	无 
****************************************************************************************/
void addToLinkList(LinkList *linklist, Student *stu, int index) // 
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

void deleteStu(LinkList *linklist, int index, int mode) //mode == 1 才释放删除的Student的内存 
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
Function: editGrade
Description: 修改某个学生的成绩 
Calls:	
Called By:	
Input:	linklist: 该学生所在链表 
		ID: 要修改的学生的ID  
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
/**************************************************************	
	if(index2 - index1 > 1)
	{
		stu1 = getStu(linklist, index1-1);
		stu2 = getStu(linklist, index2-1);
		Student *temp = (Student*)malloc(sizeof(Student));
		temp = stu1->next->next;
		stu1->next->next = stu2->next->next;
		stu2->next->next = temp;
		temp = stu1->next;
		stu1->next = stu2->next;
		stu2->next = temp;
	}
	else if(index2 - index1 == 1)
	{
		stu1 = getStu(linklist, index1-1);
		stu2 = getStu(linklist, index2-1);
		Student *temp = (Student*)malloc(sizeof(Student));
		temp = stu2->next;
		stu1->next->next = stu2->next->next;
		stu1->next = temp;
		temp->next = stu2;
	}
//纪念一下我傻逼的算法 
***************************************************************/
	 
}







