#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>			
#include <string.h>
#define MOSI PB5
#define MISO PB6
#define SCK PB7
#define SS PB4
void SPI_Init()					// SPI inicjalizacja
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	
						
	PORTB |= (1<<SS);			/* PIN HIGH aby wybrac slave */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	/* SPI Fosc16  sterujemy przez SPR0, SPR1, SPI2X czytamy z dokumentacji*/
		
}
char SPI_Read()				
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Czekamy az dane sie ogarna */
	return(SPDR);			
}
void SPI_MasterSendByte(uint8_t data) {
	// Dajac stan niski na SS, informujemy ze juz mozna przesylac dane.
	PORTB &= ~(1 << SS);
	
	// wysylamy dane
	SPDR = data;
	
	// Czekamy az przesyl sie zakonczy
	while (!(SPSR & (1 << SPIF)));
	
	// Dajemy na stan wysoki pin SS przez co wylaczamy przesyl
	PORTB |= (1 << SS);
}
int main(void)
{
	SPI_Init();
    // Dane do podstawienia
	//0xAA to 170 w decimalnym
	uint8_t dataToSend = 0xAA;
    while (1) 
    {
		SPI_MasterSendByte(dataToSend);
		
		// Zwiekszaj o 1 zmienna
		dataToSend++;
		
		_delay_ms(500);
    }
}

