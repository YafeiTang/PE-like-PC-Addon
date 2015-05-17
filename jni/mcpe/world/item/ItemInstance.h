#pragma once
#include "Item.h"

class ItemInstance {
public:
	short count;
	short damage;
	void* item;
	char filler[12];

	void _setItem(int);
	ItemInstance(int, int, int);
	ItemInstance(Item*);
};
