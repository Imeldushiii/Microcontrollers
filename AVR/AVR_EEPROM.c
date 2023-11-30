#include <avr/io.h>
#include <avr/eeprom.h>
#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <util/delay.h>

#define BYTE_ADDR 0x1

void USARTInit(uint16_t ubrr_value)
{
	UBRRL = ubrr_value;
	UBRRH = (ubrr_value>>8);
	UCSRC=(1<<URSEL)|(3<<UCSZ0);
	UCSRB=(1<<TXEN);
}
void UART_TransmitChar(uint8_t data)
{
	while (!(UCSRA & (1 << UDRE)))
	{
	}
	UDR = data;
}
void USARTWriteChar(const char* data)
{
	while (*data != '\0') {
		UART_TransmitChar(*data);
		data++;
	}
}

int main()
{
	//eeprom_write_byte((uint8_t*)BYTE_ADDR, 6);
	//eeprom_write_byte((uint8_t*)3, 9);
	eeprom_write_word((uint16_t*)(0x04), 0x1234);
	//eeprom_write_dword((uint32_t*)0x09, 0x12345678);
	eeprom_update_word((uint16_t*)(0x04), 0x4567);
	
	USARTInit(51);
	while(1)
	{
		char bufon[50];
		uint8_t ee;
		
		
		
		
		
		
		
		for (uint8_t x =0; x < 20; x++) {
			ee = eeprom_read_byte((uint16_t*)x);
			sprintf(bufon, "EEPROM adres: %d wartosc: %d\n",x, ee);
			USARTWriteChar(bufon);
			
		}
		_delay_ms(50);
	}
}