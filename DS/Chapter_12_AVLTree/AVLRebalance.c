#include <stdio.h>
#include "BinaryTree3.h"

// LL ÈžÀü
BTreeNode * RotateLL(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
	ChangeRightSubTree(cNode, pNode);
	return cNode;
}

// RR ÈžÀü
BTreeNode * RotateRR(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode, pNode);
	return cNode;
}

// RL ÈžÀü
BTreeNode * RotateRL(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, RotateLL(cNode));   // ºÎºÐÀû LL ÈžÀü
	return RotateRR(pNode);     // RR ÈžÀü
}

// LR ÈžÀü
BTreeNode * RotateLR(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);
	
	ChangeLeftSubTree(pNode, RotateRR(cNode));   // ºÎºÐÀû RR ÈžÀü
	return RotateLL(pNode);     // LL ÈžÀü
}

// Æ®ž®ÀÇ ³ôÀÌžŠ °è»êÇÏ¿© ¹ÝÈ¯
int GetHeight(BTreeNode * bst) 
{
	int leftH;		// left height
	int rightH;		// right height

	if(bst == NULL)
		return 0;

	// ¿ÞÂÊ Œ­ºê Æ®ž® ³ôÀÌ °è»ê
	leftH = GetHeight(GetLeftSubTree(bst));

	// ¿Àž¥ÂÊ Œ­ºê Æ®ž® ³ôÀÌ °è»ê
	rightH = GetHeight(GetRightSubTree(bst));

	// Å« °ªÀÇ ³ôÀÌžŠ ¹ÝÈ¯ÇÑŽÙ.
	if(leftH > rightH)
		return leftH + 1;
	else
		return rightH + 1;
}

// µÎ Œ­ºê Æ®ž®ÀÇ ³ôÀÌÀÇ Â÷žŠ ¹ÝÈ¯
int GetHeightDiff(BTreeNode * bst)
{
	int lsh;    // left sub tree height
	int rsh;    // right sub tree height

	if(bst == NULL)
		return 0;

	lsh = GetHeight(GetLeftSubTree(bst));
	rsh = GetHeight(GetRightSubTree(bst));

	return lsh - rsh;
}

// Æ®ž®ÀÇ ±ÕÇüÀ» ÀâŽÂŽÙ.
BTreeNode * Rebalance(BTreeNode ** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot);

	if(hDiff > 1)     // ¿ÞÂÊ Œ­ºê Æ®ž® ¹æÇâÀž·Î ³ôÀÌ°¡ 2 ÀÌ»ó Å©ŽÙžé
	{
		if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0)
			*pRoot = RotateLL(*pRoot);
		else
			*pRoot = RotateLR(*pRoot);
	}
	
	if(hDiff < -1)     // ¿Àž¥ÂÊ Œ­ºê Æ®ž® ¹æÇâÀž·Î 2 ÀÌ»ó Å©ŽÙžé
	{
		if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0)
			*pRoot = RotateRR(*pRoot);
		else
			*pRoot = RotateRL(*pRoot);
	}
	
	return *pRoot;
}