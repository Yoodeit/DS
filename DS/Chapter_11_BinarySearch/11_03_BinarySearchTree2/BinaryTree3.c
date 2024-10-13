#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree3.h"

BTreeNode * MakeBTreeNode(void)
{
	BTreeNode * nd = (BTreeNode*)malloc(sizeof(BTreeNode));

	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData GetData(BTreeNode * bt)
{
	return bt->data;
}

void SetData(BTreeNode * bt, BTData data)
{
	bt->data = data;
}

BTreeNode * GetLeftSubTree(BTreeNode * bt)
{
	return bt->left;
}

BTreeNode * GetRightSubTree(BTreeNode * bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub)
{
	if(main->left != NULL)
		free(main->left);

	main->left = sub;
}

void MakeRightSubTree(BTreeNode * main, BTreeNode * sub)
{
	if(main->right != NULL)
		free(main->right);

	main->right = sub;
}

void PreorderTraverse(BTreeNode * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	action(bt->data);
	PreorderTraverse(bt->left, action);
	PreorderTraverse(bt->right, action);
}

void InorderTraverse(BTreeNode * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	InorderTraverse(bt->left, action);
	action(bt->data);
	InorderTraverse(bt->right, action);
}

void PostorderTraverse(BTreeNode * bt, VisitFuncPtr action)
{
	if(bt == NULL)
		return;

	PostorderTraverse(bt->left, action);
	PostorderTraverse(bt->right, action);
	action(bt->data);
}

// 왼쪽 자식 노드를 트리에서 제거, 제거된 노드의 주소 값이 반환된다.
BTreeNode * RemoveLeftSubTree(BTreeNode * bt)
{
	BTreeNode * delNode;

	if(bt != NULL) { //bt가 빈 게 아니라면
		delNode = bt->left; //delNode에 기존좌측서브트리를 담고
		bt->left = NULL; //NULL로 밀어버림
	}
	return delNode; //삭제된 노드 반환
}

// 오른쪽 자식 노드를 트리에서 제거, 제거된 노드의 주소 값이 반환된다.
BTreeNode * RemoveRightSubTree(BTreeNode * bt)
{
	BTreeNode * delNode;

	if(bt != NULL) {
		delNode = bt->right;
		bt->right = NULL;
	}
	return delNode;
}

// 메모리 소멸을 수반하지 않고  main의 왼쪽 자식 노드를 변경한다.
void ChangeLeftSubTree(BTreeNode * main, BTreeNode * sub) 
{
	main->left = sub; //걍 받은 main의 left를 새로 받은 sub으로 연결할 뿐.
}
 
// 메모리 소멸을 수반하지 않고 main의 오른쪽 자식 노드를 변경한다.
void ChangeRightSubTree(BTreeNode * main, BTreeNode * sub)
{
	main->right = sub;
}