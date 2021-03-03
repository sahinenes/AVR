/*
 * USART.c
 *
 * Created: 3.03.2021 14:07:27
 * Author : Enes
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define BAUD 9600 // Baud Oranýný Tanýmlýyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlýyoruz

void uart_transmit (unsigned char data);
unsigned char veri_al();
void veri_gonder_uzun(char *data);

uint8_t sayi;
char str[50];
int main(void)
{
   
   UCSR0B |=(1<<TXEN0)|(1<<RXEN0);//TX ve RX aktif
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatýný ayarlýyoruz
   UBRR0= BAUDRATE; //Bant geniþilði ayarlandý
   
   DDRB=0x20;
   PORTB=0x00;
   
   sayi=200;
   
    while (1) 
    {
		if (veri_al()=='a')
		{
			PORTB=0x20;
		}
		else
		{
			PORTB=0x00;
			
		}
		
    }
}

// veri gönderme fonksiyonu
void veri_gonder (unsigned char data)
{
	while (!( UCSR0A & (1<<UDRE0))); // yazmacýn boþ olmasýný bekle
	UDR0 = data; // yazmaca veri yükle
}
unsigned char veri_al()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
void veri_gonder_uzun(char *data)
{
	
	while (*data!='\0')
	{
		while (!( UCSR0A & (1<<UDRE0))); 
		UDR0=*data++;
		
	}
}
