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
	//Örnek 1 (ADC Hazýrlama ve Okuma)
	
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); 
	ADMUX |= (1<<REFS0); // Referans AVCC yani 5V
	ADCSRA |= (1<<ADEN); // ADC'yi Aç
	ADCSRA |= (1<<ADSC); // Ýlk deneme ölçümünü yap ve diðer ölçüme hazýr hale getir.
    //Örnek 1 (ADC Hazýrlama ve Okuma)


   DDRD=0xf0;
   
   
    while (1) 
    {
		//Örnek 1 (ADC Hazýrlama ve Okuma)
		//read_adc(0x00);//ADC0 oku
		//Örnek 1 (ADC Hazýrlama ve Okuma)
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


//Örnek 1 (ADC Hazýrlama ve Okuma)
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0; // Eski kanal bilgisini temizle
	ADMUX |= channel; // Yeni kanal bilgisini yükle
	ADCSRA |= (1<<ADSC); // Yeni Çevirim Baþlat
	while(ADCSRA & (1<<ADSC)); // Çevirim bitene kadar bekle (bu kýsým çok önemli)
	return ADCW; // ADC çevirim deðerini geri döndür.
}
//Örnek 1 (ADC Hazýrlama ve Okuma)