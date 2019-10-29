#include <stdio.h>
#include <stdlib.h>
/*
	实现带头结点、尾结点的双向链表(非循环)
	--zjp
	marc07@qq.com
*/
typedef struct DNode
{
	int data;
	struct DNode *prev, *next;
}DListNode;

//1.初始化带头结点、尾结点的双向非循环链表
void Init_DList(DListNode **pHead, DListNode **pTail)
{
	*pHead = (DListNode *)malloc(sizeof(DListNode));
	*pTail = (DListNode *)malloc(sizeof(DListNode));
	if (*pHead == NULL || *pTail == NULL)
	{
		printf("Init_DList fail:malloc error\n");
		return;
	}
	(*pHead)->prev = NULL;//头结点的前置为空指针
	(*pTail)->next = NULL;//尾结点的后继为空指针
	//链表为空时，将头结点和尾结点相连
	(*pHead)->next = (*pTail);
	(*pTail)->prev = (*pHead);
}

//2.创建带头结点、尾结点的双向非循环链表
void Create_DList(DListNode *pHead, DListNode *pTail)
{
	DListNode *pMove;
	DListNode *pInsert = (DListNode *)malloc(sizeof(DListNode));
	if (pInsert == NULL)
	{
		printf("Create_DList fail:malloc error\n");
		return;
	}
	pInsert->prev = NULL;
	pInsert->next = NULL;
	pMove = pHead;
	scanf("%d", &(pInsert->data));
	while (pInsert->data > 0)//插入结点数据，输入0完成创建
	{
		pMove->next = pInsert;
		pInsert->prev = pMove;//串联上各个结点
		pInsert->next = pTail;
		pTail->prev = pInsert;
		pMove = pInsert;

		pInsert = (DListNode *)malloc(sizeof(DListNode));
		if (pInsert == NULL)
		{
			printf("Create_DList fail:malloc error\n");
			return;
		}
		pInsert->prev = NULL;
		pInsert->next = NULL;
		scanf("%d", &(pInsert->data));
	}
}

//3.正序打印链表
void Print_DList(DListNode *pHead, DListNode *pTail)
{
	DListNode *pMove;
	pMove = pHead->next;
	while (pMove != pTail)
	{
		printf("%d ", pMove->data);
		pMove = pMove->next;
	}
	printf("\n");
}

//4.逆序打印链表
void Print_Reverse_DList(DListNode *pHead, DListNode *pTail)
{
	DListNode *pMove;
	pMove = pTail->prev;
	while (pMove != pHead)
	{
		printf("%d ", pMove->data);
		pMove = pMove->prev;
	}
	printf("\n");
}

//5.清除链表中所有元素，置为空表
void Clear_DList(DListNode *pHead, DListNode *pTail)
{
	DListNode *pMove;
	pMove = pHead->next;
	while (pMove != pTail)
	{
		pMove->next->prev = pHead;
		pHead->next = pMove->next;
		free(pMove);
		pMove = pHead->next;
	}
}

//6.计算链表长度
int GetSize_DList(DListNode *pHead, DListNode *pTail)
{
	int length = 0;
	DListNode *pMove;
	pMove = pHead->next;
	while (pMove != pTail)
	{
		length++;
		pMove = pMove->next;
	}
	printf("GetSize_DList = %d\n", length);
	return length;
}

//7.判断链表是否为空
int IsEmpty_DList(DListNode *pHead, DListNode *pTail)
{
	if (pHead->next == pTail)
	{
		printf("当前链表为空\n");
		return 1;
	}
	else
	{
		printf("当前链表非空");
		return 0;
	}
}

//8.获取链表中第pos个结点中的元素，返回值-1表示获取失败
int GetElementFromPos_DList(DListNode *pHead, DListNode *pTail, int pos)
{
	int i = 1;//从第1个结点起
	DListNode *pMove;
	if (pos < 1)
	{
		printf("Error.Please input 'pos' > 0.\n");
		return -1;
	}
	pMove = pHead->next;
	while (pMove != pTail)
	{
		if (i == pos)
		{
			printf("pos = %d, value = %d\n", pos, pMove->data);
			return pMove->data;//返回找到的元素
		}
		i++;
		pMove = pMove->next;
	}
	printf("GetElementFromPos fail.\n");
	return -1;
}

//9.获取给定值x的第一个元素，返回data域地址
int *GetElementAddr_DList(DListNode *pHead, DListNode *pTail, int x)
{
	DListNode *pMove;
	pMove = pHead->next;
	while (pMove != pTail)
	{
		if (pMove->data == x)
		{
			printf("The x=%d addr is 0x%p\n", x, &(pMove->data));
			return &(pMove->data);//返回元素地址
		}
		pMove = pMove->next;
	}
	printf("GetElementAddr fail\n");
	return NULL;
}

//10.将链表中第pos个结点的数据值修改为x
int ModifyElement_DList(DListNode *pHead, DListNode *pTail, int pos, int x)
{
	int i = 1;//从第1个结点起
	DListNode *pMove;
	if (pos < 1)
	{
		printf("please input 'pos' > 0.\n");
		return -1;
	}
	pMove = pHead->next;
	while (pMove != pTail)
	{
		if (i == pos)
		{
			pMove->data = x;//修改元素
			return 1;
		}
		i++;
		pMove = pMove->next;
	}
	printf("ModifyElement_DList fail\n");
	return -1;
}

//11.向链表头部插入元素
int InsertElement_Head_DList(DListNode *pHead, DListNode *pTail, int x)
{
	DListNode *pInsert = (DListNode *)malloc(sizeof(DListNode));
	if (pInsert == NULL)
	{
		printf("InsertElement_Head_DList fail:malloc error\n");
		return -1;
	}
	pInsert->data = x;
	pHead->next->prev = pInsert;//以头结点为基准
	pInsert->next = pHead->next;
	pInsert->prev = pHead;
	pHead->next = pInsert;
	return 1;
}

//12.向链表尾部插入元素
int InsertElement_Tail_DList(DListNode *pHead, DListNode *pTail, int x)
{
	DListNode *pInsert = (DListNode *)malloc(sizeof(DListNode));
	if (pInsert == NULL)
	{
		printf("InsertElement_Head_DList fail:malloc error\n");
		return -1;
	}
	pInsert->data = x;
	pTail->prev->next = pInsert;//以尾结点为基准
	pInsert->prev = pTail->prev;
	pInsert->next = pTail;
	pTail->prev = pInsert;
	return 1;
}

void test_DoublyLinkedList(void)
{
	DListNode *pHead, *pTail;
	//初始化双链表：头结点、尾结点
	Init_DList(&pHead, &pTail);
	//创建双链表
	Create_DList(pHead, pTail);
	//打印双链表
	Print_DList(pHead, pTail);//1 2 3 4 5 6
	//逆序打印双链表
	Print_Reverse_DList(pHead, pTail);// 6 5 4 3 2 1 
	//获取双链表长度
	GetSize_DList(pHead, pTail);//6
	//获取指定位置元素
	GetElementFromPos_DList(pHead, pTail, 5);//5
	//获取指定元素第一个位置的地址
	GetElementAddr_DList(pHead, pTail, 3);//地址随机
	//改变指定位置的元素值
	ModifyElement_DList(pHead, pTail, 3, 10);
	Print_DList(pHead, pTail);//1 2 10 4 5 6
	//头部插入法
	InsertElement_Head_DList(pHead, pTail, 99);
	Print_DList(pHead, pTail);//99 1 2 10 4 5 6
	InsertElement_Head_DList(pHead, pTail, 98);
	Print_DList(pHead, pTail);//98 99 1 2 10 4 5 6
    //尾部插入法
	InsertElement_Tail_DList(pHead, pTail, 100);
	Print_DList(pHead, pTail);//98 99 1 2 10 4 5 6 100
	//清空双链表
	Clear_DList(pHead, pTail);
	//判断双链表是否为空
	IsEmpty_DList(pHead, pTail);//当前链表为空
}



