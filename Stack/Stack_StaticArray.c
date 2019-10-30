#include <stdio.h>
/*
	实现静态顺序栈
	--zjp
	marc07@qq.com
*/
#define STACK_MAX_SIZE	5
typedef struct SSNode
{
	int stack_arr[STACK_MAX_SIZE];
	int stack_top;
}StaticStackNode;

//判断栈是否为满
int IsFullStaticStack(StaticStackNode *ptr)
{
	if (ptr->stack_top == STACK_MAX_SIZE - 1)
	{
		return 1;//栈为满
	}
	return 0;//栈为未满
}

//判断栈是否为空
int IsEmptyStaticStack(StaticStackNode *ptr)
{
	if (ptr->stack_top == -1)
	{
		return 1;//栈为空
	}
	return 0;//栈为非空
}

//入栈
void PushStaticStack(StaticStackNode *ptr, int value)
{
	if (IsFullStaticStack(ptr))
	{
		printf("栈满，入栈失败\n");
		return;
	}
	
	ptr->stack_top++;
	ptr->stack_arr[ptr->stack_top] = value;
	printf("入栈元素：%d\n", ptr->stack_arr[ptr->stack_top]);
}

//出栈
void PopStaticStack(StaticStackNode *ptr, int *value)
{
	if (IsEmptyStaticStack(ptr))
	{
		printf("栈空，出栈失败\n");
		return;
	}

	*value = ptr->stack_arr[ptr->stack_top];
	ptr->stack_top--;
	printf("出栈元素：%d\n", *value);
}

//获取栈顶元素
void GetTopElement(StaticStackNode *ptr, int *top_value)
{
	if (IsEmptyStaticStack(ptr))
	{
		printf("栈空，获取失败\n");
		return;
	}
	*top_value = ptr->stack_arr[ptr->stack_top];
	printf("栈顶元素：%d\n", *top_value);
}

//遍历栈
void PrintStaticStack(StaticStackNode *ptr)
{
	int value;
	int i;
	if (IsEmptyStaticStack(ptr))
	{
		printf("栈空，遍历失败\n");
		return;
	}
	printf("当前元素：\n");
	for(i = ptr->stack_top; i >= 0; i--)
	{
		value = ptr->stack_arr[i];
		printf("%d ", value);
	}
	printf("\n");
}

//测试静态顺序栈
void test_Stack_StaticArray(void)
{
	int top_value;
	StaticStackNode ptr = { {0}, -1 };//初始化栈顶为-1
	//（1）入栈测试
	PushStaticStack(&ptr, 1);
	PushStaticStack(&ptr, 2);
	PushStaticStack(&ptr, 3);
	PushStaticStack(&ptr, 4);
	PushStaticStack(&ptr, 5);
	//打印栈
	PrintStaticStack(&ptr);//5 4 3 2 1
	//获取栈顶元素
	GetTopElement(&ptr, &top_value);//5
	//入栈溢出（栈满）测试
	PushStaticStack(&ptr, 6);//栈满，入栈失败
	PrintStaticStack(&ptr);//5 4 3 2 1

	//（2）出栈测试
	PopStaticStack(&ptr, &top_value);
	PopStaticStack(&ptr, &top_value);
	PopStaticStack(&ptr, &top_value);
	PopStaticStack(&ptr, &top_value);
	PopStaticStack(&ptr, &top_value);
	//打印空栈
	PrintStaticStack(&ptr);//（空）
	//出栈溢出（栈空）测试
	PopStaticStack(&ptr, &top_value);
	//再次入栈
	PushStaticStack(&ptr, 1);
	PushStaticStack(&ptr, 2);
	PrintStaticStack(&ptr);//2 1
	GetTopElement(&ptr, &top_value);//2
}

