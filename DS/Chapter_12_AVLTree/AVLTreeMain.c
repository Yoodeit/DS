#include <stdio.h>
#include "BinaryTree3.h"	// Æ®ž®ÀÇ ±žÁ¶žŠ È®ÀÎÇÏ±â À§ÇØŒ­
#include "BinarySearchTree3.h"

int main(void)
{
	BTreeNode * avlRoot;
	BTreeNode * clNode;		// current left node
	BTreeNode * crNode;		// current right node
	BSTMakeAndInit(&avlRoot);

	BSTInsert(&avlRoot, 1);
	BSTInsert(&avlRoot, 2);
	BSTInsert(&avlRoot, 3);
	BSTInsert(&avlRoot, 4);
	BSTInsert(&avlRoot, 5);
	BSTInsert(&avlRoot, 6);
	BSTInsert(&avlRoot, 7);
	BSTInsert(&avlRoot, 8);
	BSTInsert(&avlRoot, 9);

	printf("·çÆ® ³ëµå: %d \n", GetData(avlRoot));

	clNode = GetLeftSubTree(avlRoot);
	crNode = GetRightSubTree(avlRoot);
	printf("¿ÞÂÊ1: %d, ¿Àž¥ÂÊ1: %d \n", GetData(clNode), GetData(crNode));

	clNode = GetLeftSubTree(clNode);
	crNode = GetRightSubTree(crNode);
	printf("¿ÞÂÊ2: %d, ¿Àž¥ÂÊ2: %d \n", GetData(clNode), GetData(crNode));

	clNode = GetLeftSubTree(clNode);
	crNode = GetRightSubTree(crNode);
	printf("¿ÞÂÊ3: %d, ¿Àž¥ÂÊ3: %d \n", GetData(clNode), GetData(crNode));

	clNode = GetLeftSubTree(clNode);
	crNode = GetRightSubTree(crNode);
	printf("¿ÞÂÊ4: %d, ¿Àž¥ÂÊ4: %d \n", GetData(clNode), GetData(crNode));
	return 0;
}