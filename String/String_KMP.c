#include <stdio.h>
#include <stdlib.h>

/*
	实现串-KMP算法
	--zjp
	marc07@qq.com
	KMP算法为字符串匹配算法
*/

//模式串自身与自身匹配一次，获得next数组
void get_next(char *T, int *next)
{
	int i, j;
	i = 1;
	j = 0;
	next[1] = 0;
	while (i < T[0])//此处T[0]表示模式串T的长度
	{
		if (j == 0 || T[i] == T[j])//T[i]表示后缀的单个字符；T[j]表示前缀的单个字符
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];//若当前字符不相同，则j回溯
		}
	}
}

//返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数返回值为0
int KMP(char *S, char *T, int pos)
{
	int i = pos;
	int j = 1;
	int next[255];
	get_next(T, next);//获取next数组
	while (i <= S[0] && j <= T[0])
	{
		if (j == 0 || S[i] == T[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];//j回溯
		}
	}
	//返回结果
	if (j > T[0])
	{
		return i - T[0];
	}
	else
	{
		return 0;
	}
}

void test_String_KMP(void)
{
	int res = -1;
	char S[20], T[10];
	S[0] = 10;//首元素为字符主串长度
	T[0] = 5;//首元素为模式串串长度
	memcpy((char *)(S + 1), "abcabcee", 9);//创建字符串主串
	memcpy((char *)(T + 1), "abcee", 6);//创建模式串（待匹配串）
	res = KMP(S, T, 1);//KMP算法匹配
	printf("res = %d\n", res);//res = 4
}

