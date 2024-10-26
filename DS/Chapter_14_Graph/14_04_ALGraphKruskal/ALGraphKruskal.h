#ifndef __AL_GRAPH_KRUSKAL__
#define __AL_GRAPH_KRUSKAL__

#include "DLinkedList.h"
#include "PriorityQueue.h"

#include "ALEdge.h"

// Á€Á¡ÀÇ ÀÌž§µéÀ» »óŒöÈ­
enum {A, B, C, D, E, F, G, H, I, J};

typedef struct _ual
{
	int numV;
	int numE;
	List * adjList;
	int * visitInfo;
	PQueue pqueue;    // °£Œ±ÀÇ °¡ÁßÄ¡ Á€ºž ÀúÀå
} ALGraph;

// ±×·¡ÇÁÀÇ ÃÊ±âÈ­
void GraphInit(ALGraph * pg, int nv);

// ±×·¡ÇÁÀÇ ž®ŒÒœº ÇØÁŠ
void GraphDestroy(ALGraph * pg);

// °£Œ±ÀÇ Ãß°¡
void AddEdge(ALGraph * pg, int fromV, int toV, int weight);

// °£Œ±ÀÇ Á€ºž Ãâ·Â
void ShowGraphEdgeInfo(ALGraph * pg);

// Depth First Search: Á€Á¡ÀÇ Á€ºž Ãâ·Â
void DFShowGraphVertex(ALGraph * pg, int startV);

// Å©·çœºÄ® ÃÖŒÒ ºñ¿ë œÅÀå Æ®ž®ÀÇ ±žŒº
void ConKruskalMST(ALGraph * pg);

// °£Œ±ÀÇ °¡ÁßÄ¡ Á€ºž Ãâ·Â
void ShowGraphEdgeWeightInfo(ALGraph * pg);

#endif