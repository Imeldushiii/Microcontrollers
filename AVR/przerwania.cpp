		
#include <avr/io.h>			
#include <util/delay.h>		
#include <avr/interrupt.h>


ISR(INT0_vect) {
	PORTA |= (1 <<PA0);
	_delay_ms(250);
	PORTA &= ~(1 << PA0);
	_delay_ms(250);
}


int main() {
	MCUCR |= (1 << ISC00) | (1 << ISC01);
	GICR |= (1 << INT0); //JEZELI PODEPNIEMY INT0 do masy albo VCC to wylaczy siê ISR()
	//Gdy zamiast INT0 damy do INT1 to gdy pojawi sie VCC to wtedy wylaczy sie ISR()
	sei(); // inicjuje przerwania
	DDRA = 0xFF;
	while(1) {
		PORTA |= (1 <<PA1);
		_delay_ms(200);
		PORTA &= ~(1 << PA1);
		_delay_ms(200);
		PORTA |= (1 <<PA2);
		_delay_ms(200);
		PORTA &= ~(1 << PA2);
		_delay_ms(200);
		PORTA |= (1 <<PA3);
		_delay_ms(200);
		PORTA &= ~(1 << PA3);
		_delay_ms(200);
	}
	return 0;
}
