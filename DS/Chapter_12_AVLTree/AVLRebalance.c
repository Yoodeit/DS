#include <stdio.h>
#include "BinaryTree3.h"

// LL Rotation
BTreeNode * RotateLL(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);

	ChangeLeftSubTree(pNode, GetRightSubTree(cNode));
	// pNode를 cNode의 우측으로 붙이며 기존 우측서브트리가 날라갈 수 있으니 미리 pNode에 붙여둠.
	ChangeRightSubTree(cNode, pNode);
	return cNode;
}

// RR 회전
BTreeNode * RotateRR(BTreeNode * bst)
{
	BTreeNode * pNode; //부모노드
	BTreeNode * cNode; //자식노드
	
	
	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, GetLeftSubTree(cNode));
	ChangeLeftSubTree(cNode, pNode);
	return cNode;
}

// RL 회전
BTreeNode * RotateRL(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetRightSubTree(pNode);

	ChangeRightSubTree(pNode, RotateLL(cNode));   // 부분적 LL 회전
	return RotateRR(pNode);     // RR 회전
}

// LR 회전
BTreeNode * RotateLR(BTreeNode * bst)
{
	BTreeNode * pNode;
	BTreeNode * cNode;

	pNode = bst;
	cNode = GetLeftSubTree(pNode);
	
	ChangeLeftSubTree(pNode, RotateRR(cNode));   // 부분적 RR회전
	return RotateLL(pNode);     // LL 회전
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

// 4가지 상황 중 어떤 회전이 필요한지 판단하는 함수
BTreeNode * Rebalance(BTreeNode ** pRoot)
{
	int hDiff = GetHeightDiff(*pRoot); //균형 인수를 계산해서 hDiff에 담는다.
	
	//우선 균형 인수가 +2 이상이면 LL상태 혹은 LR상태이다.
	
	if(hDiff > 1)     // 왼쪽 서브 트리 방향으로 높이가 2 이상 크다면
	{
		if(GetHeightDiff(GetLeftSubTree(*pRoot)) > 0) //왼쪽으로 한 단계 내려가서 그대로 왼쪽이 더 긴지 오른쪽으로 꺾어서 긴지를 확인
			*pRoot = RotateLL(*pRoot); //쭉 왼쪽이 길면 LL회전이고
		else
			*pRoot = RotateLR(*pRoot); //꺾이면 LR회전이지.
	}
	
	//균형 인수가 -2 이하이면 RR상태 또는 RL상태이다.
	
	if(hDiff < -1)     // 오른쪽 서브 트리 방향으로 2이상 크다면
	{
		if(GetHeightDiff(GetRightSubTree(*pRoot)) < 0) //쭉 오른쪽이면
			*pRoot = RotateRR(*pRoot); //RR 회전을 하면 되고
		else
			*pRoot = RotateRL(*pRoot); //꺾이면 RL회전을 하면 된다.
	}
	
	return *pRoot;
}