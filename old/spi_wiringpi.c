#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>

#define BUSY 21			// gpio pin number for read int
#define CHANNEL		0	// spi channel
#define SPI_SPEED   1000000	// spi speed

//static variable
unsigned char data_buffer[8][3];
unsigned char saved_data_buffer[8][100000000];
int saved_data_buffer_cursor[8]={0,0,0,0,0,0,0,0};
clock_t start,end;

//functions
void SPI_ad7606();
void Save_buffer();
int Chk_time();
void Save_data2file();

//---------------------------------
// Save_data2file ( input void , output x )
// function for saving stacked data during 5 minutes.
//---------------------------------

void Save_data2file(){
	FILE* fp;
	int i=0;
	if((fp=fopen("data.txt","w")) == NULL){
		printf("failed data.txt open!");
		exit(1);
	}
	for(i=0;i<8;i++){
		fprintf(fp,"%d %s\n",i+1,saved_data_buffer[i]);
	}
	fclose(fp);
}

//---------------------------------
// Chk_time ( input void , output int )
// function for chk that if execution time more over than 5 minute.
//---------------------------------
int Chk_time(){
	if((double)(end - start)/CLOCKS_PER_SEC > 300)
	{
		start=clock();
		return 1;
	}
	else
		return 0;
}
//---------------------------------
// BusyHandler ( input void , output x )
// function for handling BusyPin.
//---------------------------------
void BusyHandler(void) {
	SPI_ad7606();
	Save_buffer();
}

//---------------------------------
// SPI_ad7606 ( input void , output x )
// function for spi communication with ad7606.
//---------------------------------
void SPI_ad7606(void){
	int i=0;
	int result;
	for(i=0;i<8;i++)
	{
		data_buffer[i][0] = 0x00;
		data_buffer[i][1] = i;
		result = wiringPiSPIDataRW(CHANNEL, data_buffer[i], 2);
		printf("result = %x %x channel %d \n",data_buffer[i][0],data_buffer[i][1],i+1);
	}
}

//---------------------------------
// Save_buffer ( input void , output x )
// fuction for save buffer
//---------------------------------

void Save_buffer(){
	int i=0;
	for(i=0;i<8;i++)
	{
		saved_data_buffer[i][saved_data_buffer_cursor[i]]=data_buffer[i][0];
		saved_data_buffer[i][saved_data_buffer_cursor[i]+1]=data_buffer[i][1];
		saved_data_buffer[i][saved_data_buffer_cursor[i]+2]='\0';
		saved_data_buffer_cursor[i]+=2;
	}
}

int main(void) {
	int spi_state;

	wiringPiSetup();					//	init

	pinMode(BUSY, INPUT);					//	pin setup

	spi_state = wiringPiSPISetupMode(CHANNEL, 14000000 , 2);		//	spi init ( ce0 , clock )

	wiringPiISR(BUSY, INT_EDGE_RISING, &BusyHandler);		//	INT SETUP ( INT_EDGE_FALLING , INT_EDGE_RISING )

	printf("spi state = %d",spi_state);
	start = clock();

	while(1){
		end=clock();
		if(Chk_time())
			Save_data2file();
	}
}
