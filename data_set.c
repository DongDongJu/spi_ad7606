#include "data_set.h"

#include <stdio.h>
#include <stdlib.h>

void push(struct data_set *self, uint8_t data);
bool is_valid(struct data_set *self);

struct data_set *init_data_set(int size)
{
	// TODO : Exception Handler for when size is 0

	struct data_set *self = (struct data_set *) malloc(sizeof(struct data_set));

	self->data = (uint8_t *) malloc(sizeof(uint8_t) * size);
	self->ivds = (uint8_t *) calloc(1, sizeof(uint8_t) * ((size+7)/8));

	self->size = size;
	self->cs = -1;

	self->is_full = false;

	self->push = push;
	self->is_valid = is_valid;

	return self;
}

void push(struct data_set *self, uint8_t data)
{
	if ((++self->cs) >= self->size) {
		self->is_full = true;
		self->cs = 0;
	}

	self->data[self->cs] = data;

	{
		int gl = self->cs / 8;
		int ll = self->cs % 8;

		uint8_t invl = (data == 0 ? 0x80 : 0x00); // TODO : Modify the condition of invalid data

		self->ivds[gl] &= ~(0x80 >> ll);
		self->ivds[gl] |= invl >> ll;
	}
}

bool is_valid(struct data_set *self)
{
	int num = (self->size + 7)/8;
	int n;

	for (n = 0; n < num; n++) {
		if (self->ivds[n])
				return false;
	}

	return true;
}
