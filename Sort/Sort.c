#include <stdio.h>
#include <stdlib.h>

/*
	实现常见排序
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

/****************************************1、冒泡排序**************************************************/
//冒泡排序算法1--初级冒泡排序
void BubbleSort_1(void)
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
void BubbleSort_2(void)
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
void BubbleSort_2_Improve(void)
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

/****************************************2、选择排序**************************************************/
void SelectSort(void)
{
	int i, j, min;
	SqList L = { { 9999, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素保留使用，不参与排序运算

	for (i = 1; i < L.length; i++)
	{
		min = i;
		for (j = i + 1; j <= L.length; j++)
		{
			if (L.r[min] > L.r[j])
			{
				min = j;
			}
		}
		if (min != i)
		{
			Swap(&L, i, min);
		}
	}

	Print_Result(&L);//打印排序结果
}

/****************************************3、直接插入排序**************************************************/
void InsertSort(void)
{
	int i, j;
	SqList L = { { 0, 5, 1, 4, 6, 2 }, 5 };//首元素作哨兵，不参与排序运算

	for (i = 2; i <= L.length; i++)
	{
		if (L.r[i] < L.r[i - 1])
		{
			L.r[0] = L.r[i];//哨兵元素，即此处记录为待操作元素
			for (j = i - 1; L.r[j] > L.r[0]; j--)
			{
				L.r[j + 1] = L.r[j];//元素往后移动，腾出位置
			}
			L.r[j + 1] = L.r[0];//找到了合适位置，插入哨兵元素
		}
	}

	Print_Result(&L);//打印排序结果
}

/****************************************4、希尔排序**************************************************/
void ShellSort(void)
{
	int i, j;
	SqList L = { { 0, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };//首元素作哨兵，不参与排序运算
	int increment = L.length;
	do
	{
		increment = increment / 3 + 1; //此处自定义增量序列
		for (i = increment + 1; i < L.length; i++)
		{
			if (L.r[i] < L.r[i - increment])
			{
				L.r[0] = L.r[i];
				for (j = i - increment; j > 0 && L.r[j] > L.r[0]; j -= increment)
				{
					L.r[j + increment] = L.r[j];
				}
				L.r[j + increment] = L.r[0];
			}//此处实质为直接插入排序，只不过增量变为increment，而不是1
		}
		printf("对增量为 %d 的序列进行希尔排序\n", increment);
		Print_Result(&L);//打印希尔排序中间过程结果
	} while (increment > 1);//根据增量序列，进行多次直接插入排序
	printf("最终希尔排序结果：\n");
	Print_Result(&L);//打印最终排序结果
}

/****************************************5、堆排序**************************************************/
/* 堆排序过程（以大顶堆为例）
（1）构建一个完全二叉树大顶堆，取出堆顶数字（也就是最大值）；
（2）将剩下的数字重新构建一个大顶堆，再取出堆顶数字（也就是剩下值当中的最大值）；
（3）重复以上过程，直到取完堆中数字，最终得到一个从大到小排列的序列
*/
//构建完全二叉树大顶堆
void HeapAddjust(SqList *L, int s, int m)
{
	int temp, j;
	temp = L->r[s];
	for (j = 2 * s; j <= m; j *= 2)//孩子节点下标以2倍跃进，
	{
		if (j < m && L->r[j] < L->r[j + 1])
		{
			++j;	//沿关键字较大的孩子结点
		}
		if (temp >= L->r[j])
		{
			break;
		}
		L->r[s] = L->r[j];//调换
		s = j; //记录调换位置
	}
	L->r[s] = temp;	//插入
}
//堆排序算法
void HeapSort()
{
	int i;
	SqList L = { { 0, 9, 1, 5, 8, 3, 7, 2, 4, 6, 10 }, MAXSIZE };
	//1、构建大顶堆，从下标为n/2的节点开始
	for (i = L.length / 2; i > 0; i--)
	{
		HeapAddjust(&L, i, L.length);
	}
	//2、获取从大到小的堆顶数字，重新构建大顶堆，最后获取结果序列
	for (i = L.length; i > 1; i--)
	{
		Swap(&L, 1, i);//将堆顶记录和当前未经排序的子序列的最后一个记录交换
		HeapAddjust(&L, 1, i - 1);//将L.r[1...i -1]重新构建为大顶堆，从堆顶开始
	}

	Print_Result(&L);//打印最终排序结果
}

/****************************************6、归并排序**************************************************/
//最后一步，归并，排序
void Merge(int SR[], int TR[], int left, int middle, int rightEnd)
{
	int j, k, l;
	for (j = middle + 1, k = left; left <= middle && j <= rightEnd; k++)
	{   
		if (SR[left] < SR[j])
		{
			TR[k] = SR[left++];
		}
		else
		{
			TR[k] = SR[j++];
		}
	}
	if (left <= middle)//右边先结束
	{
		for (l = 0; l <= (middle - left); l++)
		{
			TR[k + l] = SR[left + l];//剩下的元素直接保存到目标区域
		}
	}
	if(j <= rightEnd)//左边先结束
	{
		for (l = 0; l <= (rightEnd - j); l++)
		{
			TR[k + l] = SR[j + l];
		}
	}
}

void MSort(int SR[], int TR1[], int left, int rightEnd)
{
	int middle;
	int TR2[MAXSIZE + 1];
	if (left == rightEnd)
	{
		TR1[left] = SR[rightEnd];
	}
	else
	{
		middle = (left + rightEnd) / 2;//取中间分界
		MSort(SR, TR2, left, middle);//左边递归
		MSort(SR, TR2, middle + 1, rightEnd);//右边递归
		Merge(TR2, TR1, left, middle, rightEnd);//归并，排序
	}
}

//归并排序算法实现
void MergeSort(void)
{
	SqList L = { { 0, 9, 1, 5, 8, 3 }, 5 };//首元素保留，不参与排序
	MSort(L.r, L.r, 1, L.length);//采用递归形式
	Print_Result(&L);//打印最终排序结果
}

/****************************************7、快速排序**************************************************/
/*
	快速排序
	（1）基本思想：通过一趟排序将待排序记录分割成独立的两部分，其中一部分记录的关键字均比另一部分记录的关键字小，
	则可分别对这两部分记录继续进行排序，已达到整个序列有序的目的
	（2）基本过程：a.选定pivot中心轴；b.将大于pivot的数字放在pivot右边，将小于pivot的数字放在pivot左边；
	c.分别对左右子序列重复前两步操作。
*/
int Partition(SqList *L, int low, int high)
{
	int pivotkey;
	pivotkey = L->r[low];//固定选取第1个元素为枢轴
	while (low < high)
	{
		while (low < high && L->r[high] >= pivotkey)
		{
			high--;
		}
		Swap(L, low, high);
		while (low < high && L->r[low] <= pivotkey)
		{
			low++;
		}
		Swap(L, low, high);
	}
}

void QSort(SqList *L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition(L, low, high);
		QSort(L, low, pivot - 1);
		QSort(L, pivot + 1, high);
	}
}

//快速排序算法实现1
void QuickSort()
{
	SqList L = { { 0, 9, 1, 5, 8, 3, 8 }, 6 };//首元素保留，不参与排序
	QSort(&L, 1, L.length);
	Print_Result(&L);//打印最终排序结果
}

/****快速排序算法优化1****/
int Partition_2(SqList *L, int low, int high)
{
	int pivotkey;
	int mid = low + (high - low) / 2; // 即(low + high) / 2，但为了避免两个整数相加超出int范围，则转为等式low + (high - low) / 2
	//优化一：对pivotkey值进行取值优化，三数取中(去掉大值和小值，取中间值为枢轴）
	if (L->r[low] > L->r[high])
	{
		Swap(L, low, high);
	}
	if (L->r[mid] > L->r[high])
	{
		Swap(L, mid, high);
	}
	if (L->r[mid] > L->r[low])
	{
		Swap(L, mid, low);
	}
	/*此时L.r[low]已经为整个序列左右中三个关键字的中间值*/

	pivotkey = L->r[low];
	L->r[0] = pivotkey;//将枢轴值存到哨兵处
	//优化二：优化不必要的交换
	while (low < high)
	{
		while (low < high && L->r[high] >= pivotkey)
		{
			high--;
		}
		L->r[low] = L->r[high];//直接替换，因为首次遍历时的L->r[low]已经保存到哨兵处
		while (low < high && L->r[low] <= pivotkey)
		{
			low++;
		}
		L->r[high] = L->r[low];//直接替换
	}
	L->r[low] = L->r[0];//最后的位置替换为哨兵元素即可
	return low;//返回枢轴所在位置
}

void QSort_2(SqList *L, int low, int high)
{
	int pivot;
	if (low < high)
	{
		pivot = Partition_2(L, low, high);
		QSort_2(L, low, pivot - 1);
		QSort_2(L, pivot + 1, high);
	}
}
//对上面QSort_2函数进行优化
#define MAX_LENGTH_INSERT_SORT	7
void QSort_2_new(SqList *L, int low, int high)
{
	int pivot;
	if ((high - low) > MAX_LENGTH_INSERT_SORT)
	{
		while(low < high)
		pivot = Partition_2(L, low, high);
		QSort_2_new(L, low, pivot - 1);
		low = pivot + 1;//优化一：尾递归优化，减少一次递归调用
	}
	else//优化二：小数据量转化为直接插入算法为佳
	{
		//InsertSort(L); //此处需自行修改为带参数的直接插入算法
	}
}

//快速排序算法实现2--优化1
void QuickSort_2()
{
	SqList L = { { 0, 9, 1, 5, 8, 3, 8 }, 6 };//首元素保留，不参与排序
	QSort_2(&L, 1, L.length);
	Print_Result(&L);//打印最终排序结果
}

void test_Sort(void)
{
	//1、冒泡排序
	//BubbleSort_1();
	//BubbleSort_2();
	//BubbleSort_2_Improve();

	//2、选择排序
	//SelectSort();

	//3、直接插入排序
	//InsertSort();

	//4、希尔排序
	//ShellSort();

	//5、堆排序
	//HeapSort();

	//6、归并排序
	//MergeSort();

	//7、快速排序
	//QuickSort();
	QuickSort_2();
}

