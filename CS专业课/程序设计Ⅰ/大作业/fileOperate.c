#include "operate.c"

LinkList *getStuInfor();
Student *readStu(FILE *in);
void writeStu(LinkList *linklist);


/****************************************************************************************
Function: getStuInfor
Description: 通过文件指针in，获取文件内学生信息，并返回由学生信息构成的链表的指针 
Calls:
Called By:
Input:	in:将要进行读取的文件的文件指针 
Return:	该函数返回储存学生信息的链表的指针 
****************************************************************************************/ 
LinkList *getStuInfor()
{
	FILE *in = fopen("Information.txt", "r");
	if(in == 0)
	{
		printf("文件内没有记录.已为您创建新的指针");
		return newLinkList();
	}//这个功能还没办法实现 正在研究 
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
Description: 通过文件指针in，获取下一个学生的信息，并返回该学生的指针 
Calls:	NULL 
Called By:	getStuInfor; 
Input:	in:将要进行读取的文件的文件指针 
Return:	该函数返回该学生的指针 
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
Description: 将当前linklist中的信息保存到文件 
Calls:	NULL 
Called By:	
Input:	out:将要进保存进的文件的文件指针 
		linklist: 将要保存的链表 
Return:	该函数返回该学生的指针 
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
