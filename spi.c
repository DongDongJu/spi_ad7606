#include <wiringPi.h>
#include <wiringPiSPI.h>

#include <stdio.h>
#include <stdlib.h>

#include "channel.h"

#define BUSY 21
#define LED 22
#define RESET 23

#define CS 0

struct channel ch[8];

void spi_ad7606(void) {
	unsigned char frag[2];
	
	short sum;
	int i;

	for (i = 0; i < 8; i++) {
		wiringPiSPIDataRW(CS, frag, 2);
		push_data(&ch[i], frag);
	}

// FOR DEBUG ONLY.
#if 1
	if(ch[0].is_full) {
		for(i = 0; i < DATA_SET_NUM; i++)
			printf("%hd\n", ch[0].data[i]);

		exit(0);
	}
#endif
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
		init_channel(&ch[i]);

	wiringPiSPISetupMode(CS, 14000000, 2);

	wiringPiSetup();
	pinMode(BUSY, INPUT);
	pinMode(LED, OUTPUT);

	wiringPiISR(BUSY, INT_EDGE_RISING, &busy_handler);

	while(1);
}
