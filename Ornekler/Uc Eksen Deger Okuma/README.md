
# Üç Eksen Değer Okuma

> ## **MPU6050**

## Teori
• https://www.youtube.com/playlist?list=PLmkV2uU8kdpIvFZhuZjFI4hEHXdvxzTDw linkinden takip ediyoruz. <br>
• https://controllerstech.com/how-to-interface-mpu6050-gy-521-with-stm32/ ve https://youtu.be/3xSWTsK8YNY adresinden örnek uygulamayı inceleyebiliriz. <br>
• https://cbsakademi.ibb.istanbul/imu-nedir/ linkinden IMU hakkında bilgi edinebiliriz. <br>
• https://youtu.be/UxABxSADZ6U, https://youtu.be/7VW_XVbtu9k, https://youtu.be/IE7GtyrnLFY, https://ozgurayik.com/2022/01/24/ivme-olcer-ve-jiroskop-verilerini-kullanarak-pitch-roll-ve-yaw-acilarinin-hesaplanmasi/ ve https://selcukozbayraktar.com/2021/08/25/ivme-ve-gyro-sensorleri-ile-egim-acilarinin-olculmesi/ linklerinde ivmeölçer ve jiroskop verilerinden roll, pitch ve yaw değerlerin nasıl hesaplandığı anlatılıyor. <br>

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="400"> <br>
• Connectivity başlığı altından I2C seçip Mode ekranından I2C seçiyoruz. <br>
<img src="image\image-3.png" width="250"> <br>
• I2C için Speed Mode olarak Fast Mode seçimi yapıyoruz. <br>
<img src="image\image-4.png" width="250"> <br>

## Kod Kısmı

• Core sekmesinin Inc klasörüne mpu6050.h adında Header File, Src klasörüne mpu6050.c adında Source File ekliyoruz. <br>
• Eğer ayrı klasör sekmesinde tutmak istersek bunun için Include dosyasını tanımlamak gerekiyor. <br> 
Bunun için proje dosyasına sağ tıklayıp Properties tıklanır. <br> 
C/C++ Build kısmından Settings kısmına gelinir ve buradan Tool Settings kısmından MCU GCC Compiler kısmından Include paths tıklanır ve buradan dosya yolu eklenir. <br>
• Header File içerisinde fonksiyon tanımları, veri türü tanımları ve makrolar barındırır. <br>
<img src="image\image-5.png" width="250"> <br>
• Kütüphanelerde I2C kullanabilmek için main içerisinde tanımlananı kütüphanemize ekliyoruz. <br> 
Bunu tanımlayabilmek için öncesinde stm32f4xx_hal.h kütüphanesini dahil ediyoruz. <br>
• Mpu6050.h kütüphanesi için bunları ekliyoruz. <br>
<img src="image\image-6.png" width="250"> <br>
• Mpu6050.c kütüphanesi için Mpu6050.h kütüphanesini ekliyoruz. <br>
• Öncelikle HAL_I2C_IsDeviceReady() fonksiyonu ile hedef cihazın iletişim için hazır olup olmadığını kontrol ederiz. <br> 
• Mpu6050.h dosyasında fonksiyonu tanımlarız. <br>
• Mpu6050.c kütüphanesinde fonksiyonu yazarız. <br>
<img src="image\image-7.png" width="400"> <br>
• Yolladığımız i değişkeni eğer eşleşirse break komutu ile if yapısından çıkar. <br>
Fonksiyonu çalıştırmak için Main.c dosyasına ekleriz. <br>
<img src="image\image-8.png" width="200"> <br>
• 8. satıra break point koyuyoruz ve debug tıklıyoruz. i değişkenimize Expression kısmında bakıyoruz. Tarama işlemi sonrası bize 208 sayısını gösteriyor yani D0 adresi olduğunu gösterir. <br> 
• Fonksiyon bize 8 bitlik yani 7 bitlik adresin 1 bit sola kaydırılmış halinin sonucunu verir. <br> 
• Aslında bulduğum adres, 0x68 adresin 1 bit kaydırılmış halidir. <br> 
Daha sonra bulduğum adresi tanımlıyorum. <br>
<img src="image\image-9.png" width="550"> <br>
• Datasheet kısmından sensörün register haritasını inceliyoruz. <br>
• Register adresleri tanımlıyoruz. <br>
<img src="image\image-10.png" width="250"> <br>
• Yazacağımız fonksiyonları tanımladık. <br>
<img src="image\image-11.png" width="250"> <br>
<img src="image\image-12.png" width="450"> <br>
• WHO_AM_I, cihazın kimliğini doğrulamak için kullanılır. <br> 
• Adresin 0x68 olup olmadığını kontrol ediyoruz. <br> 
<img src="image\image-13.png" width="500"> <br>
<img src="image\image-14.png" width="450"> <br>
• Sensörü uyandırmak için PWR_MGMT_1 registarına yazıyoruz. <br>
<img src="image\image-15.png" width="500"> <br>
<img src="image\image-16.png" width="450"> <br>
• Örnekleme hızını ayarlamamız gerekiyor. <br> 
• Sample Rate = Gyroscope Output Rate / (1 + SMPLRT_DIV) <br>
• Gyroscope Output Rate 8kHz'dir ve biz örnekleme hızı 1 kHz olacak şekilde formülden SMPLRT_DIV değerini 7 olarak ayarlıyoruz. <br>
<img src="image\image-17.png" width="450"> <br>
<img src="image\image-18.png" width="450"> <br>
<img src="image\image-19.png" width="150"> <br>
<img src="image\image-20.png" width="150"> <br>
<img src="image\image-21.png" width="450"> <br>
<img src="image\image-22.png" width="450"> <br>
<img src="image\image-23.png" width="150"> <br>
<img src="image\image-24.png" width="150"> <br>
<img src="image\image-25.png" width="500"> <br>
• Sensörün ayarlama kısımlarını tamamladık böylece okuma kısmına geçebiliriz. <br>
• Okuma işlemini her registerdan ayrı ayrı 1 byte okuyabiliriz ya da hep birlikte 6 byte okuma yapabiliriz. <br>
<img src="image\image-26.png" width="450"> <br>
<img src="image\image-27.png" width="300"> <br>
• Yukarıda gösterildiği gibi,  X Ekseni boyunca ivme verileri ACCEL_XOUT_H ve ACCEL_XOUT_L olarak saklanır. Bu 2 byte'ı 16 bitlik bir tamsayı değerinde birleştirmemiz gerekiyor. <br>
• ACCEL_X = (ACCEL_XOUT_H << 8 | ACCEL_XOUT_L)<br>
• Örnek verirsek ACCEL_XOUT_H = 11101110 ve ACCEL_XOUT_L = 10101010 olsun. Sonuç olarak bize 16 bit değeri olarak 1110111010101010 bunu verir. <br>
• g değerleri elde etmek için  ± 2g aralığını seçtiğimizden RAW değerlerini  16384 'a bölmemiz gerekir. <br>
<img src="image\image-28.png" width="500"> <br>
<img src="image\image-29.png" width="450"> <br>
<img src="image\image-30.png" width="250"> <br>
• dps ( °/s ) cinsinden değerleri elde etmek için  ± 250 °/s aralığını seçtiğimizden RAW değerlerini 131.0'a bölmemiz gerekir. <br>
<img src="image\image-31.png" width="500"> <br>
• Main.c içerisine aşağıdakileri yazıp istediğimiz değerleri okuyoruz. <br>
<img src="image\image-32.png" width="150"> <br>
<img src="image\image-33.png" width="150"> <br>
<img src="image\image-34.png" width="200"> <br>
<img src="image\image-35.png" width="250"> <br>
<img src="image\image-36.png" width="300"> <br>
• İvmeölçer verisinden aşağıdaği formülü kullanarak roll ve pitch hesabı yapıyoruz. <br>
• Bu formülü anlamak için https://www.nxp.com/files-static/sensors/doc/app_note/AN3461.pdf linkteki belgede üç eksenli ivmeölçer ile eğim algılama hakkında yazılmış yazıdan yararlanabiliriz <br>
<img src="image\image-37.png" width="250"> <br>
<img src="image\image-38.png" width="150"> <br>
<img src="image\image-39.png" width="200"> <br>
<img src="image\image-40.png" width="200"> <br>
<img src="image\image-41.png" width="450"> <br>

---


<br>


> ## **ADXL345**

## Teori

• Kart hakkında bilgi edinmek için https://learn.adafruit.com/adxl345-digital-accelerometer linki okunabilir. <br>
• https://controllerstech.com/adxl345-accelerometer-using-stm32/, https://youtu.be/m2iDrosoc2g ve https://youtu.be/KMhbV1p3MWk örnek uygulamayı inceleyebiliriz. <br>
• Kütüphane için https://github.com/CanGuveren/ADXL345-STM32 bu linki kaynak alıp kütüphane kullanabiliriz. <br> 
<img src="image\image-42.png" width="200"> <br>
<img src="image\image-43.png" width="500"> <br>
• CS pinine VDD I/O bağlandığında yani besleme hattı çekilirse ADXL345 sensörü I2C modundadır. <br>
<img src="image\image-44.png" width="200"> <br>
• Standart (100kHz) ve Hızlı (400kHz) veri aktarım modlarını  destekler. <br>
• Tek veya çok byte okuma ve yazma desteklenir. <br>
<img src="image\image-45.png" width="650"> <br>
• ALT ADDRESS pini high olduğunda 7 bit I2C adresi 0x1D'dir ve ardından R/W biti gelir. Yazma için 0x3A, okuma için 0x3B kullanılır. <br>
• ALT ADDRESS pini topraklanarak alternatif I2C adresi 0x53 yapılır ve ardından R/W biti gelir. Yazma için 0xA6, okuma için 0xA7 kullanılır. <br>
• Uygun çalışma için pull-up direnci gerekebilir. Bununla ilgili ayrıntılara https://antrak.org.tr/genel/i2c-bus-veri-ileti%C5%9Fim-standartlar%C4%B1/ linkinden öğrenebiliriz. <br>

## Konfigürasyon Kısmı

<img src="image\image-46.png" width="400"> <br>
<img src="image\image-47.png" width="400"> <br>
• Connectivity başlığı altından I2C seçip Mode ekranından I2C seçiyoruz. <br> 
<img src="image\image-48.png" width="300"> <br>
• I2C için Speed Mode olarak Fast Mode seçimi yapıyoruz. <br>
<img src="image\image-49.png" width="300"> <br>

## Kod Kısmı

<img src="image\image-50.png" width="200"> <br>
<img src="image\image-51.png" width="300"> <br>
<img src="image\image-52.png" width="400"> <br>
<img src="image\image-53.png" width="600"> <br>
• HAL_I2C_IsDeviceReady() fonksiyonu ile hedef cihazın iletişim için hazır olup olmadığını kontrol ederiz. <br> 
• Bu fonksiyona hal_i2c.c dosyasından ulaşırız. <br> 
• DevAddres kısmına hedefteki aygıtın adresi yazılır. <br> 
Yazılırken 7 bitlik adresin sola kaydırılarak 8 bitlik yazılmasını istiyor o yüzden tanımlarken ona göre yazmamız gerekir. <br>
• Trials deneme sayısını ifade eder. <br>
• Yolladığımız i değişkeni eğer eşleşirse break komutu ile if yapısından çıkar. <br>
• 92.satır ve 214.satıra break point koyuyoruz ve debug tıklıyoruz. Ardından i değişkenimizi Watch Expression kısmına ekliyoruz. Tarama işlemi bitirdiğinde bize 166 sayısını gösteriyor yani A6 adresi olduğunu gösterir. <br> 
<img src="image\image-54.png" width="100"> <br>
• Aslında bulduğum adres, 0x53 adresin 1 bit kaydırılmış halidir. 0x53 adresi 0101 0011 iken 0xA6 adresi 1010 0110'dır. <br>
• 0x53 << 1 tanımı adresi 1 bit sola kaydır demektir. <br>
• Önce bulduğum adresi tanımlıyorum. <br>
<img src="image\image-55.png" width="250"> <br>
• İlk kullanıma hazır hale getiriyoruz.
• Datasheet kısmından sensörün register haritasını inceliyoruz. <br>
<img src="image\image-56.png" width="450"> <br>
<img src="image\image-57.png" width="250"> <br>
• DEVID, cihazın yolunda olup olmadığını söyler. DEVID kaydı 0xE5 olarak tutulur yani 0x00 adresi bize 0xE5 olarak dönerse cihaz kullanıma hazır demektir. <br>
• Bunun için okuma fonksiyonu yazıyoruz. Fonksiyonda tanımlamalarımız okuyacağı register ve kaç byte veri okuyacağımızı yazıyoruz. <br>
<img src="image\image-58.png" width="400"> <br>
<img src="image\image-59.png" width="200"> <br>
• ADXL345_Init içerisinde ADXL345_Read fonksiyonu kullanarak 0x00 adresinden 1 byte'lık veriyi okuyacağımı söylüyorum. <br>
• ADXL345_Read fonksiyonunda okuma yapabilmek için yani Master cihaza bağlı Slave cihazın ilgili adresini okuyabilmek için HAL_I2C_Mem_Read fonksiyonunu kullanıyorum. <br>
<img src="image\image-60.png" width="550"> <br>
<img src="image\image-61.png" width="200"> <br>
<img src="image\image-62.png" width="850"> <br>
• Devadress, Slave cihaz için tanımladığımız adres oluyor. <br> 
• MemAddress, Slave cihazda okuma yapacağım adres oluyor. Biz buraya 0x00 yazmak yerine fonksiyonda yazdığımız rRegister yazıyoruz. <br>
• MemAddSize, okuma yapılacak adresin boyutunu yazıyoruz. 8 bit veri okuması yapacağımızdan 1 yazıyoruz. <br>
• pData, datayı yazacağımız yeri yazıyoruz. Biz myDatas yazıyoruz. <br> 
• Ardından Size kısmına 6 elemanlı dizi olarak tanımladığımdan 6 yazıyoruz. <br>
<img src="image\image-63.png" width="150"> <br>
• Size, gönderilecek veri miktarı yazıyoruz. <br>
• 223.satır ve 224.satıra break point koyuyoruz ve debug tıklıyoruz. Ardından myDatas değişkenimizi Expression kısmına ekliyoruz. Tarama işlemi bitirdiğinde bize 229 sayısını gösteriyor yani E5 adresi olduğunu gösterir. Böylece ilk kullanıma hazır olduğu anlamına gelir. <br>
<img src="image\image-64.png" width="350"> <br>
• Her sensörün control registerı vardır. Bizim bunu önce default olarak sıfırlarız sonra kendimize göre işlem yaparız. <br>
• Öncelikle Power_CTL registerını sıfırlıyoruz. Bunun için yazma yapacağımdan ADXL345_Write fonksiyonu tanımlıyoruz. <br>
<img src="image\image-65.png" width="400"> <br>
<img src="image\image-66.png" width="450"> <br>
• HAL_I2C_Master_Transmit() fonksiyonuyla yazdırma işlemi yapıyoruz. pData kısmına datayı yazacağımız yer olan data dizisini yazıyoruz. Size olarak dizi iki elemanlı olduğundan 2 yazıyoruz. <br>
<img src="image\image-67.png" width="650"> <br>
• Bu şekilde Power_CTL registerı sıfırlanmış oldu. <br>
<img src="image\image-68.png" width="200"> <br>
• Şimdi Power_CTL registerına işlem yapmak için hangi bitleri set ya da reset yapacağımıza karar veriyoruz. <br>
• Links Bit ile AUTO_SLEEP Bit 0 yapıyoruz. <br>
• Measure Bit, 0 olduğunda bekleme moduna geçerken 1 olduğunda okuma moduna geçiyor. Biz bu biti 1 yapıyoruz. <br>
• Sleep Bit, 0 olduğunda normal mod durumuna getirirken 1 olduğunda uyku moduna geçer. Biz bu biti 0 yapıyoruz. <br>
• Wakeup Bit, uyku modunda okuma sıklığını ifade eder. Tabloya göre işlem yaparız. Biz uyku modunda çalışmadığımızdan D1 ve D0 bitini 0 yapıyoruz. <br>
<img src="image\image-69.png" width="150"> <br>
<img src="image\image-70.png" width="350"> <br>
• g değerini ayarlıyoruz. <br>
<img src="image\image-71.png" width="250"> <br>
• Data_Format registerında Range kısmını ayarlıyoruz. +-4g için D1 bitini 0, D0 bitini 1 yapıyoruz. <br>
<img src="image\image-72.png" width="150"> <br>
<img src="image\image-73.png" width="350"> <br>
• Veriler 0x32 ile 0x37 registerları arasında toplamda 6 adet saklanır. Bunlar her biri 8 bit olmak üzere DATA X0, DATA X1, DATA Y0, DATA Y1, DATA Z0, DATA Z1'dir. <br> 
• 16 bitlik eksen okumasını ikiye ayırıyor. O yüzden her eksenden iki çıktı veriyor. X ekseni için DATA X0 en düşük 8 bitlik iken DATA X1 en yüksek 8 bittir. <br>
<img src="image\image-74.png" width="250"> <br>
• x, y ve z verilerini 16 bit değişkene atayıp birleştireceğiz. <br>
<img src="image\image-75.png" width="150"> <br>
• 0x32 adresinden 6 adet byte verisini okumaya başlıyorum. <br>
• Bunlar myDatas dizisinin 0. ve 1. olan byte x; 2. ve 3.byte y; 4. ve 5.byte z verisini temsil eder. <br> 
• x, y ve z verilerin en yüksek 8 biti yazarken 0.bitten 8 bit kaydırarak yazıyoruz. Böylece 8 bit ayrılmış iki veriyi 16 bitte birleştirmiş olduk. <br>
• 6 byte veri okuyacağımdan Size kısmı önceden kalan 1 yerine numberOfBytes olarak değiştiriyorum. <br>
• Buraya 6'da yazabilirdik fakat döngü içerisinde zaten yazdık. <br>
<img src="image\image-76.png" width="550"> <br>
• Her g range'in katsayı değeri vardır. <br> 
• +-4g için 7.8mg/LSB katsayısını alırsak bunu önce mg'dan g'ye dönüştürürüz ve eksenleri 0.0078 ile çarparız ya da 128 LSB/g katsayısını alırsak eksenleri 128'e böleriz. <br>
<img src="image\image-77.png" width="600"> <br>
<img src="image\image-78.png" width="300"> <br>
<img src="image\image-79.png" width="200"> <br>
<img src="image\image-80.png" width="450"> <br>


---


<br>
