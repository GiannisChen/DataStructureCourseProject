#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

typedef int ElementType;
int max(int a, int b);


typedef struct TreeNode
{
	int pos;
	ElementType data;
	TreeNode* LeftChild;
	TreeNode* RightChild;
	int height;
}*BT;

int TreeHeight(BT T);

class BinaryTree
{
public:
	BT TreeRoot;

public:
	BinaryTree()
	{
		CreateBinaryTree();
	}
	~BinaryTree() = default;
	void InitBinaryTree();
	void CreateBinaryTree();
	void R_PreOrderTravel();
	void R_InOrderTravel();
	void R_PostOrderTravel();
	void N_PreOrderTravel();
	void N_InOrderTravel();
	void N_PostOrderTravel();
	void LevelOrderTravel();
	bool isCBT();
	void Clear();
	BT ReturnTreeRoot();
	int Height();
	BT FindLeftSibling(ElementType x);
	BT FindRightSibling(ElementType x);
	BT FindParent(ElementType x);
	BT FindLeftChild(ElementType x);
	BT FindRightChild(ElementType x);
private:
	virtual BT InsertTreeNode(ElementType x, BT T);
	virtual BT DeleteTreeNode(ElementType x, BT T);
	virtual BT FindTreeNode(ElementType x, BT T);
	BT FindLeftSibling(ElementType x, BT T);
	BT FindRightSibling(ElementType x, BT T);
	BT FindParent(ElementType x, BT T);
	BT FindLeftChild(ElementType x, BT T);
	BT FindRightChild(ElementType x, BT T);
	void RecursivePreOrderTravel(BT T);
	void RecursiveInOrderTravel(BT T);
	void RecursivePostOrderTravel(BT T);
	void NonRecursivePreOrderTravel(BT T);
	void NonRecursiveInOrderTravel(BT T);
	void NonRecursivePostOrderTravel(BT T);
	void LevelOrderTravel(BT T);
};

//函数定义：
//返回树高
int BinaryTree::Height()
{
	return TreeHeight(TreeRoot);
}

//初始化二叉树
void BinaryTree::InitBinaryTree()
{
	if (!TreeRoot)
		TreeRoot = NULL;
	else
	{
		Clear();
		TreeRoot = NULL;
	}
}

//创建二叉树
void BinaryTree::CreateBinaryTree()
{
	InitBinaryTree();
}

//递归前序遍历二叉树
void BinaryTree::RecursivePreOrderTravel(BT T)
{
	if (T)
	{
		std::cout << T->data << "--";
		RecursivePreOrderTravel(T->LeftChild);
		RecursivePreOrderTravel(T->RightChild);
	}
}

//递归中序遍历二叉树
void BinaryTree::RecursiveInOrderTravel(BT T)
{
	if (T)
	{
		RecursiveInOrderTravel(T->LeftChild);
		std::cout << T->data << "--";
		RecursiveInOrderTravel(T->RightChild);
	}
}

//递归后序遍历二叉树
void BinaryTree::RecursivePostOrderTravel(BT T)
{
	if (T)
	{
		RecursivePostOrderTravel(T->LeftChild);
		RecursivePostOrderTravel(T->RightChild);
		std::cout << T->data << "--";
	}
}

//非递归前序遍历二叉树
void BinaryTree::NonRecursivePreOrderTravel(BT T)
{
	if (T)
	{
		BT tempT = T;
		std::stack<BT> S;

		while (tempT || !S.empty())
		{
			while (tempT)
			{
				S.push(tempT);
				std::cout << tempT->data << "--";
				tempT = tempT->LeftChild;
			}

			if (!S.empty())
			{
				tempT = S.top();
				S.pop();
				tempT = tempT->RightChild;
			}
		}
		delete tempT;
	}
	else
	{
		std::cout << "该二叉树为空树" << std::endl;
	}
}

//非递归中序遍历二叉树
void BinaryTree::NonRecursiveInOrderTravel(BT T)
{
	if (T)
	{
		BT tempT = T;
		std::stack<BT> S;

		while (tempT || !S.empty())
		{
			while (tempT)
			{
				S.push(tempT);
				tempT = T->LeftChild;
			}

			if (!S.empty())
			{
				tempT = S.top();
				S.pop();
				std::cout << tempT->data << "--";
				tempT = tempT->RightChild;
			}
		}
		delete tempT;
	}
	else
	{
		std::cout << "该二叉树为空树" << std::endl;
	}
}

//非递归后序遍历二叉树
void BinaryTree::NonRecursivePostOrderTravel(BT T)
{
	if (T)
	{
		BT tempT = T;
		std::stack<BT> S;
		std::vector<BT> V;

		S.push(tempT);

		while (!S.empty())
		{
			tempT = S.top();
			V.push_back(tempT);
			S.pop();
			if (tempT->LeftChild)
				S.push(tempT->LeftChild);
			if (tempT->RightChild)
				S.push(tempT->RightChild);
		}

		for (std::vector<BT>::reverse_iterator riter = V.rbegin(); riter != V.rend(); riter++)
			std::cout << (*(riter))->data << "--";
		std::cout << std::endl;
		
		delete tempT;
	}
	else
	{
		std::cout << "该二叉树为空树" << std::endl;
	}
}

//层序遍历二叉树
void BinaryTree::LevelOrderTravel(BT T)
{
	if (T)
	{
		std::queue<BT> Q;
		T->pos = 1;
		BT tempT = T;
		Q.push(tempT);
		int index = 1;
		int level = 1;
		while (!Q.empty())
		{
			tempT = Q.front();
			Q.pop();
			
			while (index != tempT->pos)
			{
				std::cout << "(" << index << ")" << "null" << "  ";
				if (index == (int)(pow(2, level) - 1))
				{
					std::cout << std::endl;
					level++;
				}
				index++;
			}
			
			std::cout << "(" << index << ")" << tempT->data << "  ";
			if (index == (int)(pow(2, level) - 1))
			{
				std::cout << std::endl;
				level++;
			}
			index++;
			if (tempT->LeftChild)
			{
				tempT->LeftChild->pos = tempT->pos * 2;
				Q.push(tempT->LeftChild);
			}
			if (tempT->RightChild)
			{
				tempT->RightChild->pos = tempT->pos * 2 + 1;
				Q.push(tempT->RightChild);
			}
		}
		tempT = NULL;
		delete tempT;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "该二叉树为空树" << std::endl;
	}
}

//插入节点用纯虚函数，方便以后平衡二叉搜索树及二叉搜索树使用
BT BinaryTree::InsertTreeNode(ElementType x, BT T)
{
	return NULL;
}

//删除指定节点用纯虚函数，方便以后平衡二叉搜索树及二叉搜索树使用
BT BinaryTree::DeleteTreeNode(ElementType x,BT T)
{
	return NULL;
}

//寻找指定节点用纯虚函数，方便以后平衡二叉搜索树及二叉搜索树使用
BT BinaryTree::FindTreeNode(ElementType x,BT T)
{
	return NULL;
}

//返回树根
BT BinaryTree::ReturnTreeRoot()
{
	return TreeRoot;
}

//清空树，树根为NULL
void BinaryTree::Clear()
{
	if (TreeRoot)
	{
		std::queue<BT> Q;

		BT tempT = TreeRoot;
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
		std::cout << "end" << std::endl;
		
		TreeRoot = NULL;
	}
	
	std::cout << "操作完成！" << std::endl;
	
}

//递归求树高
int TreeHeight(BT T)
{
	if (!T)
		return 0;
	else if (!T->LeftChild && !T->RightChild)
		return 1;
	else
		return max(TreeHeight(T->LeftChild), TreeHeight(T->RightChild)) + 1;
}

int max(int a, int b)
{
	return ((a > b) ? a : b);
}

BT BinaryTree::FindLeftSibling(ElementType x, BT T)
{
	BT tempT = FindParent(x, T);
	if (!tempT)
		return NULL;
	if (tempT->LeftChild)
		return tempT->LeftChild;
	else
		return NULL;
}

BT BinaryTree::FindRightSibling(ElementType x, BT T)
{
	BT tempT = FindParent(x, T);
	if (!tempT)
		return NULL;
	if (tempT->RightChild)
		return tempT->RightChild;
	else
		return NULL;
}

BT BinaryTree::FindParent(ElementType x, BT T)
{
	BT parent = T;
	if (!T)
		return parent;
	BT tempT = parent;
	
	if (x > parent->data)
		tempT = parent->RightChild;
	else if (x < parent->data)
		tempT = parent->LeftChild;
	else
		return NULL;

	BT ptrtmp;
	while (tempT)
	{
		ptrtmp = tempT;
		if (x < tempT->data)
			tempT = tempT->LeftChild;
		else if (x > tempT->data)
			tempT = tempT->RightChild;
		else
			return parent;
		parent = ptrtmp;
	}
	return NULL;
}

BT BinaryTree::FindLeftChild(ElementType x, BT T)
{
	BT tempT = FindTreeNode(x, T);
	if (!tempT)
		return NULL;
	if (tempT->LeftChild)
		return tempT->LeftChild;
	else
		return NULL;
}

BT BinaryTree::FindRightChild(ElementType x, BT T)
{
	BT tempT = FindTreeNode(x, T);
	if (!tempT)
		return NULL;
	if (tempT->RightChild)
		return tempT->RightChild;
	else
		return NULL;
}

//基类定义结束

void BinaryTree::R_PreOrderTravel()
{
	RecursivePreOrderTravel(TreeRoot);
}

void BinaryTree::R_InOrderTravel()
{
	RecursiveInOrderTravel(TreeRoot);
}

void BinaryTree::R_PostOrderTravel()
{
	RecursivePostOrderTravel(TreeRoot);
}

void BinaryTree::N_PreOrderTravel()
{
	NonRecursivePreOrderTravel(TreeRoot);
}

void BinaryTree::N_InOrderTravel()
{
	NonRecursiveInOrderTravel(TreeRoot);
}

void BinaryTree::N_PostOrderTravel()
{
	NonRecursivePostOrderTravel(TreeRoot);
}

void BinaryTree::LevelOrderTravel()
{
	LevelOrderTravel(TreeRoot);
}

BT BinaryTree::FindLeftSibling(ElementType x)
{
	return FindLeftSibling(x, TreeRoot);
}

BT BinaryTree::FindRightSibling(ElementType x)
{
	return FindRightSibling(x, TreeRoot);
}

BT BinaryTree::FindParent(ElementType x)
{
	return FindParent(x, TreeRoot);
}

BT BinaryTree::FindLeftChild(ElementType x)
{
	return FindLeftChild(x, TreeRoot);
}

BT BinaryTree::FindRightChild(ElementType x)
{
	return FindRightChild(x, TreeRoot);
}

bool BinaryTree::isCBT()
{
	if (TreeRoot)
	{
		std::queue<BT> Q;
		int flag = 0;
		BT tempT = TreeRoot;
		Q.push(tempT);

		while (!Q.empty())
		{
			tempT = Q.front();
			Q.pop();
			
			if (tempT->LeftChild == NULL)
				flag = 1;
			else
			{
				if (flag)
					return false;
				else
					Q.push(tempT->LeftChild);
			}
			if (tempT->RightChild == NULL)
				flag = 1;
			else
			{
				if (flag)
					return false;
				else
					Q.push(tempT->RightChild);
			}
			
		}
		tempT = NULL;
		delete tempT;
		return true;
		std::cout << std::endl;
	}
	else
	{
		std::cout << "该二叉树为空树" << std::endl;
		return false;
	}
}