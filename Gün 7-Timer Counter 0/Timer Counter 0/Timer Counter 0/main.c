/*
 * Timer Counter 0.c
 *
 * Created: 11.03.2021 15:45:52
 * Author : Enes
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	/*
    // Normal Mod
	TCCR0B|=(1<<CS00)|(1<<CS02);//  (CLCK/1024)
	TIMSK0|=(1<<TOIE0);
	TCNT0=0x00; 
	DDRD|=(1<<PORTD2);
	//
	*/

	//CTC Mod
	
	
	OCR0A =250;
	TCCR0A|=(1<<WGM01)|(1<<COM0A0);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	//TIMSK0 |= (1 << OCIE0A);
	DDRD|=(1<<PORTD6);
	
	sei();
	
    while (1) 
    {
		
    }
}



ISR (TIMER0_OVF_vect)
{
	//PORTD^=(1<<PORTD2);
}
ISR(TIMER0_COMPA_vect)
{
	
	//PORTD^=(1<<PORTD2);
}
