#include <stdio.h>
#include <stdlib.h>

/*
	实现常见查找算法
	--zjp
	marc07@qq.com
*/
#define MAX_SIZE	20 
typedef struct
{
	int arr[MAX_SIZE + 1]; //数据集合（1个哨兵 + 10个数据）
	int length;
}SearchDataStruct;

void printResult(int res)
{
	printf("result index is : %d\n", res);
}

/****************************************1、顺序表查找**************************************************/
void Sequential_Search(void)
{
	int i;
	int keyValue = 15;//待查找元素
	SearchDataStruct search = { { 9999, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }, 10};//模拟数据，首元素为哨兵，保留使用
	search.arr[0] = keyValue;//哨兵元素
	i = search.length;
	while (search.arr[i] != keyValue)
	{
		i--;
	}
	printResult(i);//打印结果
}

/****************************************2、有序表查找**************************************************/
//（1）折半查找
void Binary_Search(void)
{
	int low, high, mid, result = -1;
	int keyValue = 15;//待查找元素
	SearchDataStruct search = { { 9999, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }, 10 };//模拟数据，首元素为哨兵，保留使用
	low = 1;
	high = search.length;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (keyValue < search.arr[mid])
		{
			high = mid - 1;
		}
		else if (keyValue > search.arr[mid])
		{
			low = mid + 1;
		}
		else//找到待查找元素
		{	
			result = mid;
			break;
		}
	}
	printResult(result);
}

//（2）插值查找（按比例查找）
//插值查找，相对于折半查找，对mid进行修改即可。
void Inter_Search(void)
{
	int low, high, mid, result = -1;
	int keyValue = 15;//待查找元素
	SearchDataStruct search = { { 9999, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }, 10 };//模拟数据，首元素为哨兵，保留使用
	low = 1;
	high = search.length;
	while (low <= high)
	{
		//对mid = low + (high - low) * (1 / 2)中的1/2进行优化，变为(keyValue - search.arr[low]) / (search.arr[high] - search.arr[low]);
		mid = low + (high - low) * (keyValue - search.arr[low]) / (search.arr[high] - search.arr[low]);
		if (keyValue < search.arr[mid])
		{
			high = mid - 1;
		}
		else if (keyValue > search.arr[mid])
		{
			low = mid + 1;
		}
		else//找到待查找元素
		{
			result = mid;
			break;
		}
	}
	printResult(result);
}

//(3)斐波那契查找
//a.首先生成斐波那契数列
//fib_arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144....};
#define FIB_MAXSIZE 15  
void ProduceFib(int *fib, int size)
{
	int i;
	fib[0] = 0;
	fib[1] = 1;
	fib[2] = 1;
	for (i = 3; i < size; i++)
	{
		fib[i] = fib[i - 1] + fib[i - 2];
	}
}
//b.实现斐波那契查找算法
void Fibonacci_Search(void)
{
	int low, high, mid, k, i, fib_arr[FIB_MAXSIZE], result = -1;
	int keyValue = 9;//待查找元素
	//SearchDataStruct search = { { 9999, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 }, 10 };//模拟数据，首元素为哨兵，保留使用
	SearchDataStruct search = { { 9999, 5, 7, 9, 11, 13, 15, 17, 19 }, 8 };//模拟数据，首元素为哨兵，保留使用
	k = 0;
	low = 1;
	high = search.length;
	ProduceFib(fib_arr, FIB_MAXSIZE);//生成斐波那契数列 fib_arr[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144....};
	while (search.length > fib_arr[k])
	{
		k++;
	}
	for (i = search.length; i < fib_arr[k]; i++)
	{
		search.arr[i] = search.arr[search.length]; //补全元素
	}

	while (low <= high)
	{
		mid = low + fib_arr[k - 1] - 1;//根据斐波那契数列进行黄金分割  
		if (keyValue < search.arr[mid])
		{
			high = mid - 1;
			k = k - 1;
		}
		else if (keyValue > search.arr[mid])
		{
			low = mid + 1;
			k = k - 2;
		}
		else
		{
			if (mid <= search.length)//若相等则说明mid即为查找到的位置
			{
				result = mid;
			}
			else
			{
				result = search.length;//若mid > length说明是补全数值，返回search.length
			}
			break;
		}
	}
	printResult(result);
}

extern void test_DenseIndex(void);

void test_Search(void)
{
	//1、顺序表查找
	//Sequential_Search();

	//2、有序表查找
	//Binary_Search();//折半查找
	//Inter_Search();//插值查找
	//Fibonacci_Search();//斐波那契查找

	//3、稠密索引-见文件DenseIndexSearch.c
	test_DenseIndex();
}
