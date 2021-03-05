# Analog Comparator

Analog karşılaştırıcı, pozitif pin AIN0 ve negatif pin AIN1 üzerindeki giriş değerlerini karşılaştırır. Pozitif pin AIN0 üzerindeki voltaj, negatif pin AIN1 üzerindeki voltajdan yüksek olduğunda, analog karşılaştırıcı çıkışı ACO ayarlanır. Karşılaştırıcının çıkışı, Zamanlayıcıyı tetikleyecek şekilde ayarlanabilir.

Şimdi kayıtçıları inceleyelim.
![](https://i.ibb.co/4gf9xnt/2021-05-3-15-48-39.png)
– ACME: Bu bit negatif girişi seçer.Ayrıntılı bilgi için aşağıdaki tabloyu incele.
![](https://i.ibb.co/kmbq78j/2021-05-3-15-57-25.png)


![](https://i.ibb.co/f9sxKcK/2021-05-3-15-48-48.png)

- ACD: Analog Karşılaştırıcı Devre Dışı Bırakma
- ACBG: Analog Karşılaştırıcı Bant Aralığı Seçimi
- ACO: Analog Karşılaştırıcı Çıkışı
- ACI: Analog Karşılaştırıcı Kesme İşareti
- ACIE: Analog Karşılaştırıcı Kesmeyi Etkinleştirme
- ACIC: Analog Karşılaştırıcı Giriş Yakalama Etkinleştir
- ACIS1..0;
![](https://i.ibb.co/6b6QHxM/2021-05-3-15-48-59.png)

![](https://i.ibb.co/HBwn3Wv/2021-05-3-15-49-10.png)
- AIN1D, AIN0D: AIN1, AIN0 Dijital Giriş Devre Dışı Bırakma

# Örnekler
# Örnek 1 
- AIN0 da potansiyometre , AIN1 de 1k lık direnç bağlıdır.
- AIN0 daki voltaj değeri AIN1 deki voltaj değerinden büyük ise PB0 a bağlı led yanıcak.
```sh
#include <avr/io.h>

int main(void)
{
    DDRB|=(1<<PORTB0);
	ADCSRB|=(1<<ACME);
	
    while (1) 
    {
		if (ACSR & (1<<ACO))
		PORTB = 0x01;
		else		
		PORTB = 0x00;	
    }
}
```