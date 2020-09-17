/*
 *函数清单：
 *struct LinkedList *createLinkedList();新建一个链表并返回其指针 
 *void addObj(struct LinkedList *linkedlist, struct object *toAdd);添加一个object到指定链表的末尾 
 *struct object *createObj(char data[]);创建一个object并返回它的指针 
 *void listLinkedList(struct LinkedList *linkedlist);把链表里的内容列出来 
 *void insertObj(struct LinkedList *linkedlist, struct object *toInsert, int before);插入一个object到一个链表的指定位置（末尾除外） 
 *void deleteObj(struct LinkedList *linkedlist, int index);删除链表中的一个object 
 *void swapObj(struct LinkedList *linkedlist, int index1, int index2); 用于交换两个object 
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct object{
	int index;
	char data[20];
	struct object *next;
	struct object *previous;
	short hasNext;
};

struct LinkedList{
	struct object *head;
	struct object *final;
	int num;
};

struct LinkedList *createLinkedList();
void addObj(struct LinkedList *linkedlist, struct object *toAdd);
struct object *createObj(char data[]);
void listLinkedList(struct LinkedList *linkedlist);
void insertObj(struct LinkedList *linkedlist, struct object *toInsert, int before);
void deleteObj(struct LinkedList *linkedlist, int index);
void swapObj(struct LinkedList *linkedlist, int index1, int index2);


/*
 *Function: void listLinkedList
 *Describe: to list all the object in linkedlist
 *Input://struct LinkedList *linkedlist: which is to be listed
 */
void listLinkedList(struct LinkedList *linkedlist)
{
	int i;
	struct object *p = linkedlist->head;
	printf("链表如下：\n");
	for(i = 0; i < linkedlist->num; i++)
	{
		printf("index = %d\tdata = %s\tprevious = %d\tnext = %d\titSelf = %d\thasNext = %d\n\n",
			 (p)->index, p->data, (p)->previous, (p)->next, p, (p)->hasNext);
		p = p->next;
	}
}

/*
 *Function: createLinkedList
 *Describe: create a linkedlist and return its address
 */
struct LinkedList *createLinkedList()
{
	struct LinkedList *linkedlist = malloc(sizeof(struct LinkedList));
	linkedlist->head = NULL;
	linkedlist->final = NULL;
	linkedlist->num = 0;
	struct object *objS = malloc(sizeof(struct object));
	printf("成功创建一个链表，链表数据如下：\naddress = %d\n\n", linkedlist);
	return linkedlist;
}

/*
 *Function: struct object *createObj
 *Describe: to create a new object with data, and return the address
 *Input://char data[]: to decide the data of the new object
 */
struct object *createObj(char data[])
{
	struct object *obj = malloc(sizeof(struct object));
	obj->next = NULL;
	obj->previous = NULL;
	strcpy(obj->data, data);
	return obj;
}

/*
 *Function: addObject
 *Describe:add toAdd to the end of linkedlist
 *Input://LinkedList linkedlist: which LinkedList to be added to;
 *		//struct object toAdd: what to be added
 */
void addObj(struct LinkedList *linkedlist, struct object *toAdd)
{
	struct object *p = malloc(sizeof(struct object));
	p = toAdd;
	p->index = (linkedlist->num)++;
	if(linkedlist->head == NULL && linkedlist->final == NULL)
	{
		p->previous = p;
		linkedlist->head = p;
		linkedlist->final = p;	
	}
	else if(linkedlist->head->next == linkedlist->head)
	{
		linkedlist->head->next = p;
		linkedlist->head->previous = p;
		p->previous = linkedlist->head;
	} 	
	else
	{ 
		p->previous = linkedlist->final;
		linkedlist->final->next = p;
		linkedlist->head->previous = p;
	}
	p->next = linkedlist->head;
	linkedlist->final = p;
	
	printf("成功添加一个object，该object数据如下：\nindex = %d\tdata = %s\tprevious = %d\tnext = %d\titSelf = %d\thasNext = %d\n\n", p->index, p->data, p->previous, p->next, p, p->hasNext);
}

/*
 *Function: void insertObj
 *Describe: insert toInsert into the No.before in linkedlist
 *Input://struct LinkedList *linkedlist: which LinkedList to insert
 		//struct object *toInsert: what to insert
		//int before: where in the LinkedList to insert
 */
void insertObj(struct LinkedList *linkedlist, struct object *toInsert, int before)
{
	int i;
	if(before > (linkedlist->num-1) || before < 0)
	{
		printf("插入失败: 位置错误");
	}
	else
	{
		if(before == 0)
		{
			toInsert->index = -1;
			linkedlist->final->next = toInsert;
			toInsert->next = linkedlist->head;
			toInsert->previous = linkedlist->final;
			linkedlist->head->previous = toInsert;
			linkedlist->head = toInsert;
			linkedlist->num++;
			struct object *p = linkedlist->head;
			for(i = 0; i < linkedlist->num; i++)
			{
				p->index++;
				p = p->next;
			}
		}
		else
		{
			struct object *p = linkedlist->head;
			//将p指向第before个 
			for(i = 0; i < before; i++)
			{
				p = p->next;
			}
			toInsert->index = before;
			toInsert->next = p;
			toInsert->previous = p->previous;
			p->previous->next = toInsert; 
			p->previous = toInsert;
			linkedlist->num++;
			for(i = before + 1; i < linkedlist->num; i++)
			{
				p->index++;
				p = p->next;
			}
		}
		printf("成功添加一个object，该object数据如下：\nindex = %d\tdata = %s\tprevious = %d\tnext = %d\titSelf = %d\thasNext = %d\n\n",
			 toInsert->index, toInsert->data, toInsert->previous, toInsert->next, toInsert, toInsert->hasNext);
	}
}

/*
 *Function: void deleteObj
 *Describe: delete the No.index obeject in linkedlist
 *Input://struct LinkedList *linkedlist: object of which LinkedList to be deleted;
 		//int index: which to delete
 */
void deleteObj(struct LinkedList *linkedlist, int index)
{
	int i;
	if(0 <= index && index <= linkedlist->num)
	{
		struct object *p = linkedlist->head;
		//将p指向第index个 
		for(i = 0; i < index; i++)
		{
			p = p->next;
		}
		p->previous->next = p->next;
		p->next->previous = p->previous;
		linkedlist->num--;
		p = p->next;
		printf("\n\n%d\n\n", linkedlist->num);
		for(i = index; i < linkedlist->num; i++)
		{
			p->index--;
			p = p->next;
		}
		printf("成功删除第%d个", index);
	}
	else
	{
		printf("删除失败：位置错误");
	}
}

/*
 *Function: void swapObj
 *Describe: to swap the order of two object in linkeddlist
 *Input://struct LinkedList *linkedlist: swap in which LinkedList
 		//int index1:  
		//int index2: which index to swap 
 */
void swapObj(struct LinkedList *linkedlist, int index1, int index2)
{
	int temp, i;
	if(index1 > index2)
	{
		temp = index1;
		index1 = index2;
		index2 = temp;	
	} 
	struct object *p1 = linkedlist->head;
	//将p指向第index1个 
	for(i = 0; i < index1; i++)
	{
		p1 = p1->next;
	}
	struct object *p2 = linkedlist->head;
	//将p指向第index2个 
	for(i = 0; i < index2; i++)
	{
		p2 = p2->next;
	}
	if(0 > index1 || index1 > linkedlist->num-1)
	{
		printf("交换失败：index1位置错误");
	}
	else if(0 > index2 || index2 > linkedlist->num-1)
	{
		printf("交换失败: index2位置错误");
	}
	else if(index1 == index2)
	{
	}
	else 
	{
		if(index2-index1 == 1)
		{
			struct object *oTemp1P = p1->previous;
			struct object *oTemp2N = p2->next;
			oTemp1P->next = p2;
			oTemp2N->previous = p1;
			p1->next = oTemp2N;
			p2->previous = oTemp1P;
			p1->previous = p2;
			p2->next = p1; 
		}
		else
		{
			struct object *oTemp1N = p1->next;
			struct object *oTemp1P = p1->previous;
			struct object *oTemp2N = p2->next;
			struct object *oTemp2P = p2->previous;
			oTemp2N->previous = p1;
			oTemp2P->next = p1;
			oTemp1N->previous = p2;
			oTemp1P->next = p2;
			p1->next = oTemp2N;
			p1->previous = oTemp2P;
			p2->next = oTemp1N;
			p2->previous = oTemp1P;
		}
			p1->index = index2;
			p2->index = index1;
		
		if(index1 == 0 && index2 == linkedlist->num-1)
		{
			
			linkedlist->head = p2;
			linkedlist->final = p1;
		}
		else if(index1 == 0 && index2 != linkedlist->num-1)
		{
			linkedlist->head = p2;
		}
		else if(index2 == linkedlist->num && index1 != 0)
		{
			linkedlist->final = p1;
		}
		printf("成功交换第%d和第%d个\n", index1, index2);
	} 
}





















