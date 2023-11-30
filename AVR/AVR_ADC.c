#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>
#ifndef F_CPU
#define F_CPU 1000000UL
#endif
#include <util/delay.h>
void ADC_INIT() {
	DDRA = 0x0; //Zainicjowanie PORTU A NA PINIE 0
	//REJESTRY ADCSRA
	ADCSRA |= (1<< ADEN);
	ADCSRA |= (1 << ADSC);
	ADCSRA &= ~(1<< ADATE);
	ADCSRA &= ~(1 << ADIF);
	ADCSRA &= ~(1 << ADIE); //Wlaczanie przerwan
	ADCSRA |= (1 << ADPS2);
	ADCSRA |= (1 << ADPS1);
	ADCSRA |= (1 << ADPS0);
	//REJESTRY ADMUX
	//ADMUX = 0x40;
	ADMUX &= ~(1 << REFS1);
	ADMUX |= (1 << REFS0);
	ADMUX &= ~(1 << ADLAR);
	ADMUX &= ~(1 << MUX4);
	ADMUX &= ~(1 << MUX3);
	ADMUX &= ~(1 << MUX2);
	ADMUX &= ~(1 << MUX1);
	ADMUX &= ~(1 << MUX0);
	
}
int ADC_READ(char channel) {
	int ain, ainlow;
	ADMUX=ADMUX|(channel & 0x0f);
	ADCSRA |= (1 << ADSC);
	while((ADCSRA&(1 <<ADIF)) == 0); // Czekamy az buffer sie zwolni
	_delay_us(10);
	ainlow = (int)ADCL;
	ain = (int)ADCH*256;
	ain = ain + ainlow;
	return(ain);
}
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
	char send[5];
	
	int wartosc;
	ADC_INIT();
	USARTInit(51);
	while(1)
	{
		wartosc = ADC_READ(0);
		itoa(wartosc, send, 10);
		
		
		USARTWriteChar(send);
		USARTWriteChar("\n");
		_delay_ms(10);
	}
}