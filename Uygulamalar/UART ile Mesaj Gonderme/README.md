
# UART ile Mesaj Gönderme

> ## **HAL**

## Teori

• TTL, dijital mantık devrelerinde yaygın olarak kullanılan bir elektriksel sinyal standardıdır. Düşük gerilim seviye olarak 0V ile yüksek gerilim seviyeleri için 3.3V veya 5V kullanır. <br> 
• İletişimi USB, RS232 veya RS485 üzerinden sağlamak için TTL dönüştürücü kullanmamız gerekir. USB için FT232, RS232 için MAX3232 veya MAX232, RS485 için MAX485 gibi entegreleri kullanabiliriz. <br>
• Nucleo kartların USART2 pini ile bağlantı yapıldığında, terminal ile  haberleşmeyi kartın üzerindeki USB ile sağlayabiliriz. USART2 dışındaki diğer USART pinlerini kullanırsak bu pinlerin çıkışına TTL dönüştürücü kullanmamız gerekir. <br>
• Seri Port işlemlerinde kullandığınız TTL dönüştürücü bilgisayarınızda gözükmüyorsa çipin driverını yüklemeniz gerekiyor. [FT232RL](https://www.ftdichip.com/old2020/Drivers/CDM/CDM%20v2.12.28%20WHQL%20Certified.zip) için linkten driver indirip aygıt yöneticisinden güncelleyebilirsiniz. <br>
• Printf komutu ile veri göndermek için https://www.youtube.com/watch?v=SpTh30wTmcM ile https://www.youtube.com/watch?v=WnCpPf7u4Xo linklerindeki videoları inceleyebiliriz. <br>
[Printf](https://bilgisayarkavramlari.com/2012/05/31/printf-sprintf-fprintf/) fonksiyonu ve türevleri hakkında bilgi almak için link üzerinden bakabiliriz. <br>
• Aşağıda yapılan örnek çalışmalar Transmit için yapılmıştır fakat Receive için yapılan işlemler de aynıdır.

<br>
<br>

# Polling

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="400"> <br>
• Sadece Transmit yapacağımızdan Data Direction kısmından Transmit Only seçeneğini seçebiliriz. <br>
<img src="image\image-3.png" width="300"> <br>
<img src="image\image-4.png" width="300"> <br>

## Kod Kısmı

• Sprintf komutu için stdio.h, strlen kütüphanesi için string.h kütüphanesini ekledik. <br>
<img src="image\image-5.png" width="150"> <br>
• Göndereceğimiz ifadeleri tutacağımız char değişkenli dizi ekliyoruz. <br>
<img src="image\image-6.png" width="200"> <br>
• Yazdırma yapmak için **sprintf** veya **snprintf** fonksiyonlarını kullanabiliriz. <br> 
sprintf fonksiyonu, belirtilen formatta bir dizi karakteri bir buffer'a yazar. <br> 
snprintf fonksiyonu, belirtilen formatta bir dizi karakteri bir buffer'a yazar, ancak aynı zamanda bu buffer'ın maksimum boyutunu da kontrol eder. <br> 
• Boyutunu belirtmek için **strlen** veya **sizeof** fonksiyonunu kullanırız. <br> 
sizeof, bir veri türünün veya değişkenin bellekte kapladığı toplam boyutu (byte cinsinden) belirleyen bir operatördür. Derleme zamanında değerlendirilir. <br> 
strlen fonksiyonu, bir karakter dizisindeki karakterlerin sayısını hesaplar. Bu sayıya, dizinin sonunu belirten null karakter (\0) dahil edilmez. <br> 
• \n, metinde bir alt satıra geçmek için \r ise metinde paragraf başı yapmak için kullanılır. <br> 
<img src="image\image-7.png" width="600"> <br>
• USART işleminde ilk olarak polling mode için HAL_UART_Transmit() fonksiyonunu kullanacağız. <br>
• Fonksiyon için 4 parametre giriyoruz. Birincisi UART ayarların tutulduğu **veri yapısı**, ikincisi gönderilecek **veri**, üçüncüsü verinin kaç karakter göndereceğimiz yani **kaç byte** olduğu ve son olarak dördüncüsü veri aktarımının tamamlanması için beklenen **maksimum süredir**. <br>
• uint8_t tipinde bir data göndermemizi istiyor fakat biz char değişkeni kullandığımızdan bir çevrim yapmamız gerekiyor. <br>
<img src="image\image-8.png" width="450"> <br>
• Float değeri yazdırmak için bir ayar yapılmalıdır. Bunun için proje dosyasına sağ tıklayıp Properties tıklanır. C/C++ Build kısmından Settings kısmına gelinir ve buradan Tool Settings kısmından MCU Settings kısmından -u_printf_float kutucuğu işaretlenir. <br>
<img src="image\image-9.png" width="500"> <br>
• Timeout süresi, milisaniye cinsinden belirtilir. Kod kısmında timeout süresi 50 olarak belirledik. Bu, veri gönderme işleminin en fazla 50 milisaniye sürmesi gerektiği anlamına gelir. Eğer belirtilen süre içinde veri gönderimi tamamlanamazsa, iletişim timeout olur ve ilgili hata durumu işlenebilir. <br>
• Timeout süresini ihtiyaçlarınıza göre ayarlayabiliriz. Daha uzun süreler belirlemek, daha yavaş veya yoğun bir iletişim ortamında güvenilirlik sağlayabilir. Ancak, çok uzun timeout süreleri kullanmak, iletişim hatalarını algılama ve hızlı bir şekilde hata durumlarına yanıt verme yeteneğini azaltabilir. <br>
• Timeout süresini öğrenmek için farklı yollara başvurabiliriz. <br> 
Biz **Hal_GetTick()** fonksiyonunu kullanarak ne kadarlık bir veri gönderme süresi olduğunu buluruz. Bize sonuç verirken 1ms gecikme ekler. <br>
• Kodu aşağıdaki gibi düzenleriz. Int değişken türünde time1 ve time değişkenlerini globalde atarız. Daha sonra fonksiyonun dönüşünden gelen değeri önceki satırdaki gelen değeri çıkararak sonuca ulaşırız. <br>
• Debug girdiğimizde time değişkenine baktığımızda 36 değeri döndürüyor. Çıkan sonuçtan 1 çıkarırız. Sonuç olarak toplamda 35ms'de veriyi gönderiyor. Böylece Timeout için girdiğimiz 50 değeri yeterlidir. <br>
• Hesap yaparak öğrenmek istersek 35 byte veri gönderdiğimizi biliyoruz. Bu değeri bir byte için geçen süre ile çarparsak buluruz. <br> 
9600 baud rate için bir byte'ın iletiminde geçen süre 1/9600'den çıkan sonucu 10 ile çarparız daha sonra gönderilen bytte adeti olan 35 ile çarparsak sonucunda 35ms olduğunu buluruz. <br> 
• Sonuç olarak Polling metodunu kullanarak ana döngüde transmit yaparken 35ms bekleme yapıyor. Bu bekleme döngünün çalışrken başka yapılan bir işi yavaşlatır. <br> 
<img src="image\image-10.png" width="450"> <br>
• Printf komutu ile yazdırmak istersek aşağıdaki kodu ekleriz. Bu kod ile while döngüsünde Transmit fonksiyonunu yazmamıza gerek kalmıyor. <br>
<img src="image\image-11.png" width="400"> <br>
<img src="image\image-12.png" width="450"> <br>

<br>

# Interrupt 

## Konfigürasyon Kısmı

• Eğer Interrupt kullanacaksak aktif edilmesi gerekir. <br>
<img src="image\image-13.png" width="450"> <br>

## Kod Kısmı

• USART işleminde interrupt mode olarak HAL_UART_Transmit_IT() fonksiyonunu kullanacağız. Böylece döngünün ana akışını kesmeden veriyi yollamış olacağız. <br> 
Ayrıca **HAL_UART_TxCpltCallback**, geri çağırma fonksiyonu ile UART iletişim modülü tarafından bir veri iletim işlemi tamamlandığında otomatik olarak çağırarak yapılması gereken işlemleri gerçekleştirebiliriz. <br>
Bu fonksiyonun amacı, veri gönderimi tamamlandığında gerçekleştirilmesi gereken işleri yapmak (örneğin, başka bir veri gönderme işlemi başlatmak, bir bayrak ayarlamak, vs.) için kullanıcı tarafından doldurulmasıdır. <br> 
• Interruptı kullanırken iki türlü kullanabiliriz. 
Birincisi, Transmit fonksiyonu ana döngü içerisinde yazıp çalıştırabiliriz daha sonra kesmeye girdiğinde Callback fonksiyonu ile başka işlemler gerçekleştirebiliriz. <br> 
<img src="image\image-14.png" width="400"> <br>
• İkincisinde ana döngüye girmeden bir kere Transmit edip daha sonra Callback fonksiyonuyla transfer işlemini sürekli hale getirebiliriz. <br> 
<img src="image\image-15.png" width="400"> <br>
<img src="image\image-16.png" width="400"> <br>
• Her iki durumda da ana döngü bloke olmamış olacaktır. <br> 

<br>

# DMA 

## Konfigürasyon Kısmı

• Eğer DMA kullanacaksak aktif edilmesi gerekir. <br>
• Memory'den Peripheral'a yazacağımızdan DMA Request için USART1_TX seçilir. <br>
• Dairesel modda, DMA verileri iletmeye devam edecektir. Tüm verileri ilettikten sonra, otomatik olarak baştan başlayacaktır. <br>
Hafızada sadece 1 byte yer kaplayan karakterleri gönderdiğimiz için Data With kısmı Byte olarak seçilmiştir. <br>
<img src="image\image-17.png" width="450"> <br>

## Kod Kısmı

• USART işleminde DMA mode olarak HAL_UART_Transmit_DMA() fonksiyonunu kullanacağız.  <br>
DMA ayrıca kesme ile aynı şekilde çalışır. Böylece kesme için kullanabildiğimiz Callback fonksiyonlarını kullanabiliriz. <br>
<img src="image\image-18.png" width="400"> <br>
• İkincisinde ana döngüye girmeden bir kere Transmit edip daha sonra Callback fonksiyonuyla transfer işlemini sürekli hale getirebiliriz. <br>
<img src="image\image-19.png" width="400"> <br>
• Eğer sürekli veri göndermek istiyorsan, DMA'yı **Circular** modda çalıştırabiliriz. Bu modda DMA transferi hiç durmaz, sürekli olarak veriyi gönderir. <br>
• Duruma göre bu yöntemlerden birini seçebilirsin. <br>
**Sürekli döngüde tekrarlamak:**, basit ve kolay bir yöntemdir, ancak işlem sürekli döngüde kalır. <br>
**DMA Transfer Tamamlanma Callback,** daha esnek ve profesyonel bir yaklaşımdır, çünkü verinin ne zaman gönderileceği üzerinde daha fazla kontrol sağlar. <br>
**Circular Mode,** sürekli ve kesintisiz aynı veriyi göndermek istiyorsan en verimli yöntemdir. <br>

<br>

## Logic Analyzer Kısmı

• Ayrıca seri port dışında logic analayzer ile bakarakta sonuçları elde edebiliriz. <br>
Bağladığımız kanal için Async Serial seçimi yapıp benzer ayarlamaları yapıyoruz. <br>
<img src="image\image-20.png" width="300"> <br>
• İşlemcinin Tx ucunu Logic Analayzer'da Channel2'ye bağladık. <br>
• Sonuç olarak 500ms aralıklarla 35 byte veriyi 35ms'de yolluyor. <br> 
• Ayrıca veri göndermeyi 50 ms altında yaparak işlemci zaman aşımına uğramıyor. Eğer kod kısmında 50 değil de 35'in altında bir değer yazsaydık veri kaybı olacaktı. <br>
<img src="image\image-21.png" width="800"> <br>
• Verileri görüntülerken gelen dataları ASCII olarak görüntülüyoruz. <br> 
<img src="image\image-22.png" width="800"> <br>
• Gelen verideki 5 verisine detaylı bakalım. 5'i ASCII'den Binary'e çevirmemiz gerekiyor. <br> 
• Ekran üzerinden de değiştirebiliriz ya da https://www.rapidtables.com/convert/number/ascii-to-binary.html linkten bu işlemi yapabiliriz. <br> 
• Ayrıca https://www.netdunyasi.com/blog/uploads/images/202105/image_750x_60985f549fe84.jpg linkten ASCII tablosuna bakabiliriz. <br>
• Binary'e çevirdiğimizde 00110101 değerini görürüz. <br> 
• İlk ve son bitler start ve stop bit olmak üzere nokta ile belirtilmiş 8 bitlik data ile birlikte toplamda 10 bit var. <br>
Burada sırayla bakıldığında binary değeri ile aynı sonucu görmüş oluruz. <br> 1
<img src="image\image-23.png" width="800"> <br>

## Seri Port Kısmı

• Seri port yazdırmak için Termite programını kullanıyoruz. Programı açtıktan sonra bazı ayarları yapmamız gerekiyor. Bağlı olduğu port seçimi ile yukarıda belirlediğimiz 9600 baud rate değerini seçiyoruz. <br>
<img src="image\image-24.png" width="400"> <br>
• Port ayarlarını yaptıktan sonuçları görüntüleyebiliriz. <br>
<img src="image\image-25.png" width="400"> <br>


---


<br>


