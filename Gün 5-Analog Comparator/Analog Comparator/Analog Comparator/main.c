/*
 * Analog Comparator.c
 *
 * Created: 5.03.2021 16:41:12
 * Author : Enes
 */ 

#include <avr/io.h>


int main(void)
{
    DDRB|=(1<<PORTB0);
	ADCSRB|=(1<<ACME);
	
    while (1) 
    {
		if (ACSR & (1<<ACO))
		PORTB = 0x01;
		else		
		PORTB = 0x00;	
    }
}

