#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	实现循环链表创建及合并
	--zjp
	marc07@qq.com
*/
typedef struct node
{
	int data;
	struct node *pNext;
}CLListNode;

//创建循环链表
CLListNode *Create_CLList(int arr[], int length)
{
	CLListNode *head, *pNewNode, *rear;
	int i;
	head = (CLListNode *)malloc(sizeof(CLListNode));
	rear = head;

	for (i = 0; i < length; i++)
	{
		pNewNode = (CLListNode *)malloc(sizeof(CLListNode));
		pNewNode->data = arr[i];
		rear->pNext = pNewNode;
		rear = pNewNode;
	}
	rear->pNext = head;//将尾结点的next域指向头结点，形成循环
	return rear;//返回尾结点指针
}

//遍历输出
void Print_CLList(CLListNode *p)
{
	CLListNode *pHead = p->pNext;//循环链表建立的尾指针的next域指向的是头结点
	CLListNode *pCur = pHead->pNext;
	while (pCur != pHead)
	{
		printf("%d ", pCur->data);
		pCur = pCur->pNext;
	}
	printf("\n");
}

//两个循环链表合并
//输入参数：链表a尾指针，链表b尾指针
//返回值：合并后的链表尾指针
CLListNode *Connect_CLList(CLListNode *La, CLListNode *Lb)
{
	CLListNode *p;
	p = La->pNext;//记录链表a的头结点地址
	La->pNext = Lb->pNext->pNext;//将链表b的第一个结点（非头结点）连接到链表a的尾部
	free(Lb->pNext);//释放链表b的头结点，因为不需要两个头结点，只保留链表a的头结点
	Lb->pNext = p;//将原本链表a的头结点连接到链表b的尾部
	return Lb;//返回新链表的尾指针
/*	        _______________________________
	       |							   |
	链表a 头结点++++++++++++++++++++++++++La |
	        ____________________________|  |
	       |							   |
	链表b 第一个结点+++++++++++++++++++++++++Lb
	*/
}

void test_CircularLinkedList(void)
{
	//单循环链表
	int arr[] = { 11, 22, 33, 44, 55 };
	CLListNode *pRear = Create_CLList(arr, sizeof(arr)/sizeof(int));
	Print_CLList(pRear);//11 22 33 44 55
	printf("===============\n");
	//双循环链表合并
	int La_arr[] = { 1, 3, 5, 7, 9 };
	int Lb_arr[] = { 2, 4, 6, 8, 10};
	CLListNode *La = Create_CLList(La_arr, sizeof(La_arr) / sizeof(int));
	CLListNode *Lb = Create_CLList(Lb_arr, sizeof(Lb_arr) / sizeof(int));
	CLListNode *pRear_Con = Connect_CLList(La, Lb);
	Print_CLList(pRear_Con);//1 3 5 7 9 2 4 6 8 10
}
