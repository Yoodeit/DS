#ifndef __USEFUL_HEAP_H__
#define __USEFUL_HEAP_H__

#define TRUE	1
#define FALSE	0

/*** HeapÀÇ Á€ÀÇ ****/
#define HEAP_LEN	100

typedef char HData;

// d1ÀÇ ¿ìŒ±ŒøÀ§°¡ ³ôŽÙžé 0ºžŽÙ Å« °ª
// d2ÀÇ ¿ìŒ±ŒøÀ§°¡ ³ôŽÙžé 0ºžŽÙ ÀÛÀº °ª
// d1°ú d2ÀÇ ¿ìŒ±ŒøÀ§°¡ °°ŽÙžé 0À» ¹ÝÈ¯
typedef int PriorityComp(HData d1, HData d2);
// typedef int (* PriorityComp)(HData d1, HData d2) 이런 식으로 구현했다면 Heap 멤버에 *를 넣을 필요가 없었음. 선택임.

typedef struct _heap
{
	PriorityComp * comp;
	int numOfData;
	HData heapArr[HEAP_LEN];
} Heap;

/*** Heap °ü·Ã ¿¬»êµé ****/
void HeapInit(Heap * ph, PriorityComp pc);
int HIsEmpty(Heap * ph);

void HInsert(Heap * ph, HData data);
HData HDelete(Heap * ph);

#endif