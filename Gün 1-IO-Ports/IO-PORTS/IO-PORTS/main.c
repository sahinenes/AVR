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
	
	//�rnek 1 (S�rekli Yanan Led)
	
	DDRD |=(1<<2);  //PORT �IKI� OLARAK AYARLANDI
	PORTD |=(1<<2); //PORTA �IKI� VER�LD�
	
    //�rnek 1 (S�rekli Yanan Led)
	
  */
  
  	/*
	
	//�rnek 2 (Yan�p S�nen Led)
	
	DDRB |=(1<<1);  //PORT �IKI� OLARAK AYARLANDI
	
    //�rnek 2 (Yan�p S�nen Led)
	
	*/
	  
	  /*
  	//�rnek 3 (Bit Seviyesinde) (Kara �im�ek) 
	  
     DDRD|=(1<<PORTD0)|(1<<PORTD1)|(1<<PORTD2)|(1<<PORTD3);
	 
    //�rnek 3 (Bit Seviyesinde) (Kara �im�ek) 
     */
	  
	  //�rnek 4 (Buton ile Led Kontrol�)
	  
	  DDRD|=(1<<PORTD2);//�IKI�
	  DDRB&=~(1<<PORTB2);//G�R��
	  PORTB|=(1<<PORTB2);//DAH�L� PULL UP
	  MCUCR|=(1<<PUD);
	  
	  //�rnek 4 (Buton ile Led Kontrol�)
	  
    while (1) 
    {
		/*
		//�rnek 2 (Yan�p S�nen Led)
		
		PORTB|=(1<<1);
		_delay_ms(500);
		PORTB&=~(1<<1);
		_delay_ms(500);
		
		//�rnek 2 (Yan�p S�nen Led)
		*/
		
		/*
		
		//�rnek 3 (Bit Seviyesinde) (Kara �im�ek)
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
		
		//�rnek 3 (Bit Seviyesinde) (Kara �im�ek)
		
		
		//�rnek 4 (Buton ile Led Kontrol�)
		
		if ((PINB & (1<<PINB2)))
		{
			PORTD|=(1<<PORTD2);
		} 
		else
		{
			PORTD&=~(1<<PORTD2);
		}
		
		//�rnek 4 (Buton ile Led Kontrol�)
		
    }
}

