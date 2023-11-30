#define F_CPU 1000000UL
#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void USARTInit(uint16_t ubrr_value)
{
	UCSRA |= (1 << U2X);
	UBRRL = ubrr_value; //BAUD
	UBRRH = (ubrr_value>>8); //ILE BITOWY
	UCSRB= (1<<TXEN) | (1 <<RXEN) | (1 << RXCIE); //USTAWIAMY TYLKO NA ODBIOR
	UCSRC=(1<<URSEL)|(3<<UCSZ0); // BITY RAMKI
}
void USARTWriteChar(char data)
{
	while(!(UCSRA & (1<<UDRE)))
	{
		// CZEKAMY AZ BUFOR MAGISTRALI BEDZIE PUSTY
	}
	UDR=data; // WYSYLANIE DANYCH
}
unsigned char UART_RECEIVE() {
	while(!(UCSRA & (1 << RXC)));
	return UDR;
}
int main()
{
	DDRD |= (1 <<PIND7);
	DDRB |= (1 <<PINB0) | (1<< PINB1);
	PORTB |= (1<<PINB0) | (1 << PINB1);
	unsigned char data, status; // Inicjujemy zmienna
	USARTInit(51);    // ZE WZORU Z NOTY KATALOGOWEJ, np: (F_CPU/BAUD*16) -1
	sei();
	while(1)
	{
		PORTD &= ~(1 << PIND7);
		data= UART_RECEIVE();
		switch (data) {
			case 'h':
				status = 1;
				break;
			case 'k':
				status = 0;
				break;
			default:
				asm("nop");	
		}
		switch (status) {
			case 1:
				PORTB |= (1 << PINB0);
				PORTB &= ~(1 << PINB1);
				break;
			case 0:
				PORTB &= ~(1 << PINB0);
				PORTB |= (1 << PINB1);
				break;
			default:
				asm("nop");
		}
		USARTWriteChar(data);
	}
}
ISR(USART_RXC_vect) {
	PORTD |= (1 << PIND7);
	_delay_us(10);
	
}