
#define F_CPU 1000000UL //Szybkosc CPU dla biblioteki delay.h
#include <avr/io.h>
#include <util/delay.h>

void clock_init(void) {
	CLKPR = (1 <<CLKPCE); // Wlaczenie edytowania zegara
	CLKPR = (1 << CLKPS2); // wedlug noty to /16
}
int main(void)
{
	clock_init();
	DDRB |= (1<< PB0); //PB0 jako wyjscie
	
    while (1) 
    {
		PORTB |= (1<<PB0); // Stan wysoki
		_delay_ms(500);
		PORTB &= ~(1<<PB0);
		_delay_ms(500);
		
    }
}

