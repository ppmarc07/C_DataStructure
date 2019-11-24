#include <stdio.h>
#include <stdlib.h>
/*
	实现线索二叉树(带头结点)
	--zjp
	marc07@qq.com
*/
typedef char ElemType;
/*
	线索存储标志位
	Link(0):表示指向左右孩子的指针
	Thread(1):表示指向前驱后继的线索
*/
typedef enum 
{
	Link, 
	Thread
}PointerTag;
/*
	二叉线索存储结点结构
*/
typedef struct BiThrNode 
{
	ElemType data;/* 结点数据 */
	struct BiThrNode *lchild;/* 左右孩子指针 */
	struct BiThrNode *rchild;
	PointerTag ltag;/* 左右标志*/
	PointerTag rtag;
}BiThrTreeNode, *BiThrTree;

//全局变量，始终指向刚刚访问过的节点
BiThrTree pre;

//先序创建二叉树
void CreateBiThrTree(BiThrTree *T)
{
	ElemType ch;
	scanf("%c", &ch);
	getchar();//当scanf输入字符型数据时，需调用getchar去除'\n'字符
	if ('#' == ch)
	{
		*T = NULL;
	}
	else
	{
		*T = (BiThrTreeNode *)malloc(sizeof(BiThrTreeNode));
		if (*T == NULL)
		{
			printf("CreateBiThrTree fail:malloc error\n");
			return;
		}
		(*T)->data = ch;
		(*T)->ltag = Link;
		(*T)->rtag = Link;
		printf("请输入%c的左子结点：\n", ch);
		CreateBiThrTree(&((*T)->lchild));
		printf("请输入%c的右子结点：\n", ch);
		CreateBiThrTree(&((*T)->rchild));
	}
}

/* 中序遍历线索化 */
void InThreading(BiThrTree T)
{
	if (T)
	{
		InThreading(T->lchild);//遍历左子树
		if (T->lchild == NULL)//这样容易理解//if(!T->lchild)
		{
			T->ltag = Thread;
			T->lchild = pre;//保存当前结点的前驱
		}
		if (pre != NULL && pre->rchild == NULL)
		{
			pre->rtag = Thread;
			pre->rchild = T;//保存刚访问过的上一个结点的后继
		}
		pre = T;//更新pre指针，始终指向刚刚访问过的上一个结点
		InThreading(T->rchild);//遍历右子树
	}
}

/* 中序遍历二叉树线索化，带头结点 */
BiThrTree InOrderThreading(BiThrTree T)
{
	BiThrTree	Thrt;//Thrt为头结点指针
	Thrt = (BiThrTreeNode *)malloc(sizeof(BiThrTreeNode));
	if (Thrt == NULL)
	{
		printf("InOrderThreading fail:malloc error\n");
		return;
	}
	Thrt->ltag = Link;//头结点左指针域需指定为根结点，所以这里标志为Link，表示指向左孩子
	Thrt->rtag = Thread;//头结点右指针域需指定为最后一个结点，所以这里标志为Thread,表示指向后继
	Thrt->rchild = Thrt;//右指针回指
	if (T == NULL)
	{
		Thrt->lchild = Thrt;//若二叉树为空，则左指针回指
	}
	else
	{
		Thrt->lchild = T;//头结点左孩子指向根节点
		pre = Thrt;//初始化上一个访问的结点，pre全局变量
		InThreading(T);//中序遍历进行中序线索化
		pre->rtag = Thread;//打上标记，右指针域指向后继，而不是右孩子
		pre->rchild = Thrt;//最后一个结点后继线索化，指向头结点
		Thrt->rchild = pre;//头结点后继线索化
	}
	return Thrt;
}

//中序遍历线索二叉树--非递归
void InOrderTraverse_Thr(BiThrTree Thrt)
{
	BiThrTree p = Thrt->lchild;
	while (p != Thrt)
	{
		//一直找左孩子
		while (p->ltag == Link)
		{
			p = p->lchild;
		}
		printf("%c ", p->data);
		//当结点右标志位为1时，直接找到其后继结点
		while (p->rtag == Thread && p->rchild != Thrt)
		{
			p = p->rchild;
			printf("%c ", p->data);
		}
		//否则，按照中序遍历的规律，找其右子树中最左下的结点，也就是继续循环遍历
		p = p->rchild;
	}
}

//测试线索二叉树
void test_BinaryTree_Threaded(void)
{
	BiThrTree T = NULL;
	BiThrTree Thrt = NULL;//头结点
	printf("输入前序二叉树根结点:\n");
	CreateBiThrTree(&T);
	Thrt = InOrderThreading(T);
	printf("输出中序序列:\n");
	InOrderTraverse_Thr(Thrt);
}





