#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ALGraphKruskal.h"
#include "DLinkedList.h"
#include "ArrayBaseStack.h"

int WhoIsPrecede(int data1, int data2);
int PQWeightComp(Edge d1, Edge d2); //가중치 기준 내림차순으로 간선 정보 꺼내기 위함.

void GraphInit(ALGraph * pg, int nv)
{
	int i;	

	pg->adjList = (List*)malloc(sizeof(List)*nv);
	pg->numV = nv;
	pg->numE = 0;

	for(i=0; i<nv; i++)
	{
		ListInit(&(pg->adjList[i]));
		SetSortRule(&(pg->adjList[i]), WhoIsPrecede); 
	}

	pg->visitInfo= (int *)malloc(sizeof(int) * pg->numV);
	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);

	// 이 부분이 Kruskal Algorithm을 위해 추가된 부분.
	// 우선순위 큐의 초기화
	PQueueInit(&(pg->pqueue), PQWeightComp); //우선도 비교가 가능하도록 하는 함수 포인터를 넘겨주며 초기화.
}

void GraphDestroy(ALGraph * pg)
{
	if(pg->adjList != NULL)
		free(pg->adjList);

	if(pg->visitInfo != NULL)
		free(pg->visitInfo);
}

void AddEdge(ALGraph * pg, int fromV, int toV, int weight)
{
	Edge edge = {fromV, toV, weight};     // 간선의 가중치 정보를 담음

	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	pg->numE += 1;

	// 간선의 가중치 정보를 우선순위 큐에 저장.
	PEnqueue(&(pg->pqueue), edge);
}

// ConKruskalMST Helper function
// 삭제된 간선 정보를 복구하는 함수: ConKruskalMST Helper function
void RecoverEdge(ALGraph * pg, int fromV, int toV, int weight)
{
	LInsert(&(pg->adjList[fromV]), toV);
	LInsert(&(pg->adjList[toV]), fromV);
	(pg->numE)++;
}

// 한 쪽 간선 삭제하는 함수
// RemoveEdge 함수를 방향별로 쪼개기 위해 필요함.
// 이렇게 하면 무방향그래프 뿐 아니라 방향그래프에서도 써먹을 수 있기 때문에.
void RemoveWayEdge(ALGraph * pg, int fromV, int toV)
{
	int edge;

	if(LFirst(&(pg->adjList[fromV]), &edge))
	{
		if(edge == toV)
		{
			LRemove(&(pg->adjList[fromV]));
			return;
		}

		while(LNext(&(pg->adjList[fromV]), &edge))
		{
			if(edge == toV)
			{
				LRemove(&(pg->adjList[fromV]));
				return;
			}
		}
	}
	/*
	삭제는 연결리스트의 Remove 구현과 똑같다.
	첫 번째 요소가 삭제대상이면 삭제, 아니면 LNext로 넘겨넘겨가며 삭제대상을 찾는다.
	*/
}

// 그래프에서 간선정보를 삭제하는 함수: ConKruskalMST Helper function
// 간선의 소멸
void RemoveEdge(ALGraph * pg, int fromV, int toV)
{
	RemoveWayEdge(pg, fromV, toV); //무방향 그래프라서 두 번 없애야 합니다. A에서 B로, B에서 A로
	RemoveWayEdge(pg, toV, fromV);
	(pg->numE)--;
}
/*
인접 리스트 기반 무방향 그래프인 관계로 하나의 간선을 완전히 소멸하기 위해서는 두 개의 간선 정보를 소멸시켜야 한다.
*/
 
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

void ShowGraphEdgeWeightInfo(ALGraph * pg)
{
	PQueue copyPQ = pg->pqueue;
	Edge edge;

	while(!PQIsEmpty(&copyPQ))
	{
		edge = PDequeue(&copyPQ);
		printf("(%c-%c), w:%d \n", edge.v1+65, edge.v2+65, edge.weight);
	}
}

int WhoIsPrecede(int data1, int data2)
{
	if(data1 < data2)
		return 0;
	else
		return 1;
}

int PQWeightComp(Edge d1, Edge d2)
{
	return d1.weight - d2.weight; //가중치 기준 내림차순으로 간선 정보 꺼내기 위함.
}

int VisitVertex(ALGraph * pg, int visitV)
{
	if(pg->visitInfo[visitV] == 0)
	{
		pg->visitInfo[visitV] = 1;
	//	printf("%c ", visitV + 65);
		return TRUE;
	}
	
	return FALSE;
}


void DFShowGraphVertex(ALGraph * pg, int startV)
{
	Stack stack;
	int visitV = startV;
	int nextV;

	StackInit(&stack);
	VisitVertex(pg, visitV);
	SPush(&stack, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE;

		if(VisitVertex(pg, nextV) == TRUE)
		{
			SPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else
		{
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
		
		if(visitFlag == FALSE)
		{
			if(SIsEmpty(&stack) == TRUE)
				break;
			else
				visitV = SPop(&stack);	
		}
	}

	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
}

// 두 정점이 연결되어있는지 확인하는 함수.
// 인자로 전달된 두 정점이 연결되어 있다면 TRUE, 아니라면 FALSE를 반환
// DFShowGraphVertex 함수와 99% 유사하다.
int IsConnVertex(ALGraph * pg, int v1, int v2)
{
	Stack stack;
	int visitV = v1; //시작점이 v1 정점
	int nextV;

	StackInit(&stack);
	VisitVertex(pg, visitV);
	SPush(&stack, visitV);

	while(LFirst(&(pg->adjList[visitV]), &nextV) == TRUE)
	{
		int visitFlag = FALSE;
		// 정점을 돌아다니는 와중에 목표값을 발견하면 TRUE를 반환한다.

		if(nextV == v2) //한방에 목표값을 찾았을 수도 있으니까
		{
			// 함수가 반환하기 전에 초기화를 진행한다.
			memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
			return TRUE; // 목표를 찾았으니 TRUE 반환.
		}

		if(VisitVertex(pg, nextV) == TRUE) //방문을 시도했는데 방문에 성공하면
		{
			SPush(&stack, visitV);
			visitV = nextV;
			visitFlag = TRUE;
		}
		else //이미 방문한 정점이라면
		{
			while(LNext(&(pg->adjList[visitV]), &nextV) == TRUE)
			{
				
				if(nextV == v2) //근데 그게 찾으려는 값이라면
				{
					memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
					return TRUE;
				}

				if(VisitVertex(pg, nextV) == TRUE) //또 못찾았으면 RE
				{
					SPush(&stack, visitV);
					visitV = nextV;
					visitFlag = TRUE;
					break;
				}
			}
		}
		
		if(visitFlag == FALSE)
		{
			if(SIsEmpty(&stack) == TRUE)
				break; //여기까지 했음 없는거지.
			else
				visitV = SPop(&stack);	//여긴 되돌아가는 쪽이고
		}
	}

	memset(pg->visitInfo, 0, sizeof(int) * pg->numV);
	return FALSE; // 여기까지 왔다면 정점을 못찾았다는 거니까 연결되지 않았음을 시사함.
}


// 크루스칼 알고리즘 기반의 MST 구성
void ConKruskalMST(ALGraph * pg)
{
	Edge recvEdge[20];    // 복원할 간선의 정보 저장
	Edge edge;
	int eidx = 0;
	int i;

	// MST를 형성할 때까지 아래의 while문 반복
	while(pg->numE+1 > pg->numV) // MST 간선의 수 + 1 == 정점의 수(최소비용신장트리가 되기 전까지 반복하겠단 얘기임.)
	{
		edge = PDequeue(&(pg->pqueue)); //가중치 순으로 간선 정보 획득(우선순위 큐에서 차례로 꺼내기만 하면 정렬된 상태일테니)
		RemoveEdge(pg, edge.v1, edge.v2); //획득한 정보의 간선 실제 삭제

		if(!IsConnVertex(pg, edge.v1, edge.v2)) //삭제 후 두 정점 연결 경로 있는지 확인
		{
			// 정점 연결이 안될 경우(정점이 독립되어버릴 경우)
			RecoverEdge(pg, edge.v1, edge.v2, edge.weight); //연결 경로 없으면 간선 복원
			recvEdge[eidx++] = edge; // 간선정보를 잠시 백업했다가, 아래에서 회복시킴.
		}
	}

	// 우선순위 큐에서 삭제된 간선의 정보를 회복
	for(i=0; i<eidx; i++)
		PEnqueue(&(pg->pqueue), recvEdge[i]);

}