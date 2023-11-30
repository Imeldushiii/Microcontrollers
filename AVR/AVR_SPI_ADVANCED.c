#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#define MOSI PB5
#define MISO PB6
#define SCK PB7
#define SS PB4
void SPI_Init(void)					// SPI inicjalizacja
{
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);
	
	PORTB |= (1<<SS);			/* PIN HIGH aby wybrac slave */
	// REJESTRY SPCR
	SPCR |= (1<< SPIE); // WLACZENIE PRZERWAN
	SPCR |= (1 << SPE); // WLACZENIE SPI
	SPCR &= ~(1 << DORD); // Zmienia bit kolejnosci
	SPCR |= (1 << MSTR); // 1 - Master, 0 - Slave
	SPCR &= ~(1 << CPOL); // Polaryzacja clocka, 1 - od jedynki, 0 - od zera
	SPCR &= ~(1 << CPHA);
	SPCR &= ~(1 << SPR1); // dzielnik czestotliwosci
	SPCR |= (1 << SPR0); // dzielnik czestotliwosci, nalezy zajrzec do noty katalogowej
	// REJESTRY SPSR
	//SPSR &= (1 << SPIF);
	//SPCR &= (1 << WCOL);
	//SPCR &= (1 << SPI2X); //1 - Podwaja szybkosc, 0 - nic
}
char SPI_Read(void)
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
	uint8_t dataToSend = 1;
	
	while (1)
	{
		SPI_MasterSendByte(dataToSend);
		
		// Zwiekszaj o 1 zmienna
		dataToSend++;
		
		_delay_ms(20);
	}
}