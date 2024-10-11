#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include "BinaryTree2.h"

typedef BTData	BSTData;

// BSTÀÇ »ýŒº ¹× ÃÊ±âÈ­
void BSTMakeAndInit(BTreeNode ** pRoot);

// ³ëµå¿¡ ÀúÀåµÈ µ¥ÀÌÅÍ ¹ÝÈ¯
BSTData BSTGetNodeData(BTreeNode * bst);

// BSTžŠ Žë»óÀž·Î µ¥ÀÌÅÍ ÀúÀå(³ëµåÀÇ »ýŒº°úÁ€ Æ÷ÇÔ)
void BSTInsert(BTreeNode ** pRoot, BSTData data);

// BSTžŠ Žë»óÀž·Î µ¥ÀÌÅÍ Åœ»ö
BTreeNode * BSTSearch(BTreeNode * bst, BSTData target);

#endif