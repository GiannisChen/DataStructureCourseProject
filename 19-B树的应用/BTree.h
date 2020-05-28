#ifndef _BTREE_H  //�����ض���
#define _BTREE_H 

#include <iostream>
#include <cstdio>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <array>


/*-----------------B���Ķ���-------------------
* һ��m��B������Ϊ�����������Ե�m������
*��1��������ÿ���ڵ���ຬ��m������
*��2�������ڵ��Ƿ��ն˽�㣬����������������
*��3�������ڵ�֮������з��ն˽��������(m+1)/2������
*��4��ÿ�����ն˽ڵ������Ϣ����n,A0,K1,A1....����
		4.1��Ki(1<=i<=n)Ϊ�ؼ��֣��ҹؼ��ְ���������
		4.2��ָ��Ai(1<=i<=n)ָ�������ĸ��ڵ㣬Ai-1ָ�����������нڵ�Ĺؼ��־�С��Ki�Ҵ���Ki-1
		4.3���ؼ��ֵĸ����������㣺(m+1)/2-1<=n<=m-1
*��5������Ҷ�ӽڵ��������ͬһ�㣬Ҷ�ӽڵ㲻�����κ���Ϣ��ʵ������Щ�ڵ㲻���ڣ�ָ����Щ�ڵ��ָ��Ϊ��
*/

//m��B���Ľڵ����Ͷ���
#define m 3  //����B���Ľ���Ϊ3
typedef int KeyType;			//����ؼ���Ϊ��������
typedef struct BTNode 
{ 
	int keynum;					//�ڵ㵱ǰ�Ĺؼ��ָ���
	std::array<KeyType, m + 1> key;			//�ؼ������飬key[0]δ��
	struct BTNode *parent;		//˫�׽ڵ�ָ��
	std::array<BTNode*, m + 1> ptr;  //���ӽڵ�ָ������
	//Recode *recptr[m + 1];		//��¼ָ��������0�ŵ�Ԫδ��
}BTNode,*BTree;

//B���Ҳ鷵����Ϣ�Ľṹ��
typedef struct 
{
	BTree pt;		//ָ���ҵ��Ľڵ�
	int i;			//�ڽڵ��йؼ��ֵ�λ��
	int tag;		//1���Ҳ�ɹ� 0���Ҳ�ʧ��
}result;

typedef BTree ElemType;

bool visitValue(KeyType e, bool flag);					//�������ú���

class B_Tree
{
private:
	BTree TreeRoot;

private:
	void create();								//������B��			
	int searchNode(BTree p, KeyType k);							//�ڽڵ�p���Ҳ��һ���ؼ��ֱ�k���λ��
	void searchBTree(KeyType k, result& r);		/*
	*��B��T���Ҳ�ؼ���k������r�����������Ϣ
	*���Ҳ�ɹ�������r.tagΪ1������r.ptָ���r.i���ؼ��ֵ���k
	*����r.tag = 0,��Ҫ����ؼ���Ϊk�ļ�¼����Ӧλ��r.pt�ڵ�ĵ�r.i-1���͵�r.i���ؼ���֮��
	*/
	void insertNode(BTree& q, int i, KeyType x, BTree ap);		//�ؼ���x���½ڵ�ָ��ap�ֱ���뵽q->key[i]��q->ptr[i]
	void newRoot(BTree p, KeyType x, BTree ap);	//�����½ڵ�
	void split(BTree& q, int s, BTree& ap);					//��q�ڵ���ѳ������ڵ㣬ǰһ�뱣����ԭ�ڵ㣬��һ��һ��apָ����½ڵ�
	void insertBTree(KeyType k, BTree q, int i);	/*
	*��B��T��q�ڵ��key[i - 1]��key[i]֮�����ؼ���k
	*��������н���֤��T����m�����������ؼ��ָ�������ʱ����˫��ָ�������нڵ����
	*/
	void DeleteBTree(BTree& p, int i);						//ɾ��B���Ľڵ�p�ĵ�i���ؼ���
	void Successor(BTree& p, int i);						//��Pi�������ҳ����²���ն˽ڵ����С�ؼ������Ki
	void remove(BTree p, int i);							//�ӽڵ�p��ɾ��key[i]
	void restore(BTree& p);									//����B��
	void merge(BTree& q, BTree& p, bool flag, int j);		//�ϲ�B���Ľڵ㣬��flag=0��ʱ��ϲ������ֵܺͼ�����ߵĸ��ڵ�ؼ��֣�����ϲ������ֵܺͼ�����ߵĸ��ڵ�ؼ���
public:
	B_Tree();
	bool insert(KeyType k);					//��B��T�в���ؼ���k
	bool insert(KeyType a[], int n);			//��������Ĺؼ������������ֵ��nΪ�ؼ�������Ĺؼ��ָ���
	void traverse(bool(*visit)(KeyType e, bool flag) = visitValue);//��α���B��T��visit�Ƕ�����Ԫ�ز�����Ӧ�ú���
	bool erase(KeyType k);					//ɾ��B����ֵΪk�Ľڵ�
	void traverse(bool(*visit)(bool e));	//��α���B��T��visit�Ƕ�����Ԫ�ز�����Ӧ�ú�������α�����ʹ���˶���
	bool search(KeyType k);					//�ж�ĳ���ؼ�����B�����Ƿ����
	int depth();									//��B�������
	int keySum();									//��B���ؼ��ֵ�����
	bool empty();									//�ж��Ƿ�Ϊ��B��
};

#endif