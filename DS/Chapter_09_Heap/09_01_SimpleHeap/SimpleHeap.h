#ifndef __SIMPLE_HEAP_H__
#define __SIMPLE_HEAP_H__

#define TRUE	1
#define FALSE	0

#define HEAP_LEN	100

typedef char HData;
typedef int Priority;

typedef struct _heapElem
{
	Priority pr;	//우선도
	HData data; //데이터
} HeapElem;

typedef struct _heap
{
	int numOfData; //데이터개수
	HeapElem heapArr[HEAP_LEN ]; //힙이 될 배열 만들기. 요소 하나하나는 HeapElem
} Heap;


void HeapInit(Heap * ph);
int HIsEmpty(Heap * ph);

void HInsert(Heap * ph, HData data, Priority pr);
HData HDelete(Heap * ph);

#endif