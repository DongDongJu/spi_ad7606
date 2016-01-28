#include <bcm2835.h>
#include <stdio.h>

int main(int argc,char **argv)
{
	char data_buffer[8];
	int i;
	if(!bcm2835_init())
	{
		printf("init failed!");
		return 1;
	}
	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16);
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0,LOW);
	for(i=0;i<8;i++)
		data_buffer[i] = 0x00 + i;
	bcm2835_spi_transfern(&data_buffer[0],8);
	for(i=0;i<8;i++)
		printf("0x%02X\n",data_buffer[i]);
	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}
