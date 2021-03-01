#  Analog Digital Converter

Bu yazımızda analog değeri dijital bir değere dönüştürme uygulamaları yapıcaz. Ama önceliklele analog ve dijital sinyal nedir bunları inceleyelim.

Fiziksel değişimlerle ilgili bilgiyi taşıyan ve bu bilgiyi matematiksel bir fonksiyon olarak ifade eden kavrama sinyal denir. 

![](https://i.ibb.co/gyBZWy6/2021-01-3-14-29-41.png)

### Analog Sinyal
Analog sinyal, sürekli (continuous) sinyallerdir. Yani zamana bağlı olarak sürekli bir değer alırlar. Analog sinyaller gürültüye dayanıklı değillerdir. Ayrıca analog sinyaller sürekli değiştiklerinden belli aralıklardaki tüm değerleri alabilirler. Doğadaki sinyallerin çoğu sürekli olarak bir değer aldıkları için analog sinyal olarak tanımlanırlar.
![](https://i.ibb.co/VSV6bxy/2021-01-3-14-31-10.png)

### Dijital Sinyal
Dijital sinyal, kesik zamanlı (discrete time) sinyaldir. Yani sürekli olarak belli bir değer almazlar. Analog sinyalden zamana bağlı olarak örnekler(sample) alınır ve dijital sinyal bu örneklerle oluşturulabilirler. Dijital sinyal veriyi binary formda taşır. Günlük hayatta kullandığımız elektronik cihazlardaki işlemlerin çoğu dijital sinyaller ile yapılmaktadır.
![](https://i.ibb.co/nQXWM3y/2021-01-3-14-32-14.png)

### Üsteki bulunan yazının ve görsellerin tamamı [Berkan Aydın] ' ın Analog Sinyal ve Dijital Sinyal yazısından alınmıştır.
### Kaynakçalar;
- [Yazı Kaynak 1]
- [Yazı Kaynak 2]
- [Yazı Kaynak 3]

### ADC işlemini adım adım anlatmak gerekirse şu şekilde olmalıdır;
• Seçili ADC kanal ayağını giriş olarak tanımlamalıdır.
• AVR’nin ADC modülü faal hale getirilmelidir. Çünkü açılış resetinde güç tüketimini önlemek
için devre dışıdır.
• Çevirim hızı seçilir. ADPS2:0 bitleri bu işlemi yapar.
• ADC giriş kanallarındaki gerilim referansı seçilir. ADMUX yazmacındaki REFS0 ve REFS1
bitleri referans seçmek için görevlidir. ADMUX yazmacındaki MUX4:0 bitleri ise ADC giriş
kanalını seçmeye yarar.
• ADCSRA yazmacındaki ADSC biti HIGH yapılarak çevirim başlatılır.
• ADCSRA yazmacındaki ADIF yani ADC kesme bayrağı biti kontrol edilerek çevirimin
bitmesi beklenir.
• ADIF biti HIGH konuma geçtikten sonra ADCL ve ADCH yazmaçlarındaki dijital veri çıkışı
okunur. Öncelikle ADCL yazmacını sonrası ADCH yazmacını okumak gereklidir.
İşte AVR mikrodenetleyicilerde ADC okuma işlemleri bu şekilde olmaktadır.

### Üste bulunan yazının tamamı Gökhan Dökmetaş ın C ile AVR Programalama kitabından alınmıştır.
### Kitap Linkleri;
-[C ile AVR Programlama]
-[AVR ile Mikrodenetleyici Uygulamaları]
### Özellikle İncele
-[lojikprob.com]

Şimdi ADC kayıtçılarını inceleyelim.

![](https://i.ibb.co/09NdGs0/2021-01-3-14-55-01.png)

![](https://i.ibb.co/k4h5wzt/2021-01-3-14-55-22.png)

![](https://i.ibb.co/W23FYcn/2021-01-3-14-55-09.png)

##### ADMUX Kayıtçısının;

- MUX3..0 bitleri hangi bacaktan analog okuma yapacağımzı seçmemizi sağlar
- REFS1..0 bitleri ise gerilim referansını seçmemizi sağlar

![](https://i.ibb.co/WGCn8z9/2021-01-3-14-55-31.png)

![](https://i.ibb.co/pxzQ5Rb/2021-01-3-14-55-43.png)

##### ADCSRA Kayıtçısının;
- ADPS2..0 bitleri sistem saat frekansı ile ADC’nin giriş saati arasındaki bölme faktörünü belirlemeye yarar.
- ADIE  biti "1" yapılırsa ve SREG kesmesindeki I biti de "1" konumdaysa ADC Çevirim Bitme Kesmesi faal hale gelir.
- ADIF  ADC Kesme Bayrağı
- ADSC bitini her bir çevirimi başlatırken bu biti "1" yaparız. Serbest
çalışma modunda ise ilk çevirimi yapmak için bu biti "1" yapmamız gerekir. Çevirim
yapmadan önce ADEN bitini "1" konumuna getirmek sonra ADSC bitini "1" konuma
getirmek gerekir. Bunun ardından Analog-Dijital Çevirimi yaparız. ADSC biti bu çevirim boyunca "1" konumunda kalır ve çevirim bittikten sonra tekrar "0" konumuna geçer. 
- ADEN bu biti HIGH yapmak ADC’yi faal hale getirir. Sıfır yapınca ADC kapatılır

### Örnekler
### Örnek 1 (ADC Hazırlama ve Okuma)
```sh
#include <avr/io.h>
uint16_t read_adc(uint8_t channel);
int main(void)
{
	
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); 
	ADMUX |= (1<<REFS0); // Referans AVCC yani 5V
	ADCSRA |= (1<<ADEN); // ADC'yi Aç
	ADCSRA |= (1<<ADSC); // İlk deneme ölçümünü yap ve diğer ölçüme hazır hale getir.

    while (1) 
    {
		read_adc(0x00);//ADC0 oku
    }
}
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0; // Eski kanal bilgisini temizle
	ADMUX |= channel; // Yeni kanal bilgisini yükle
	ADCSRA |= (1<<ADSC); // Yeni Çevirim Başlat
	while(ADCSRA & (1<<ADSC)); // Çevirim bitene kadar bekle (bu kısım çok önemli)
	return ADCW; // ADC çevirim değerini geri döndür.
}
```
### Örnek 2 (Potansiyometre Değerini Okumak)
- Arduino nun ADC2(A2) bacağına bağlı potansiyometre ve D portunun son 4 bitine led bağlıdır.
- Potansiyometre değerinin okuyoruz ve eğer değer 250 den büyük veya eşit ise D portunun son 4 bitini "1" (HIGH) yapıyoruz.
- 
```sh
#include <avr/io.h>
uint16_t read_adc(uint8_t channel);

int main(void)
{
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)); 
	ADMUX |= (1<<REFS0); // Referans AVCC yani 5V
	ADCSRA |= (1<<ADEN); // ADC'yi Aç
	ADCSRA |= (1<<ADSC); // İlk deneme ölçümünü yap ve diğer ölçüme hazır hale getir.
   DDRD=0xf0;
   
    while (1) 
    {
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
uint16_t read_adc(uint8_t channel){
	ADMUX &= 0xF0; // Eski kanal bilgisini temizle
	ADMUX |= channel; // Yeni kanal bilgisini yükle
	ADCSRA |= (1<<ADSC); // Yeni Çevirim Başlat
	while(ADCSRA & (1<<ADSC)); // Çevirim bitene kadar bekle (bu kısım çok önemli)
	return ADCW; // ADC çevirim değerini geri döndür.
}
```



[Datasheet]: <https://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-7810-Automotive-Microcontrollers-ATmega328P_Datasheet.pdf>

[lojikprob.com]: <http://www.lojikprob.com/>

[AVR ile Mikrodenetleyici Uygulamaları]: <http://www.lojikprob.com/diger/kitap/avr-ile-mikrodenetleyici-uygulamalari-gokhan-dokmetas-ucretsiz-e-kitap/>

[C ile AVR Programlama]: <http://www.lojikprob.com/avr/c-ile-avr-programlama-gokhan-dokmetas-e-kitap/>

[Berkan Aydın]: <https://medium.com/@berkanaydn16/analog-sinyal-ve-dijital-sinyal-dc5590cc5e1a>
[Yazı Kaynak 1]: <https://www.elprocus.com/differences-between-analog-signal-and-digital-signal/>
[Yazı Kaynak 2]: <https://teknolojiprojeleri.com/elektronik/analog-ve-sayisal-sinyaller-sistemler-nedir>
[Yazı Kaynak 3]: <http://mekatronik-sistemler.blogspot.com/2017/03/analog-dijital-sinyal-donusum-mantg.html>