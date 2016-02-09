#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>

#define BUSY 5			// gpio pin number for read int
#define CHANNEL		0	// spi channel
#define SPI_SPEED   1000000	// spi speed
unsigned char buffer[1000];
//---------------------------------
// BusyHandler ( input void , output x )
// function for handling BusyPin
//---------------------------------
void BusyHandler(void) {
	// here spi

}
int main(void) {
	int spi_state;

	wiringPiSetup();					//	init

	pinMode(BUSY, INPUT);					//	pin setup

	spi_state = wiringPiSPISetup(CHANNEL, 500000);		//	spi init ( ce0 , clock )

	wiringPiISR(BUSY, INT_EDGE_BOTH, &BusyHandler);		//	INT SETUP ( INT_EDGE_FALLING , INT_EDGE_RISING )

	printf("spi state = %d",spi_state);

	
	while(1){}
}
