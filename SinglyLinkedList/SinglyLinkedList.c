#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	实现带有头结点的单链表
	--zjp
	marc07@qq.com
*/
typedef int elemType;
typedef struct NodeList
{
	elemType element;
	struct NodeList *next;
}Node;

//1.初始化带头结点的单链表
void InitialList(Node **pNode)
{
	*pNode = (Node *)malloc(sizeof(Node));
	if (*pNode != NULL)
	{
		(*pNode)->next = NULL;
	}
	else
	{
		printf("InitialList fail:malloc error\n");
		return;
	}
	printf("InitialList success\n");
}

//2.创建带头结点的单链表
void CreateList(Node *pNode)
{
	Node *pInsert;
	Node *pMove;
	pInsert = (Node *)malloc(sizeof(Node));
	if (pInsert == NULL)
	{
		printf("CreateList fail:malloc error\n");
		return;
	}
	memset(pInsert, 0, sizeof(Node));
	pInsert->next = NULL;
	scanf("%d", &(pInsert->element));
	pMove = pNode;
	while (pInsert->element > 0)
	{
		pMove->next = pInsert;
		pMove = pInsert;
		pInsert = (Node *)malloc(sizeof(Node));
		if (pInsert == NULL)
		{
			printf("CreateList fail:malloc error\n");
			return;
		}
		memset(pInsert, 0, sizeof(Node));
		pInsert->next = NULL;
		scanf("%d", &(pInsert->element));
	}
	printf("CreateList success\n");
}

//3.打印带头结点的单链表
void PrintList(Node *pNode)
{
	/**
	*  注意，如果单链表为空（只有一个头结点），则也显示打印成功，只是里面没有元素，打出来为空；
	*/
	Node *pMove;
	pMove = pNode->next;
	while (pMove != NULL)
	{
		printf("%d ", pMove->element);
		pMove = pMove->next;
	}
	printf("\n");
	printf("PrintList success\n");
}

//4.清除线性表中的所有元素，即释放所有节点（除了头结点），使之成为一个空表
void ClearList(Node *pNode)
{
	Node *pMove;
	pMove = pNode->next;
	while (pMove != NULL)
	{
		pNode->next = pMove->next;
		free(pMove);
		pMove = pNode->next;
	}
	printf("ClearList success\n");
}

//5.获取带头结点的单链表的长度
int GetListSize(Node *pNode)
{
	int i = 0;
	Node *pMove;
	pMove = pNode->next;
	while (pMove != NULL)
	{
		i++;
		pMove = pMove->next;
	}
	return i;
}

//6.判断带头结点的单链表是否为空，为空则返回1，否则返回0
int IsEmptyList(Node *pNode)
{
	int isEmptyFlag = 0;
	if (pNode->next == NULL)
	{
		isEmptyFlag = 1;//链表为空
	}
	else
	{
		isEmptyFlag = 0;//链表非空
	}
	return isEmptyFlag;
}

//7.获取单链表中第pos个结点中的元素，若返回-1，表示没有找到
int GetElement(Node *pNode, int pos)
{
	int i = 1;
	Node *pMove;
	pMove = pNode->next;
	while (pMove != NULL)
	{
		if (i == pos)
		{
			return pMove->element;
		}
		pMove = pMove->next;
		i++;
	}
	printf("GetElement fail:no element at pos=%d\n", pos);
	return -1;
}

//8.从单链表中查找具有给定值x的第一个元素，若查找成功则返回该结点data域的存储地址，否则返回NULL
int *GetElemAddr(Node *pNode, elemType x)
{
	int i;
	Node *pMove;
	pMove = pNode->next;
	while (pMove != NULL)
	{
		if (pMove->element == x)
		{
			return &(pMove->element);
		}
		pMove = pMove->next;
	}
	printf("GetElemAddr fail:no %d in pNode\n", x);
	return NULL;
}

//9.把单链表中第pos个结点的值修改为x的值
Node *ModifyElem(Node *pNode, int pos, elemType x)
{
	int i = 1;
	Node *pMove;
	pMove = pNode->next;
	while (pMove != NULL)
	{
		if (pos == i)
		{
			pMove->element = x;
			return pNode;
		}
		i++;
		pMove = pMove->next;
	}
	return NULL;
}

//10.向单链表的表头插入一个元素
Node *InsertListHead(Node *pNode, elemType x)
{
	Node *pInsert;
	pInsert = (Node *)malloc(sizeof(Node));
	if (pInsert == NULL)
	{
		return NULL;
	}
	memset(pInsert, 0, sizeof(Node));
	pInsert->element = x;
	pInsert->next = pNode->next;
	pNode->next = pInsert;
	return pNode;
}

// 11.向单链表的末尾添加一个元素
Node *InsertListTail(Node *pNode, elemType x)
{
	Node *pInsert;
	Node *pMove;
	pInsert = (Node *)malloc(sizeof(Node));
	if (pInsert == NULL)
	{
		return NULL;
	}
	memset(pInsert, 0, sizeof(Node));
	pInsert->element = x;
	pInsert->next = NULL;
	pMove = pNode;
	while (pMove->next != NULL)
	{
		pMove = pMove->next;
	}
	pMove->next = pInsert;
	return pNode;
}

//单链表测试
void test_SinglyLinkedList(void)
{
	Node *pNode;
	Node *pTest = NULL;
	int temp = 0;
	int *test;

	InitialList(&pNode);//初始化链表
	CreateList(pNode);//创建链表（输入0完成创建）:1 2 3 4 5 6 7 8 9 10 
	PrintList(pNode);//打印链表所有元素：1 2 3 4 5 6 7 8 9 10 
	temp = GetListSize(pNode);//获取链表长度：10
	printf("GetListSize = %d\n", temp);
	temp = GetElement(pNode, 5);//获取链表第5个位置的元素:5
	printf("GetElement = %d\n", temp);
	test = GetElemAddr(pNode, 5);//获取链表第5个位置元素的地址：0xxx(地址随机)
	if(test != NULL)
	{
		printf("GetElemAddr = 0x%p\n", test);
	}
	pTest = ModifyElem(pNode, 10, 20);//改变链表中第10个位置元素为20:
	if (pTest != NULL)
	{
		PrintList(pNode);//1 2 3 4 5 6 7 8 9 20 
	}
	pTest = InsertListHead(pNode, 50);//在链表头部插入元素50:50 1 2 3 4 5 6 7 8 9 20
	if (pTest != NULL)
	{
		PrintList(pNode);
	}
	pTest = InsertListTail(pNode, 100);//在链表尾部插入元素100:50 1 2 3 4 5 6 7 8 9 20 100
	if (pTest != NULL)
	{
		PrintList(pNode);
	}
	ClearList(pNode);//清除链表
	PrintList(pNode);//打印清除链表后的链表:空
	temp = GetListSize(pNode);//获取清除链表后的长度：为0
	printf("GetListSize = %d\n", temp);
}








