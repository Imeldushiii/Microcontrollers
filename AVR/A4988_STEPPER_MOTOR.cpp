#define  F_CPU 1000000UL
#include <util/delay.h>
#include <avr/io.h>
#define dir PB0
#define step PB1

int main(void)
{
    DDRB |= (1 << dir);
	DDRB |= (1 << step);
    while (1) 
    {
		PORTB |= (1 << dir);
		for (uint8_t x=0; x < 200; x++) { //UINT8_T bo w forze jest 200 a w uincie8_t maxymalna wartosc to 255, wiec lepsze
			PORTB |= (1 << step);
			_delay_us(500);
			PORTB &= ~(1 << step);
			_delay_us(500);
		}
		_delay_ms(500);
		PORTB &= ~(1 << dir);
		for (uint8_t y = 0; y < 200; y++ ){
			PORTB |= (1 << step);
			_delay_us(500);
			PORTB &= ~(1 << step);
			_delay_us(500);
		}
		_delay_ms(500);
		
    }
}

