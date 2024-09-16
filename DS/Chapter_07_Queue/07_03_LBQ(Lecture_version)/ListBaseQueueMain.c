#include <stdio.h>
#include "ListBaseQueue.h"

int main(void)
{
	// QueueÀÇ »ýŒº ¹× ÃÊ±âÈ­ ///////
	Queue q;
	QueueInit(&q);

	// µ¥ÀÌÅÍ ³Ö±â ///////
	Enqueue(&q, 1);  Enqueue(&q, 2);
	Enqueue(&q, 3);  Enqueue(&q, 4);
	Enqueue(&q, 5);

	// µ¥ÀÌÅÍ ²š³»±â ///////
	while(!QIsEmpty(&q))
		printf("%d ", Dequeue(&q)); 

	return 0;
}