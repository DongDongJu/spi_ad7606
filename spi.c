#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <stdio.h>
#include <stdlib.h>

#include "data_set.h"

#define BUSY 21
#define LED 22

#define CHANNEL 0

struct data_set ds[8];

void spi_ad7606(void) {
	unsigned char buf[2];
	
	short sum;
	int i;

	for (i = 0; i < 8; i++) {
		wiringPiSPIDataRW(CHANNEL, buf, 2);
		ds[i].push(&ds[i], COMB_BUF(buf));
	}

	// FOR DEBUG ONLY.
	if(ds[0].is_full) {
		for(i = 0; i < ds[0].size; i++)
			printf("%hd\n", ds[0].data[i]);

		exit(0);
	}
}

void busy_handler(void) {
	static int count = 0;
	static int state = 0;

	spi_ad7606();
	
	if((++count) == 128) {
		digitalWrite(LED, state);
		state = !state;

		count = 0;
	}
}

int main(void) {
	int i;

	for(i = 0; i < 8; i++)
		init_data_set(&ds[i]);

	wiringPiSPISetupMode(CHANNEL, 14000000, 2);

	wiringPiSetup();
	pinMode(BUSY, INPUT);
	pinMode(LED, OUTPUT);

	wiringPiISR(BUSY, INT_EDGE_RISING, &busy_handler);

	while(1);
}
