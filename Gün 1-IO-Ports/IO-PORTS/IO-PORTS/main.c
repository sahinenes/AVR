/*
 * IO-PORTS.c
 *
 * Created: 26.02.2021 14:26:24
 * Author : Enes
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>


int main(void)

{
	/*
	
	//Örnek 1 (Sürekli Yanan Led)
	
	DDRD |=(1<<2);  //PORT ÇIKIÞ OLARAK AYARLANDI
	PORTD |=(1<<2); //PORTA ÇIKIÞ VERÝLDÝ
	
    //Örnek 1 (Sürekli Yanan Led)
	
  */
  
  	/*
	
	//Örnek 2 (Yanýp Sönen Led)
	
	DDRB |=(1<<1);  //PORT ÇIKIÞ OLARAK AYARLANDI
	
    //Örnek 2 (Yanýp Sönen Led)
	
	*/
	  
	  /*
  	//Örnek 3 (Bit Seviyesinde) (Kara Þimþek) 
	  
     DDRD|=(1<<PORTD0)|(1<<PORTD1)|(1<<PORTD2)|(1<<PORTD3);
	 
    //Örnek 3 (Bit Seviyesinde) (Kara Þimþek) 
     */
	  
	  //Örnek 4 (Buton ile Led Kontrolü)
	  
	  DDRD|=(1<<PORTD2);//ÇIKIÞ
	  DDRB&=~(1<<PORTB2);//GÝRÝÞ
	  PORTB|=(1<<PORTB2);//DAHÝLÝ PULL UP
	  MCUCR|=(1<<PUD);
	  
	  //Örnek 4 (Buton ile Led Kontrolü)
	  
    while (1) 
    {
		/*
		//Örnek 2 (Yanýp Sönen Led)
		
		PORTB|=(1<<1);
		_delay_ms(500);
		PORTB&=~(1<<1);
		_delay_ms(500);
		
		//Örnek 2 (Yanýp Sönen Led)
		*/
		
		/*
		
		//Örnek 3 (Bit Seviyesinde) (Kara Þimþek)
		for(uint16_t i=0x01;i<=0x08;i=i*2)
		{
			PORTD=i;
			_delay_ms(100);
		}
		for(uint16_t i=0x08;i>=0x01;i=i/2)
		{    PORTD=i;
			_delay_ms(100);
			
		}
		*/
		
		//Örnek 3 (Bit Seviyesinde) (Kara Þimþek)
		
		
		//Örnek 4 (Buton ile Led Kontrolü)
		
		if ((PINB & (1<<PINB2)))
		{
			PORTD|=(1<<PORTD2);
		} 
		else
		{
			PORTD&=~(1<<PORTD2);
		}
		
		//Örnek 4 (Buton ile Led Kontrolü)
		
    }
}

