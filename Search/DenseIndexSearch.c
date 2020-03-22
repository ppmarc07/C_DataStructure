#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*
	查找算法-线性索引查找-稠密索引-案例分析
	--zjp
	marc07@qq.com
*/

//案例实现：班级有10个学生，现在进行稠密索引查找

#define MAX_DATA_SIZE	10
typedef struct _Student  //记录
{
	int key;//索引关键码，此处可理解学生学号
	char name[10]; //学生信息
	struct _Student *next;
}Student;

typedef struct _Index //索引
{
	int key;
	Student *ind;
}Index;

Student* S;
Index I[MAX_DATA_SIZE];//首元素作保留使用，用于记录索引表长度
int Insert_Search(Index *ind, int n, int key, int *loc);

//插入信息，及更新索引表
void AddInfo(int key, char* name)
{
	//创建数据
	Student *ST;
	int loc, i;
	ST = (Student *)malloc(sizeof(Student));
	strcpy(ST->name, name);
	ST->key = key;
	ST->next = S;//链表头部插入法
	S = ST;
	//插入索引
	if (Insert_Search(I, I[0].key, ST->key, &loc) == -1)
	{
		for (i = I[0].key + 1; i > loc; i--)//loc为目标应插入的位置，类似直接插入排序算法
		{	//腾出空间	
			I[i].key = I[i - 1].key;
			I[i].ind = I[i - 1].ind;
		}
		//插入目标元素
		I[i].key = ST->key;
		I[i].ind = ST;
		I[0].key++;    //存储数组大小
	}
}

//查找元素
int Search_Info(int key, Student** stu)
{
	int loc, res = -1;
	res = Insert_Search(I, I[0].key, key, &loc);
	if (res != -1) {
		*stu = I[loc].ind;
		printf("the target key=%d index is %d\n", key, loc);
	} else {
		return -1;
	}
	return 1;
}

//插值查找
int Insert_Search(Index *ind, int n, int key, int *loc)
{
	int low, high, mid;
	low = 1;
	high = n;
	if (n <= 1)
		mid = n + 1;//第0、1个目标元素的插入位置为索引表的1、2位置
	if (key<I[low].key)
	{
		*loc = low;//若插入元素小于索引表第1个元素，则将目标元素插入到索引表第1元素位置
		return -1;
	}
	else if (key > I[high].key)
	{
		*loc = high + 1;//若插入元素大于索引表最后元素，则将目标元素插入到索引表最后元素的下一个位置
		return -1;
	}
	else
	{
		while (low <= high)
		{
			mid = low + (key - ind[low].key) / (ind[high].key - ind[low].key) * (high - low);//插值查找
			//mid = low + (high - low) / 2; //折半查找，或二分查找
			if (ind[mid].key < key)
				low = mid + 1;
			else if (ind[mid].key > key)
				high = mid - 1;
			else
			{
				*loc = mid;
				return mid;
			}
		}
		mid++;//位置加1才是正确的插入位置
	}
	*loc = mid;//得到目标元素插入位置
	return -1;
}

void test_DenseIndex(void)
{
	int key;
	char name[10];
	Student* info;
	I[0].key = 0;//索引表首元素保留使用，用于记录索引表当前长度

	//插入目标元素
	key = 10;
	strcpy(name, "zjp1");
	AddInfo(key, name);

	key = 30;
	strcpy(name, "zjp3");
	AddInfo(key, name);

	key = 50;
	strcpy(name, "zjp5");
	AddInfo(key, name);

	key = 20; //插入比前面元素数值小的元素
	strcpy(name, "zjp2");
	AddInfo(key, name);

	key = 1; //插入比前面元素数值小的元素
	strcpy(name, "zjp1-1");
	AddInfo(key, name);

	//查找目标1
	if (Search_Info(50, &info) == 1)
		printf("find student:%s %d\n", info->name, info->key);
	else
		printf("no find\n");
	//查找目标2
	if (Search_Info(1, &info) == 1)
		printf("find student:%s %d\n", info->name, info->key);
	else
		printf("no find\n");

	//打印索引表关键码
	for (int i = 0; i < MAX_DATA_SIZE; i++)
	{
		printf("Index[%d].key = %d\n", i, I[i].key);//首元素为索引表长度
	}
}

