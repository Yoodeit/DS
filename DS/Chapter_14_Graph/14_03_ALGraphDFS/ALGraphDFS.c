#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALGraphDFS.h"
#include "DLinkedList.h"
#include "ArrayBaseStack.h" //스택 사용

int WhoIsPrecede(int data1, int data2);

// 그래프의 초기화
void GraphInit(ALGraph * pg, int nv)
{
	int i;	
	
	// 정점의 수에 해당하는 길이의 리스트 배열을 생성한다.
	pg->adjList = (List*)malloc(sizeof(List)*nv); // 간선정보를 저장할 리스트 생성
	pg->numV = nv;	// 정점의 수는 nv에 저장된 값으로 결정
	pg->numE = 0;     // 초기의 간선 수는 0개

	// 정점의 수만큼 생성된 리스트들을 초기화한다.
	for(i=0; i<nv; i++)
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede); // 그래프와 연관 없음. 걍 연결리스트 구현할 때 rule함수 넣도록 세팅했기에 넣어줄 뿐.
	}

	//멤버 visitinfo 관련 추가 코드
	pg->visitInfo= (int *)malloc(sizeof(int) * pg->numV); // 정점의 수를 길이로 하여 배열을 할당
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV); // 배열의 모든 요소를 0으로 초기화
}

// 그래프 리소스의 해제
void GraphDestroy(ALGraph * pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

// 간선의 추가
void AddEdge(ALGraph * pg, int fromV, int toV)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;
}

// 간선의 정보 출력
void ShowGraphEdgeInfo(ALGraph * pg)
{
	int i;
	int vx;

	for(i=0; i<pg->numV; i++)
	{
		printf("%c¿Í ¿¬°áµÈ Á€Á¡: ", i + 65);
		
		if(LFirst(&(pg->adjList[i]), &vx))
		{
			printf("%c ", vx + 65);
			
			while(LNext(&(pg->adjList[i]), &vx))
				printf("%c ", vx + 65);
		}
		printf("\n");
	}
}

int WhoIsPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}


// 방문한 정점의 정보를 기록 및 출력
int VisitVertex(ALGraph * pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0) // visitV(접근한 정점)에 처음 방문(0)일 때 '참'인 if문
	{
		pg->visitInfo[visitV] = 1; // 처음 방문했으니까 visitV에 방문한 것으로 기록
		printf("%c ", visitV + 65);     // 방문한 정점의 이름을 출력
		return TRUE; // 방문 성공을 의미
	}
	
	return FALSE; // 방문 실패를 의미(이미 방문한 정점이라면 False가 반환됨)
}

// Depth First Search: 정점의 정보 출력(DFS기반)
void DFShowGraphVertex(ALGraph * pg, int startV)
{
	Stack stack; // 스택 생성
	int visitV = startV; //시작정점부터 방문을 시작해야 하니까
	int nextV;

	// 스택 초기화
	StackInit(&stack);

	VisitVertex(pg, visitV);    // 시작 정점 방문
	SPush(&stack, visitV);		// 시작 정점 떠나면서 스택으로

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE) //연결된 정점의 정보를 얻어서 nextV에 저장.
	{
		int visitFlag = FALSE; //visitFlag의 default값이 일단 FALSE

		if(VisitVertex(pg, nextV) == TRUE) //만약 방문을 시도했는데 방문에 성공하면
		{
			// 방문한 정점을 떠나야 하니 해당 정보는 스택으로 보낸다.
			SPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else //방문을 시도했는데 이미 방문한 적 있는 곳이라면
		{
			// 연결된 다른 정점을 찾아서 방문을 시도하는 일련의 과정임.
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				if(VisitVertex(pg, nextV) == TRUE)
				{
					
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		
		if(visitFlag == FALSE) // 연결된 정점과의 방문이 모두 완료되었다면,
		{
			if(SIsEmpty(&stack) == TRUE)    // 스택이 비면 종료
				break;
			else
				visitV = SPop(&stack);	// 스택이 빈 게 아니라면 아직 남았으니 되돌아가기 위한 POP dustks
		}
	}

	// Åœ»ö Á€ºž ÃÊ±âÈ­
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}