#define  F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#define dir PB0
#define step PB1
void delay(uint16_t x) {
	for (int i = 0; i < x; i++) {
		_delay_us(1);
	}
	
}
void krok(uint8_t kroki, uint8_t direction, uint16_t czas) {
	if (direction == 1) {
		PORTB |= (1 << dir);
	}
	else if(direction == 0) {
		PORTB &= ~(1 << dir);
	}
	for (int i = 0; i < kroki; i++) {
		
		for (int x = 0; x < 200; x++) {
			PORTB |= (1 << step);
			delay(czas);
			PORTB &= ~(1 << step);
			delay(czas);
		}
	}
}
int main(void)
{
	DDRB |= (1 << dir);
	DDRB |= (1 << step);
	
	while (1)
	{
		krok(3, 1, 200);
		_delay_ms(200);
		krok(1, 0, 200);
		_delay_ms(200);
		
	}
}