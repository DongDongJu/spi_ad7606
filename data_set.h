#include <stdbool.h>

struct data_set {
	uint8_t *data, *ivds;

	int size, cs;
	bool is_full;

	void (*push) (struct data_set *, uint8_t);
	bool (*is_valid) (struct data_set *);
}

struct data_set *init_data_set(int size);
