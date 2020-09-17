#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#define N 20

struct Student{
	int index;
	long long ID;
	int grade;
	struct Student *next;
};

struct LinkList{
	int num;
	struct Student *head;
};

typedef struct Student Student;
typedef struct LinkList LinkList;

LinkList *LLCreate();
Student *ObjCreate(long long ID, int grade);
void ObjAdd(LinkList *linklist, Student *student);
void Print(LinkList *linklist);
void scan(FILE *in, LinkList *linklist);
void PrintStuInf(Student *student);
void IDOrder(LinkList *Lc);
Student *getObj(LinkList *linklist, int index);
void LJoint(LinkList *Lc, LinkList *La, LinkList *Lb);
void ObjSwap(LinkList *linklist, int index1, int index2);

int main()
{
	FILE *in = NULL;
	LinkList *La = LLCreate();
	LinkList *Lb = LLCreate();
	LinkList *Lc = LLCreate();
	in = fopen("La.dat", "r");
	scan(in, La);
	in = fopen("Lb.dat", "r");
	scan(in, Lb);
	fclose(in);
	printf("原链表a:\n"); 
	Print(La);
	printf("原链表b:\n");
	Print(Lb);
	LJoint(Lc, La, Lb);
	IDOrder(Lc);
	
	Print(Lc);
}
//从文档读入信息并存放到linklist中 
void scan(FILE *in, LinkList *linklist)
{
	char c;
	long long ID;
	int grade;
	int i = 0;
	if(in != NULL)
	{
		while(!feof(in))
		{
			fscanf(in, "%lld,%d", &ID, &grade);
			ObjAdd(linklist, ObjCreate(ID, grade));
		}
	}
}
//创建链表 
LinkList *LLCreate()
{
	LinkList *linklist = (LinkList*)malloc(sizeof(LinkList));
	if(linklist == NULL)
	{
		printf("no enough memory");
		return;
	}
	linklist->num = 0;
	linklist->head = ObjCreate(0, 0);
	linklist->head->next = NULL;
	return linklist;
}
//创建Student 
Student *ObjCreate(long long ID, int grade)
{
	Student *student = (Student*)malloc(sizeof(Student));
	if(student == NULL)
	{
		printf("no enough memory");
		return;
	}
	student->ID = ID;
	student->grade = grade; 
	student->next = NULL;
	return student;
}

//向linklist的尾部加入student 
void ObjAdd(LinkList *linklist, Student *student)
{
	int i;
	Student *sp = linklist->head;
	for(i = 0; i < linklist->num; i++)
	{
		sp = sp->next;
	}
	sp->next = student;
	linklist->num++;
	student->index = linklist->num;
}

//合并 
void LJoint(LinkList *Lc, LinkList *La, LinkList *Lb)
{
	int i;
	Student *sp = La->head;
	for(i = 0; i < La->num; i++)
	{
		sp = sp->next;
	}
	sp->next = Lb->head->next;
	Lc->head->next = La->head->next;
	Lc->num = La->num + Lb->num;
}

//交换 
void ObjSwap(LinkList *linklist, int index1, int index2)
{
	int i;
	Student *sp1 = getObj(linklist, index1-1);
	Student *sp2 = getObj(linklist, index2-1);
	Student *tp = (Student*)malloc(sizeof(Student));
	if((index1-index2) == 1 || (index1-index2)== -1)
	{
		Student *tp2 = (Student*)malloc(sizeof(Student));
		tp = sp2->next->next;
		tp2 = sp2->next;
		
		sp2->next = tp;
		tp2->next = sp2;
		sp1->next = tp2;
		
	}
	else
	{
		tp = sp1->next->next;
		sp1->next->next = sp2->next->next;
		sp2->next->next = tp;
		tp = sp1->next;
		sp1->next = sp2->next;
		sp2->next = tp;	
	}

}

//排序 
void IDOrder(LinkList *Lc)
{
	int i,j,min, num = Lc->num;
	for(i = 1; i < num+1; i++)
	{
		min = i;
		for(j = i+1; j < num+1; j++)
		{
			if((getObj(Lc, j)->ID < getObj(Lc, min)->ID))
			{
				min = j;
			} 
		}
		if(min != i) ObjSwap(Lc, i, min);
	}
}
//返回linklist对应链表中index对应的Student的指针 
Student *getObj(LinkList *linklist, int index)
{
	int i = 0;
	Student *sp = linklist->head;
	for(; i < index; i++)
	{
		sp = sp->next;
	}
	return sp;
}
//打印链表中所有信息内容 
void Print(LinkList *linklist)
{
	Student *ps = linklist->head->next;
	printf("学号\t\t成绩\n");
	while(ps != NULL)
	{
		printf("%lld\t\t%d\n",ps->ID, ps->grade);
		ps = ps->next;
	}
}

void PrintStuInf(Student *student)
{
	printf("ID: %lld\t\tgrade: %d", student->ID, student->grade);
}




















