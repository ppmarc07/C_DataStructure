#include <stdio.h>
#include <stdlib.h>
/*
	实现带头结点的链式栈
	(单链表模拟栈，栈顶为头结点的next域)
	--zjp
	marc07@qq.com
*/
typedef struct LSNode
{
	int data;
	struct LSNode *next;
}LinkStackNode;

//创建带头结点的链式栈
void CreateLinkedStack(LinkStackNode **pHead)
{
	*pHead = (LinkStackNode *)malloc(sizeof(LinkStackNode));
	if (pHead == NULL)
	{
		printf("CreateLinkedStack fail:malloc error\n");
		return;
	}
	(*pHead)->next = NULL;
}

//清空栈
void ClearLinkStack(LinkStackNode *pHead)
{
	LinkStackNode *pDel;
	pDel = pHead->next;
	while (pDel != NULL)
	{
		pHead->next = pDel->next;
		free(pDel);
		pDel = pHead->next;//从头结点获取下一个要释放的结点
	}
}

//判断栈是否为空
int IsEmptyLinkStack(LinkStackNode *pHead)
{
	if (pHead->next == NULL)
	{
		printf("栈为空\n");
		return 1;
	}
	return 0;
}

//入栈
void PushLinkedStack(LinkStackNode *pHead, int data)
{
	LinkStackNode *pInsert;
	pInsert = (LinkStackNode *)malloc(sizeof(LinkStackNode));
	if (pInsert == NULL)
	{
		printf("PushLinkedStack fail:malloc error\n");
		return;
	}
	pInsert->data = data;
	pInsert->next = pHead->next;//单链表头插法
	pHead->next = pInsert;
}

//出栈
void PopLinkStack(LinkStackNode *pHead, int *data)
{
	LinkStackNode *pNode;
	if (IsEmptyLinkStack(pHead))
	{
		return;
	}
	pNode = pHead->next;
	*data = pNode->data;
	pHead->next = pNode->next;//将出栈的结点的下一个结点连接上头结点
	free(pNode);//释放出栈结点，防止内存泄漏
	pNode = NULL;//指向NULL，防止野指针
}

//获取栈顶元素
void GetTopElement_LinkStack(LinkStackNode *pHead, int *data)
{
	if (IsEmptyLinkStack(pHead))
	{
		return;
	}
	*data = pHead->next->data;//头结点的下一个结点为栈顶结点
}

//获取栈大小
int GetSize_LinkStack(LinkStackNode *pHead)
{
	int size = 0;
	LinkStackNode *pMove;
	pMove = pHead->next;
	while (pMove != NULL)
	{
		size++;
		pMove = pMove->next;
	}
	return size;
}

//打印栈元素
void PrintLinkStack(LinkStackNode *pHead)
{
	LinkStackNode *pMove;
	pMove = pHead->next;
	while (pMove != NULL)
	{
		printf("%d ", pMove->data);
		pMove = pMove->next;
	}
	printf("\n");
}

//测试链式栈
void test_Stack_Link(void)
{
	int value;
	LinkStackNode *pHead;
	//创建链式栈
	CreateLinkedStack(&pHead);
	//入栈
	PushLinkedStack(pHead, 1);
	PushLinkedStack(pHead, 3);
	PushLinkedStack(pHead, 5);
	PushLinkedStack(pHead, 7);
	PushLinkedStack(pHead, 9);
	//打印栈元素
	PrintLinkStack(pHead);//9 7 5 3 1
	//获取栈大小
	value = GetSize_LinkStack(pHead);
	printf("size:%d\n", value);//5
	//获取栈顶元素
	GetTopElement_LinkStack(pHead, &value);
	printf("栈顶元素 = %d\r\n", value);//9
	//出栈
	PopLinkStack(pHead, &value);
	printf("出栈元素 = %d\r\n", value);//9
	PopLinkStack(pHead, &value);
	printf("出栈元素 = %d\r\n", value);//7
	PopLinkStack(pHead, &value);
	printf("出栈元素 = %d\r\n", value);//5
	PopLinkStack(pHead, &value);
	printf("出栈元素 = %d\r\n", value);//3
	PopLinkStack(pHead, &value);
	printf("出栈元素 = %d\r\n", value);//1
	//出栈溢出测试
	PopLinkStack(pHead, &value);//栈为空
	//清空栈
	ClearLinkStack(pHead);
	//判断栈是否为空
	IsEmptyLinkStack(pHead);//栈为空
}


