# USART
### USART NEDİR ?
UART (Universal Asynchronous Receiver Transmitter), bilgisayar ve mikrokontroller veya mikrokontroller ve çevre birimler arasında haberleşmeyi sağlayan haberleşme protokolüdür. Asenkron olarak çalıştığı için herhangi bir “clock” ihtiyacı duymaz. USART (Universal Synchronous Asynchronous Receiver Transmitter) ise hem senkron hem de asenkron olarak çalışabilir. UART’a göre daha gelişmiş bir protokoldür. Haberleşme mantıklı aynı şekilde çalışır ancak USART aynı zamanda senkron haberleşmeleri de gerçekleştirebilir. Yeni çıkan bir mikroişlemcinin datasheet’ine baktığınız zaman bu birimleri genelde USART birimi olarak görüyoruz çünkü USART aynı zamanda UART’ı da kapsayan bir birim olarak tasarlanmıştır.

UART haberleşmesini gerçekleştirirken ilk olarak baudrate (veri taşıma hızı) ayarlanması gerekir. Veri taşıma hızı çok çeşitli aralıklarda olabilir ancak piyasada yaygın olarak kullanılan baudrate’ler 4800, 9600, 57600, 115200 ve mikroişlemciler için çok fazla tercih edilmese de 921600. (921600 genelde hızlı işlem gerektiren yerlerde kullanılır.) Baudrate bizim verimizin saniyede ne kadarlık byte’ını taşıyacağını belirlememize yarar.

### Üste bulunan yazının tamamı [herenkeskin.com] dan alınmıştır.

Şimdi USART Kayıtçılarını inceleyelim;

![](https://i.ibb.co/xXDTpDL/2021-02-3-16-25-16.png)

Burada gönderim ve alım için ortak kullanılan ve okuma/yazma yapılabilen 8 bitlik bir
yazmaç görüyoruz. Yapacağımız okuma ve yazmalar bu yazmaç üzerinden olacaktır.

![](https://i.ibb.co/n7tD7h8/2021-02-3-16-25-25.png)

UCSRnA kayıtçısı;
MPCMn : Bu bit çoklu işlemci iletişim modunu faal hale getirir
U2Xn : Bu bit ancak asenkron çalışmada etkili olur. Senkron iletişimde bu bit bir (1) olmalıdır. Bu biti bir (1) yapmak veri aktarım hızı bölücüsünü 16’dan 8’e düşürür ve böylelikle transfer hızını ikiye katlar.
UPEn : Bu bir eşlik hatası gerçekleştiğinde bir (1) konumuna geçer.
DORn : Bu bit veri aşma tespit edilirse bir (1) konumuna geçer. Bir veri aşma hatası alış tamponu dolu olduğunda gerçekleşir.
FEn : Bu bit alıcı tamponunun sonraki karakteri çerçeve hatasına sahipse bir (1) konumuna geçer.
UDREn : Bu bit gönderici tamponunun yani UDR0’ın yeni veri almaya müsait olduğunu belirtir. Eğer UDRE0 biti bir (1) konumunda ise tampon bellek boştur. Ayrıca bu bayrak biti Veri yazmacı boş kesmesini yürütmek için kullanılabilir.
TXC0 : UDR0 yazmacındaki tüm bitler gönderildiği zaman bu bit bir (1) konumuna geçer. TXC0 bayrak biti eğer gönderim tamamlanma kesmesi yürürse otomatik olarak sıfır (0) konumuna geçer.
RXC0 : Bu bayrak biti tampon bellekte okunmamış bir gelen veri olduğunda bir (1) konumuna geçer. Tampon bellekte veri kalmadığı zaman ise tekrar sıfır (0) konumuna geçer.

![](https://i.ibb.co/2ncsDnk/2021-02-3-16-25-38.png)

RXCIE0 : Alım Tamamlandı Kesmesi Etkinleştirme 0 

TXCIE0 : Gönderim Tamamlandı Kesmesi Etkinleştirme 0
Bu bite bir (1) yazmak TXC0 bayrak bitindeki kesmeyi etkin hale getirir.
UDRIE0 : USART Veri Yazmacı Boş Kesmesini Etkinleştirme 0
Bu biti bir (1) yapmak UDRE0 bayrak bitindeki kesmeyi etkin hale getirir.
RXEN0 : Alıcı Etkinleştirme 0 Bu biti bir (1) yapmak USART alıcısını etkinleştirir.
TXEN0 : Verici Etkinleştirme 0 Bu biti bir (1) yapmak USART vericisini etkinleştirir.
UCSZ02 : Karakter boyutu 0UCSZ02 biti UCSZ0 [1:0] bitleriyle beraber çalışır. Bu bitler alıcı ve verici görevleri yürütülürken belirlenen veri boyutu çerçevesini belirlemede kullanılır.
RXB80 : Alıcı 8. Veri Biti Eğer veri çerçevesi boyutu 9 bit ise burada 9. bit saklanır. UDR0’ın düşük bitlerini okumadan önce okunmalıdır.
TXB80 : Verici 8. Veri Biti Eğer veri çerçevesi boyutu 9 bit olarak belirlenirse gönderilecek 9. bit buraya yerleştirilir. UDR0’ın düşük bitlerini yazmadan önce yazılmalıdır.

![](https://i.ibb.co/jV2MQ3T/2021-02-3-16-25-48.png)


![](https://i.ibb.co/ch8T0YT/2021-02-3-18-24-02.png)

Bu bitler USART’ın çalışma modunu seçer

![](https://i.ibb.co/xzntc54/2021-02-3-18-24-09.png)

Bu bitler eşlik üretimi tipini ayarlar ve bunu denetler. Eğer etkinleştirilirse verici otomatik olarak eşlik bitini oluşturur ve veri çerçevesi içerisinde bunu gönderir

![](https://i.ibb.co/wz5MxgF/2021-02-3-18-24-18.png)

Bu bit verici tarafından yerleştirilen stop bitlerinin sayısını belirler. Alıcı bu ayarı görmezden gelir.

![](https://i.ibb.co/nf93TwJ/2021-02-3-18-24-24.png)

Bu bitler veri çerçevesindkei veri bitlerinin sayısını belirler

![](https://i.ibb.co/z2NRf16/2021-02-3-21-25-38.png)

![](https://i.ibb.co/93QDvdY/2021-02-3-18-44-21.png)

Bu 12 bitlik yazmaç USART veri iletim hızı bilgisini içinde bulundurur. UBRR0H baş dört biti
bulundururken UBRR0L son sekiz biti bulundurur. Baud hızı iletişim sırasında değişirse Alıcı ve verici düzgün işleyemez. UBRR0L yazmacına veri yazmak baud oranında ani bir değişme yapar


USART birimi yüklenmesi için şu adımlar gerçekleştirilmelidir,
- Baud Oranı Ayarlanmalıdır
- Veri Boyutu Ayarlanmalıdır
- TXEN ve RXEN bitleri ile Alıcı ve Verici Etkinleştirilmelidir.
- Eşlik biti ve Stop bitlerinin sayısı ayarlanmalıdır.

![](https://i.ibb.co/NtnsPSV/2021-02-3-21-59-46.png)

### Örnekler
### Örnek 1 (USART Kullanımı)
- 'a' karakteri usart ile gönderme uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600 // Baud Oranını Tanımlıyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlıyoruz

void uart_transmit (unsigned char data);
unsigned char veri_al();

int main(void)
{
   
   UCSR0B |=(1<<TXEN0)|(1<<RXEN0);//TX ve RX aktif
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatını ayarlıyoruz
   UBRR0= BAUDRATE; //Bant genişilği ayarlandı
    while (1) 
    {
		veri_gonder('a');
		_delay_ms(1000);
    }
}

// veri gönderme fonksiyonu
void veri_gonder (unsigned char data)
{
	while (!( UCSR0A & (1<<UDRE0))); // yazmacın boş olmasını bekle
	UDR0 = data; // yazmaca veri yükle
}
unsigned char veri_al()
{
	while(!(UCSR0A & (1<<RXC0)));
	return UDR0;
}
```
### Örnek 2 (USART Kullanımı Uzun Veri Gönderimi)
- "DENEME" kelimesi usart ile gönderme uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>

#define BAUD 9600 // Baud Oranını Tanımlıyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlıyoruz

void uart_transmit (unsigned char data);
unsigned char veri_al();
void veri_gonder_uzun(char *data);
int main(void)
{
   
   UCSR0B |=(1<<TXEN0)|(1<<RXEN0);//TX ve RX aktif
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatını ayarlıyoruz
   UBRR0= BAUDRATE; //Bant genişilği ayarlandı
    while (1) 
    {
    	veri_gonder_uzun("DENEME");
		_delay_ms(1000);
    }
}

// veri gönderme fonksiyonu
void veri_gonder (unsigned char data)
{
	while (!( UCSR0A & (1<<UDRE0))); // yazmacın boş olmasını bekle
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
```
### Örnek 3 (USART Kullanımı Rakam veya Sayı Gönderme)
- "DENEME" kelimesi usart ile gönderme uygulaması
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define BAUD 9600 // Baud Oranını Tanımlıyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlıyoruz

void uart_transmit (unsigned char data);
unsigned char veri_al();
void veri_gonder_uzun(char *data);

uint8_t sayi;
char str[50];

int main(void)
{
   
   UCSR0B |=(1<<TXEN0)|(1<<RXEN0);//TX ve RX aktif
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatını ayarlıyoruz
   UBRR0= BAUDRATE; //Bant genişilği ayarlandı
   
   sayi=200;
   
    while (1) 
    {
		itoa(sayi,str,10);
		veri_gonder_uzun(str);
		_delay_ms(1000);
    }
}

// veri gönderme fonksiyonu
void veri_gonder (unsigned char data)
{
	while (!( UCSR0A & (1<<UDRE0))); // yazmacın boş olmasını bekle
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
```
### Örnek 4 (USART Kullanımı Bilgisayardan Veri Gönderme)
- Bilgisayardan gelen veri ile kullanıcı ledinin yakılması
- -PB5 de bağlı led vardır.
```sh
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#define BAUD 9600 // Baud Oranını Tanımlıyoruz
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1) // UBRR için baud verisini ayarlıyoruz

void uart_transmit (unsigned char data);
unsigned char veri_al();
void veri_gonder_uzun(char *data);

uint8_t sayi;
char str[50];
int main(void)
{
   
   UCSR0B |=(1<<TXEN0)|(1<<RXEN0);//TX ve RX aktif
   UCSR0C|= (1<<UCSZ00)|(1<<UCSZ01); // Veri formatını ayarlıyoruz
   UBRR0= BAUDRATE; //Bant genişilği ayarlandı
   
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
	while (!( UCSR0A & (1<<UDRE0))); // yazmacın boş olmasını bekle
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
void UART_veri_al_satır(char* buf, uint8_t n)
{
    uint8_t bufIdx = 0;
    char c;

  
    do
    {
        
        c = veri_al();

        
        buf[bufIdx++] = c;
    }
    while((bufIdx < n) && (c != '\r'));

    
    buf[bufIdx] = 0;
}
```



[herenkeskin.com]: <https://www.elprocus.com/differences-between-analog-signal-and-digital-signal/>
