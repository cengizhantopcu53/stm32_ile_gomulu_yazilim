
# İrtifa Ölçüm

> ## **BMP180**

## Teori

• https://controllerstech.com/interface-bmp180-with-stm32/ adresinden örnek uygulamayı inceleyebiliriz. <br>
<img src="image\image-1.png" width="400"> <br>
• BMP180 sensörü dengelenmemiş sıcaklık ve basınç verilerini sunar. <br> 
• E2PROM  176 bit kalibrasyon datasını saklar. Bu değerler ile sıcaklık ve basınç değerlerini doğrularız. <br> 
• UP, pressure datadır. 16bit ile 19bittir. UT, temperature datadır, 16 bittir. <br>
• Mikrodenetleyici, sıcaklık ve basınç ölçümünü başlatmak için bir başlatma sinyalini gönderir. Daha sonra I2C üzerinden sıcaklık ve basınç verisi okunur. Sıcaklığı °C ve basıncı hPa cinsinden okumak için kalibrasyon verileri okunmalıdır. Bunun için I2C aracılığıyla E2PROM'dan bakılır. <br>
<img src="image\image-2.png" width="250"> <br>
• Aşağıda diyagram üzerinden sensörden nasıl sıcaklık ve basınç değerin okunduğunun işleyişi anlatılıyor. <br>
<img src="image\image-3.png" width="500"> <br>


## Konfigürasyon Kısmı

<img src="image\image-4.png" width="400"> <br>
<img src="image\image-5.png" width="400"> <br>
<img src="image\image-6.png" width="400"> <br>
• Connectivity başlığı altından I2C seçip Mode ekranından I2C seçiyoruz. <br> 
<img src="image\image-7.png" width="250"> <br>
• I2C için Speed Mode olarak Fast Mode seçimi yapıyoruz. <br>
<img src="image\image-8.png" width="250"> <br>

## Kod Kısmı

• Dosyamızın Inc klasörü için bmp180.h adında Header File, Src klasörüne bmp180.c adında Source File ekliyoruz. <br>
• Ardından birkaç fonksiyon ekliyorum. Sensörü başlatmak ve kalibrasyon için fonksiyon yazıyoruz. <br> 
• Sensörle haberleşme yaparken okuma ve yazma yapabilmek için kullanacağım adresleri tanımlıyorum. <br> 
• BMP180 adresine okuma yapmak için ilk bit 1 yapılır ve 0xEF adresine karşılık gelir. <br>
• Yazma yapmak için ilk bit 0 yapılır, 0xEE adresine karşılık gelir. <br>
<img src="image\image-9.png" width="250"> <br>
• Böylece yazma için 0xEE, okuma için 0xEF adreslerini tanımlıyorum. <br> 
<img src="image\image-10.png" width="300"> <br>
• Bunları yazdıktan sonra Init fonksiyonun içeriğini yazmaya başlıyoruz. <br>
• Her çevre birimin control registerı vardır. Biz datasheet'ten Memory Map tablosunu inceliyoruz. <br>
<img src="image\image-11.png" width="600"> <br>
• Ctrl_meas adresi 0xF4'tür. Adresin 8 bittin ilk 4 biti measurement control, 5.biti sco, 6. ve 7.bit oss'dir. <br>
• sco, Start of conversion yani çevrim başlangıcıdır. <br> 
• Oss, oversampling_setting için girilen değerdir. <br> 
• Basıncı farklı modlar kullanarak optimum güç tüketimi, hız ve çözünürlük arasında seçim yapabiliriz. Bunun için oss değerine girilecek bitler ultra low power için 00, standard 01, high resolution için 10, ultra high resolution 11'dir. <br>
<img src="image\image-12.png" width="450"> <br>
• Kütüphanelerde I2C kullanabilmek için gerekli kütüphaneleri ekliyorum. <br>
<img src="image\image-13.png" width="200"> <br>
• Ardından HAL_I2C_IsDeviceReady() fonksiyonunu kullanıyoruz. <br> 
<img src="image\image-14.png" width="550"> <br>
• hal_i2c.c dosyasından ulaştığımız HAL_I2C_IsDeviceReady() fonksiyonu ile hedef cihazın iletişim için hazır olup olmadığını kontrol ederiz. <br> 
• If yapısı içerisi 1 değil ise ledi yakar yani sensörün işlemci ile bağlantısı yoksa led yanar. <br> 
<img src="image\image-15.png" width="500"> <br>
• Bu uygulamayı görebilmek için main.c dosyasına bmp.h kütüphanesini ekleriz ve BMP180_Init() fonksiyonunu çağırırız. <br>
<img src="image\image-16.png" width="200"> <br>
<img src="image\image-17.png" width="200"> <br>
• Asıl initialization işlemi yani başlatma işlemi kalibrasyon işlemi için E2PROM'dan çekilecek verilerdir. <br>
• 176 bitlik E2PROM her biri 16 bitlik 11 kelimeye bölünmüştür. Her sensör modülün ayrı katsayısı vardır. <br> 
• Sıcaklık ve basınç hesabı yapmadan önce E2PROM verileri okunur. Veri haberleşmesinde her bir kelimenin 0 ya da 0xFFFF değeri olmadığı kontrol edilir. <br>
<img src="image\image-18.png" width="200"> <br>
• Bu verileri bmp180.c dosyasında tanımlıyoruz. <br>
<img src="image\image-19.png" width="200"> <br>
• Bunlar için kaç adet olduğuna dair tanımlama yapıyorum. Her biri 16 bit olduğunu biliyorum. Tanımlarken 8 bit olarak tanımlama yapacağımdan toplam veri 22 adet oluyor. <br> 
<img src="image\image-20.png" width="300"> <br>
• bmp180.h dosyasında void BMP180_Get_Calibration_Value() fonksiyonu tanımlıyorum ve bmp.c dosyasında fonksiyonu yazıyoruz. Önce 22 veriyi diziye atıp değerlerini sıfırlıyoruz. <br>
<img src="image\image-21.png" width="350"> <br>
• Okuma işlemini HAL_I2C_Mem_Read() fonksiyonu ile yapıyoruz. <br>
<img src="image\image-22.png" width="800"> <br>
• Devadress, Slave cihaz için tanımladığımız adres oluyor. <br> 
• MemAddress, Slave cihazda okuma yapacağım adres oluyor. Biz buraya verileri okuyacağımız ilk veri olan AC1'in başlangıç adresi olan 0xAA yazıyoruz. <br>
• Bunun içinde bmp180.h dosyasında tanımlama yapıyoruz. <br>
<img src="image\image-23.png" width="350"> <br>
• MemAddSize, okuma yapılacak adresin boyutunu yazıyoruz. 8 bit veri okuması yapacağımızdan 1 yazıyoruz. <br>
• pData, datayı yazacağımız yeri yazıyoruz. 22 veriyi tanımladığımız dizinin ismini yazıyoruz. <br> 
• Ardından Size kısmına 22 elemanlı dizi olarak tanımladığımdan 22 yazıyoruz. <br>
<img src="image\image-24.png" width="750"> <br>
• Okuma işlemini yapıp bunları diziye kaydettik. Bu kaydedilen verileri tanımladığımız verilere yazıyoruz. Biz diziye kaydederken 8 bit olarak kaydediyorduk ama verimiz 16 bit olduğundan ilk 8 biti 8 bit sola kaydediyoruz. İkinci 8 biti aynen yazıyoruz <br>.
<img src="image\image-25.png" width="250"> <br>
<img src="image\image-26.png" width="750"> <br>
• Yazdığımız BMP180_Get_Calibration_Value() fonksiyonunu BMP180_Init() fonksiyonu içerisine ekleriz. <br>
<img src="image\image-27.png" width="550"> <br>
• STMStudio programını açıp File kısmından Import variables tıklıyoruz ve çalışma dosyamızın debug içerisindeki elf. Uzantılı dosyayı seçiyoruz ve içerisinde okuyacağımız değişkeni import edip yandaki grafiğe ekliyoruz. <br>
• Sonuçlar sabit değerlerdir. <br>
<img src="image\image-28.png" width="350"> <br>
• Böylelikle sıcaklık ve basınç değerlerini hesaplayabiliriz. <br>
• Void yazmamızın sebebi fonksiyonlar bir parametre istemiyor ve geri döndürülmesine gerek olmadığından yazıyoruz ama sıcaklık ve basınç değerlerini hesapladığımız fonksiyonları geri değer döndürüyoruz. <br>
<img src="image\image-29.png" width="300"> <br>
• Ardından hesaplama için gerekli değişkenleri yazıyorum. <br>
<img src="image\image-30.png" width="450"> <br>
• Sıcaklık değerini hesaplamak için önce BME180_Get_Uncompensated_Temperature() fonksiyonunu yazıyoruz. Bunun için datasheet kısmına baktığımızda yapılacak ilk işlem 0xF4 adresine 0x2E datasını yazıyoruz. Ardından 4.5ms bekliyoruz. Daha sonra 0xF6 ve 0xF7 adreslerinden okuma yapıyorum. Bu adreslerde okuduğumuz 8 bitlik 2 datayı 16 bitlik yeni değere yazıyoruz. <br> 
• Yazma işlemini HAL_I2C_Mem_Write() fonksiyonu ile yapıyoruz. <br>
<img src="image\image-31.png" width="750"> <br>
• Devadress, Slave cihaz için tanımladığımız adres oluyor. <br> 
• MemAddress, Slave cihaza yazma yapacağım adres oluyor. Biz buraya 0xF4 yazıyoruz. <br>
• MemAddSize, yazma yapılacak adresin boyutunu yazıyoruz. 8 bit veri okuması yapacağımızdan 1 yazıyoruz. <br>
• pData, datayı okuyacağımız yeri yazıyoruz. Bunun için fonksiyon içinde 0x2E adresini tanımlıyorum. Bu şekilde tanımladığımdan fonksiyon içinde pointer için başına & işareti koyuyorum. <br>
<img src="image\image-32.png" width="150"> <br>
• Ardından Size kısmına 1 yazıyoruz. <br>
<img src="image\image-33.png" width="550"> <br>
• Bekleme için delay yazıyoruz. <br>
<img src="image\image-34.png" width="80"> <br>
• Okuma işlemini HAL_I2C_Mem_Read() fonksiyonu ile yapıyoruz. <br>
<img src="image\image-35.png" width="750"> <br>
• Devadress, Slave cihaz için tanımladığımız adres oluyor. <br> 
• MemAddress, Slave cihazda okuma yapacağım adres oluyor. Biz buraya verileri okuyacağımız ilk veri olan 0xF6 yazıyoruz. <br>
• MemAddSize, okuma yapılacak adresin boyutunu yazıyoruz. 8 bit veri okuması yapacağımızdan 1 yazıyoruz. <br>
• pData, datayı yazacağımız yeri yazıyoruz. 2 veriyi tanımladığımız dizinin ismini yazıyoruz. <br>  
<img src="image\image-36.png" width="150"> <br>
• Ardından Size kısmına 2 elemanlı dizi olarak tanımladığımdan 2 yazıyoruz. <br>
<img src="image\image-37.png" width="750"> <br>
• 0xF6 adresinden okuduğum 8 bitlik datayı 8 bit sola kaydırıyorum ardından 0xF7 adresindeki 8 bitlik datayı direk yazıyorum. <br>
<img src="image\image-38.png" width="250"> <br>
<img src="image\image-39.png" width="550"> <br>
• UT değerini görebilmek için yazdığımız BMP180_Get_Uncompensated_Temperature() fonksiyonunu main.c dosyasına ekliyoruz. <br>
<img src="image\image-40.png" width="250"> <br>
<img src="image\image-41.png" width="350"> <br>
• Asıl şimdi sıcaklık değerini bulacağız. <br> 
• Temp değeri 0.1°C'deki değeri olduğundan 10 ile bölerz ya da 0.1 ile çarparız. <br>
<img src="image\image-42.png" width="250"> <br>
<img src="image\image-43.png" width="150"> <br>
<img src="image\image-44.png" width="250"> <br>
<img src="image\image-45.png" width="350"> <br>
• Basınç değerini hesaplamak için önce BME180_Get_Uncompensated_Pressure() fonksiyonunu yazıyoruz. Bunun için datasheet kısmına baktığımızda yapılacak ilk işlem 0xF4 adresine 0x34 datasını ve buna oss değerini sola 6 bit kaydırarak ekleyerek yazıyoruz. Ardından oss değerine göre datasheet'deki Conversion Time için verilen ms değeri kadar bekleriz. Daha sonra 0xF6, 0xF7 ve 0xF8 adreslerinden okuma yapıyorum. Bu adreslerden okuduğumuz 8 bitlik 3 datayı 24 bitlik yazıyorum ve 8'den oss değerini çıkarıp ardından bu sayıyı 24 bitlik değer kadar sağa kaydırma yapıyorum. <br> 
	• Oss için ultra high resolution yani ultra yüksek çözünürlük seçimi yapıyoruz. Bunun parametre değeri 3'tür. <br> 
• Fonksiyon içinde tanımlıyorum. <br>
<img src="image\image-46.png" width="80"> <br>
• Yazma işlemini HAL_I2C_Mem_Write() fonksiyonu ile yapıyoruz. <br>
<img src="image\image-47.png" width="750"> <br>
• Devadress, Slave cihaz için tanımladığımız adres oluyor. <br> 
• MemAddress, Slave cihaza yazma yapacağım adres oluyor. Biz buraya 0xF4 yazıyoruz. <br>
• MemAddSize, yazma yapılacak adresin boyutunu yazıyoruz. 8 bit veri okuması yapacağımızdan 1 yazıyoruz. <br>
• pData, datayı okuyacağımız yeri yazıyoruz. Bunun için fonksiyon içinde datatowrite değişkenine yazdığım adresini tanımlıyorum. Bu şekilde tanımladığımdan fonksiyon içinde pointer için başına & işareti koyuyorum. <br>
<img src="image\image-48.png" width="250"> <br>
• Ardından Size kısmına 1 yazıyoruz. <br>
<img src="image\image-49.png" width="550"> <br>
• Bekleme için delay yazıyoruz. <br>
<img src="image\image-50.png" width="80"> <br>
• Okuma işlemini HAL_I2C_Mem_Read() fonksiyonu ile yapıyoruz. <br>
<img src="image\image-51.png" width="750"> <br>
• Devadress, Slave cihaz için tanımladığımız adres oluyor. <br> 
• MemAddress, Slave cihazda okuma yapacağım adres oluyor. Biz buraya verileri okuyacağımız ilk veri olan 0xF6 yazıyoruz. <br>
• MemAddSize, okuma yapılacak adresin boyutunu yazıyoruz. 8 bit veri okuması yapacağımızdan 1 yazıyoruz. <br>
• pData, datayı yazacağımız yeri yazıyoruz. 3 veriyi tanımladığımız dizinin ismini yazıyoruz. <br>  
<img src="image\image-52.png" width="200"> <br>
• Ardından Size kısmına 3 elemanlı dizi olarak tanımladığımdan 3 yazıyoruz. <br>
<img src="image\image-53.png" width="550"> <br>
• 0xF6 adresinden okuduğum 8 bitlik datayı 16 bit sola kaydırıyorum ardından 0xF7 adresindeki okuduğum 8 bitlik datayı 8 bit sola kaydırıyorum ardından 0xF8 adresindeki 8 bitlik datayı direk yazıyorum. <br>
<img src="image\image-54.png" width="450"> <br>
<img src="image\image-55.png" width="500"> <br>
• UP değerini görebilmek için yazdığımız BMP180_Get_Uncompensated_Pressure() fonksiyonunu main.c dosyasına ekliyoruz. <br>
<img src="image\image-56.png" width="300"> <br>
<img src="image\image-57.png" width="350"> <br>
• Asıl şimdi basınç değerini bulacağız. <br> 
• Press değeri Pa cinsindendir. <br>
<img src="image\image-58.png" width="300"> <br>
<img src="image\image-59.png" width="150"> <br>
<img src="image\image-60.png" width="300"> <br>
<img src="image\image-61.png" width="350"> <br>
• Artık irtifayı hesaplayabiliriz. İrtifa hesaplamak için gerekli formül aşağıdadır. <br>
<img src="image\image-62.png" width="200"> <br>
• P değeri bizim bulduğumuz basınç değeridir.
• P0 değeri yani Standart Atmosferik Basınç değeri için bmp180.h dosyasına 101325Pa değerini tanımlıyoruz. <br> 
<img src="image\image-63.png" width="200"> <br>
• Önce formülü yazacağımız bmp180.h dosyasına fonksiyonu tanımlıyoruz ardından bmp180.c dosyasındaformülü yazıyoruz. <br>
<img src="image\image-64.png" width="200"> <br>
<img src="image\image-65.png" width="450"> <br>
<img src="image\image-66.png" width="150"> <br>
<img src="image\image-67.png" width="300"> <br>
• Bulunduğumuz bölgenin irtifası 20m üzerindedir. <br>
<img src="image\image-68.png" width="350"> <br>
• BMP180 sensöründen okuma yaptığımız basınç, sıcaklık verisi ile basınç verisini kullanarak elde ettiğimiz irtifa verisinin sonuçları aşağıdadır. <br>
<img src="image\image-69.png" width="350"> <br>


---


<br>


> ## **BME280**

## Teori

• Kart hakkında bilgi edinmek için https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout linki okunabilir.
• https://controllerstech.com/bme280-with-stm32/ adresinden örnek uygulamayı inceleyebiliriz.
• Sensörün haberleşmelere göre bağlantı şekilleri aşağıdaki gibidir. <br>
<img src="image\image-70.png" width="350"> <br>
<img src="image\image-71.png" width="550"> <br>
<img src="image\image-72.png" width="400"> <br>
• ctrl_hum register adındaki 0xF2 adresindeki ilk 3 bitteki osrs_h[2:0] için nemin oversampling değeri kontrol edilir. <br> 
• Nem ölçümü için birçok oversampling seçeneği mevcuttur. <br> 
<img src="image\image-73.png" width="250"> <br>
<img src="image\image-74.png" width="450"> <br>
• ctrl_meas register adındaki 0xF4 adresindeki ilk 2 bitteki mode[1:0] için cihazın sensör durumu , 2., 3. ve 4.bitte osrs_p[2:0] için basıncın oversampling değeri, 5., 6. ve 7.bitte osrs_t[2:0] için sıcaklığın oversampling değeri kontrol edilir. <br> 
• Basınç ve sıcaklık ölçümü için birçok oversampling seçeneği mevcuttur. <br> 
• Basınç ve sıcaklık ölçümünün çözünürlüğü IIR filtresi ve oversampling ayarına bağlıdır. <br> 
IIR filtresi etkinleştirildiğinde 20bittir. <br>
• IIR filtresi devre dışı bırakıldığında 16 + (osrs_p – 1) bittir. <br>
<img src="image\image-75.png" width="250"> <br>
<img src="image\image-76.png" width="250"> <br>
• BME280'nin 3 güç modu bulunur. Bunlar uyku, normal ve zorunlu modlardır. <br>
Uyku modunda hiçbir ölçüm yapılmaz ve güç tüketimi minimumdur. Tüm kayıtlara erişilebilir ve bunları okuyabilir veya değiştirebiliriz.
Zorunlu modda, sensör tek bir ölçüm yapar ve tekrar uyku moduna geçer. Ölçüm sonuçları veri kayıtlarından elde edilebilir. Bir sonraki ölçüm için, zorunlu modun yeniden seçilmesi gerekir. <br>
Normal modda, uyku moduna geçmez. Ölçüm ve bekleme arasında devam eder. Bu mod genellikle, verilerin sürekli olarak gerekli olduğu durumlarda kullanılır. <br>
• Normal modda toplam çevrim süresi, aktif sürenin ve bekleme süresinin toplamına bağlıdır. <br>
• IIR filtresini kullanırken normal modun kullanılması önerilir. <br>
<img src="image\image-77.png" width="350"> <br>
• Normal mode durumunda ölçüm süresi basınç, nem ve basınç için seçilen oversampling değerlerine bağlıdır. Aşağıdaki formül ile hesaplanarak ms cinsinden elde edilir. <br>
<img src="image\image-78.png" width="450"> <br>
• Normal moddaki ölçüm hızı, ölçüm süresine ve bekleme süresine bağlıdır. Aşağıdaki formül ile hesaplanarak Hz cinsinden elde edilir. <br>
<img src="image\image-79.png" width="200"> <br>
<img src="image\image-80.png" width="150"> <br>
<img src="image\image-81.png" width="450"> <br>
• config register adındaki 0xF5 adresindeki ilk bitte spi3w_en[0] kısmı, 2., 3. ve 4.bitte filter[2:0] için IIR filtre katsayısı, 5., 6. ve 7.bitte t_sb[2:0] için normal mode durumundaki bekleme süresi kontrol edilir. <br> 
• Sıcaklık ve basınç için kısa süreli dalgalanmaları ortadan kaldıran isteğe bağlı IIR filtresinden geçirilir. Nem için böyle bir filtre gerekli değildir. <br>
<img src="image\image-82.png" width="200"> <br>
<img src="image\image-83.png" width="200"> <br>
• press register adındaki 0xF7 ile 0xF9 arsındaki adreslerden basınç değeri okunur. <br> 
<img src="image\image-84.png" width="450"> <br>
• temp register adındaki 0xFA ile 0xFC arsındaki adreslerden sıcaklık değeri okunur. <br> 
<img src="image\image-85.png" width="450"> <br>
• hum register adındaki 0xFD ile 0xFE arsındaki adreslerden nem değeri okunur. <br> 
<img src="image\image-86.png" width="450"> <br>
• Veriler, basınç ve sıcaklık için unsigned 20 bit formatında iken nem için unsigned 16 bit formatında okunur. Daha sonrasında okunan verilere kalibrasyon yapılmalıdır. <br>

## Konfigürasyon Kısmı

<img src="image\image-87.png" width="400"> <br>
<img src="image\image-88.png" width="400"> <br>
• Connectivity başlığı altından I2C seçip Mode ekranından I2C seçiyoruz. <br> 
<img src="image\image-89.png" width="250"> <br>
• I2C için Speed Mode olarak Fast Mode seçimi yapıyoruz. <br>
<img src="image\image-90.png" width="250"> <br>

## Kod Kısmı

• Dosyamızın Inc klasörü için bme280.h adında Header File, Src klasörüne bme280.c adında Source File ekliyoruz. <br>
• Kütüphanelerde I2C kullanabilmek için gerekli kütüphaneleri ekliyorum. <br>
<img src="image\image-91.png" width="200"> <br>
<img src="image\image-92.png" width="200"> <br>
• Ardından slave adresi tanımlıyoruz. <br>
• 7 bitlik cihaz adresi 111011X şeklindedir. Buradaki X, SDO pinin durumuna göre belirlenir. SDO'nun GND'ye beğlanması durumunda X=0 olur böylece 1110110 yani 0x76 adreslidir. <br>
SDO'nun VDDIO'ya bağlanması durumunda X=1 olur böylece 1110111 yani 0x77 adreslidir. <br>
Bunları 8 bit yapmak için 1 bit sola kaydırılırsa 0x76 adresi 0xEC, 0x77 adresi 0xEE olur. <br>
• SDO pinini GND'ye bağlıyoruz böylece slave adresimiz 0xEC olur. <br>
<img src="image\image-93.png" width="550"> <br>
• I2C yazma modunda iken RW=0 olur. <br>
<img src="image\image-94.png" width="500"> <br>
• I2C okuma moduna geçebilmek için önce yazma modu gönderilir. <br>
• I2C okuma modunda iken RW=1 olur. <br>
<img src="image\image-95.png" width="500"> <br>
• Main.c içerisine tanımladığımız değişkenleri kütüphane dosyasına ekleriz. <br>
<img src="image\image-96.png" width="300"> <br>
• bme280.h dosyasında tanımlanan aşağıdadır. <br>
<img src="image\image-97.png" width="200"> <br>
<img src="image\image-98.png" width="600"> <br>
• BME280_WakeUP() fonksiyonu cihazın mod durumunu okur ardından modu Zorunlu mod olarak değiştirir. <br>
<img src="image\image-99.png" width="550"> <br>
• Datasheet'te belirtilen Trimming parametreleri okunur. <br>
<img src="image\image-100.png" width="300"> <br>
• Verilerin değişkenlerini yazıyoruz. <br>
<img src="image\image-101.png" width="450"> <br>
• HAL_I2C_Mem_Read fonksiyonuyla slave cihazdan okuduğumuz verileri diziye yazıyoruz. Ardından dizedeki verileri atadığımız değişkenlere yazıyoruz. <br>
<img src="image\image-102.png" width="500"> <br>
• 0xF7 ile 0xFE arasındaki adreslerdeki basınç, sıcaklık ve nem değerlerini okuyoruz. <br>
• Okumadan önce id kontrol edilir. <br>
<img src="image\image-103.png" width="100"> <br>
• id register adındaki 0xDO adresinde çip kimlik numarası olarak 0x60 içermesi lazım bu yüzden 0XDO adresinden okuma yapıp chipID'ye yazıyoruz. Eğer 0x60 ile eşleşirse okuma yapabiliriz. <br> 
<img src="image\image-104.png" width="200"> <br>
<img src="image\image-105.png" width="550"> <br>
• Datashetteki Compensation formülleri yazılır. <br>
• Sıcaklık için, <br>
<img src="image\image-106.png" width="550"> <br>
• Basınç için, <br>
<img src="image\image-107.png" width="550"> <br>
• Nem için, <br>
<img src="image\image-108.png" width="550"> <br>
• TrimRead() fonksiyonunu çağırırız. Okunan değerler kalıcı bellekte değişmeden saklanır. <br>
• Okunduktan sonra cihazı resetleriz. Bunun için reset register adındaki 0xE0 adresine 0xB6 yazmamız durumunda cihaz açılışta sıfırlanır. 0xB6 dışında bir şey yazmanın bir etkisi yoktur. <br> 
0xE0 adresinin okuma değeri her zaman 0x00'dır. <br>
• Sıfırladıktan sonra Nem için oversampling değerini 0xF2 adresine yazıyoruz. <br> 
• Ardından bekleme süresi ile filtre katsayısını 0xF5 adresine yazıyoruz. Bekleme süresini yazarken 5 bit, filtre katsayısını 2 bit sola kaydırıyorum. <br>
• Daha sonra sıcaklık ile basınç için oversampling değerini ve mode durumunu 0xF4 adresine yazıyoruz. Sıcaklığın oversampling değerini yazarken 5 bit, basıncın oversampling değerini 2 bit sola kaydırıyorum. Modu aynen yazıyorum. <br>
<img src="image\image-109.png" width="550"> <br>
• Artık main.c dosyasına kodumuzu yazmaya başlayabiliriz. <br>
• Kütüphane eklenir. <br>
<img src="image\image-110.png" width="200"> <br>
• Değişkenler tanımlanır. <br>
<img src="image\image-111.png" width="250"> <br>
• BME280_Config() fonksiyonun parametreleri girilir. <br> 
• Sıcaklık için oversampling 2, basınç için oversampling 16, nem için oversampling 1, mode olarak normal mode, bekleme süresi 0.5ms, ve filtre katsayısını 16 giriyoruz. <br>
• Bu değerleri girmek için datasheette örnek çalışma modları var. Biz Indoor navigation yani iç mekan navigasyon örneğini kullanıyoruz. <br>
<img src="image\image-112.png" width="450"> <br>
<img src="image\image-113.png" width="450"> <br>
• Döngümüzde BME280_Measure() fonksiyonunu çağırırız. <br>
<img src="image\image-114.png" width="200"> <br>
• Fonksiyonun içeriği aşağıdadır. <br> 
• Nem birimi %RH, basınç birimi Pa, sıcaklık birimi DegC'dir. <br>
<img src="image\image-115.png" width="450"> <br>
• İrtifa verisini ekleme için main.c dosyasında Altitude değişkeni tanımlıyorum. <br>
<img src="image\image-116.png" width="300"> <br>
• Altitude değişkenini BME280_STM32.c dosyasına ekliyorum. <br>
<img src="image\image-117.png" width="350"> <br>
• Ardından irtifa formülünde kullanacağım pow matematik değeri için math.h kütüphanesini ekliyorum. <br>
<img src="image\image-118.png" width="150"> <br>
• BME280_Measure() fonksiyonunda basıncı bulduğum satırın altına irtifa formülünü yazıyorum. <br>
<img src="image\image-119.png" width="600"> <br>
• BME280 sensöründen okuma yaptığımız basınç, sıcaklık ve nem verisi ile basınç verisini kullanarak elde ettiğimiz irtifa verisinin sonuçları aşağıdadır. <br>
<img src="image\image-120.png" width="450"> <br>


---


<br>
