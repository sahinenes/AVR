/*
 * EEPROM.c
 *
 * Created: 5.03.2021 19:43:14
 * Author : Enes
 */ 
#define F_CPU 16000000
#define BAUD 9600 // Baud Oranýný Tanýmlýyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlýyoruz
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

void EEPROM_yaz(unsigned int adress, unsigned char data);
unsigned char EEPROM_oku(unsigned int adress);
void veri_gonder(unsigned char data);


char str[50];

int main(void)
{
	
   UCSR0B |=(1<<TXEN0)|(1<<RXEN0);//TX ve RX aktif
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatýný ayarlýyoruz
   UBRR0= BAUDRATE; //Bant geniþilði ayarlandý
	
   // EEPROM_yaz(0x00,'a');
	
	
    while (1) 
    {
		
	veri_gonder(EEPROM_oku(0x00));
	_delay_ms(1000);
    }
}

void EEPROM_yaz(unsigned int adress, unsigned char data)
{
	while(EECR & (1<<EEPE));
	
	EEAR = adress;
	EEDR = data;
	
	EECR |= (1<<EEMPE);
	
	EECR |= (1<<EEPE);
}
unsigned char EEPROM_oku(unsigned int adress)
{
	
	while(EECR & (1<<EEPE));

	EEAR = adress;

	EECR |= (1<<EERE);
	
	return EEDR;
}
void veri_gonder (unsigned char data)
{
	while (!( UCSR0A & (1<<UDRE0))); // yazmacýn boþ olmasýný bekle
	UDR0 = data; // yazmaca veri yükle
}