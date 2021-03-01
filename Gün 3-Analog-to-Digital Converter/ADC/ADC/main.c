/*
 * ADC.c
 *
 * Created: 1.03.2021 18:18:03
 * Author : Enes
 */ 

#include <avr/io.h>
uint16_t read_adc(uint8_t channel);

int main(void)
{
	//�rnek 1 (ADC Haz�rlama ve Okuma)
	
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); 
	ADMUX |= (1<<REFS0); // Referans AVCC yani 5V
	ADCSRA |= (1<<ADEN); // ADC'yi A�
	ADCSRA |= (1<<ADSC); // �lk deneme �l��m�n� yap ve di�er �l��me haz�r hale getir.
    //�rnek 1 (ADC Haz�rlama ve Okuma)


   DDRD=0xf0;
   
   
    while (1) 
    {
		//�rnek 1 (ADC Haz�rlama ve Okuma)
		//read_adc(0x00);//ADC0 oku
		//�rnek 1 (ADC Haz�rlama ve Okuma)
		if (read_adc(0x02)>=250)
		{
			PORTD=0xf0;
		}
		else
		{
			PORTD=0x00;
		}
		
		
    }
}


//�rnek 1 (ADC Haz�rlama ve Okuma)
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0; // Eski kanal bilgisini temizle
	ADMUX |= channel; // Yeni kanal bilgisini y�kle
	ADCSRA |= (1<<ADSC); // Yeni �evirim Ba�lat
	while(ADCSRA & (1<<ADSC)); // �evirim bitene kadar bekle (bu k�s�m �ok �nemli)
	return ADCW; // ADC �evirim de�erini geri d�nd�r.
}
//�rnek 1 (ADC Haz�rlama ve Okuma)