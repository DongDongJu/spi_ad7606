#include <stdbool.h>
#include <stdint.h>

#define SAMPLING_SEC 300
#define DATA_PER_SEC 128

#define DATA_NUM (SAMPLING_SEC * DATA_PER_SEC)

#define COMB_BUF(x) ((x[0] << 8) + x[1])

struct data_set {
	uint16_t data[DATA_NUM];
	uint16_t ivds[(DATA_NUM+15)/16];

	int size, cs;
	bool is_full;

	void (*push) (struct data_set *, uint16_t);
	bool (*is_valid) (struct data_set *);
};

void init_data_set(struct data_set *self);
