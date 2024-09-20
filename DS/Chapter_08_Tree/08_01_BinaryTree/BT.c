#include <stdio.h>
#include <stdlib.h>
#include "BT.h"

BTreeNode * MakeBTreeNode(void) //이진트리의 노드를 만드는 함수
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

void SetData(BTreeNode * bt, BTData data) //노드에 값 저장하는 함수
{
	bt->data = data; //받은 값을 전달한 노드에 저장합니다.
}

BTreeNode * GetLeftSubTree(BTreeNode * bt) // 왼쪽 서브트리 갖다주는 함수
{
	return bt->left;
}

BTreeNode * GetRightSubTree(BTreeNode * bt)
{
	return bt->right;
}

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub) //왼쪽에 서브트리를 붙여줍니다.
{
	if(main->left != NULL) //왼쪽이 Null이 아니면(뭐가 있으면) free해줍니다.
		free(main->left);

	main->left = sub;
}

void MakeRightSubTree(BTreeNode * main, BTreeNode * sub)
{
	if(main->right != NULL) //기존에 연결된 노드는 삭제되게 구현
		free(main->right);

	main->right = sub;
}
