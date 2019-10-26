#include <stdio.h>
/*
	实现静态数组循环队列
	--zjp
	marc07@qq.com
*/

#define QUEUE_SIZE	5
int queue[QUEUE_SIZE];
int head = 0;
int tail = 0;

//入队列
void EnQueue(int value)
{
	if (isQueueFull())
	{
		printf("队列已满，无法从队尾插入元素\n");
	}
	else
	{
		queue[tail] = value;
		tail = (tail + 1) % QUEUE_SIZE;
	}
}

//出队列
int DeQueue(void)
{
	int temp;
	if (isQueueEmpty())
	{
		printf("队列为空，元素无法出队列\n");
		return -1;
	}
	else
	{
		temp = queue[head];
		head = (head + 1) % QUEUE_SIZE;
	}
	printf("delete %d\n", temp);
	return temp;
}

//判断队列是否为空
int isQueueEmpty(void)
{
	if (head == tail)
	{
		return 1;//队列为空
	}
	else
	{
		return 0;//队列非空
	}
}

//判断队列是否已满
/*
*  这里判断队满的的方法：
牺牲一个单元来区分队空和队满，入队时少用一个队列单元。如果数组的大小为Size,那么实际只能存放(Size-1)个元素。（这是比较常用的判满的方式）
*
*/
int isQueueFull(void)
{
	if ((tail + 1) % QUEUE_SIZE == head)
	{
		return 1;//队列为满
	}
	else
	{
		return 0;//队列非满
	}
}

//打印出队列元素
void PrintQueue(void)
{
	int i = head;
	while(i != tail)
	{
		printf("%d ", queue[i]);
		i = (i + 1) % QUEUE_SIZE;
	}
	printf("\n");
}

//静态数组循环队列测试
void test_Queue_Array(void)
{
	EnQueue(10);
	EnQueue(20);
	EnQueue(30);
	EnQueue(40);
	PrintQueue();//10 20 30 40
	EnQueue(50);//"队列已满，无法从队尾插入元素"
	PrintQueue();//10 20 30 40
	DeQueue();//delete 10
	PrintQueue();//20 30 40
	EnQueue(50);
	PrintQueue();//20 30 40 50
	DeQueue();//delete 20
	DeQueue();//delete 30
	DeQueue();//delete 40
	DeQueue();//delete 50
	DeQueue();//"队列为空，元素无法出队列"
}
