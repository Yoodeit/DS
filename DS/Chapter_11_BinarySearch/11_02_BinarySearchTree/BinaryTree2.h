#ifndef __BINARY_TREE2_H__
#define __BINARY_TREE2_H__

typedef int BTData;

typedef struct _bTreeNode
{
	BTData data;
	struct _bTreeNode * left;
	struct _bTreeNode * right;
} BTreeNode;

BTreeNode * MakeBTreeNode(void); //노드를 동적으로 할당해서 그 노드의 주소 값을 반환한다.
BTData GetData(BTreeNode * bt); //노드에 저장된 데이터를 반환한다.
void SetData(BTreeNode * bt, BTData data); //인자로 전달된 데이터를 노드에 저장한다.

BTreeNode * GetLeftSubTree(BTreeNode * bt); // 인자로 전달된 노드의 왼쪽 자식 노드의 주소 값을 반환.
BTreeNode * GetRightSubTree(BTreeNode * bt); // 인자로 전달된 노드의 오른쪽 자식 노드의 주소 값을 반환.

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub); // 인자로 전달된 노드의 왼쪽 자식 노드를 교체한다.
void MakeRightSubTree(BTreeNode * main, BTreeNode * sub); // 인자로 전달된 노드의 오른쪽 자식 노드를 교체한다.

typedef void VisitFuncPtr(BTData data);

void PreorderTraverse(BTreeNode * bt, VisitFuncPtr action);
void InorderTraverse(BTreeNode * bt, VisitFuncPtr action);
void PostorderTraverse(BTreeNode * bt, VisitFuncPtr action);

#endif