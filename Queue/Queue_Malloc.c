#include <stdio.h>
#include <string.h>
/*
	实现动态内存循环队列(名字自定，仅用于辨识文件内容)
	--zjp
	marc07@qq.com
*/
typedef enum
{
	ERROR = 0,
	OK = 1,
	TRUE = 2,
	FALSE = 3
}STATUS;

typedef struct
{
	int *pBase;
	int front;
	int rear;
	int maxSize;
}queue;

//创建队列
STATUS initQueue(queue *pQueue, int queueCapacity)
{
	pQueue->pBase = (int *)malloc(queueCapacity * sizeof(int));
	if (pQueue->pBase == NULL)
	{
		printf("initQueue fail:malloc error\n");
		return ERROR;
	}
	pQueue->front = 0;
	pQueue->rear = 0;
	pQueue->maxSize = queueCapacity;
	return OK;
}

//销毁队列
void destroyQueue(queue *pQueue)
{
	free(pQueue);
	pQueue = NULL;//避免成为野指针
}

//清空队列
void clearQueue(queue *pQueue)
{
	pQueue->front = 0;
	pQueue->rear = 0;
}

//判断队列是否为空
STATUS isEmptyQueue(queue *pQueue)
{
	if (pQueue->front == pQueue->rear)
	{
		return TRUE;
	}
	return FALSE;
}

//判断队列是否为满
STATUS isFullQueue(queue *pQueue)
{
	if ((pQueue->rear + 1) % pQueue->maxSize == pQueue->front)
	{
		return TRUE;
	}
	return FALSE;
}

//获取队列长度
int getQueueLen(queue *pQueue)
{
	return (pQueue->rear - pQueue->front + pQueue->maxSize) % pQueue->maxSize;
}

//新元素入队
STATUS enQueue(queue *pQueue, int element)
{
	if (isFullQueue(pQueue) == TRUE)
	{
		printf("队列已满，入队失败\n");
		return ERROR;
	}
	pQueue->pBase[pQueue->rear] = element;
	pQueue->rear = (pQueue->rear + 1) % pQueue->maxSize;
	return OK;
}

//元素出队
STATUS deQueue(queue *pQueue, int *pElement)
{
	if (isEmptyQueue(pQueue) == TRUE)
	{
		printf("队列为空，出队失败\n");
		return ERROR;
	}
	*pElement = pQueue->pBase[pQueue->front];
	pQueue->front = (pQueue->front + 1) % pQueue->maxSize;
	return OK;
}

//遍历队列
void printQueue(queue *pQueue)
{
	int temp = pQueue->front;//此处不允许直接操作pQueue->front，否则影响原数值，应用局部变量替代
	while (temp != pQueue->rear)
	{
		printf("%d ", pQueue->pBase[temp]);
		temp = (temp + 1) % pQueue->maxSize;
	}
	printf("\n");
}

void test_Queue_Malloc(void)
{
	int temp = 0;
	int value = 0;
	queue *pQueue;
	pQueue = (queue *)malloc(sizeof(queue));
	if (pQueue == NULL)
	{
		printf("queue malloc error\n");
		return;
	}
	//初始化队列，元素容量为5
	initQueue(pQueue, 5);
	//元素入队
	enQueue(pQueue, 1);
	enQueue(pQueue, 2);
	enQueue(pQueue, 3);
	enQueue(pQueue, 4);
	printQueue(pQueue);//1 2 3 4
	enQueue(pQueue, 5);//队列已满，入队失败
	printQueue(pQueue);//1 2 3 4
	temp = getQueueLen(pQueue);
	printf("getqueuelen = %d\n", temp);//getqueuelen = 4
	//出队一个元素，让出空位置
	deQueue(pQueue, &value);
	printf("delete %d\n", value);//delete 1
	printQueue(pQueue);//2 3 4
	temp = getQueueLen(pQueue);
	printf("getqueuelen = %d\n", temp);//getqueuelen = 3
	//出队一个元素后，空位置插入一个新元素
	enQueue(pQueue, 5);
	printQueue(pQueue);// 2 3 4 5 
	temp = getQueueLen(pQueue);
	printf("getqueuelen = %d\n", temp);//getqueuelen = 4

	//清空队列，重新插入元素
	clearQueue(pQueue);
	enQueue(pQueue, 10);
	enQueue(pQueue, 20);
	enQueue(pQueue, 30);
	enQueue(pQueue, 40);
	printQueue(pQueue);//10 20 30 40
	temp = getQueueLen(pQueue);
	printf("getqueuelen = %d\n", temp);//getqueuelen = 4

	//销毁队列
	destroyQueue(pQueue);
}