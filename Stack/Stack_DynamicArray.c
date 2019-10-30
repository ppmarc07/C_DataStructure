#include <stdio.h>
#include <stdlib.h>
/*
	实现动态顺序栈
	--zjp
	marc07@qq.com
*/
typedef struct DSNode
{
	int *stack_arr;//栈区
	int stack_size;//栈大小
	int stack_top;//栈顶
}DynamicStackNode;//动态顺序栈结构

//创建动态顺序栈
DynamicStackNode *CreateDynamicStack(int capacity)
{
	DynamicStackNode *ptr = (DynamicStackNode *)malloc(sizeof(DynamicStackNode));
	if (ptr == NULL)
	{
		printf("CreateDynamicStack fail:malloc error\n");
		return;
	}
	ptr->stack_size = capacity;
	ptr->stack_top = -1;
	ptr->stack_arr = (int *)malloc(capacity * sizeof(int));
	if (ptr->stack_arr == NULL)
	{
		printf("CreateDynamicStack fail:malloc error\n");
		return;
	}
	return ptr;
}

//判断栈是否为满
int IsFullDynamicStack(DynamicStackNode *ptr)
{
	if (ptr->stack_top == ptr->stack_size - 1)
	{
		return 1;//栈为满
	}
	return 0;//栈为未满
}

//判断栈是否为空
int IsEmptyDynamicStack(DynamicStackNode *ptr)
{
	if (ptr->stack_top == -1)
	{
		return 1;//栈为空
	}
	return 0;//栈为非空
}

//入栈
void PushDynamicStack(DynamicStackNode *ptr, int value)
{
	if (IsFullDynamicStack(ptr))
	{
		printf("栈满，入栈失败\n");
		return;
	}

	ptr->stack_top++;
	ptr->stack_arr[ptr->stack_top] = value;
	printf("入栈元素：%d\n", ptr->stack_arr[ptr->stack_top]);
}

//出栈
void PopDynamicStack(DynamicStackNode *ptr, int *value)
{
	if (IsEmptyDynamicStack(ptr))
	{
		printf("栈空，出栈失败\n");
		return;
	}

	*value = ptr->stack_arr[ptr->stack_top];
	ptr->stack_top--;
	printf("出栈元素：%d\n", *value);
}

//获取栈顶元素
void GetTopElement_DStack(DynamicStackNode *ptr, int *top_value)
{
	if (IsEmptyDynamicStack(ptr))
	{
		printf("栈空，获取失败\n");
		return;
	}
	*top_value = ptr->stack_arr[ptr->stack_top];
	printf("栈顶元素：%d\n", *top_value);
}

//遍历栈
void PrintDynamicStack(DynamicStackNode *ptr)
{
	int value;
	int i;
	if (IsEmptyDynamicStack(ptr))
	{
		printf("栈空，遍历失败\n");
		return;
	}
	printf("当前元素：\n");
	for (i = ptr->stack_top; i >= 0; i--)
	{
		value = ptr->stack_arr[i];
		printf("%d ", value);
	}
	printf("\n");
}

//测试动态顺序栈
void test_Stack_DynamicArray(void)
{
	int top_value;
	DynamicStackNode *ptr;
	//（0）创建动态顺序栈
	ptr = CreateDynamicStack(5);
	//（1）入栈测试
	PushDynamicStack(ptr, 1);
	PushDynamicStack(ptr, 2);
	PushDynamicStack(ptr, 3);
	PushDynamicStack(ptr, 4);
	PushDynamicStack(ptr, 5);
	//打印栈
	PrintDynamicStack(ptr);//5 4 3 2 1
	//获取栈顶元素
	GetTopElement_DStack(ptr, &top_value);//5
	//入栈溢出（栈满）测试
	PushDynamicStack(ptr, 6);//栈满，入栈失败
	PrintDynamicStack(ptr);//5 4 3 2 1

	//（2）出栈测试
	PopDynamicStack(ptr, &top_value);
	PopDynamicStack(ptr, &top_value);
	PopDynamicStack(ptr, &top_value);
	PopDynamicStack(ptr, &top_value);
	PopDynamicStack(ptr, &top_value);
	//打印空栈
	PrintDynamicStack(ptr);//（空）
	//出栈溢出（栈空）测试
	PopDynamicStack(ptr, &top_value);//栈空，出栈失败
	//再次入栈
	PushDynamicStack(ptr, 1);
	PushDynamicStack(ptr, 2);
	PrintDynamicStack(ptr);//2 1
	GetTopElement_DStack(ptr, &top_value);//2
}

