
# Timer ile Delay Oluşturma

> ## **HAL**

## Teori

• https://controllerstech.com/create-1-microsecond-delay-stm32/  ve https://deepbluembedded.com/stm32-delay-microsecond-millisecond-utility-dwt-delay-timer-delay/ linkleri kaynak olarak kullanabiliriz. <br>
• HAL_Delay() fonksiyonuyla minimum 1 milisaniye(ms) gecikme oluşturabiliyoruz fakat 1 mikrosaniye(us) gecikme oluşturan bir fonksiyon bulunmuyor. Bunu yapmak için Timer birimin zamanlayıcısını kullanacağız. <br> 
• Öncellikle bir Timer birimi seçmemiz gerekiyor. Bu işlem için özel bir Timer seçmemize gerek yok. Seçim sonrası bağlı olduğu clock hattını bilmemiz gerekiyor. <br>

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
• Timer1 birimini kullanacağız ve bu birim APB1 clock hattına bağlıdır. <br> 
• Mode kısmında Clock Source için Internal Clock seçimi yapıyoruz. <br>
• Prescaler değerine APB1 clock hattın değerini yazıyoruz. Counter Period değerine yazılabilecek maksimum değer olan 16 bitin karşılığı 65535 değerini yazıyoruz. <br>
<img src="image\image-2.png" width="400"> <br>


## Kod Kısmı

• Milisaniye ve mikrosaniye için fonksiyon yazıyoruz. <br>
• delay_us() fonksiyonu için önce TIM1'deki sayaçın ilk değeri 0 ayarlanır. Sonra parametre olarak girdiğimiz 16 bitlik us değişkenine ulaşana kadar saymaya devam eder. <br>
<img src="image\image-3.png" width="400"> <br>
• Ana döngüye girmeden önce timer başlatılır. <br>
<img src="image\image-4.png" width="250"> <br>
• Delay için delay_us() ya da delay_ms() fonksiyonlarını istediğimiz gibi kullanabiliriz. <br>
<img src="image\image-5.png" width="450"> <br>

---

<br>
