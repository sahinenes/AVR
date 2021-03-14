# Timer Counter 0 (8-bit)
![](https://i.ibb.co/YcFkCQh/2021-10-3-21-21-49.png)
![](https://i.ibb.co/9W3MxcD/2021-10-3-21-22-17.png)
![](https://i.ibb.co/rkYvsjG/2021-10-3-21-22-46.png)
![](https://i.ibb.co/CKsBkW1/2021-10-3-21-23-02.png)
/

/
![](https://i.ibb.co/QdHHZfT/2021-10-3-21-23-57.png)
![](https://i.ibb.co/dgTTk9H/2021-10-3-21-24-18.png)
![](https://i.ibb.co/Y2bB2BM/2021-10-3-21-24-33.png)
![](https://i.ibb.co/TwLMdcG/2021-10-3-21-25-10.png)
//

//
![](https://i.ibb.co/72dRMK9/2021-10-3-21-25-26.png)
![](https://i.ibb.co/YL1YPVj/2021-10-3-21-25-50.png)

![](https://i.ibb.co/PMgyJkM/2021-10-3-21-51-41.png)
- Zamanlayıcı / Sayaç kaydı, hem okuma hem de yazma işlemleri için Zamanlayıcı / Sayaç ünitesi 8 bitlik sayaca doğrudan erişim sağlar.

![](https://i.ibb.co/KX2tCY6/2021-10-3-21-52-01.png)
- Çıkış karşılaştırma kaydı A, sayaç değeri (TCNT0) ile sürekli olarak karşılaştırılan 8 bitlik bir değer içerir. Bir eşleşme, bir çıkış karşılaştırma kesmesi oluşturmak veya OC0A pininde bir dalga formu çıkışı oluşturmak için kullanılabilir.

![](https://i.ibb.co/37dD2dz/2021-10-3-21-52-21.png)
- Çıkış karşılaştırma kaydı B, sayaç değeri (TCNT0) ile sürekli olarak karşılaştırılan 8 bitlik bir değer içerir. Bir eşleşme, bir çıkış karşılaştırma kesmesi oluşturmak veya OC0B pininde bir dalga formu çıkışı oluşturmak için kullanılabilir.

![](https://i.ibb.co/7X9CLQF/2021-10-3-21-52-41.png)
- OCIE0A: Zamanlayıcı / Sayaç0 Çıkış Karşılaştırma A Eşleştirme Kesme Etkinleştirme
- OCIE0B: Zamanlayıcı / Sayaç Çıkışı Karşılaştırma B Maçı Kesmeyi Etkinleştir
- TOIE0: Zamanlayıcı / Sayaç0 Taşma Kesintisini Etkinleştir


### Şimdi modları inceleyelim
- Normal: Normal modda, TCNT1 sayar ve 0xFFFF'den 0x0000'e geçtiğinde Zamanlayıcı / Sayaç 1 Taşma kesintisini tetikler.
- Compare Output Mode: Çıkış Karşılaştırma modu, tekrarlanan zamanlamayı gerçekleştirmek için kullanılır. TCNT0'deki değer (ön ölçekleyici seçim bitleri tarafından durdurulmadığı takdirde artan) kalıcı olarak OCR0x'daki değerle karşılaştırılır. Bu değerler birbirine eşit olduğunda çıktı karşılaştırma kesme işareti ayarlanır ve bir ISR çağrılabilir.
- PWM :Açılımı Pulse Width Modulation yani Sinyal Genişlik Modülasyonu
### Örnekler
### Örnek 1 (Normal Mod)
- pd2 pinine 1 adet led bağlıdır bu ledi timer/counter her 0xff değerine ulaştığında kemeye gider ve toggle işlemi yapar.
```sh
/*
 * Timer Counter 0.c
 *
 * Created: 11.03.2021 15:45:52
 * Author : Enes
 */ 
#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{

	TCCR0B|=(1<<CS00)|(1<<CS02);//  (CLCK/1024)
	TIMSK0|=(1<<TOIE0);
	TCNT0=0x00; 
	DDRD|=(1<<PORTD2);

	
	

	
	sei();
	
    while (1) 
    {
    }
}

ISR (TIMER0_OVF_vect)
{
	PORTD^=(1<<PORTD2);
}
```
### Örnek 2 (CTC Mode)
- Bu örnek COM0A0 pinini toggle olarak çalıştıryoruz.
- Yine COM0A0 pinine led bağlıdır.
- isterseniz kesmeyi etkinleştirerek PD2 deki ledi toggle çalıştırabilirisiniz
```sh
#define  F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	OCR0A =250;
	TCCR0A|=(1<<WGM01)|(1<<COM0A0);
	TCCR0B |= (1 << CS02) | (1 << CS00);
	//TIMSK0 |= (1 << OCIE0A);
	DDRD|=(1<<PORTD6);
	
	sei();
	
    while (1) 
    {
		
    }
}


ISR(TIMER0_COMPA_vect)
{
	
	PORTD^=(1<<PORTD2);
}

```
