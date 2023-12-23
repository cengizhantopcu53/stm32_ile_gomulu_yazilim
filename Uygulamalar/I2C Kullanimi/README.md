
# I2C Kullanımı

> ## **REGISTER**

## Konfigürasyon Kısmı

• RCC için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-1.png" width="300"> <br>
• I2C2 kullanacağız. Clock hattı APB1'e gidiyor. <br>
<img src="image\image-2.png" width="250"> <br>
<img src="image\image-3.png" width="450"> <br>
• 22.biti 1 yapıyoruz. <br>
<img src="image\image-4.png" width="250"> <br>
<img src="image\image-5.png" width="150"> <br>
• I2C2 hangi porta bağlı olduğunu öğrenmek için datasheet'e bakarız. B portun 10. ve 11.pinine bağlıymış. <br>
<img src="image\image-6.png" width="500"> <br>
• Portlar AHB1 kısmına gidiyor. <br>
<img src="image\image-7.png" width="250"> <br>
<img src="image\image-8.png" width="450"> <br>
• Buton için A portunu, I2C2 için B portunu kullandığımızdan bu portları aktif ediyoruz. <br>
<img src="image\image-9.png" width="250"> <br>
<img src="image\image-10.png" width="200"> <br>
• B portun 10. ve 11. pinleri I2C için kullanacağımızdan bu pinleri alternate function mode yapıyoruz. <br>
<img src="image\image-11.png" width="450"> <br>
<img src="image\image-12.png" width="400"> <br>
<img src="image\image-13.png" width="250"> <br>
• Kullanacağımız çevresel birim olan I2C kullanacağımızı belirteceğiz. <br>
<img src="image\image-14.png" width="450"> <br>
<img src="image\image-15.png" width="450"> <br>
• Biz 10 ve 11. pinleri kullandığımızdan high olanı kullanıyoruz. <br>
<img src="image\image-16.png" width="350"> <br>
• Seçtiğimiz I2C2 çevresel birimi hangi AF'de olduğunu bilmek için Reference Manuel kitapçığına bakıyoruz. <br>
<img src="image\image-17.png" width="400"> <br>
• I2C, AF7'de bulunuyor. Böylece pinlere AF4 için olan 0100 tanımlaması yapacağız. <br>
• AFR'nin High ve Low olduğunuda belirtmemiz gerekiyor. High kullandığımızdan  1 yazıyoruz. <br>
<img src="image\image-18.png" width="200"> <br>
<img src="image\image-19.png" width="450"> <br>
<img src="image\image-20.png" width="400"> <br>
<img src="image\image-21.png" width="200"> <br>
• GPIO için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-22.png" width="550"> <br>
<img src="image\image-23.png" width="450"> <br>
<img src="image\image-24.png" width="400"> <br>
<img src="image\image-25.png" width="150"> <br>
<img src="image\image-26.png" width="450"> <br>
<img src="image\image-27.png" width="400"> <br>
• 100 kHz çalışmak için 0x28 yazınız demiş. <br>
<img src="image\image-28.png" width="150"> <br>
<img src="image\image-29.png" width="450"> <br>
<img src="image\image-30.png" width="400"> <br>
• Geri besleme döngüsünün maksimum süresi için I2C_CR2'nin FREQ[5:0] bitlerine 0x08 yazdığımızdan TRISE[5:0] bitlerine 0x09 yazmalıyız. <br>
<img src="image\image-31.png" width="150"> <br>
<img src="image\image-32.png" width="450"> <br>
<img src="image\image-33.png" width="400"> <br>
• I2C2 aktif edildi. <br>
<img src="image\image-34.png" width="150"> <br>
• I2C için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-35.png" width="400"> <br>


## Kod Kısmı

• I2C için Write ve Read fonksiyonlarını yazmaya başlıyoruz. <br>
• I2C_Write fonksiyonuna adress ve data olmak üzere 2 parametre yazıyoruz. <br>
<img src="image\image-36.png" width="400"> <br>
• Start yolluyorum. <br>
<img src="image\image-37.png" width="150"> <br>
<img src="image\image-38.png" width="450"> <br>
• Yolladığım startı kontrol ediyorum. <br>
<img src="image\image-39.png" width="400"> <br>
• While döngüsü 1 olduğu sürece çalışır. <br> 
• SB biti 1 olana dek 0 olacağından ve döngünün çalışabilmesi için başına "!" işareti koyarak tersliyoruz. <br> 
• 0.bit 1 olduğunda döngüden çıkacaktır. <br>
<img src="image\image-40.png" width="200"> <br>
• Slave tarafına adresini yolluyoruz. Bizim kullandığımız cihazın adresi 0x4E'dir. <br>
<img src="image\image-41.png" width="450"> <br>
<img src="image\image-42.png" width="400"> <br>
<img src="image\image-43.png" width="150"> <br>
• Slave adresin gönderimini beklememiz lazım. Bunun için kontrol yapıyoruz. <br>
<img src="image\image-44.png" width="450"> <br>
<img src="image\image-45.png" width="400"> <br>
<img src="image\image-46.png" width="200"> <br>
• Master oldu mu onu kontrol ediyoruz. <br>
<img src="image\image-47.png" width="450"> <br>
<img src="image\image-48.png" width="400"> <br>
<img src="image\image-49.png" width="200"> <br>
• TXE'nin boş olmasını bekliyoruz. <br>
<img src="image\image-50.png" width="450"> <br>
<img src="image\image-51.png" width="400"> <br>
<img src="image\image-52.png" width="200"> <br>
<img src="image\image-53.png" width="100"> <br>
<img src="image\image-54.png" width="450"> <br>
<img src="image\image-55.png" width="400"> <br>
<img src="image\image-56.png" width="200"> <br>
<img src="image\image-57.png" width="450"> <br>
<img src="image\image-58.png" width="400"> <br>
<img src="image\image-59.png" width="150"> <br>
• I2C için yazdığımız Write fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-60.png" width="450"> <br>
• Her butona bastığımızda cihaza sırayla adres yolluyor. <br> 
<img src="image\image-61.png" width="250"> <br>


---

<br>
