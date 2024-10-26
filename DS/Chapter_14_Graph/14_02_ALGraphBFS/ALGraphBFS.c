#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALGraphBFS.h"
#include "DLinkedList.h"
#include "CircularQueue.h" //큐사용

int WhoIsPrecede(int data1, int data2);

// 그래프의 초기화
void GraphInit(ALGraph * pg, int nv)
{
	int i;

	// 정점의 수에 해당하는 길이의 리스트 배열을 생성한다.
	pg->adjList = (List*)malloc(sizeof(List)*nv); // 간선정보를 저장할 리스트 생성
	pg->numV = nv; // 정점의 수는 nv에 저장된 값으로 결정
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
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;
		printf("%c ", visitV + 65);    // 방문한 정점의 이름을 출력
		return TRUE;
	}
	
	return FALSE;
}

// Breadth First Search: Á€Á¡ÀÇ Á€ºž Ãâ·Â
void BFShowGraphVertex(ALGraph * pg, int startV)
{
	Queue queue; //큐 생성
	int visitV = startV;
	int nextV;

	// 생성한 큐 초기화
	QueueInit(&queue);

	// 시작점 방문
	VisitVertex(pg, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
		// visitV에 연결된 정점 정보 얻음
	{
		if(VisitVertex(pg, nextV) == TRUE)
			Enqueue(&queue, nextV);

		while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			//계속해서 정점 visitV에 연결된 정점정보 얻음
		{
			if(VisitVertex(pg, nextV) == TRUE)
				Enqueue(&queue, nextV);
		}

		if(QIsEmpty(&queue) == TRUE)    // 큐가 비면 탈출조건 성립
			break;
		else
			visitV = Dequeue(&queue);	
	}

	// Åœ»ö Á€ºž ÃÊ±âÈ­
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}