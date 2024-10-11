#include <stdio.h>
#include "BinaryTree2.h"
#include "BinarySearchTree.h"

void BSTMakeAndInit(BTreeNode ** pRoot)
{
	*pRoot = NULL;
}

BSTData BSTGetNodeData(BTreeNode * bst)
{
	return GetData(bst);
}

void BSTInsert(BTreeNode ** pRoot, BSTData data)
{
	BTreeNode * pNode = NULL;    // parent node
	BTreeNode * cNode = *pRoot;    // current node
	BTreeNode * nNode = NULL;    // new node

	// »õ·Î¿î ³ëµå°¡ Ãß°¡µÉ À§Ä¡žŠ Ã£ŽÂŽÙ.
	while(cNode != NULL)
	{
		if(data == GetData(cNode))
			return;    // Å°ÀÇ Áßº¹À» Çã¿ëÇÏÁö ŸÊÀœ

		pNode = cNode;

		if(GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}
	
	// pNodeÀÇ Œ­ºê ³ëµå¿¡ Ãß°¡ÇÒ »õ ³ëµåÀÇ »ýŒº
	nNode = MakeBTreeNode();    // »õ ³ëµåÀÇ »ýŒº
	SetData(nNode, data);    // »õ ³ëµå¿¡ µ¥ÀÌÅÍ ÀúÀå

	// pNodeÀÇ Œ­ºê ³ëµå¿¡ »õ ³ëµåžŠ Ãß°¡
	if(pNode != NULL)    // »õ ³ëµå°¡ ·çÆ® ³ëµå°¡ ŸÆŽÏ¶óžé,
	{
		if(data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else    // »õ ³ëµå°¡ ·çÆ® ³ëµå¶óžé,
	{
		*pRoot = nNode;
	}
}

BTreeNode * BSTSearch(BTreeNode * bst, BSTData target)
{
	BTreeNode * cNode = bst;    // current node
	BSTData cd;    // current data

	while(cNode != NULL)
	{
		cd = GetData(cNode);

		if(target == cd)
			return cNode;
		else if(target < cd)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	return NULL;
}