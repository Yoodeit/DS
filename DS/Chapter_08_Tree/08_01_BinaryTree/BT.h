#ifndef __BINARY_TREE_H__
#define __BINARY_TREE_H__

typedef int BTData;

typedef struct _bTreeNode //트리를 이루는 노드 구조체
{
	BTData data; //노드가 담을 값과
	struct _bTreeNode * left; // 왼쪽 노드
	struct _bTreeNode * right; //오른쪽 노드
} BTreeNode;

/*** BTreeNode 관련 연산들 ****/
BTreeNode * MakeBTreeNode(void); //노드 생성하는 함수
BTData GetData(BTreeNode * bt); //루트노드를 주면 값을 가져다주는 함수
void SetData(BTreeNode * bt, BTData data); //전달한 노드에 데이터를 담는 함수

BTreeNode * GetLeftSubTree(BTreeNode * bt); // 루트노드를 주면 왼쪽 서브트리를 반환하는 함수
BTreeNode * GetRightSubTree(BTreeNode * bt);// 루트노드를 주면 오른쪽 서브트리를 반환하는 함수

void MakeLeftSubTree(BTreeNode * main, BTreeNode * sub); 
void MakeRightSubTree(BTreeNode * main, BTreeNode * sub); 

#endif