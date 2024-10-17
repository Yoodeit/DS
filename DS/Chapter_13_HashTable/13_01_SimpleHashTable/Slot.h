#ifndef __SLOT_H__
#define __SLOT_H__

#include "Person.h"

typedef int Key;
typedef Person * Value;

enum SlotStatus {EMPTY, DELETED, INUSE};

typedef struct _slot
{
	Key key;
	Value val;
	enum SlotStatus status;
}Slot;

// Slot°ú °ü·ÃÇØŒ­ŽÂ º°µµÀÇ ÇÔŒöžŠ Á€ÀÇÇÏÁö ŸÊŽÂŽÙ.
#endif