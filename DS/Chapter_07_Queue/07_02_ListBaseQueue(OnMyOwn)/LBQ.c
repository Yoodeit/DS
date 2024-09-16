#include <stdio.h>
#include <stdlib.h>
#include "LBQ.h"

void QueueInit(Queue * pq)
{
	pq->front = (Node*)malloc(sizeof(Node)); //front노드 생성
	pq->rear = (Node*)malloc(sizeof(Node)); //rear 노드 생성
	pq->front->next = NULL; // fornt 노드 초기화
	pq->rear->next = NULL; //rear 노드 초기화
	pq->numOfData = 0; //데이터 개수 0개
}

int QIsEmpty(Queue * pq)
{
	if(pq->numOfData == 0) //numOfData가 0이면 없는거지.
		return TRUE;
	else
		return FALSE;
}

void Enqueue(Queue * pq, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node)); // 노드 하나 생성
	newNode->data = data; // 새 노드에 데이터 담기
	newNode->next = NULL; //다음은 아직 없으니.
	
	if(QIsEmpty(pq)){
		pq->front->next = newNode; //front가 가리키는 노드가 이번 노드(첫입력)
		pq->rear->next = newNode; //rear가 가리키는 노드 역시 이번 노드(첫입력이니까)
	
		(pq->numOfData)++;	
	}
	
	else{ //첫 입력이 아니라면
		pq->rear->next->next = newNode; //현 rear에 있는 녀석과 새 노드를 연결
		pq->rear->next = newNode; //rear가 새로 추가한 노드를 가리키도록 함.
		(pq->numOfData)++; //데이터 추가되었음을 의미.
	}
	
}

Data Dequeue(Queue * pq)
{
	
	if(QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}
	
	Node * rpos = pq->front->next; //복사할 위치는 front가 가리키는 노드의 위치
	Data rdata = rpos->data; // 복사할 데이터는 그 노드가 담는 데이터
	
	pq->front->next = pq->front->next->next; //front 한 칸 옆으로 옮기기
	
	free(rpos);
	(pq->numOfData)--;
	return rdata;
}

Data QPeek(Queue * pq)
{
	if(QIsEmpty(pq))
	{
		printf("Queue Memory Error!");
		exit(-1);
	}
	
	return pq->front->next->data;
}


