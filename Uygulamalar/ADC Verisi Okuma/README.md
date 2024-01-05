
# ADC Verisi Okuma

> ## **HAL**

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="450"> <br>
• Analog değer okumak için potansiyometreyi PA0'a bağladık. Bunun için Analog kısmından ADC1'den IN0 tıklarız. Gerçek voltaj değerini de hesaplayacağımızdan Vrefinit Channel'da seçilir. <br>
<img src="image\image-3.png" width="150"> <br>
• **Clock Prescaler**, Bu ayar ADC’nin çalışmak için ihtiyaç duyduğu saat darbesini PCLK2 hattından kaç ile bölerek kullanacağını belirtir. <br>
• **Resolution**, çözünürlük ayarı. Daha düşük çözünürlük seçerek daha az saat derbesi gerektiren daha hızlı ölçümler yapılabilir. <br>
• **Data Alignment**, Analog dijital çevrim sonunda elde edilen verinin en değerli biti sağda mı yoksa solda mı olacağını belirler. <br>
• **Scan Conversion**, Aktif edilmesi durumunda aynı ADC’ de birden fazla kanal kullanılacağı zaman ölçümleri arka arkaya yapar. Böylece her kanal için ölçüm sonrası ayrı ayrı sayısal dönüştürme yapmaz, aktif edilen tüm kanallar için ölçüm bitince tek sefer dönüştürme yapar. Bu da dönüştürme işleminin daha hızlı olmasını sağlar. <br>
• **Continuous Conversion**, ADC dönüşümü yazılımda bir kere başlatıldığında tekrar başlatmaya gerek kalmaz. Dönüştürme tamamlanınca tekrar çevrim başlar. <br>
• **DMA Continuous Request**, ADC’nin DMA ile kullanımı için yapılması gereken ayar. <br>
• **Number of Conversion**, ADC başlatıldığında yapılacak çevrim sayısı. Aktif edilmek istenen kanal sayısı kadar seçilmelidir. <br>
• **Channel**, aktif edilen ADC kanalının seçimidir. <br>
• **Sampling Time**, ADC ile yapılacak 1 çevrim işlemi için gereken cycle sayısı. Cycle sayısı artarsa çevrim süresi uzar ama ölçüm daha doğru gerçekleşir. <br>
<img src="image\image-4.png" width="400"> <br>
• Continuous Conversion Mode Enabled yapılır. Tekrar tekrar okuma durumu yapar eğer çalıştırmazsak bir kere okur daha sonra bir daha değer okumaz. <br>
• Çözünürlüğümüzü 12 bit yaptık yani en fazla 4095 değerini görebiliriz. <br>
• Çok kanal olduğundan Scan Mode Enabled yapılır. <br>
<img src="image\image-5.png" width="400"> <br>
• Number Of Conversion kısmı 2 kanal olduğundan iki yazılır ardından rank kısmından öncelik sırası verilir. <br>

## Kod Kısmı

• ADC okumada 3 mod var. Okumada Interrupt ve DMA kullanmayacağız. Polling Mode kullanımı yapacağız. Bunun nasıl kullanıldığını öğrenmek için hal_adc.c dosyasından bakıyoruz. <br>
<img src="image\image-6.png" width="450"> <br>
• ADC çevre birimini başlatmak için HAL_ADC_Start() fonksiyon kullanılır. <br>
<img src="image\image-7.png" width="400"> <br>
• Çevrimin takibini HAL_ADC_PollForConversion() fonksiyon ile yapıyoruz. <br>
• Timeout için milisecond cinsinden istiyor. <br>
<img src="image\image-8.png" width="600"> <br>
<img src="image\image-9.png" width="400"> <br>
<img src="image\image-10.png" width="400"> <br>
• İşlemcinin beslemesi gerçekte 3.3V değildir. Bunun için ayrı hesap yapılması gerekir. Hesap için 2 değer için birini ADC okumasından diğerini ise adres kısmından bulacağız. <br>
• Adres kısmı için datasheet kısmından bakılması gerekir. <br> 
<img src="image\image-11.png" width="500"> <br>
• Bu adres için kodda tanımlama yapılması gerekiyor. <br> 
• Tanımlama yaparken bizim kullanacağımız bit 12, adres biti 32  bittir. Bizim burada 32 bitten 16 bite dönüştürme yapmamız gerekiyor. <br>
<img src="image\image-12.png" width="350"> <br>
• İki kanalı adc_value değişkenine dizi halinde yazdık. 0.dizi rank'daki ayara göre ilk kanal oluyor. <br> 
• Diğer kanalı okuması için count değişkeni koyduk. <br>
<img src="image\image-13.png" width="400"> <br>
<img src="image\image-14.png" width="400"> <br>


---

<br>
