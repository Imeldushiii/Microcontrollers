#include <avr/io.h>
#include <inttypes.h>
#include <stdlib.h>

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <util/delay.h>

int main()
{
	int myNumber = 12345;
	char buffer[10];
	while(1)
	{
		itoa(myNumber, buffer, 10); //INT INTO STRING
	}
	
}
