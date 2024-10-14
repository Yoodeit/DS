#ifndef __BINARY_TREE3_H__
#define __BINARY_TREE3_H__

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode * left;
	struct _bTreeNode * right;
} BTreeNode;

BTreeNode * MakeBTreeNode(void);
BTData GetData(BTreeNode * bt);
void SetData(BTreeNode * bt, BTData data);

BTreeNode * GetLeftSubTree(BTreeNode * bt);
BTreeNode * GetRightSubTree(BTreeNode * bt);

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub);
void MakeRightSubTree(BTreeNode * main, BTreeNode * sub);

typedef void VisitFuncPtr(BTData data);

void PreorderTraverse(BTreeNode * bt, VisitFuncPtr action);
void InorderTraverse(BTreeNode * bt, VisitFuncPtr action);
void PostorderTraverse(BTreeNode * bt, VisitFuncPtr action);

// ¿ÞÂÊ ÀÚœÄ ³ëµå ÁŠ°Å, ÁŠ°ÅµÈ ³ëµåÀÇ ÁÖŒÒ °ªÀÌ ¹ÝÈ¯µÈŽÙ.
BTreeNode * RemoveLeftSubTree(BTreeNode * bt);

// ¿Àž¥ÂÊ ÀÚœÄ ³ëµå ÁŠ°Å, ÁŠ°ÅµÈ ³ëµåÀÇ ÁÖŒÒ °ªÀÌ ¹ÝÈ¯µÈŽÙ.
BTreeNode * RemoveRightSubTree(BTreeNode * bt);

// žÞžðž® ŒÒžêÀ» Œö¹ÝÇÏÁö ŸÊ°í mainÀÇ ¿ÞÂÊ ÀÚœÄ ³ëµåžŠ º¯°æÇÑŽÙ. 
void ChangeLeftSubTree(BTreeNode * main, BTreeNode * sub);

// žÞžðž® ŒÒžêÀ» Œö¹ÝÇÏÁö ŸÊ°í mainÀÇ ¿Àž¥ÂÊ ÀÚœÄ ³ëµåžŠ º¯°æÇÑŽÙ. 
void ChangeRightSubTree(BTreeNode * main, BTreeNode * sub);

#endif