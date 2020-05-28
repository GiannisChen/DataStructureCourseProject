#include "BTree.h"
#include <queue>


B_Tree::B_Tree()
{
	create();
}


//创建空B树
void B_Tree::create()
{
	TreeRoot = NULL;
}


//判断是否为空B树
bool B_Tree::empty()
{
	if (NULL == TreeRoot)
		return true;
	return false;
}


//在节点p中找查第一个关键字比k大的位置
int B_Tree::searchNode(BTree p, KeyType k)
{
	int i = 1;
	while (i <= p->keynum && k > p->key[i])
		i++;
	return i;
}


/**
*在B树T上找查关键字k，并用r返回其相关信息
*若找查成功，则标记r.tag为1，且且r.pt指向的r.i个关键字等于k
*否则r.tag = 0,若要插入关键字为k的记录，则应位于r.pt节点的第r.i-1个和第r.i个关键字之间
*/
void B_Tree::searchBTree(KeyType k, result& r)
{
	int i = 0, found = 0;   //暂存r中的信息
	BTree p = TreeRoot, q = NULL;  //p指向根节点，p将用于指向待查节点，q将指向p的双亲
	while (NULL != p && 0 == found)
	{
		i = searchNode(p, k);  //在p->key[1...p->keynum]中找查p->key[i-1]<k<=p->key[i]
		if (i <= p->keynum && p->key[i] == k)
			found = 1;
		else
		{
			q = p;
			p = p->ptr[i - 1];
		}
	}
	//找查成功
	if (1 == found)
	{
		r.pt = p;
		r.i = i;
		r.tag = 1;
	}
	//找查失败
	else
	{
		r.pt = q;       //返回空节点的上一个节点
		r.i = i;
		r.tag = 0;
	}
}


//判断某个值在B数中是否存在
bool B_Tree::search(KeyType k)
{
	result r;
	searchBTree(k, r);
	if (r.tag == 1)
		return true;
	return false;
}


//关键字x和新节点指针ap分别插入到q->key[i]和q->ptr[i]
void B_Tree::insertNode(BTree& q, int i, KeyType x, BTree ap)
{
	int j;
	for (j = q->keynum; j >= i; j--)
	{
		q->key[j + 1] = q->key[j];	//关键字右移
		q->ptr[j + 1] = q->ptr[j];	//子树指针右移
	}
	q->key[i] = x;					//插入新的关键字和指针
	q->ptr[i] = ap;
	if (NULL != ap)
		ap->parent = q;				//使新插入的节点的子树指针指向q
	q->keynum++;
}


//插入给定的关键字数组
bool B_Tree::insert(KeyType a[], int n)
{
	bool flag1, flag2 = true;
	for (int i = 0; i < n; i++)
	{
		flag1 = insert(a[i]);
		if (flag1 == false)
			flag2 = false;
	}
	return flag2;
}


//生成新节点
void B_Tree::newRoot(BTree p, KeyType x, BTree ap)
{
	TreeRoot = (BTree)malloc(sizeof(BTNode));
	TreeRoot->keynum = 1;
	TreeRoot->ptr[0] = p;
	TreeRoot->ptr[1] = ap;
	TreeRoot->key[1] = x;
	if (NULL != p)
		p->parent = TreeRoot;
	if (NULL != ap)
		ap->parent = TreeRoot;
	TreeRoot->parent = NULL;
}


//将q节点分裂成两个节点，前一半保留在原节点，后一半移入ap指向的新节点
void B_Tree::split(BTree& q, int s, BTree& ap)
{
	int i, j, n = q->keynum;
	ap = (BTree)malloc(sizeof(BTNode));  //生成新节点
	ap->ptr[0] = q->ptr[s];
	//移入新节点
	for (i = s + 1, j = 1; i <= n; i++, j++)
	{
		ap->key[j] = q->key[i];
		ap->ptr[j] = q->ptr[i];
	}
	ap->keynum = n - s;
	ap->parent = q->parent;
	for (i = 0; i <= ap->keynum; i++)
	{
		if (ap->ptr[i] != NULL)
			ap->ptr[i]->parent = ap;
	}
	q->keynum = s - 1;
}


/**
*在B树T中q节点的key[i - 1]和key[i]之间插入关键字k
*插入过程中将保证树T仍是m阶子树，当关键字个数超出时将沿双亲指针链进行节点分裂
*/
void B_Tree::insertBTree(KeyType k, BTree q, int i)
{
	int x, s, finished = 0, needNewRoot = 0;
	BTree ap;
	if (NULL == q)
		newRoot(NULL, k, NULL);			//当为空树时生成新节点
	else
	{
		x = k;
		ap = NULL;
		while (0 == needNewRoot && 0 == finished)
		{
			insertNode(q, i, x, ap);				//把x和ap分别插入到q->key[i]和q->ptr[i]
			if (q->keynum < m) finished = 1;	//完成插入
			//否则需要分裂
			else
			{
				s = (m + 1) / 2;
				split(q, s, ap);
				x = q->key[s];
				if (NULL != q->parent)
				{
					q = q->parent;
					i = searchNode(q, x);  //在双亲中找查x的插入位置
				}
				else
					needNewRoot = 1;  //否则需要生成新节点
			}
		}
		if (1 == needNewRoot)
			newRoot(q, x, ap);
	}
}


//在B树T中插入关键字k
bool B_Tree::insert(KeyType k)
{
	result r;
	searchBTree(k, r);           //判断节点是否已经存在，当不存在的时候返回插入的位置
	if (r.tag == 1)
		return false;				//值为k的节点已经存在
	insertBTree(k, r.pt, r.i);
	return true;
}


//删除B树中值为k的节点
bool B_Tree::erase(KeyType k)
{
	result r;
	searchBTree(k, r);
	if (r.tag == 0)
		return false;	//值为k的节点不存在
	DeleteBTree(r.pt, r.i);
	if (TreeRoot->keynum == 0)
	{
		while (r.pt->parent != NULL && r.pt->parent->keynum != 0)
			r.pt = r.pt->parent;

		TreeRoot = r.pt;
		TreeRoot->parent = NULL;
	}
	if (TreeRoot->keynum == 0)
		TreeRoot = NULL;
	return true;
}


//删除p节点上的第i个关键字
void B_Tree::DeleteBTree(BTree& p, int i)
{
	if (NULL == p->ptr[i] && p->parent == NULL)//当只剩下根节点
		remove(p, i);
	else if (NULL != p->ptr[i])
	{
		Successor(p, i);             //在Ai子树中找出最下层非终端节点的最小关键字替代Ki
		DeleteBTree(p, 1);           //转换为删除最下层非终端节点中的最小关键字
	}
	else
	{
		remove(p, i);                //从节点p中删除key[i]
		if (p->keynum < (m - 1) / 2)   //若删除关键字后个数小于(m-1)/2 则进行调整
			restore(p);          //调整B树
	}
}


//在Ai子树中找出最下层非终端节点的最小关键字替代Ki
void B_Tree::Successor(BTree& p, int i)
{
	BTree t = p->ptr[i];
	while (t->ptr[0] != NULL)
		t = t->ptr[0];
	KeyType exchange = t->key[1];
	t->key[1] = p->key[i];
	p->key[i] = exchange;
	p = t;
}


//从节点p中删除key[i]
void B_Tree::remove(BTree p, int i)
{
	for (int j = i; j < p->keynum; j++)
	{
		p->key[j] = p->key[j + 1];
		p->ptr[j] = p->ptr[j + 1];
	}
	p->ptr[p->keynum] = NULL;
	p->keynum--;
}


/**
*合并B树的节点
*当flag = 0时，合并其左兄弟
*flag = 1时，合并其右兄弟
*/
void B_Tree::merge(BTree& q, BTree& p, bool flag, int j)
{
	//合并其左兄弟
	if (flag == 0)
	{
		BTree left = q->ptr[j - 1];
		int i;
		for (i = left->keynum + 1; i <= left->keynum + 1 + p->keynum; i++)
		{
			if (i == left->keynum + 1)
			{
				left->key[i] = q->key[j];
				left->ptr[i] = p->ptr[0];
				if (p->ptr[0] != NULL)
					p->ptr[0]->parent = left;
			}
			else
			{
				left->key[i] = p->key[i - left->keynum - 1];
				left->ptr[i] = p->ptr[i - left->keynum - 1];
				if (p->ptr[i - left->keynum - 1] != NULL)
					p->ptr[i - left->keynum - 1]->parent = left;
			}
		}
		left->keynum += 1 + p->keynum;
		remove(q, j);
		p = left;
	}
	//合并其右兄弟
	else if (flag == 1)
	{
		BTree right = q->ptr[j + 1];
		int i;
		for (i = p->keynum + 1; i <= p->keynum + 1 + right->keynum; i++)
		{
			if (i == p->keynum + 1)
			{
				p->key[i] = q->key[j + 1];
				p->ptr[i] = right->ptr[0];
				if (right->ptr[0] != NULL)
					right->ptr[0]->parent = p;
			}
			else
			{
				p->key[i] = right->key[i - p->keynum - 1];
				p->ptr[i] = right->ptr[i - p->keynum - 1];
				if (right->ptr[i - p->keynum - 1] != NULL)
					right->ptr[i - p->keynum - 1]->parent = p;
			}
		}
		p->keynum += 1 + right->keynum;
		remove(q, j + 1);
	}
}


//调整B树
void B_Tree::restore(BTree& p)
{
	BTree q = p->parent;           //取其父节点
	BTree left, right;
	int j;
	if (q == NULL)
		return;
	for (j = 0; j <= q->keynum; j++)	   //找到p在父节点的位置
		if (q->ptr[j] == p)
			break;
	//当节点不是最左端的节点时

	if (0 != j)
	{
		left = q->ptr[j - 1];				//p的左兄弟
		//当左兄弟富余时
		if (left->keynum > (m - 1) / 2)
		{
			KeyType exchange = q->key[j];			//取父节点最接近p且小于p的关键字
			q->key[j] = left->key[left->keynum];	//用左兄弟的最大关键字代替原关键字
			for (int r = p->keynum; r >= 0; r--)
			{										//为插入父节点的关键字做准备
				if (r > 0)
					p->key[r + 1] = p->key[r];
				p->ptr[r + 1] = p->ptr[r];
			}
			p->key[1] = exchange;
			p->keynum++;							//关键字数加一
			p->ptr[0] = left->ptr[left->keynum];
			if (left->ptr[left->keynum] != NULL)
				left->ptr[left->keynum]->parent = p;
			remove(left, left->keynum);				//删除左兄弟的最大关键字
			return;
		}
	}
	//当p点并非最右端节点且左兄弟不富余的时候
	if (q->keynum != j)
	{
		right = q->ptr[j + 1];				//p的右兄弟
		//当右兄弟富余时
		if (right->keynum > (m - 1) / 2)
		{
			KeyType exchange = q->key[j + 1];		//取父节点最接近p且大于p的关键字
			q->key[j + 1] = right->key[1];		//用右子树的最小关键字代替原关键字
			p->key[p->keynum + 1] = exchange;
			p->keynum++;
			p->ptr[p->keynum] = right->ptr[0];
			if (right->ptr[0] != NULL)
				right->ptr[0]->parent = p;
			//删除右兄弟的最小关键字
			for (int i = 0; i < right->keynum; i++)
			{
				right->ptr[i] = right->ptr[i + 1];
				if (i > 0)
					right->key[i] = right->key[i + 1];
			}
			right->keynum--;
			return;
		}
	}
	//当左右兄弟均不富余的时候
	if (j > 0)	//合并其左兄弟
		merge(q, p, 0, j);
	else		//合并其右兄弟
		merge(q, p, 1, j);
	if (q->keynum < (m - 1) / 2 && q->parent != NULL)
		restore(q);
}



//层次遍历B树T，visit是对数据元素操作的应用函数
void B_Tree::traverse(bool(*visit)(KeyType e, bool))
{
	//LQueue Q;
	std::queue<BTree> Q;
	int i, j;
	BTree p = NULL;// T->ptr[0];
	BTree q1, q2;
	//InitQueue(Q);  //初始化空队列
	//EnQueue(Q, T); //B树的第一个节点入队
	Q.push(TreeRoot);
	while (!Q.empty())
	{
		j = 0;
		//DeQueue(Q, p);
		p = Q.front();
		Q.pop();
		if (NULL != p)
		{
			j = p->keynum;
			for (i = 0; i <= p->keynum; i++)
			{
				//EnQueue(Q, p->ptr[i]);
				Q.push(p->ptr[i]);
				if (i >= 1 && i < p->keynum)
					visit(p->key[i], true);   //同一节点之间关键字用逗号作为间隔
				if (i == p->keynum)
					visit(p->key[i], false);		   //不同节点之间关键字用空格做为间隔
			}
			printf("   ");
			if (p->parent == NULL)    //遍历玩根节点后换行
				printf("\n");
			else
			{
				bool flag = false;
				q1 = q2 = p;
				while (q1->parent != NULL)
				{
					q2 = q1;
					q1 = q1->parent;
					if (q1->ptr[q1->keynum] != q2)
						flag = true;
				}
				if (flag == false && q1->ptr[q1->keynum] == q2 && p->parent->ptr[p->parent->keynum] == p)    //遍历完一层以后换行
					printf("\n");
			}
		}
	}
}


//求B树的深度
int B_Tree::depth()
{
	int i = 0;
	BTree p = TreeRoot;
	while (p != NULL)
	{
		i++;
		p = p->ptr[0];
	}
	return i;
}


//求B树关键字的总数
int B_Tree::keySum()
{
	//LQueue Q;
	std::queue<BTree> Q;
	int i, j, sum = 0;
	BTree p = NULL;
	//InitQueue(Q);  //初始化空队列
	//EnQueue(Q, T); //B树的第一个节点入队
	Q.push(TreeRoot);
	//while (false == QueueEmpty(Q))
	while (!Q.empty())
	{
		j = 0;
		//DeQueue(Q, p);
		p = Q.front();
		Q.pop();
		if (NULL != p)
		{
			j = p->keynum;
			for (i = 0; i <= p->keynum; i++)
			{
				//EnQueue(Q, p->ptr[i]);
				Q.push(p->ptr[i]);
				if (i > 0)
					sum++;
			}
		}
	}
	return sum;
}


//遍历调用函数
bool visitValue(KeyType e, bool flag)
{
	if (flag == true)
		printf("%d,", e);
	else
		printf("%d", e);
	return true;
}