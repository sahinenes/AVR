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
   