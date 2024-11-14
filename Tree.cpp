#include <bits/stdc++.h>
using namespace std;

#define ElementType int

typedef struct tagTNode // cau truc cua 1 cay
{
	ElementType key;
	tagTNode* pLeft, *pRight;
}TNode;

void InitTree(TNode* root) // tao cay rong
{
	root = NULL;
}

bool IsEmptyTree(TNode* root) // kiem tra cay rong
{
	return root == NULL;
}

bool IsLeafTree(TNode* root) // kiem tra nut la
{
	return root->pLeft == NULL && root->pRight == NULL;
}

void NLR(TNode* root)
{
	if(root != NULL)
	{
		NLR(root->pLeft);
		// xu ly thong tin tai root
		NLR(root->pRight);
	}
}

void  

int main() 
{
	
	return 0;
}
