#include "channel.h"

#include <stdio.h>
#include <stdlib.h>

#define COMBINE_FRAGS(x) ((x[0] << 8) | x[1])

void init_channel(struct channel *ch)
{
	int i;

	for(i = 0; i < CHANNEL_SIZE; i++) {
		ch->ds[i].cs = 0;
	}

	ch->cs = 0;
	ch->is_full = false;
}

void push_data(struct channel *ch, unsigned char *frag)
{
	struct data_set *ds = ch->ds[ch->cs];

	ds->data[ds->cs] = COMBINE_FRAGS(frag);

	// move cursor forward.
	if((++ds->cs) >= DATA_SET_SIZE) {
		ch->cs = (ch->cs+1)%CHANNEL_SIZE;
		ds->cs = 0;

		if(ch->cs >= DATA_SET_NUM) {
			ch->is_full = 1;
		}

		// TODO : assess data set with another thread.
	}
}

int assess_channel(struct channel *ch)
{
	// TODO : assess whole channel EXCEPT extra data sets.
}

int assess_data_set(struct data_set *ds)
{
	// TODO : translate 'ChannelAssessment.m' into C code.
}



// Ignore this code snippet below!!! (saving old code, just in case.)

#if 0
	{
		int gl = ch->cs / 8;
		int ll = ch->cs % 8;

		uint8_t invl = (data == 0 ? 0x80 : 0x00);

		ch->ivdsgl] &= ~(0x80 >> ll);
		ch->ivds[gl] |= invl >> ll;
	}
#endif
