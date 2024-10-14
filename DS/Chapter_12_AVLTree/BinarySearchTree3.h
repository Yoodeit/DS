#ifndef __BINARY_SEARCH_TREE3_H__
#define __BINARY_SEARCH_TREE3_H__

#include "BinaryTree3.h"

typedef BTData	BSTData;

// ÀÌÁø Åœ»ö Æ®ž®ÀÇ »ýŒº ¹× ÃÊ±âÈ­
void BSTMakeAndInit(BTreeNode ** pRoot);

// ³ëµå¿¡ ÀúÀåµÈ µ¥ÀÌÅÍ ¹ÝÈ¯
BSTData BSTGetNodeData(BTreeNode * bst);

// ÀÌÁø Åœ»ö Æ®ž®žŠ Žë»óÀž·Î µ¥ÀÌÅÍ ÀúÀå(³ëµåÀÇ »ýŒº°úÁ€ Æ÷ÇÔ)
void BSTInsert(BTreeNode ** pRoot, BSTData data);

// ÀÌÁø Åœ»ö Æ®ž®žŠ Žë»óÀž·Î µ¥ÀÌÅÍ Åœ»ö
BTreeNode * BSTSearch(BTreeNode * bst, BSTData target);

// Æ®ž®¿¡Œ­ ³ëµåžŠ ÁŠ°ÅÇÏ°í ÁŠ°ÅµÈ ³ëµåÀÇ ÁÖŒÒ °ªÀ» ¹ÝÈ¯ÇÑŽÙ. 
BTreeNode * BSTRemove(BTreeNode ** pRoot, BSTData target);

// ÀÌÁø Åœ»ö Æ®ž®¿¡ ÀúÀåµÈ žðµç ³ëµåÀÇ µ¥ÀÌÅÍžŠ Ãâ·ÂÇÑŽÙ.
void BSTShowAll(BTreeNode * bst);

#endif