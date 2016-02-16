#include <stdint.h>

#define DATA_PER_SEC 128
#define SAMPLING_SEC 5

#define DATA_SET_SIZE (DATA_PER_SEC * SAMPLING_SEC)

struct data_set {
	uint16_t data[DATA_SET_SIZE];
	int cs;
}

int assess_data_set(struct data_set *ds);

#define DATA_SET_NUM 60
#define EXTRA_DS_NUM 4

#define CHANNEL_SIZE (DATA_SET_NUM + EXTRA_DS_NUM)

struct channel {
	struct data_set ds[CHANNEL_SIZE];
	uint16_t assm[(CHANNEL_SIZE+15)/16];
	int cs;
	int is_full;
};

void init_channel(struct channel *ch);
void push_data(struct channel *ch, unsigned char *frag);
int assess_channel(struct channel *ch);
