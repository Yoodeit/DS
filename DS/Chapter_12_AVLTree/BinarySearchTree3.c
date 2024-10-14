#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree3.h"
#include "BinarySearchTree3.h"
#include "AVLRebalance.h"

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
	
	*pRoot = Rebalance(pRoot);	// ³ëµå Ãß°¡ ÈÄ ž®¹ë·±œÌ
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

BTreeNode * BSTRemove(BTreeNode ** pRoot, BSTData target)
{
	// »èÁŠ Žë»óÀÌ ·çÆ® ³ëµåÀÎ °æ¿ìžŠ º°µµ·Î °í·ÁÇØŸß ÇÑŽÙ.

	BTreeNode * pVRoot = MakeBTreeNode();    // °¡»ó ·çÆ® ³ëµå;

	BTreeNode * pNode = pVRoot;    // parent node
	BTreeNode * cNode = *pRoot;    // current node
	BTreeNode * dNode;    // delete node

	// ·çÆ® ³ëµåžŠ pVRoot°¡ °¡ž®Å°ŽÂ ³ëµåÀÇ ¿Àž¥ÂÊ Œ­ºê ³ëµå°¡ µÇ°Ô ÇÑŽÙ.
	ChangeRightSubTree(pVRoot, *pRoot);
	
	// »èÁŠ Žë»óÀ» ÀúÀåÇÑ ³ëµå Åœ»ö
	while(cNode != NULL && GetData(cNode) != target)
	{
		pNode = cNode;

		if(target < GetData(cNode))
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}

	if(cNode == NULL)    // »èÁŠ Žë»óÀÌ ÁžÀçÇÏÁö ŸÊŽÂŽÙžé,
		return NULL;

	dNode = cNode;    // »èÁŠ Žë»óÀ» dNode°¡ °¡ž®Å°°Ô ÇÑŽÙ.

	// Ã¹ ¹øÂ° °æ¿ì: »èÁŠÇÒ ³ëµå°¡ ŽÜž» ³ëµåÀÎ °æ¿ì
	if(GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL)
	{
		if(GetLeftSubTree(pNode) == dNode)
			RemoveLeftSubTree(pNode);
		else
			RemoveRightSubTree(pNode);
	}

	// µÎ ¹øÂ° °æ¿ì: ÇÏ³ªÀÇ ÀÚœÄ ³ëµåžŠ °®ŽÂ °æ¿ì
	else if(GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL)
	{
		BTreeNode * dcNode;    // delete nodeÀÇ ÀÚœÄ ³ëµå

		if(GetLeftSubTree(dNode) != NULL)
			dcNode = GetLeftSubTree(dNode);
		else
			dcNode = GetRightSubTree(dNode);

		if(GetLeftSubTree(pNode) == dNode)
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode);
	}

	// ŒŒ ¹øÂ° °æ¿ì: µÎ °³ÀÇ ÀÚœÄ ³ëµåžŠ žðµÎ °®ŽÂ °æ¿ì
	else
	{
		BTreeNode * mNode = GetRightSubTree(dNode);    // mininum node
		BTreeNode * mpNode = dNode;    // mininum nodeÀÇ ºÎžð ³ëµå
		int delData;

		// »èÁŠÇÒ ³ëµåžŠ ŽëÃŒÇÒ ³ëµåžŠ Ã£ŽÂŽÙ.
		while(GetLeftSubTree(mNode) != NULL)
		{
			mpNode = mNode;
			mNode = GetLeftSubTree(mNode);
		}
		
		// ŽëÃŒÇÒ ³ëµå¿¡ ÀúÀåµÈ °ªÀ» »èÁŠÇÒ ³ëµå¿¡ ŽëÀÔÇÑŽÙ.
		delData = GetData(dNode);    // ŽëÀÔ Àü µ¥ÀÌÅÍ ¹éŸ÷
		SetData(dNode, GetData(mNode));

		// ŽëÃŒÇÒ ³ëµåÀÇ ºÎžð ³ëµå¿Í ÀÚœÄ ³ëµåžŠ ¿¬°áÇÑŽÙ.
		if(GetLeftSubTree(mpNode) == mNode)
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode));
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode;
		SetData(dNode, delData);    // ¹éŸ÷ µ¥ÀÌÅÍ º¹¿ø
	}

	// »èÁŠµÈ ³ëµå°¡ ·çÆ® ³ëµåÀÎ °æ¿ì¿¡ ŽëÇÑ Ã³ž®
	if(GetRightSubTree(pVRoot) != *pRoot)
		*pRoot = GetRightSubTree(pVRoot);

	free(pVRoot);

    *pRoot = Rebalance(pRoot); 	// ³ëµå ÁŠ°Å ÈÄ ž®¹ë·±œÌ!
	return dNode;
}

void ShowIntData(int data)
{
	printf("%d ", data);
}

void BSTShowAll(BTreeNode * bst)
{
	InorderTraverse(bst, ShowIntData);
}