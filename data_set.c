#include "data_set.h"

#include <stdio.h>
#include <stdlib.h>

void push(struct data_set *self, uint16_t data);
bool is_valid(struct data_set *self);

void init_data_set(struct data_set *self)
{
	self->size = DATA_NUM;
	self->cs = -1;

	self->is_full = false;

	self->push = push;
	self->is_valid = is_valid;
}

void push(struct data_set *self, uint16_t data)
{
	if ((++self->cs) >= self->size) {
		self->is_full = true;
		self->cs = 0;
	}

	self->data[self->cs] = data;

#if 0
	{
		int gl = self->cs / 8;
		int ll = self->cs % 8;

		uint8_t invl = (data == 0 ? 0x80 : 0x00);

		self->ivds[gl] &= ~(0x80 >> ll);
		self->ivds[gl] |= invl >> ll;
	}
#endif
}

bool is_valid(struct data_set *self)
{
	int num = (self->size+15)/16;
	int n;

	for (n = 0; n < num; n++) {
		if (self->ivds[n])
				return false;
	}

	return true;
}

