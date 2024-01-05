
# DMA ile ADC Değer Okuma

> ## **HAL**

## Giriş

• ADC'den okuduğumuz değerleri, hiç CPU'ya uğratmadan DMA ile direk RAM'e yazacağız. <br>

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="450"> <br>
<img src="image\image-3.png" width="450"> <br>
• DMA ayarları için Add diyoruz. Ardından Stream, Direction ve Priority için seçenekleri seçiyoruz. <br> 
• Daha sonra Direction kısmından seçtiğimiz Peripheral ve Memory için adres değişikliği için Increment Adress için işaretliyoruz. <br> 
Ardından gönderilecek data boyutu belirliyoruz. 12bit çalıştığımızdan 16 bitlik olan Half Word seçimi yapıyoruz. <br>
<img src="image\image-4.png" width="450"> <br>

## Kod Kısmı

<img src="image\image-5.png" width="500"> <br>
• pData kısmına veriyi tutacağımız değişkeni yazıyoruz. Bizim değişken 16 bit olarak tanımladığımızdan dönüştürmemiz gerekiyor. <br>
• Length ile kaç tane veri okuyacağımızı yazıyoruz. <br>
<img src="image\image-6.png" width="500"> <br>
<img src="image\image-7.png" width="200"> <br>
<img src="image\image-8.png" width="400"> <br>

---


<br>


