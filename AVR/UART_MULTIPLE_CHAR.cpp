#include <avr/io.h>
#include <inttypes.h>
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>
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
   USARTInit(51);    
   while(1)
   {
      char* hej = "Hello";
      USARTWriteChar(hej);
		_delay_ms(50);
   }
}
