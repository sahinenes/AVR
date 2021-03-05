# EEPROM
Atmel® ATmega328P, 1Kbyte veri EEPROM belleği içerir. Tek baytların okunup yazılabildiği ayrı bir veri alanı olarak düzenlenmiştir. EEPROM'un en az 100.000 yazma dayanıklılığı vardır.


![](https://i.ibb.co/tC6rsw1/2021-05-3-19-19-07.png)
- EEPROM adresinin yazılacağı adresi tutan kayıtçı

![](https://i.ibb.co/1sC6zRs/2021-05-3-19-19-20.png)
- EEPROM a yazılacak verinin girildiği kayıtçı

![](https://i.ibb.co/4VLsH7z/2021-05-3-19-19-27.png)
- EERIE: EEPROM Hazır Kesmesini Etkinleştir
- EEMPE: EEPROM Ana Yazmayı Etkinleştir
- EEPE: EEPROM Yazmayı Etkinleştir
- EERE: EEPROM Okuma Etkinleştir

![](https://i.ibb.co/fqXQYhw/2021-05-3-19-19-37.png)

EEPROM'u yazmak (3. ve 4. adımların sırası gerekli değildir): 
1. EEPE sıfır olana kadar bekleyin.
2. SPMCSR'de SELFPRGEN sıfır olana kadar bekleyin. 
3. Yeni EEPROM adresini EEAR'a yazın (isteğe bağlı). 
4. Yeni EEPROM verilerini EEDR'ye yazın (isteğe bağlı).
5. EECR'de EEPE'ye sıfır yazarken EEMPE bitine mantıksal bir  yazın. 
6. EEMPE'yi ayarladıktan sonra dört saat döngüsü içinde, EEPE'ye mantıksal bir yazın

# Örnek
- EEPROM un "0x00" adresine 'a' karakteri yazılır.Daha sonra USART kullanılarak okunan veri seri ekrana gönderilir.
```sh
#define F_CPU 16000000
#define BAUD 9600 // Baud Oranını Tanımlıyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlıyoruz
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
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatını ayarlıyoruz
   UBRR0= BAUDRATE; //Bant genişilği ayarlandı
	
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
	while (!( UCSR0A & (1<<UDRE0))); // yazmacın boş olmasını bekle
	UDR0 = data; // yazmaca veri yükle
}
```