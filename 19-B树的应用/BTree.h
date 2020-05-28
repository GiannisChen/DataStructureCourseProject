#ifndef _BTREE_H  //重置重定义
#define _BTREE_H 

#include <iostream>
#include <cstdio>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <array>


/*-----------------B树的定义-------------------
* 一棵m阶B树或者为满足以下特性的m叉树：
*（1）树中中每个节点最多含有m棵子树
*（2）若根节点是非终端结点，则至少有两棵子树
*（3）除根节点之外的所有非终端结点至少有(m+1)/2棵子树
*（4）每个非终端节点包含信息：（n,A0,K1,A1....）则：
		4.1）Ki(1<=i<=n)为关键字，且关键字按升序排序
		4.2）指针Ai(1<=i<=n)指向子树的根节点，Ai-1指向子树中所有节点的关键字均小于Ki且大于Ki-1
		4.3）关键字的个数必须满足：(m+1)/2-1<=n<=m-1
*（5）所有叶子节点均出现在同一层，叶子节点不包含任何信息，实际上这些节点不存在，指向这些节点的指针为空
*/

//m阶B树的节点类型定义
#define m 3  //定义B数的阶数为3
typedef int KeyType;			//定义关键字为整形数据
typedef struct BTNode 
{ 
	int keynum;					//节点当前的关键字个数
	std::array<KeyType, m + 1> key;			//关键字数组，key[0]未用
	struct BTNode *parent;		//双亲节点指针
	std::array<BTNode*, m + 1> ptr;  //孩子节点指针数组
	//Recode *recptr[m + 1];		//记录指针向量，0号单元未用
}BTNode,*BTree;

//B树找查返回信息的结构体
typedef struct 
{
	BTree pt;		//指向找到的节点
	int i;			//在节点中关键字的位序
	int tag;		//1：找查成功 0：找查失败
}result;

typedef BTree ElemType;

bool visitValue(KeyType e, bool flag);					//遍历调用函数

class B_Tree
{
private:
	BTree TreeRoot;

private:
	void create();								//创建空B树			
	int searchNode(BTree p, KeyType k);							//在节点p中找查第一个关键字比k大的位置
	void searchBTree(KeyType k, result& r);		/*
	*在B树T上找查关键字k，并用r返回其相关信息
	*若找查成功，则标记r.tag为1，且且r.pt指向的r.i个关键字等于k
	*否则r.tag = 0,若要插入关键字为k的记录，则应位于r.pt节点的第r.i-1个和第r.i个关键字之间
	*/
	void insertNode(BTree& q, int i, KeyType x, BTree ap);		//关键字x和新节点指针ap分别插入到q->key[i]和q->ptr[i]
	void newRoot(BTree p, KeyType x, BTree ap);	//生成新节点
	void split(BTree& q, int s, BTree& ap);					//将q节点分裂成两个节点，前一半保留在原节点，后一半一如ap指向的新节点
	void insertBTree(KeyType k, BTree q, int i);	/*
	*在B树T中q节点的key[i - 1]和key[i]之间插入关键字k
	*插入过程中将保证树T仍是m阶子树，当关键字个数超出时将沿双亲指针链进行节点分裂
	*/
	void DeleteBTree(BTree& p, int i);						//删除B树的节点p的第i个关键字
	void Successor(BTree& p, int i);						//在Pi子树中找出最下层非终端节点的最小关键字替代Ki
	void remove(BTree p, int i);							//从节点p中删除key[i]
	void restore(BTree& p);									//调整B树
	void merge(BTree& q, BTree& p, bool flag, int j);		//合并B树的节点，当flag=0的时候合并其左兄弟和间隔两者的父节点关键字，否则合并其右兄弟和间隔两者的父节点关键字
public:
	B_Tree();
	bool insert(KeyType k);					//在B树T中插入关键字k
	bool insert(KeyType a[], int n);			//插入给定的关键字数组的所有值，n为关键字数组的关键字个数
	void traverse(bool(*visit)(KeyType e, bool flag) = visitValue);//层次遍历B树T，visit是对数据元素操作的应用函数
	bool erase(KeyType k);					//删除B树中值为k的节点
	void traverse(bool(*visit)(bool e));	//层次遍历B树T，visit是对数据元素操作的应用函数，层次遍历用使用了队列
	bool search(KeyType k);					//判断某个关键字在B数中是否存在
	int depth();									//求B树的深度
	int keySum();									//求B树关键字的总数
	bool empty();									//判断是否为空B树
};

#endif