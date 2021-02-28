# External Interrupt (Dış Kesmeler)
- [Datasheet] - Atmega328p

Mikrodenetleyici de kesmeler işlemciyi  dışarıdan veya içeriden bir müdahale ile durdurup özel bir fonksiyonu yürüten yapılardır.

Atmega328P mikrodenetleyicisinde 2 adet dış kesme ve 23 adet ayak değişim kesmesi bulunuyor.Şimdi sıra ile bu kesmeleri kontrol eden kayıtçıları inceleyelim.

![](https://i.ibb.co/tYC84y6/2021-28-2-14-01-28.png)
![](https://i.ibb.co/z64KPWf/2021-28-2-14-01-35.png)
![](https://i.ibb.co/vmK4qBc/2021-28-2-14-01-41.png)

Eğer EICRA Kayıtçısının;
- ISC00 ve ISC01 bitleri "0" yazılır ise LOW level de kesme işlemi yapılır.
- ISC00 -> "1" ISC01 -> "0" yazılır ise herhangi bir değişiklikte kesme işlemi yapılır.
- ISC00 -> "0" ISC01 -> "1" yazılır ise düşen kenar kesmesi işlemi yapılır.
- ISC00 -> "1" ISC01 -> "1" yazılır ise yükselen kenarda kesme işlemi yapılır.


![](https://i.ibb.co/34snSW3/2021-28-2-14-01-48.png)

Eğer EIMSK Kayıtçısının;
- INT0 -> "1" yazılır ise INT0 kesmesi etkinleştirilir 
- INT1 -> "1" yazılır ise INT1 kesmesi etkinleştirilir 

![](https://i.ibb.co/FwCDmCm/UNOV3PDF.png)

PINOUT dan görüldüğü gibi PD2 INT0 ve PD3 INT1 kesme pinleri olarak gözüküyor.Şimdi PD2 Pinine ve PD3 Pinine buton bağlayarak harici kesme uygulaması gerçekleştirelim.

### ÖRNEKLER
### Örnek 1 (Karaşimşek Hızının Ayarlanması) (INT0 , INT1)
- Bu örnekte karaşimşek hızını PD2 deki buton ile arttırıcaz veya PD3 deki butona basdığımızda hızı azaltıcaz.
- Aynı zamanda B potunu ilk 4 bacağına ledler bağlıdır.
```sh
#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint32_t bekle;

void my_delay_ms(uint32_t n);

int main(void)
{
	bekle=100;//led geçiş hızı
	
	DDRD = 1<<PORTD2; // ,INT0 kesmesi için kullanılan PD2 ayağı giriş
	PORTD = 1<<PORTD2; //DAHİLİ PULL UP
	
	DDRD = 1<<PORTD3; // ,INT1 kesmesi için kullanılan PD2 ayağı giriş
	PORTD = 1<<PORTD3; //DAHİLİ PULL UP
	
	DDRB|=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3);//LEDLER ÇIKIŞ
	
	EICRA|=(1<<ISC01)|(1<<ISC11)|(1<<ISC10); //INT1 Yükselen kenarda INT0 düşen kenerda kesme işlemi yapar
	EIMSK|=(1<<INT0)|(1<<INT1);//Kesmeler etkin
	
	sei();//kesmeler etkin interrupt.h kütüphanesini kullanmak için
	
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
    }
}
ISR (INT0_vect)
{
	bekle=bekle-50;
}
ISR (INT1_vect)
{
	bekle=bekle+50;
}

void my_delay_ms(uint32_t n) {
	while(n--) {
		_delay_ms(1);
	}
}

```
Şimdi Kayıtçılarımıza devam edelim;

![](https://i.ibb.co/3yW2nhH/2021-28-2-15-38-00.png)
PCICR Kayıtçısını İnceleyelim;
- PCIE0 biti PCINT7..0 aralığındaki pinlerin ayak değişim kesmelerini etkinleştirir.
- PCIE1 biti PCINT14..8 aralığındaki pinlerin ayak değişim kesmelerini etkinleştirir.
- PCIE2 biti PCINT23..16 aralığındaki pinlerin ayak değişim kesmelerini etkinleştirir.

![](https://i.ibb.co/VQjSVC4/2021-28-2-15-38-13.png)
![](https://i.ibb.co/hFDL9xM/2021-28-2-15-38-18.png)
![](https://i.ibb.co/SR38k6F/2021-28-2-15-38-24.png)

Üste bulunan kayıtçılar ile pinlerin kesmesini bit bit etkinleştirebilirsiniz.

Şimdi PCINT13 ve PCINT21 ile Kara Şimşek ledlerinin hız ayarlarını yapalım.

### ÖRNEKLER
### Örnek 1 (Karaşimşek Hızının Ayarlanması) (PCINT23..0)
- PCINT23 pininde bulunan buton ile hızı arttırıcaz, PCINT21 deki buton ile hızı azaltıcaz.
- Yine B portunun ilk 4 bacağında ledler bulunmaktadır.
```sh
#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

uint32_t bekle;
void my_delay_ms(uint32_t n);
int main(void)
{
	bekle=100;
	sei();
	
	DDRB|=(1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3);//LEDLER ÇIKIŞ

	DDRD&=~(1<<PORTD5);
	PORTD|=(1<<PORTD5);
	DDRD&=~(1<<PORTD7);
	PORTD|=(1<<PORTD7);
	
	PCICR|=(1<<PCIE2);//23 ile 21 inci PCINT pinleri kullnıcaz ona uygun durum değişiklik kesmesini etkinleştirdik
	PCMSK2|= (1 << PCINT21)|(1<<PCINT23);

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
}
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
```


[Datasheet]: <https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf>