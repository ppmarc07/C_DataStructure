#include <stdio.h>
#include <stdlib.h>
/*
	循环链表应用：解决约瑟夫环问题
	--zjp
	marc07@qq.com
*/
typedef struct node
{
	int data;
	struct node *pNext;
}JoseListNode;

//建立约瑟夫环的循环链表
//不带头结点：模拟约瑟夫环的工作过程
JoseListNode *Create_JoeList(int arr[], int length)
{
	JoseListNode *head, *pNewNode, *rear;
	int i;
	head = (JoseListNode *)malloc(sizeof(JoseListNode));//创建首结点
	if (head == NULL)
	{
		printf("Create_JoeList fail:head malloc error\n");
		return NULL;
	}
	head->data = arr[0];//首结点赋值  ps:注意与头结点区别，头结点不赋值
	rear = head;
	for (i = 1; i < length; i++)
	{
		pNewNode = (JoseListNode *)malloc(sizeof(JoseListNode));
		if (pNewNode == NULL)
		{
			printf("Create_JoeList fail:pNewNode malloc error\n");
			return NULL;
		}
		pNewNode->data = arr[i];
		rear->pNext = pNewNode;//连接新结点
		rear = pNewNode;//尾指针更新
	}
	rear->pNext = head;//尾指针指向首结点
	return rear;
}

void test_CircularLinkedList_JosephRing(void)
{
	//从位置1开始，初始30人，剩余15人
	int s = 1;//位置1
	int m = 9;//每逢9就出圈
	int k = 15;//生还者要有15人，表明出圈者要有15人
	int arr[30];//30人数编号
	//构造初始序列
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	{
		arr[i] = i + s;//从位置1开始：1 2 3 4 5  6 ....29 30
	}
	//创建循环链表
	JoseListNode *p, *q;
	JoseListNode *rear;
	rear = Create_JoeList(arr, sizeof(arr) / sizeof(int));
	p = rear;//p为遍历指针
	//约瑟夫环处理
	while (k > 0)//出圈人数
	{
		for (int j = 0; j < m - 1; j++)
		{
			p = p->pNext;//指针偏移（人数偏移）
		}
		//此时，p停在m-1处
		q = p->pNext;//q指向第m个人
		printf("第%d个元素出圈\n", q->data);
		//让m-1和m+1相连
		p->pNext = p->pNext->pNext;
		free(q);//释放第m个结点，出圈
		k--;
	}
}