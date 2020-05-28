#include "BTree.h"
#include <queue>


B_Tree::B_Tree()
{
	create();
}


//������B��
void B_Tree::create()
{
	TreeRoot = NULL;
}


//�ж��Ƿ�Ϊ��B��
bool B_Tree::empty()
{
	if (NULL == TreeRoot)
		return true;
	return false;
}


//�ڽڵ�p���Ҳ��һ���ؼ��ֱ�k���λ��
int B_Tree::searchNode(BTree p, KeyType k)
{
	int i = 1;
	while (i <= p->keynum && k > p->key[i])
		i++;
	return i;
}


/**
*��B��T���Ҳ�ؼ���k������r�����������Ϣ
*���Ҳ�ɹ�������r.tagΪ1������r.ptָ���r.i���ؼ��ֵ���k
*����r.tag = 0,��Ҫ����ؼ���Ϊk�ļ�¼����Ӧλ��r.pt�ڵ�ĵ�r.i-1���͵�r.i���ؼ���֮��
*/
void B_Tree::searchBTree(KeyType k, result& r)
{
	int i = 0, found = 0;   //�ݴ�r�е���Ϣ
	BTree p = TreeRoot, q = NULL;  //pָ����ڵ㣬p������ָ�����ڵ㣬q��ָ��p��˫��
	while (NULL != p && 0 == found)
	{
		i = searchNode(p, k);  //��p->key[1...p->keynum]���Ҳ�p->key[i-1]<k<=p->key[i]
		if (i <= p->keynum && p->key[i] == k)
			found = 1;
		else
		{
			q = p;
			p = p->ptr[i - 1];
		}
	}
	//�Ҳ�ɹ�
	if (1 == found)
	{
		r.pt = p;
		r.i = i;
		r.tag = 1;
	}
	//�Ҳ�ʧ��
	else
	{
		r.pt = q;       //���ؿսڵ����һ���ڵ�
		r.i = i;
		r.tag = 0;
	}
}


//�ж�ĳ��ֵ��B�����Ƿ����
bool B_Tree::search(KeyType k)
{
	result r;
	searchBTree(k, r);
	if (r.tag == 1)
		return true;
	return false;
}


//�ؼ���x���½ڵ�ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
void B_Tree::insertNode(BTree& q, int i, KeyType x, BTree ap)
{
	int j;
	for (j = q->keynum; j >= i; j--)
	{
		q->key[j + 1] = q->key[j];	//�ؼ�������
		q->ptr[j + 1] = q->ptr[j];	//����ָ������
	}
	q->key[i] = x;					//�����µĹؼ��ֺ�ָ��
	q->ptr[i] = ap;
	if (NULL != ap)
		ap->parent = q;				//ʹ�²���Ľڵ������ָ��ָ��q
	q->keynum++;
}


//��������Ĺؼ�������
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


//�����½ڵ�
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


//��q�ڵ���ѳ������ڵ㣬ǰһ�뱣����ԭ�ڵ㣬��һ������apָ����½ڵ�
void B_Tree::split(BTree& q, int s, BTree& ap)
{
	int i, j, n = q->keynum;
	ap = (BTree)malloc(sizeof(BTNode));  //�����½ڵ�
	ap->ptr[0] = q->ptr[s];
	//�����½ڵ�
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
*��B��T��q�ڵ��key[i - 1]��key[i]֮�����ؼ���k
*��������н���֤��T����m�����������ؼ��ָ�������ʱ����˫��ָ�������нڵ����
*/
void B_Tree::insertBTree(KeyType k, BTree q, int i)
{
	int x, s, finished = 0, needNewRoot = 0;
	BTree ap;
	if (NULL == q)
		newRoot(NULL, k, NULL);			//��Ϊ����ʱ�����½ڵ�
	else
	{
		x = k;
		ap = NULL;
		while (0 == needNewRoot && 0 == finished)
		{
			insertNode(q, i, x, ap);				//��x��ap�ֱ���뵽q->key[i]��q->ptr[i]
			if (q->keynum < m) finished = 1;	//��ɲ���
			//������Ҫ����
			else
			{
				s = (m + 1) / 2;
				split(q, s, ap);
				x = q->key[s];
				if (NULL != q->parent)
				{
					q = q->parent;
					i = searchNode(q, x);  //��˫�����Ҳ�x�Ĳ���λ��
				}
				else
					needNewRoot = 1;  //������Ҫ�����½ڵ�
			}
		}
		if (1 == needNewRoot)
			newRoot(q, x, ap);
	}
}


//��B��T�в���ؼ���k
bool B_Tree::insert(KeyType k)
{
	result r;
	searchBTree(k, r);           //�жϽڵ��Ƿ��Ѿ����ڣ��������ڵ�ʱ�򷵻ز����λ��
	if (r.tag == 1)
		return false;				//ֵΪk�Ľڵ��Ѿ�����
	insertBTree(k, r.pt, r.i);
	return true;
}


//ɾ��B����ֵΪk�Ľڵ�
bool B_Tree::erase(KeyType k)
{
	result r;
	searchBTree(k, r);
	if (r.tag == 0)
		return false;	//ֵΪk�Ľڵ㲻����
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


//ɾ��p�ڵ��ϵĵ�i���ؼ���
void B_Tree::DeleteBTree(BTree& p, int i)
{
	if (NULL == p->ptr[i] && p->parent == NULL)//��ֻʣ�¸��ڵ�
		remove(p, i);
	else if (NULL != p->ptr[i])
	{
		Successor(p, i);             //��Ai�������ҳ����²���ն˽ڵ����С�ؼ������Ki
		DeleteBTree(p, 1);           //ת��Ϊɾ�����²���ն˽ڵ��е���С�ؼ���
	}
	else
	{
		remove(p, i);                //�ӽڵ�p��ɾ��key[i]
		if (p->keynum < (m - 1) / 2)   //��ɾ���ؼ��ֺ����С��(m-1)/2 ����е���
			restore(p);          //����B��
	}
}


//��Ai�������ҳ����²���ն˽ڵ����С�ؼ������Ki
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


//�ӽڵ�p��ɾ��key[i]
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
*�ϲ�B���Ľڵ�
*��flag = 0ʱ���ϲ������ֵ�
*flag = 1ʱ���ϲ������ֵ�
*/
void B_Tree::merge(BTree& q, BTree& p, bool flag, int j)
{
	//�ϲ������ֵ�
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
	//�ϲ������ֵ�
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


//����B��
void B_Tree::restore(BTree& p)
{
	BTree q = p->parent;           //ȡ�丸�ڵ�
	BTree left, right;
	int j;
	if (q == NULL)
		return;
	for (j = 0; j <= q->keynum; j++)	   //�ҵ�p�ڸ��ڵ��λ��
		if (q->ptr[j] == p)
			break;
	//���ڵ㲻������˵Ľڵ�ʱ

	if (0 != j)
	{
		left = q->ptr[j - 1];				//p�����ֵ�
		//�����ֵܸ���ʱ
		if (left->keynum > (m - 1) / 2)
		{
			KeyType exchange = q->key[j];			//ȡ���ڵ���ӽ�p��С��p�Ĺؼ���
			q->key[j] = left->key[left->keynum];	//�����ֵܵ����ؼ��ִ���ԭ�ؼ���
			for (int r = p->keynum; r >= 0; r--)
			{										//Ϊ���븸�ڵ�Ĺؼ�����׼��
				if (r > 0)
					p->key[r + 1] = p->key[r];
				p->ptr[r + 1] = p->ptr[r];
			}
			p->key[1] = exchange;
			p->keynum++;							//�ؼ�������һ
			p->ptr[0] = left->ptr[left->keynum];
			if (left->ptr[left->keynum] != NULL)
				left->ptr[left->keynum]->parent = p;
			remove(left, left->keynum);				//ɾ�����ֵܵ����ؼ���
			return;
		}
	}
	//��p�㲢�����Ҷ˽ڵ������ֵܲ������ʱ��
	if (q->keynum != j)
	{
		right = q->ptr[j + 1];				//p�����ֵ�
		//�����ֵܸ���ʱ
		if (right->keynum > (m - 1) / 2)
		{
			KeyType exchange = q->key[j + 1];		//ȡ���ڵ���ӽ�p�Ҵ���p�Ĺؼ���
			q->key[j + 1] = right->key[1];		//������������С�ؼ��ִ���ԭ�ؼ���
			p->key[p->keynum + 1] = exchange;
			p->keynum++;
			p->ptr[p->keynum] = right->ptr[0];
			if (right->ptr[0] != NULL)
				right->ptr[0]->parent = p;
			//ɾ�����ֵܵ���С�ؼ���
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
	//�������ֵܾ��������ʱ��
	if (j > 0)	//�ϲ������ֵ�
		merge(q, p, 0, j);
	else		//�ϲ������ֵ�
		merge(q, p, 1, j);
	if (q->keynum < (m - 1) / 2 && q->parent != NULL)
		restore(q);
}



//��α���B��T��visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
void B_Tree::traverse(bool(*visit)(KeyType e, bool))
{
	//LQueue Q;
	std::queue<BTree> Q;
	int i, j;
	BTree p = NULL;// T->ptr[0];
	BTree q1, q2;
	//InitQueue(Q);  //��ʼ���ն���
	//EnQueue(Q, T); //B���ĵ�һ���ڵ����
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
					visit(p->key[i], true);   //ͬһ�ڵ�֮��ؼ����ö�����Ϊ���
				if (i == p->keynum)
					visit(p->key[i], false);		   //��ͬ�ڵ�֮��ؼ����ÿո���Ϊ���
			}
			printf("   ");
			if (p->parent == NULL)    //��������ڵ����
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
				if (flag == false && q1->ptr[q1->keynum] == q2 && p->parent->ptr[p->parent->keynum] == p)    //������һ���Ժ���
					printf("\n");
			}
		}
	}
}


//��B�������
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


//��B���ؼ��ֵ�����
int B_Tree::keySum()
{
	//LQueue Q;
	std::queue<BTree> Q;
	int i, j, sum = 0;
	BTree p = NULL;
	//InitQueue(Q);  //��ʼ���ն���
	//EnQueue(Q, T); //B���ĵ�һ���ڵ����
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


//�������ú���
bool visitValue(KeyType e, bool flag)
{
	if (flag == true)
		printf("%d,", e);
	else
		printf("%d", e);
	return true;
}