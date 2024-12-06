
# ADC Verisi Okuma

> ## **HAL**

#### Polling

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

<br>

#### Interrupt

## Konfigürasyon Kısmı

<img src="image\image-15.png" width="400"> <br>
<img src="image\image-16.png" width="500"> <br>
• ADC1 için IN0, Temperature Sensor Channel ve Vrefint Channel seçimi yaptık. <br>
<img src="image\image-17.png" width="150"> <br>
• Scan Mode ile Continuous Mode Enabled yapılır. <br>
<img src="image\image-18.png" width="400"> <br>
• ADC1 için 3 kanal olduğundan her biri için rank işlemi yapılır. <br>
<img src="image\image-19.png" width="400"> <br>
• ADC2 için IN1 seçimi yapılır. <br>
• ADC2 için tek kanal olduğundan Scan Mode seçimi yapılmaz. <br> 
<img src="image\image-20.png" width="400"> <br>
<img src="image\image-21.png" width="400"> <br>
• Interrupt kullanacağımızdan NVIC Settings kısmından Enabled yapılır. <br> 
• Sadece ADC1 değil ADC2 ve ADC3 için interrupts Enabled yapılmış olur. <br> 
<img src="image\image-22.png" width="500"> <br>


## Kod Kısmı

• ADC için Interrupt Mode kullanımı yapacağız. <br>
<img src="image\image-23.png" width="500"> <br>
<img src="image\image-24.png" width="400"> <br>
• Keseme olduğunda it.c dosyasındaki ADC_IRQHandler fonksiyonuna gelir ve fonksiyon içerisindeki HAL_ADC_IRQHandler fonksiyonunu çalıştırır. <br> 
• Bizim main.c dosyasında hazır olarak yazılmıştır. <br>
<img src="image\image-25.png" width="250"> <br>
• 1578.satırdaki Callback fonksiyonu main.c dosyasında kullanarak Interrupt'a girdiğinde yani ADC çevrimi tamamlandığında bu fonksiyon çalışmaya başlayacaktır. <br>
<img src="image\image-26.png" width="400"> <br>
• İçerisine önce hangi ADC'yi çalıştırdığını öğrenmemiz gerekiyor. Bunun için _HAL_ADC_GET_FLAG kullanmamız gerekiyor. <br>
<img src="image\image-27.png" width="450"> <br>
<img src="image\image-28.png" width="700"> <br>
• Temperature için Datasheet kısmından aşağıdaki tabloları kullanıyoruz. <br>  
<img src="image\image-29.png" width="500"> <br>
• Aşağıdaki formül üzerinden hesaplıyoruz. <br>
<img src="image\image-30.png" width="400"> <br>
<img src="image\image-31.png" width="400"> <br>
<img src="image\image-32.png" width="200"> <br>
<img src="image\image-33.png" width="500"> <br>
<img src="image\image-34.png" width="400"> <br>

<br>

#### DMA

## Giriş

• ADC'den okuduğumuz değerleri, hiç CPU'ya uğratmadan DMA ile direk RAM'e yazacağız. <br>

## Konfigürasyon Kısmı

<img src="image\image-35.png" width="400"> <br>
<img src="image\image-36.png" width="450"> <br>
• ADC sürekli dönüşüm modu için **Continuous Conversion** Mode, Enabled yapıldı.  <br>
• DMA ile ADC'den sürekli veri alımı için **DMA Continuous Requests**, Enabled yapıldı. <br>
<img src="image\image-37.png" width="450"> <br>
• DMA ayarları için Add diyoruz. Ardından Stream, Direction ve Priority için seçenekleri seçiyoruz. <br> 
• Daha sonra Direction kısmından seçtiğimiz Peripheral ve Memory için adres değişikliği için Increment Adress için işaretliyoruz. <br> 
Ardından gönderilecek data boyutu belirliyoruz. 12bit çalıştığımızdan 16 bitlik olan Half Word seçimi yapıyoruz. <br>
<img src="image\image-38.png" width="450"> <br>

## Kod Kısmı

<img src="image\image-39.png" width="500"> <br>
• **pData** kısmına veriyi tutacağımız değişkeni yazıyoruz. Bizim değişken 16 bit olarak tanımladığımızdan dönüştürmemiz gerekiyor. <br>
• **Length** ile kaç tane veri okuyacağımızı yazıyoruz. <br>
<img src="image\image-40.png" width="500"> <br>
<img src="image\image-41.png" width="200"> <br>
<img src="image\image-42.png" width="400"> <br>


---

<br>