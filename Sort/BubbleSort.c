#include <stdio.h>
#include <stdlib.h>

/*
	实现冒泡排序
	--zjp
	marc07@qq.com
*/

#define MAXSIZE	10
typedef struct
{
	int r[MAXSIZE + 1];	//用于存储要排序的数组，r[0]用作哨兵或临时变量
	int length;			//用于记录顺序表的长度
}SqList;

typedef enum
{
	FALSE = 0,
	TRUE
}Status;

//交换数组前后两个元素
void Swap(SqList *L, int i, int j)
{
	int temp = L->r[i];
	L->r[i] = L->r[j];
	L->r[j] = temp;
}

//打印排序结果
void Print_Result(SqList *L)
{
	printf("sort result: \n");
	for (int i = 1; i <= L->length; i++)
	{
		printf("%d ", L->r[i]);
	}
	printf("\n");
}

//冒泡排序算法1--初级冒泡排序
void BubbleSort_1()
{
	int i, j;
	SqList L = { { 9999, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算

	for (i = 1; i <= L.length; i++)
	{
		for (j = i + 1; j <= L.length; j++)
		{
			if (L.r[i] > L.r[j])	//升序
			{
				Swap(&L, i, j);
			}
		}
	}

	Print_Result(&L);//打印排序结果
}

//冒泡排序算法2--正宗冒泡排序
void BubbleSort_2()
{
	int i, j;
	SqList L = { { 9999, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算

	for (i = 1; i < L.length; i++)
	{
		for (j = L.length - 1; j >= i; j--)
		{
			if (L.r[j] > L.r[j + 1])//冒泡升序
			{
				Swap(&L, j, j+1);
			}
		}
	}

	Print_Result(&L);//打印排序结果
}

//冒泡排序算法2--冒泡优化
//可避免在大部分元素已有序的情况下进行无意义的循环判断
void BubbleSort_2_Improve()
{
	int i, j;
	Status flag = TRUE;//添加标记处理
	SqList L = { { 9999, 2, 1, 3, 4, 5, 6, 7, 8, 9, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算
	//注意，上面元素已大部分有序
	for (i = 1; i < L.length && flag; i++)//加入flag
	{
		flag = FALSE;//默认FALSE
		for (j = L.length - 1; j >= i; j--)
		{
			if (L.r[j] > L.r[j+1])
			{
				Swap(&L, j, j+1);
				flag = TRUE; //修改标记，用于指示需要进行下一次循环判断，否则排序完成。
			}
		}
	}

	Print_Result(&L);//打印排序结果
}

void test_BubbleSort(void)
{
	BubbleSort_1();
	BubbleSort_2();
	BubbleSort_2_Improve();
}

