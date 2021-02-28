# AVR Notlarım

## İsterseniz alt klöserdeki .md uzantılı dosyayı kullanabilirsiniz

# IO-PORTS
- [Datasheet] - Atmega328p
## Giriş - Çıkış ?

//

![1](https://i.ibb.co/7GSWgpw/2021-26-2-14-29-36.png)

• DDRx yazmacındaki porta ait ayak sıfır yapılır ve port yazmacındaki aynı bit de sıfır
yapılırsa giriş ve çıkış fonksiyonu giriş olur ve tri-state olarak kalır. (Ayak boşta iken bu
durum geçerlidir.)
• DDRx yazmacındaki porta ait ayak sıfır yapılır ve port yazmacındaki aynı bit de bir yapılırsa
ve PUD biti sıfır konumunda yani pull-up dirençleri devre dışı bırakılmamışsa o ayak dahili
pull-up özelliği gösterir.
• DDRx yazmacındaki porta ait ayak sıfır yapılır ve port yazmacındaki aynı ayağa karşılık
gelen bit de bir yapılır ama MCUCR yazmacındaki PUD biti 1 yapılırsa o ayak tri-state
konumunda olur. Yani pull-up olmadan giriş konumunda olur.
• DDRx yazmacındaki porta ait ayak bir yapılır ve port yazmacındaki aynı ayağa karşılık
gelen bit de sıfır yapılırsa o ayaktan dijital 0 (sıfır) çıkışı sağlanır.
• DDRx yazmacındaki porta ait ayak bir yapılır ve port yazmacındaki aynı ayağa karşılık
gelen bit de bir yapılırsa o ayaktan dijital 1 (bir) çıkışı sağlanır.

**üste bulunan yazı [lojikprob] - kitabının 33. sayfasından alınmıştır.

![2](https://microcontrollerslab.com/wp-content/uploads/2019/12/ATMEGA328P-Pin-Configuration-Diagram.png)

#### [pinout] resim link

## İşlem Basamakları
- DDRx ile hangi bitin giriş veya çıkış olarak tanımlamamıza olanak sağlar.
- Eğer bite "1" yazılırsa çıkış "0" yazılırsa giriş olarak tanımlanmış olur.
- Herhangi bir biti çıkış olarak tanımlayacağımızı varsayalım yani DDRx in herhangi bir bitine "1" yazıcaz. Bu işlemi yaptıktan sonra PORTx ile bu biti "low" (çıkış yok ,portta akım yok) veya "high" (çıkış var , portta akım var) yapılabilir.
- Eğer herhangi bir portun herhangi bir portunu giriş yapmak istersek DDRx in çıkış yapmak istediğimiz bitine "0" yazıcaz. Bu işlemdem sonra PORTx VE PUD bize 3 seçenek sunuyor. Öncelikle PUD MCUCR – MCU Control Register ında bulunan ve dahili pull-up direnci aktif veya pasif yapamamıza olanak sağlayan bir register(kayıtçı) dır.

- 1. Eğer DDRx yazmacındaki porta ait ayak sıfır yapılır ve port yazmacındaki aynı bit de sıfır yapılırsa giriş ve çıkış fonksiyonu giriş olur ve tri-state olarak kalır. 
- 2. İkinci durumda PORTx in herhangi bir bitine "1" yazılır ise ve PUD bitine "0" yazılır ise dahili pull-up özelliği gösterir.
- 3. Üçüncü durumda PUD bitine "1" ve PORTx in herhangi bir bitine de "1" yazılır ise dahili pull-up pasif olur.

## Peki ya nedir bu Pull-Up Pull-Down ?

//

![2](https://circuitdigest.com/sites/default/files/projectimage_tut/Pull-up-and-Pull-down-Resistor.png)

//
- Pull-Up ve Pull-Down dirençleri genelde butonlar için kararlı bir durum oluşturmak adına devreye eklenir. Mesala biz herhangi bir portu giriş olarak ayarladık ve bu porta bir buton bağlamak istiyoruz.Üsteki çizimde görüldüğü gibi Pull-Up direncini devremize eklediğimizi varsayalım. Şimdi butona basmadığımız sürece butonu bağladığımız portta +5 V gerilim vardır. Butona bastığımızda ise bu devreye  0 V gitmektedir. Bu durumu biz programsal olarak kontrol ederek herhangi bir işelemi mikrodenetleyicimize yaptırabiliriz.Bu dirençleri kullanmamızdaki amaç  devre için kararlı bir yapı oluşturmaktır.

### Örnekler 
![](https://i.ibb.co/FwCDmCm/UNOV3PDF.png)
## Örnek 1 (Sürekli Yanan Led)
- Bu örnekde Arduino Uno' yu Atmel Stduio yardımı ile register seviyesinde programlayacağız.
- Arduino nun PD2 bacağına bir led bağlaalım ve bu ledin sürekli yanamsı için gerekli kodları yazalım.
- Öncelikle ledimizin "D" portunda olduğunu biliyouz bu yüzden DDRD kayıtçısın 3. bitine(PD2) "1" yazmamız gerekiyor.

```sh
#include <avr/io.h>
int main(void)
{
	DDRD |=(1<<2);  //PORT ÇIKIŞ OLARAK AYARLANDI
    while (1) 
    {
    }
}
```
- Daha sonra bu porta PORTD yi kullanrak çıkış vermemiz (high) gerekiyor. 
```sh
#include <avr/io.h>
int main(void)
{
	DDRD |=(1<<2);  //PORT ÇIKIŞ OLARAK AYARLANDI
	PORTD |=(1<<2); //PORTA ÇIKIŞ VERİLDİ
    while (1) 
    {
    }
}
```
- veya
```sh
#include <avr/io.h>
int main(void)
{
	DDRD |=(1<<PORTD2);  //PORT ÇIKIŞ OLARAK AYARLANDI
	PORTD |=(1<<PORTD2); //PORTA ÇIKIŞ VERİLDİ
    while (1) 
    {
    }
}
```
## Örnek 2 (Yanıp Sönen Led)
- PORTB ni PB1 bacağına bağlı olan ledi 500 ms gecikme ile yakıp söndürme uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB |=(1<<1);  //PORT ÇIKIŞ OLARAK AYARLANDI
    while (1) 
    {
        PORTB|=(1<<1);
		_delay_ms(500);
		PORTB&=~(1<<1);
		_delay_ms(500);
    }
}
```
## Örnek 3 (Bit Seviyesinde) (Kara Şimşek)
- D portunun ilk 4 pinine bağlı ledler ile kara şimşek uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	 DDRD|=(1<<PORTD0)|(1<<PORTD1)|(1<<PORTD2)|(1<<PORTD3);
    while (1) 
    {
       	for(uint16_t i=0x01;i<=0x08;i=i*2)
		{
			PORTD=i;
			_delay_ms(100);
		}
		for(uint16_t i=0x08;i>=0x01;i=i/2)
		{    PORTD=i;
			_delay_ms(100);
		}
    }
}
```
## Örnek 4 (Buton ile Led Kontrolü) (Dahili Pull-Up)
- PD2 de bulunan ledi PB2 de bulunan buton ile kontrol etme uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	  DDRD|=(1<<PORTD2);//ÇIKIŞ
	  DDRB&=~(1<<PORTB2);//GİRİŞ
	  PORTB|=(1<<PORTB2);//DAHİLİ PULL UP
	  MCUCR&=~(1<<PUD);
    while (1) 
    {
		if (!(PINB & (1<<PINB2)))
		{
			PORTD|=(1<<PORTD2);
		} 
		else
		{
			PORTD&=~(1<<PORTD2);
		}
    }
}
```
## Örnek 5 (Buton ile Led Kontrolü) (Pull-Down)
- PD2 de bulunan ledi PB2 de bulunan buton ile kontrol etme uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	  DDRD|=(1<<PORTD2);//ÇIKIŞ
	  DDRB&=~(1<<PORTB2);//GİRİŞ
      PORTB|=(1<<PORTB2);//DAHİLİ PULL UP
	  MCUCR|=(1<<PUD);
    while (1) 
    {
		if ((PINB & (1<<PINB2)))
		{
			PORTD|=(1<<PORTD2);
		} 
		else
		{
			PORTD&=~(1<<PORTD2);
		}
    }
}
```
/
#### veya
/
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	  DDRD|=(1<<PORTD2);//ÇIKIŞ
	  DDRB&=~(1<<PORTB2);//GİRİŞ
    while (1) 
    {
		if ((PINB & (1<<PINB2)))
		{
			PORTD|=(1<<PORTD2);
		} 
		else
		{
			PORTD&=~(1<<PORTD2);
		}
    }
}
```
###### IO-PORTS da bahsedeceklerim bu kadar sizde datasheet veya diğer websitelerinde bulunan örnek ve dökümanları inceleyerek kendi uygulamalarınızı yapabilirsiniz.
### Özellikle  [lojikprob]  ve [lojikprob2] ücretsiz kitapalarını inceleyebilirsiniz.
[lojikprob2]: <http://www.lojikprob.com/diger/kitap/avr-ile-mikrodenetleyici-uygulamalari-gokhan-dokmetas-ucretsiz-e-kitap/>
[pinout]: <https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf>
[lojikprob]: <http://www.lojikprob.com/c-ile-avr-programlama-e-kitap-indir/>
[Datasheet]: <https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf>
[1]: <https://i.ibb.co/cwJhMX6/2021-26-2-14-18-47.png>
[2]: <https://i.ibb.co/bJ3tK1b/2021-26-2-14-22-30.png>
[3]: <https://i.ibb.co/18pJKSz/2021-26-2-14-22-38.png>
[4]: <https://i.ibb.co/7GSWgpw/2021-26-2-14-29-36.png>



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
