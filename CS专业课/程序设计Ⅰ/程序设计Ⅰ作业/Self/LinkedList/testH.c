#include "LinkedList.h" 

int main()
{
	
	struct LinkedList *linkedlist = createLinkedList(linkedlist);//创建一个链表 
	
	addObj(linkedlist, createObj("wHAT the?"));
	addObj(linkedlist, createObj("what THe?"));
	addObj(linkedlist, createObj("what the?"));//添加三个object到链表里 
	listLinkedList(linkedlist); 
	
	insertObj(linkedlist, createObj("hiahiahia"), 1);//插入一个object
	listLinkedList(linkedlist);
	
	swapObj(linkedlist, 1,2);
	listLinkedList(linkedlist);//交换位于1和2的object 
	
	deleteObj(linkedlist, 2);
	listLinkedList(linkedlist);//删除第二个object 
	return 0;
	
}
