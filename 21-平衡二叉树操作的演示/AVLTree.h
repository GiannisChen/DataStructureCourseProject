#ifndef _AVLTREE_H
#define _AVLTREE_H

#include "BasisTree.h"



class AVLTree :public BinaryTree
{
public:
	void Insert(ElementType x);
	void Delete(ElementType x);
	BT Find(ElementType x);
	void DeleteChildTree(ElementType x);

private:
	BT FindTreeNode(ElementType x, BT T);
	BT InsertTreeNode(ElementType x, BT T);
	BT DeleteTreeNode(ElementType x, BT T);
	BT RR_Rotation(BT A);
	BT LL_Rotation(BT A);
	BT RL_Rotation(BT A);
	BT LR_Rotation(BT A);
	
};

void AVLTree::Insert(ElementType x)
{
	TreeRoot = InsertTreeNode(x, TreeRoot);
}

void AVLTree::Delete(ElementType x)
{
	TreeRoot = DeleteTreeNode(x, TreeRoot);
}

BT AVLTree::Find(ElementType x)
{
	return FindTreeNode(x, TreeRoot);
}

BT AVLTree::FindTreeNode(ElementType x, BT T)
{
	if (!T)
	{
		std::cout << "未找到数据" << x << "，返回！" << std::endl;
		return NULL;
	}
	else
	{
		if (x == T->data)
			return T;
		else if (x < T->data)
			return FindTreeNode(x, T->LeftChild);
		else
			return FindTreeNode(x, T->RightChild);
	}
}

BT AVLTree::RR_Rotation(BT A)
{
	BT B = A->RightChild;
	A->RightChild = B->LeftChild;
	B->LeftChild = A;
	A->height = max(TreeHeight(A->LeftChild), TreeHeight(A->RightChild)) + 1;
	B->height = max(TreeHeight(B->LeftChild), TreeHeight(B->RightChild)) + 1;
	return B;
}

BT AVLTree::LL_Rotation(BT A)
{
	BT B = A->LeftChild;
	A->LeftChild = B->RightChild;
	B->RightChild = A;
	A->height = max(TreeHeight(A->LeftChild), TreeHeight(A->RightChild)) + 1;
	B->height = max(TreeHeight(B->LeftChild), TreeHeight(B->RightChild)) + 1;
	return B;
}

BT AVLTree::RL_Rotation(BT A)
{
	A->RightChild = LL_Rotation(A->RightChild);
	return RR_Rotation(A);
}

BT AVLTree::LR_Rotation(BT A)
{
	A->LeftChild = RR_Rotation(A->LeftChild);
	return LL_Rotation(A);
}

BT AVLTree::InsertTreeNode(ElementType x, BT T)
{
	if (!T)
	{
		T = new TreeNode;
		T->pos = 0;
		T->data = x;
		T->height = 0;
		T->LeftChild = NULL;
		T->RightChild = NULL;
	}
	else if (x < T->data)
	{
		T->LeftChild = InsertTreeNode(x, T->LeftChild);
		if ((TreeHeight(T->LeftChild) - TreeHeight(T->RightChild)) == 2)
		{
			if (x < T->LeftChild->data)
				T = LL_Rotation(T);
			else
				T = LR_Rotation(T);
		}
	}
	else if (x > T->data)
	{
		T->RightChild = InsertTreeNode(x, T->RightChild);
		if ((TreeHeight(T->LeftChild) - TreeHeight(T->RightChild)) == -2)
		{
			if (x < T->RightChild->data)
				T = RL_Rotation(T);
			else
				T = RR_Rotation(T);
		}
	}
	T->height = max(TreeHeight(T->LeftChild), TreeHeight(T->RightChild)) + 1;
	return T;
}

BT AVLTree::DeleteTreeNode(ElementType x, BT T)
{
	if (!T)
	{
		std::cout << "未找到" << x << "..." << std::endl;
		std::cout << "删除无效"<< std::endl;
		return NULL;
	}
		
	if (x < T->data)
	{
		T->LeftChild = DeleteTreeNode(x, T->LeftChild);
		if ((TreeHeight(T->LeftChild) - TreeHeight(T->RightChild)) == -2)
		{
			if (x < T->RightChild->data)
				T = RL_Rotation(T);
			else
				T = LL_Rotation(T);
		}
	}
	else if (x > T->data)
	{
		T->RightChild = DeleteTreeNode(x, T->RightChild);
		if ((TreeHeight(T->LeftChild) - TreeHeight(T->RightChild)) == 2)
		{
			if (x < T->LeftChild->data)
				T = RR_Rotation(T);
			else
				T = LR_Rotation(T);
		}
	}
	else
	{
		if (T->LeftChild == NULL)
		{
			BT tempT = T;
			T = T->RightChild;
			delete tempT;
		}
		else if (T->RightChild == NULL)
		{
			BT tempT = T;
			T = T->LeftChild;
			delete tempT;
		}
		else
		{
			std::cout << "删除成功！" << std::endl;
			BT tempT = T->LeftChild;
			while (tempT->RightChild != NULL)		//左子树的最大值
				tempT = tempT->RightChild;
			T->data = tempT->data;
			T->LeftChild = DeleteTreeNode(T->data, T->LeftChild);
		}
	}
	if (T)
		T->height = max(TreeHeight(T->LeftChild), TreeHeight(T->RightChild)) + 1;
	return T;
}

//删除以x为根的子树
void AVLTree::DeleteChildTree(ElementType x)
{
	BT tmpNode = Find(x);
	BT tmpParent = FindParent(x);
	if (tmpParent)
	{
		if (tmpParent->LeftChild->data == x)
			tmpParent->LeftChild = NULL;
		else
			tmpParent->RightChild = NULL;
	}
	if (tmpNode)
	{
		std::queue<BT> Q;
		
		BT tempT = tmpNode;
		Q.push(tempT);
		while (!Q.empty())
		{
			tempT = Q.front();
			Q.pop();

			if (tempT->LeftChild)
				Q.push(tempT->LeftChild);
			if (tempT->RightChild)
				Q.push(tempT->RightChild);
			delete tempT;
		}
		tmpNode = NULL;
	}
	std::cout << "操作完成！" << std::endl;
}

#endif

