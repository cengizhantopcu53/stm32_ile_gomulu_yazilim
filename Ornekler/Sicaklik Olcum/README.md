
# Sıcaklık Ölçümü

> ## **NTC**

## Teori

• NTC ve PTC hakkında bilgi edinmek için [linkteki](https://www.youtube.com/watch?v=IaQdL_WJaQs) videoyu izleyebiliriz. <br>
• Örnek Uygulamalar için [makale](https://mehmettopuz.net/stm32-ve-ntc-sensoru-ile-sicaklik-olcme/.html) ve [videodan](https://www.youtube.com/watch?v=ShkSSeY8ta8) yararlanabiliriz. <br>
• NTC, sıcaklık arattıkça direnci azalan termistördür. <br>
• Direnç değişimleri doğrusal olmadığından Stein-Hart modelini kullanacağız.<br> 
• Formüldeki R değeri NTC'nin sıcaklık anında ölçülen direnç değeridir. <br>
<img src="image\image-3.png" width="250"> <br>
• R değerini bulmak için NTC'ye bağlanan pull-down direnç sonrası oluşan gerilim bölücü voltaj değeri ile ADC ile bulduğumuz voltaj değerlerini eşitleriz.<br> 
• Kullandığımız NTC'nin değeri 10K'dır ve pull-down direnci de 10K'dır. Ayrıca 3.3V ile beslenmektedir. Kullanacağımız işlemcide ADC 12 bittir. Bu bilgilere göre aşağıdaki hesap yapılır.<br>
```
Vout = 3.3*10000/(10000*R)
Vadc = analogValue*(3.3/4095)
``` 
Sadeleştirilme yapıldığı zaman aşağıdaki formül ile direnç değerini bulabiliriz.<br>
```
R = (40950000 / analogValue) - 10000
``` 
• A, B ve C katsayısı değerlerini [linkteki](https://www.thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html) hesap programını kullanarak buluyoruz. <br> 
• Kendi kullandığımız NTC için üç farklı sıcaklıkta direnç değerini okuyup tabloya yazıyoruz ve bize döndürdüğü katsayı değerlerini formülde kullanıyoruz.<br> 
<img src="image\image-2.png" width="600"> <br>


## Konfigürasyon Kısmı

<img src="image\image-1.png" width="450"> <br>
• Sıcaklık değerini görüntülemek için USART kullanıyoruz. <br>
<img src="image\image-15.png" width="600"> <br>
• Sürekli okuma yapmak için Continuous Conversion Mode Enable yapılır. <br>
<img src="image\image-14.png" width="500"> <br>


## Kod Kısmı

• Hesaplama yapmak için math.c kütüphanesini ekliyoruz.<br>
<img src="image\image-6.png" width="250"> <br>
<img src="image\image-5.png" width="250"> <br>
<img src="image\image-6.png" width="300"> <br>
<img src="image\image-4.png" width="550"> <br>
• Aşağıdaki fonksiyon ile formülü kullanarak sıcaklık değerini elde ediyoruz.
<img src="image\image-11.png" width="950"> <br>
• Sıcaklık değeri her zaman doğru vermeyebilir bazen anlık olarak ani yüksek değerde veri yollayablilir. <br>
• Bunu çözmenin en kolay yolu ortalama almaktır.<br>
<img src="image\image-10.png" width="350"> <br>
<img src="image\image-8.png" width="250"> <br>
<img src="image\image-12.png" width="400"> <br>
• Seri Port Çizici sonucu aşağıdadır. Mavi olan temp değişkeni, kırmızı olan ortalama değişkenini temsil ediyor.<br>
<img src="image\image-13.png" width="1000"> <br>

---

<br>

