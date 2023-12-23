
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


> ## **REGISTER**

## Konfigürasyon Kısmı

• RCC için eklemeler yaptık. <br>
<img src="image\image-9.png" width="450"> <br>
• AHB, APB1 ve APB2 için clock hızını böldük. <br>
<img src="image\image-10.png" width="400"> <br>
<img src="image\image-11.png" width="150"> <br>
<img src="image\image-12.png" width="400"> <br>
<img src="image\image-13.png" width="150"> <br>
<img src="image\image-14.png" width="400"> <br>
<img src="image\image-15.png" width="150"> <br>
<img src="image\image-16.png" width="450"> <br>
• Kaldırılan bayrakları temizliyoruz. <br>
<img src="image\image-17.png" width="300"> <br>
<img src="image\image-18.png" width="150"> <br>
<img src="image\image-19.png" width="300"> <br>
<img src="image\image-20.png" width="150"> <br>
• RCC için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-21.png" width="350"> <br>
• GPIO için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-22.png" width="400"> <br>
<img src="image\image-23.png" width="450"> <br>
• Çoklu ADC okuması yapılacaksa scan yani tarama aktif edilmesi gerekir. <br>
<img src="image\image-24.png" width="400"> <br>
<img src="image\image-25.png" width="150"> <br>
• Çözünürlük için 12-bit kullanıyoruz. <br>
<img src="image\image-26.png" width="400"> <br>
<img src="image\image-27.png" width="150"> <br>
<img src="image\image-28.png" width="450"> <br>
• ADC aktif etmek için ilk bit 1 yapıldı. <br>
<img src="image\image-29.png" width="300"> <br>
Sürekli okuma yapmasını istiyoruz. <br>
<img src="image\image-30.png" width="400"> <br>
• DMA mod ile çalışacağız. <br>
<img src="image\image-31.png" width="400"> <br>
• DMA'nın sürekli çalışması için 1 yapıyorum. <br>
<img src="image\image-32.png" width="400"> <br>
• 10.bit 1 yapılır. <br>
<img src="image\image-33.png" width="400"> <br>
• Çevrim başlaması için 30.biti 1 yapıyoruz. <br>
<img src="image\image-34.png" width="400"> <br>
<img src="image\image-35.png" width="150"> <br>
• Kaç farklı kanaldan çevrim yapacağımızı belirtmemiz gerekiyor. Biz sadece A portun 0.bitinden yani 1 kanal'dan okuma yapacağım. <br>
<img src="image\image-36.png" width="500"> <br>
• SQR1 için 20.biti 0 yaparak 1 tane kanal olduğunu belirtiyoruz. <br>
<img src="image\image-37.png" width="400"> <br>
<img src="image\image-38.png" width="150"> <br>
• SQR3 için SQ1 kısmına kanal numarasını yazıyoruz. <br>
<img src="image\image-39.png" width="300"> <br>
<img src="image\image-40.png" width="150"> <br>
<img src="image\image-41.png" width="450"> <br>
<img src="image\image-42.png" width="400"> <br>
<img src="image\image-43.png" width="150"> <br>
• ADC için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-44.png" width="400"> <br>
• DMA'nın clock hattı AHB'ye gidiyor. <br>
<img src="image\image-45.png" width="200"> <br>
<img src="image\image-46.png" width="450"> <br>
<img src="image\image-47.png" width="150"> <br>
<img src="image\image-48.png" width="150"> <br>
• ADC için DMA2 kullanıyoruz. Tabloya baktığımızda biz burada Stream 4'ü seçiyoruz. <br>
<img src="image\image-49.png" width="500"> <br>
<img src="image\image-50.png" width="500"> <br>
• 0.bit 0 olduğunda konfigürasyon yapmaya imkan tanıyor. Bunun için okuma yapacağız. <br>
<img src="image\image-51.png" width="400"> <br>
• 1 olduğu sürece 0 olana kadar bekliyoruz. 0 olunca döngüden çıkıp alt satıra geçecek. <br>
<img src="image\image-52.png" width="250"> <br>
• ADC'den RAM'e yazacağız bunun için Peripheral-to-memory seçiyoruz. <br>
<img src="image\image-53.png" width="300"> <br>
<img src="image\image-54.png" width="150"> <br>
• Sürekli transfer için 8.biti 1 yapıyoruz. <br>
<img src="image\image-55.png" width="400"> <br>
<img src="image\image-56.png" width="150"> <br>
• Adresin değişmesini istemiyoruz. 9.biti 0 yapıyoruz. <br>
<img src="image\image-57.png" width="400"> <br>
<img src="image\image-58.png" width="150"> <br>
<img src="image\image-59.png" width="400"> <br>
<img src="image\image-60.png" width="150"> <br>
• Peripheral ve Memory için data boyutunu 32 bit belirliyoruz. <br>
<img src="image\image-61.png" width="400"> <br>
<img src="image\image-62.png" width="400"> <br>
<img src="image\image-63.png" width="200"> <br>
Önceliği çok yüksek yapıyoruz. <br>
<img src="image\image-64.png" width="300"> <br>
<img src="image\image-65.png" width="200"> <br>
• Kanal seçimi için 0.kanal yapıyoruz. <br>
<img src="image\image-66.png" width="300"> <br>
• Kaç tane çevresel birimden yani ADC'den okuma yaptığımızı belirtiyoruz. <br>
<img src="image\image-67.png" width="500"> <br>
<img src="image\image-68.png" width="400"> <br>
• Biz bir tane birimden yani ADC1'den okuma yapıyoruz. <br>
<img src="image\image-69.png" width="150"> <br>
• Okuma yaptığımız Çevresel birimin adresini yazıyoruz. <br>
<img src="image\image-70.png" width="450"> <br>
<img src="image\image-71.png" width="400"> <br>
<img src="image\image-72.png" width="450"> <br>
<img src="image\image-73.png" width="400"> <br>
<img src="image\image-74.png" width="250"> <br>
• Değişkenin adresini yazıyoruz. <br>
<img src="image\image-75.png" width="450"> <br>
<img src="image\image-76.png" width="400"> <br>
<img src="image\image-77.png" width="150"> <br>
<img src="image\image-78.png" width="250"> <br>
<img src="image\image-79.png" width="450"> <br>
<img src="image\image-80.png" width="400"> <br>
<img src="image\image-81.png" width="200"> <br>
• Stream4'ü fonksiyonun en son satırında aktif ediyoruz. <br>
<img src="image\image-82.png" width="200"> <br>
• Adres tanımları fonksiyonun ortalarında yazmak yerine while döngüsünün sonrasında yazdık. <br>
• DMA için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-83.png" width="500"> <br>

## Kod Kısmı

• ADC için çevrimi DMA'dan sonra başlatmak için 80.satıra tekrar yazdık. <br>
<img src="image\image-84.png" width="250"> <br>

---

<br>