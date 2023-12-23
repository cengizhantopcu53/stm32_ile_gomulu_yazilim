
# UART ile Mesaj Gönderme

> ## **HAL**

## Teori

• TTL, dijital mantık devrelerinde yaygın olarak kullanılan bir elektriksel sinyal standardıdır. Düşük gerilim seviye olarak 0V ile yüksek gerilim seviyeleri için 3.3V veya 5V kullanır. <br> 
• İletişimi USB, RS232 veya RS485 üzerinden sağlamak için TTL dönüştürücü kullanmamız gerekir. USB için FT232, RS232 için MAX3232 veya MAX232, RS485 için MAX485 gibi entegreleri kullanabiliriz. <br>
• Nucleo kartların USART2 pini ile bağlantı yapıldığında, terminal ile  haberleşmeyi kartın üzerindeki USB ile sağlayabiliriz. USART2 dışındaki diğer USART pinlerini kullanırsak bu pinlerin çıkışına TTL dönüştürücü kullanmamız gerekir. <br>
• Seri Port işlemlerinde kullandığınız TTL dönüştürücü bilgisayarınızda gözükmüyorsa çipin driverını yüklemeniz gerekiyor. [FT232RL](https://www.ftdichip.com/old2020/Drivers/CDM/CDM%20v2.12.28%20WHQL%20Certified.zip) için linkten driver indirip aygıt yöneticisinden güncelleyebilirsiniz. <br>
• Printf komutu ile veri göndermek için https://www.youtube.com/watch?v=SpTh30wTmcM ile https://www.youtube.com/watch?v=WnCpPf7u4Xo linklerindeki videoları inceleyebiliriz. <br>
[Printf](https://bilgisayarkavramlari.com/2012/05/31/printf-sprintf-fprintf/) fonksiyonu ve türevleri hakkında bilgi almak için link üzerinden bakabiliriz. <br>

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
<img src="image\image-6.png" width="150"> <br>
• Sprintf komutu ile yazdırma yaparken fonksiyon içinde de kullanabiliriz ya da ayrı satırda yazıp daha sonra fonksiyon içinde boyutunu belirtmek için strlen fonksiyonunu kullanırız. <br> 
• Strlen yerine sizeof fonksiyonu da kullanabilir. <br>
• \n, metinde bir alt satıra geçmek için \r ise metinde paragraf başı yapmak için kullanılır. <br> 
<img src="image\image-7.png" width="550"> <br>
• USART işleminde ilk olarak polling mode için HAL_UART_Transmit() fonksiyonunu kullanacağız. <br>
• Fonksiyon için 4 parametre giriyoruz. Birincisi UART ayarların tutulduğu veri yapısı, ikincisi gönderilecek veri, üçüncüsü verinin kaç karakter göndereceğimiz yani kaç byte olduğu ve son olarak dördüncüsü veri aktarımının tamamlanması için beklenen maksimum süredir. <br>
uint8_t tipinde bir data göndermemizi istiyor fakat biz char değişkeni kullandığımızdan bir çevrim yapmamız gerekiyor. <br>
<img src="image\image-8.png" width="450"> <br>
• Float değeri yazdırmak için bir ayar yapılmalıdır. Bunun için proje dosyasına sağ tıklayıp Properties tıklanır. C/C++ Build kısmından Settings kısmına gelinir ve buradan Tool Settings kısmından MCU Settings kısmından -u_printf_float kutucuğu işaretlenir. <br>
<img src="image\image-9.png" width="500"> <br>
• Timeout süresi, milisaniye cinsinden belirtilir. Kod kısmında timeout süresi 50 olarak belirledik. Bu, veri gönderme işleminin en fazla 50 milisaniye sürmesi gerektiği anlamına gelir. Eğer belirtilen süre içinde veri gönderimi tamamlanamazsa, iletişim timeout olur ve ilgili hata durumu işlenebilir. <br>
• Timeout süresini ihtiyaçlarınıza göre ayarlayabiliriz. Daha uzun süreler belirlemek, daha yavaş veya yoğun bir iletişim ortamında güvenilirlik sağlayabilir. Ancak, çok uzun timeout süreleri kullanmak, iletişim hatalarını algılama ve hızlı bir şekilde hata durumlarına yanıt verme yeteneğini azaltabilir. <br>
• Timeout süresini öğrenmek için farklı yollara başvurabiliriz. <br> 
Biz Hal_GetTick() fonksiyonunu kullanarak ne kadarlık bir veri gönderme süresi olduğunu buluruz. Bize sonuç verirken 1ms gecikme ekler. <br>
• Kodu aşağıdaki gibi düzenleriz. Int değişken türünde time1 ve time değişkenlerini globalde atarız. Daha sonra fonksiyonun dönüşünden gelen değeri önceki satırdaki gelen değeri çıkararak sonuca ulaşırız. <br>
• Debug girdiğimizde time değişkenine baktığımızda 36 değeri döndürüyor. Çıkan sonuçtan 1 çıkarırız. Sonuç olarak toplamda 35ms'de veriyi gönderiyor. Böylece Timeout için girdiğimiz 50 değeri yeterlidir. <br>
• Hesap yaparak öğrenmek istersek 35 byte veri gönderdiğimizi biliyoruz. Bu değeri bir byte için geçen süre ile çarparsak buluruz. <br> 
9600 baud rate için bir byte'ın iletiminde geçen süre 1/9600 den çıkan sonucu 10 ile çarparız daha sonra gönderilen bytte adeti olan 35 ile çarparsak sonucunda 35ms olduğunu buluruz. <br> 
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
Ayrıca HAL_UART_TxCpltCallback, geri çağırma fonksiyonu ile UART iletişim modülü tarafından bir veri iletim işlemi tamamlandığında otomatik olarak çağırarak yapılması gereken işlemleri gerçekleştirebiliriz. <br> 
• Interruptı kullanırken iki türlü kullanabiliriz. Birincisi, Transmit fonksiyonu ana döngü içerisinde yazıp çalıştırabiliriz daha sonra kesmeye girdiğinde Callback fonksiyonu ile başka işlemler gerçekleştirebiliriz. <br> 
<img src="image\image-14.png" width="400"> <br>
• İkincisinde ana döngüye girmeden bir kere Transmit edip daha sonra Callback fonksiyonuyla transfer işlemi gerçekleştirebiliriz. <br> 
Burada döngüden her çıktığında kesmeye gidiyor. <br>
<img src="image\image-15.png" width="400"> <br>
<img src="image\image-16.png" width="400"> <br>
• Her iki durumda da ana döngü bloke olmamış olacaktır. <br> 

<br>

# DMA 

## Konfigürasyon Kısmı

• Eğer DMA kullanacaksak aktif edilmesi gerekir. <br>
• Dairesel modda, DMA verileri iletmeye devam edecektir. Tüm verileri ilettikten sonra, otomatik olarak baştan başlayacaktır. <br>
Hafızada sadece 1 byte yer kaplayan karakterleri gönderdiğimiz için Data With Byte olarak seçilmiştir. <br>
<img src="image\image-17.png" width="450"> <br>

## Kod Kısmı

• USART işleminde DMA mode olarak HAL_UART_Transmit_DMA() fonksiyonunu kullanacağız.  <br>
DMA ayrıca kesme ile aynı şekilde çalışır. Böylece kesme için kullanabildiğimiz Callback fonksiyonlarını kullanabiliriz. <br>
<img src="image\image-18.png" width="400"> <br>
• Ana döngüye girmeden hem de Callback fonksiyonu çağırmadan da gönderme işlemi yapabiliriz. <br>
<img src="image\image-19.png" width="400"> <br>

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
Burada sırayla bakıldığında binary değeri ile aynı sonucu görmüş oluruz. <br> 
<img src="image\image-23.png" width="800"> <br>

## Seri Port Kısmı

• Seri port yazdırmak için Termite programını kullanıyoruz. Programı açtıktan sonra bazı ayarları yapmamız gerekiyor. Bağlı olduğu port seçimi ile yukarıda belirlediğimiz 9600 baud rate değerini seçiyoruz. <br>
<img src="image\image-24.png" width="400"> <br>
• Port ayarlarını yaptıktan sonuçları görüntüleyebiliriz. <br>
<img src="image\image-25.png" width="400"> <br>


---


<br>


> ## **REGISTER**

## Konfigürasyon Kısmı

• RCC için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-26.png" width="350"> <br>
• USART3 kullanacağız. Clock hattı APB1'e gidiyor. <br>
<img src="image\image-27.png" width="250"> <br>
<img src="image\image-28.png" width="450"> <br>
• 18.biti 1 yapıyoruz. <br>
<img src="image\image-29.png" width="200"> <br>
<img src="image\image-30.png" width="150"> <br>
• USART3 hangi porta bağlı olduğunu öğrenmek için Datasheet bakarız. B portun 10. ve 11.pinine bağlıymış. <br>
<img src="image\image-31.png" width="500"> <br>
• B Portu AHB1 kısmına gidiyor. <br>
<img src="image\image-32.png" width="250"> <br>
<img src="image\image-33.png" width="450"> <br>
• Biz B portunu kullandığımızdan sadece bunu aktif ediyoruz. <br>
<img src="image\image-34.png" width="250"> <br>
<img src="image\image-35.png" width="200"> <br>
• B portun 10. ve 11. pinleri USART3 için kullanacağımızdan bu pinleri alternate function mode yapıyoruz. <br>
<img src="image\image-36.png" width="450"> <br>
<img src="image\image-37.png" width="350"> <br>
<img src="image\image-38.png" width="200"> <br>
• Kullanacağımız çevresel birim olan USART3 kullanacağımızı belirteceğiz. <br>
<img src="image\image-39.png" width="450"> <br>
<img src="image\image-40.png" width="450"> <br>
• Biz 10 ve 11. pinleri kullandığımızdan high olanı kullanıyoruz. <br>
<img src="image\image-41.png" width="300"> <br>
• Seçtiğimiz USART3 çevresel birimi hangi AF'de olduğunu bilmek için Reference Manuel kitapçığına bakıyoruz. <br>
<img src="image\image-42.png" width="350"> <br>
• USART3, AF7'de bulunuyor. Böylece pinlere AF7 için olan 0111 tanımlaması yapacağız. <br>
• AFR'nin High ve Low olduğunuda belirtmemiz gerekiyor. High kullandığımızdan dizin kısmına 1 yazıyoruz. <br>
<img src="image\image-43.png" width="200"> <br>
• GPIO için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-44.png" width="500"> <br>
• Baud rate hesabı için aşağıdaki formül kullanılır. USARTDIV ile istenen baud rate değeri hesaplanır ve bulunan değer BRR register'a yazılır. <br>
<img src="image\image-45.png" width="300"> <br>
• OVER8 için CR1 registerında oversampling by 16 kullandığımızdan bu değeri 0 alıyoruz. <br>
• Baud rate ayarını 9600 yapmak için USARTDIV 273,4375 bulunur. <br> 
• Hesap yapmak yerine Reference Manul'deki tablolardan da bakılabilir. <br> 
• Biz 3.satırdaki değeri bulduk. <br>
<img src="image\image-46.png" width="450"> <br>
• Ondalıklı sayının tam kısmına mantissa, küsurat kısmına fraction denir. <br>
• Buna göre mantissa değeri 273 yani 0x111 bulunur. Geriye kalan 0.4375 değerini fraction değerine dönüştürmek için OVER8 değeri 0 olduğundan 16 ile çarpılır sonucunda 7 yani 0x7 bulunur. <br>
• Böylece BRR registerına 0x1117 değeri yazılır. <br>
<img src="image\image-47.png" width="450"> <br>
<img src="image\image-48.png" width="150"> <br>
• USART_BRR değerini döndürecek fonksiyon ile de yazabiliriz. <br>
<img src="image\image-49.png" width="300"> <br>
<img src="image\image-50.png" width="450"> <br>
<img src="image\image-51.png" width="300"> <br>
<img src="image\image-52.png" width="150"> <br>
<img src="image\image-53.png" width="400"> <br>
<img src="image\image-54.png" width="150"> <br>
• Mesaj geldiğinde interrupt girmesi için aktif ediyoruz. <br>
<img src="image\image-55.png" width="400"> <br>
<img src="image\image-56.png" width="150"> <br>
<img src="image\image-57.png" width="400"> <br>
<img src="image\image-58.png" width="150"> <br>
<img src="image\image-59.png" width="400"> <br>
<img src="image\image-60.png" width="150"> <br>
• Üsteki uyarıdan sebep UE registırı en alt satırında olması gerekiyor. <br>
<img src="image\image-61.png" width="400"> <br>
<img src="image\image-62.png" width="150"> <br>
<img src="image\image-63.png" width="400"> <br>
<img src="image\image-64.png" width="350"> <br>
<img src="image\image-65.png" width="150"> <br>
• USART fonksiyonu için ayarlamalar bitti. <br>
<img src="image\image-66.png" width="450"> <br>

## Kod Kısmı

• Şimdi interrupt için fonksiyon yazacağız. Öncelikle NVIC için fonksiyon yazıyoruz. <br>
<img src="image\image-67.png" width="450"> <br>
• 7.pini interrupt veriyoruz. <br>
<img src="image\image-68.png" width="400"> <br>
<img src="image\image-69.png" width="150"> <br>
<img src="image\image-70.png" width="400"> <br>
• Şimdi Interrupt fonksiyonu yazıyoruz. Öncelikle değişken ataması yapıyoruz. Haberleşme durumunu Status Register ile bu değişkene yazacağız. <br> 
• Daha sonra gelen mesajları dizeye alıyoruz. Bunun için Data register kullanıyoruz. <br>
<img src="image\image-71.png" width="500"> <br>
<img src="image\image-72.png" width="150"> <br>
<img src="image\image-73.png" width="200"> <br>
<img src="image\image-74.png" width="250"> <br>
• Send_Message'a mesajımızı yazıyoruz. Mesajımızdaki harflerin yani her dizideki elemanlarını alıyoruz ve her elemanı Send_Char'a gönderiyoruz ve burada Data register'a yazarak karşı tarafa mesaj ulaşıyor. <br>
<img src="image\image-75.png" width="200"> <br>
<img src="image\image-76.png" width="300"> <br>

---

<br>