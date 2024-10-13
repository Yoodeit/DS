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

//삽입 함수
void BSTInsert(BTreeNode ** pRoot, BSTData data) //새로 넣을 데이터랑 루트노드 주소값의 위치를 받아옵니다.
{
	BTreeNode * pNode = NULL;    // parent node
	BTreeNode * cNode = *pRoot;    // current node
	BTreeNode * nNode = NULL;    // new node

	// 새로운 노드(새 데이터가 담긴 노드)가 추가될 위치를 찾는다.
	while(cNode != NULL) //current Node가 NULL이 아닌 동안은 반복
	{
		if(data == GetData(cNode))
			return;    // 데이터의(키의) 중복을 허용하지 않음. 원래는 키 중복을 허용하지 않지만 여기서는 데이터=키니까.

		pNode = cNode; // 나중에 노드 추가하려면 부모노드에서 뭘 만져줘야 하기 때문.

		if(GetData(cNode) > data) //cNode의 데이터가 새로 넣으려는 데이터보다 크면
			cNode = GetLeftSubTree(cNode); // 좌측서브트리로 내려간다.
		else
			cNode = GetRightSubTree(cNode); //반대로 작으면 우측서브트리로 내려간다.
	}
	//내려가면서 비교가 끝나서 cNode는 NULL이고 pNode가 단말노드일 때.
	
	// 새 노드 만들고 담아줌.
	nNode = MakeBTreeNode();    // 새 노드를 만들어줍니다.
	SetData(nNode, data);    // 새 노드에 담고자 했던 데이터를 만들어줍니다.

	// pNode의 자식 노드로 새 노드를 추가
	if(pNode != NULL)    // 새 노드가 루트 노드가 아니라면
	{
		if(data < GetData(pNode)) //pNode 기준으로 왼쪽에 넣을지 오른쪽에 넣을지 결정.
			MakeLeftSubTree(pNode, nNode); //작으면 왼쪽
		else
			MakeRightSubTree(pNode, nNode); //크면 오른쪽
	}
	else    // 새 노드가 루트노드라면?
	{
		*pRoot = nNode; // 새 노드가 루트노드가 되는거지.
	}
}

// 탐색 함수
BTreeNode * BSTSearch(BTreeNode * bst, BSTData target) //조회만 할 거니까 루트노드의 주소값, 그리고 찾을 target을 찾습니다.
{
	BTreeNode * cNode = bst;    // current node
	BSTData cd;    // current data

	while(cNode != NULL) // cNode가 NULL이 아닐 때까지 진행.
	{
		cd = GetData(cNode); //cd의 루트노드의 데이터부터 담아주고. 그 뒤로는 쭉 cNode의 데이터

		if(target == cd) //target이 cd(cNode의 데이터)와 같다면
			return cNode; //cNode를 반환
		else if(target < cd) //만약 그것보다 작다면
			cNode = GetLeftSubTree(cNode); //왼쪽으로 내려가
		else
			cNode = GetRightSubTree(cNode); //크다면 오른쪽으로 내려가
	}

	return NULL; //cNode가 NULL이면 못찾고 나왔으니 NULL 반환합니다.
}