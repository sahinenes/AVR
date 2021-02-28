/*
 * External Interrupt.c
 *
 * Created: 28.02.2021 15:01:51
 * Author : Enes
 */ 

#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
volatile uint8_t portbhistory = 0xFF; 
uint32_t bekle;

void my_delay_ms(uint32_t n);

int main(void)
{
	bekle=100;
	
	
	sei();
	
	DDRB|=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3);//LEDLER �IKI�
	
	DDRD&=~(1<<PORTD5);
	PORTD|=(1<<PORTD5);
	DDRD&=~(1<<PORTD7);
	PORTD|=(1<<PORTD7);
	
	
	PCICR|=(1<<PCIE2);//23 ile 21 inci PCINT pinleri kulln�caz ona uygun durum de�i�iklik kesmesini etkinle�tirdik
	PCMSK2|= (1 << PCINT21)|(1<<PCINT23);
	/*
	//�rnek 1 (Kara�im�ek H�z�n�n Ayarlanmas�)
	
	bekle=100;//led ge�i� h�z�
	
	DDRD = 1<<PORTD2; // ,INT0 kesmesi i�in kullan�lan PD2 aya�� giri�
	PORTD = 1<<PORTD2; //DAH�L� PULL UP
	
	DDRD = 1<<PORTD3; // ,INT1 kesmesi i�in kullan�lan PD2 aya�� giri�
	PORTD = 1<<PORTD3; //DAH�L� PULL UP
	
	DDRB|=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3);//LEDLER �IKI�
	
	EICRA|=(1<<ISC01)|(1<<ISC11)|(1<<ISC10); //INT1 Y�kselen kenarda INT0 d��en kenerda kesme i�lemi yapar
	EIMSK|=(1<<INT0)|(1<<INT1);//Kesmeler etkin
	
	sei();//kesmeler etkin interrupt.h k�t�phanesini kullanmak i�in
	
	//�rnek 1 (Kara�im�ek H�z�n�n Ayarlanmas�)
   
   */
    while (1) 
    {
		
		
		
			for(uint16_t i=0x01;i<=0x08;i=i*2)
			{
				PORTB=i;
				my_delay_ms(bekle);
				
			}
			for(uint16_t i=0x08;i>=0x01;i=i/2)
			{    PORTB=i;
				my_delay_ms(bekle);
				
			}
		
		
		
		
		
		
		/*
		//�rnek 1 (Kara�im�ek H�z�n�n Ayarlanmas�)
		for(uint16_t i=0x01;i<=0x08;i=i*2)
		{
			PORTB=i;
			my_delay_ms(bekle);
		
		}
		for(uint16_t i=0x08;i>=0x01;i=i/2)
		{    PORTB=i;
			my_delay_ms(bekle);
			
		}
		//�rnek 1 (Kara�im�ek H�z�n�n Ayarlanmas�)
		*/
    }
}

/*
//	//�rnek 1 (Kara�im�ek H�z�n�n Ayarlanmas�)

ISR (INT0_vect)
{
	bekle=bekle-50;
}
ISR (INT1_vect)
{
	bekle=bekle+50;
}

//�rnek 1 (Kara�im�ek H�z�n�n Ayarlanmas�)

*/

ISR (PCINT2_vect)
{


	if(PIND &  (1 << PIND5))
	{
		bekle=bekle+50;
	}

	if(PIND & (1 << PIND7))
	{
		bekle=bekle-50;
	}



}

void my_delay_ms(uint32_t n) {
	while(n--) {
		_delay_ms(1);
	}
}