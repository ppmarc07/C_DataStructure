#include <stdio.h>
#include <stdlib.h>

/*
	实现散列表查找（哈希表查找）算法
	--zjp
	marc07@qq.com
*/

#define HASHSIZE	12
#define NULLKEY		-32768
typedef struct
{
	int elem[HASHSIZE];
}HashTable;

//初始化散列表
void InitHashTable(HashTable *H)
{
	for(int i = 0; i < HASHSIZE; i++)
	{
		H->elem[i] = NULLKEY;
	}
}

//散列函数
int Hash(int key)
{
	return key  % HASHSIZE;//除留余数法
}

//插入关键字到散列表
void InsertHash(HashTable *H, int key)
{
	int addr = Hash(key);//获取对应的散列地址
	while (H->elem[addr] != NULLKEY)//若不为空值，则说明该空间位置已存放元素，有冲突
	{
		addr = (addr + 1) % HASHSIZE;//开放定址法的线性探测，此处也可更改为其他解决冲突的方法
	}
	H->elem[addr] = key;//直到有空位后插入关键字
}

//散列表查找关键字
int SearchHash(HashTable *H, int key)
{
	int addr = Hash(key);//获取对应的散列地址
	while (H->elem[addr] != key)//若不相等，说明该空间位置已存放其他元素
	{
		addr = (addr + 1) % HASHSIZE;//开放定址法的线性探测
		if (H->elem[addr] == NULLKEY || addr == Hash(key))//下一个位置没有存放，或者循环回到原点
		{
			printf("Key %d isn't in HashTable.\n", key);
			return -1;
		}
	}
	printf("\nKey %d addr is %d\n", key, addr);
	return 1;
}

void test_HashSearch(void)
{
	HashTable H;
	int arr[HASHSIZE] = { 12, 67, 56, 16, 25, 37, 22, 29, 15, 47, 48, 34 };//模拟数据
	//1.初始化散列表
	InitHashTable(&H);

	//2.插入关键字到散列表
	for (int i = 0; i < HASHSIZE; i++)
	{
		InsertHash(&H, arr[i]);
	}
	for (int i = 0; i < HASHSIZE; i++)
	{
		printf("%d ", H.elem[i]);//显示插入结果
	}//12 25 37 15 16 29 48 67 56 34 22 47

	//3.散列表查找关键字
	SearchHash(&H, 67);
	SearchHash(&H, 60);
}


