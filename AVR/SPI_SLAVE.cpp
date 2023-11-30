#include <avr/io.h>			
#include <util/delay.h>			
#include <stdio.h>			
#include <string.h>			

#define MOSI PB5
#define MISO PB6
#define SCK PB7
#define SS PB4

char SPI_Receive()			
{
	while(!(SPSR & (1<<SPIF)));	// Czekamy na koniec transmisji
	return(SPDR);			/* Return received data */
}

void SPI_Init()				
{
	DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));  
 						
	DDRB |= (1<<MISO);	//MISO JAKO WYJSCIE
	SPCR = (1<<SPE);	// SLAVE MODE
}

int main(void)
{
	uint8_t count;
	char buffer[5];
	SPI_Init();
	while (1)			
	{
		count = SPI_Receive(); //zwraca chara
		
	}

}