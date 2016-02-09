#include <stdio.h>
#include <sys/time.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#define BUSY 5			// gpio pin number for read int
#define CHANNEL		0	// spi channel
#define SPI_SPEED   1000000	// spi speed
unsigned char data_buffer[8][3];
void SPI_ad7606();

//---------------------------------
// BusyHandler ( input void , output x )
// function for handling BusyPin
//---------------------------------
void BusyHandler(void) {
	// here spi
	SPI_ad7606();
}

//---------------------------------
// SPI_ad7606 ( input void , output x )
// function for spi communication with ad7606
//---------------------------------
void SPI_ad7606(void){
	int i=0;
	int result;
	for(i=0;i<8;i++)
	{
		data_buffer[i][0] = 0x00;
		data_buffer[i][1] = i;
		result = wiringPiSPIDataRW(CHANNEL, data_buffer[i], 2);
		printf("result = %d channel %d \n",result,i+1);
	}
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
