#include <stdio.h>
#include "BinarySearchTree.h"

int main(void)
{
	BTreeNode * bstRoot; //BST의 루트 노드 = bstRoot
	BTreeNode * sNode;    // search node

	BSTMakeAndInit(&bstRoot); // BST 생성 및 초기화

	BSTInsert(&bstRoot, 9);
	BSTInsert(&bstRoot, 1);
	BSTInsert(&bstRoot, 6);
	BSTInsert(&bstRoot, 2);
	BSTInsert(&bstRoot, 8);
//	BSTInsert(&bstRoot, 4);
	BSTInsert(&bstRoot, 3);
	BSTInsert(&bstRoot, 5);
//	BSTInsert(&bstRoot, 7);

	sNode = BSTSearch(bstRoot, 1);
	if(sNode == NULL)
		printf("탐색 실패 \n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 4);
	if(sNode == NULL)
		printf("탐색 실패 \n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 6);
	if(sNode == NULL)
		printf("탐색 실패 \n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	sNode = BSTSearch(bstRoot, 7);
	if(sNode == NULL)
		printf("탐색 실패 \n");
	else
		printf("탐색에 성공한 키의 값: %d \n", BSTGetNodeData(sNode));

	return 0;
}