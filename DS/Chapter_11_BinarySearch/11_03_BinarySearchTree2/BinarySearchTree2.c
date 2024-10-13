#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree3.h"
#include "BinarySearchTree2.h"

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

	
	while(cNode != NULL)
	{
		if(data == GetData(cNode))
			return;   

		pNode = cNode;

		if(GetData(cNode) > data)
			cNode = GetLeftSubTree(cNode);
		else
			cNode = GetRightSubTree(cNode);
	}
	
	
	nNode = MakeBTreeNode();    
	SetData(nNode, data);    

	
	if(pNode != NULL)    
	{
		if(data < GetData(pNode))
			MakeLeftSubTree(pNode, nNode);
		else
			MakeRightSubTree(pNode, nNode);
	}
	else    
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

// 삭제 기능
BTreeNode * BSTRemove(BTreeNode ** pRoot, BSTData target)
{
	

	BTreeNode * pVRoot = MakeBTreeNode();    //PVROOT라는 새 노드를 생성
	// pvroot라는 가상 루트 노드를 형성한 이유는 삭제할 노드가 루트노드인 경우의 예외적인 삭제흐름을 일반화하기 위함.
	BTreeNode * pNode = pVRoot;    // parent node(PVROOT가 루트노드가 됩니다.)
	BTreeNode * cNode = *pRoot;    // current node(기존 루트노드는 cnode)
	BTreeNode * dNode;    // delete node

	
	ChangeRightSubTree(pVRoot, *pRoot); //pVRoot의 우측 서브트리로 기존 트리를 연결
	
	//삭제 대상인 노드를 탐색
	while(cNode != NULL && GetData(cNode) != target)
		//cNode가 NULL이면 탐색실패로 탈출, target이면 탐색성공으로 탈출
	{
		pNode = cNode; //현 cNode값을 pNode에 백업하고 내려감.

		if(target < GetData(cNode)) //target이 cNode의 데이터보다 작다면
			cNode = GetLeftSubTree(cNode); //좌측으로 내려갑니다.
		else
			cNode = GetRightSubTree(cNode); //아니면 우측.
	}

	if(cNode == NULL) //삭제 대상이 존재하지 않는다면   
		return NULL; //NULL 반환

	dNode = cNode; //삭제 대상이 존재한다면 dNode가 가리키게 한다.   

	// 첫 번째 경우 : 삭제 대상이 단말 노드인 경우
	if(GetLeftSubTree(dNode) == NULL && GetRightSubTree(dNode) == NULL) //(좌우에 서브트리가 달려있지 않은 경우)
	{
		if(GetLeftSubTree(pNode) == dNode) //pNode의 왼쪽이 dNode면,
			RemoveLeftSubTree(pNode); //그걸 지웁니다.
		else
			RemoveRightSubTree(pNode); //오른쪽이면 그걸 지워요.
	}

	// 두 번째 경우 : 삭제 대상이 하나의 자식 노드를 갖는 경우
	else if(GetLeftSubTree(dNode) == NULL || GetRightSubTree(dNode) == NULL) //위에서 한 번 단말노드인 경우(좌우서브트리가 둘 다 없는 경우)는 분기했으므로 OR로 조건문을 써도 문제 X
	{
		BTreeNode * dcNode; //삭제 대상의 자식 노드 가리킴

		if(GetLeftSubTree(dNode) != NULL) // dNode의 left가 있으면
			dcNode = GetLeftSubTree(dNode); //dc노드를 그걸로 선정
		else
			dcNode = GetRightSubTree(dNode); //right가 있으면 그걸로 선정

		if(GetLeftSubTree(pNode) == dNode) //pNode의 왼쪽이 dNode면 pNode의 왼쪽을 dc로.
			ChangeLeftSubTree(pNode, dcNode);
		else
			ChangeRightSubTree(pNode, dcNode); //오른쪽이면 오른쪽을 dc로.
	}

	// 세 번째 경우 : 두 개의 자식 노드를 모두 갖는 경우
	else
	{
		BTreeNode * mNode = GetRightSubTree(dNode);    // mininum node를 right서브트리로 결정했습니다. 이제 오른쪽에서 최솟값을 대체노드로 설정할거임.
		BTreeNode * mpNode = dNode;    // 대체 노드의 부모노드는 삭제할 노드죠. 자식노드는 접합대상이고요.
		int delData;

		//삭제 대상의 대체 노드를 찾는다.
		while(GetLeftSubTree(mNode) != NULL) //좌측서브트리가 없을떄까지 파고들어갑니다.
		{
			mpNode = mNode; //현 mNode를 mpNode로 만들고요
			mNode = GetLeftSubTree(mNode); //좌측으로 파고파고 들어갑니다.
		}
		
		//대체노드에 저장된 값을 삭제할 노드에 대입한다.
		delData = GetData(dNode); // delData 변수에 dNode의 데이터값(삭제할 노드에 담긴 데이터값)을 넣어준다.
		SetData(dNode, GetData(mNode)); // dNode에 mNode의 데이터를 덮어씌워줍니다.

		// 대체 노드의 부모 노드와 자식 노드를 연결.(접합)
		if(GetLeftSubTree(mpNode) == mNode) //mpNode의 왼쪽이 대체노드라면
			ChangeLeftSubTree(mpNode, GetRightSubTree(mNode)); //대체노드는 삭제할 노드보다 큰 값 중에서 최소값임. 대체노드의 왼쪽서브트리는 존재하는 순간 모순임. 그럼 그게 최소값일테니까.
		// 그래서 mpNode의 서브트리를 mNode의 우측으로 연결한다는 건데, 혹시나 우측서브트리도 없다면 ? 그러면 그냥 NULL값 연결이니까 똑같음.
		else
			ChangeRightSubTree(mpNode, GetRightSubTree(mNode));

		dNode = mNode; 
		SetData(dNode, delData);  //반환할 삭제대상을 위한 작업.
	}

	
	if(GetRightSubTree(pVRoot) != *pRoot) //만약 상기 삭제 과정으로 루트노드가 삭제되었다면
		*pRoot = GetRightSubTree(pVRoot); //루트 도드의 변경을 반영한다.

	free(pVRoot); //가짜루트노드는 소멸
	return dNode; //삭제대상 반환.
}

void ShowIntData(int data)
{
	printf("%d ", data);
}

void BSTShowAll(BTreeNode * bst)
{
	InorderTraverse(bst, ShowIntData);
}