#ifndef __AL_GRAPH_BFS__
#define __AL_GRAPH_BFS__

// 연결 리스트를 가져다 쓴다.
#include "DLinkedList.h"

// 정점의 이름을 상수화.
enum {A, B, C, D, E, F, G, H, I, J};

typedef struct _ual
{
	int numV;   // 정점의 수(Number Vertex)
	int numE;   // 간선의 수(Number Edge)
	List * adjList;   // 간선의 정보
	int * visitInfo;	//탐색과정에서 탐색이 진행된 정점 정보를 담기 위한 멤버 추가.
} ALGraph;

//그래프의 초기화
void GraphInit(ALGraph * pg, int nv);

// 그래프의 리소스 해제
void GraphDestroy(ALGraph * pg);

// 간선의 추가
void AddEdge(ALGraph * pg, int fromV, int toV);

// 간선의 정보 출력
void ShowGraphEdgeInfo(ALGraph * pg);

// Breadth First Search: 정점의 정보 출력(BFS기반)
void BFShowGraphVertex(ALGraph * pg, int startV);

#endif