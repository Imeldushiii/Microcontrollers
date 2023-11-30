

#include <avr/io.h>
#include <inttypes.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>


void USARTInit(uint16_t ubrr_value)
{
   UBRRL = ubrr_value; //BAUD
   UBRRH = (ubrr_value>>8); //ILE BITOWY
   UCSRC=(1<<URSEL)|(3<<UCSZ0); // BITY RAMKI 
   UCSRB=(1<<TXEN); //USTAWIAMY TYLKO NA ODBIOR
}
void USARTWriteChar(char data)
{
   while(!(UCSRA & (1<<UDRE)))
   {
      // CZEKAMY AZ BUFOR MAGISTRALI BEDZIE PUSTY
   }
   
   UDR=data; // WYSYLANIE DANYCH
}

int main()
{
   char data; // Inicjujemy zmienna
   USARTInit(51);    // ZE WZORU Z NOTY KATALOGOWEJ, np: (F_CPU/BAUD*16) -1
   while(1)
   {
      data= 'H';
      USARTWriteChar(data);
		_delay_ms(50);
   }
   
}
