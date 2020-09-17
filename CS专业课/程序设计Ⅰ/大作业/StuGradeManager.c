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
#include "fileOperate.c"

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


