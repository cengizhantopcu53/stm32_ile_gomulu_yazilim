
# USB ile Sanal Port Kullanımı

> ## **HAL**

## Giriş

• https://controllerstech.com/send-and-receive-data-to-pc-without-uart-stm32-usb-com/ linkten örnek uygulamayı inceleyebiliriz. <br>
• USB Device modunda Communication Device Class (Virtual Com Port) sınıfını kullanarak seri port haberleşmesi yapacağız. <br>

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
• Connectivity kısmında USB_OTG_FS'den Mode kısmı olarak Device_Only seçimi yapıyoruz. <br>
<img src="image\image-2.png" width="300"> <br>
• Parameter Settings kısımlarında bir değişiklik yapmıyoruz.  <br>
<img src="image\image-3.png" width="300"> <br>
• Middleware kısmından USB_DEVICE seçeneği aktif oluyor ve buradan kullanacağımız sınıfı seçiyoruz. Seri port haberleşmesi için CDC sınıfını seçiyoruz. <br>
<img src="image\image-4.png" width="300"> <br>
• Parameter Settings kısımlarında bir değişiklik yapmıyoruz.  <br>
<img src="image\image-5.png" width="300"> <br>
• Device Descriptor kısmında da bir değişiklik yapmıyoruz. <br>
<img src="image\image-6.png" width="300"> <br>
• USB ile bilgisayar ile bağlantısını yaptığımızda Aygıt yöneticisine bakıp hangi porta bağlı olduğuna bakabiliriz. <br>
<img src="image\image-7.png" width="300"> <br>


## Kod Kısmı

• Veri göndermek veya almak için gerekli işlevler USB_DEVICE -> APP ->  usbd_cdc_if.c dosyasında bulunur.  <br>
• Gönderme işlemi için CDC_Transmit_FS() fonksiyonu kullanır ve bu fonksiyon gönderilecek veri ile veri uzunluğu olmak üzere iki parametre alır. <br>
<img src="image\image-8.png" width="450"> <br>
• Gerekli olan kütüphaneler main.c dosyasına eklenir. <br>
<img src="image\image-9.png" width="200"> <br>
<img src="image\image-10.png" width="200"> <br>
<img src="image\image-11.png" width="250"> <br>
<img src="image\image-12.png" width="400"> <br>
• Alma işlemi için CDC_Receive_FS() fonksiyonu kullanır ve bu fonksiyon gönderilecek veri ile veri uzunluğu olmak üzere iki parametre alır. <br>
<img src="image\image-13.png" width="450"> <br>
• CDC_Transmit_FS() fonksiyonu global iken CDC_Receive_FS() fonksiyonu statik olarak tanımlandığından bulunduğu dosyanın dışında kullanılamaz. <br>
• Kullanacağımız değişkenleri main.c dosyasında tanımlıyoruz. <br>
<img src="image\image-14.png" width="150"> <br>
• Main.c'de tanımladığımız rx_buff değişkenini usbd_cdc_if.c dosyasına extern etmemiz gerekiyor. <br>
<img src="image\image-15.png" width="200"> <br>
• CDC_Receive_FS() fonksiyonu içerisine önce veriyi alacağımız değişkeni memset fonksiyonu ile temizleyerek başlıyoruz. <br>
İçeriğine sıfır yazıyoruz. <br>
• Sonra gelen verinin uzunluğunu buluyoruz ve rx_buff değişkenimize gelen verinin içerisinde bulunduğu Buf değişkeni Len uzunluğu kadar kopyalıyoruz. <br>
• En son Buf değişkenini sıfırlıyoruz. <br>
<img src="image\image-16.png" width="400"> <br>
• Gelen veriye göre led yakma işlemini gerçekleştiriyoruz. <br>
<img src="image\image-17.png" width="450"> <br>
<img src="image\image-18.png" width="400"> <br>






---

<br>

