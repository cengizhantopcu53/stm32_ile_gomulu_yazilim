
# Harici Led Yakma

> ## **HAL**

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="450"> <br>
• Timers kısmından TIM4 seçimi yapılır. Ardından Mod kısmından kanal seçimi yapılır. <br>
<img src="image\image-3.png" width="450"> <br>
• Period değerimize göre kanal çıkışlarına Pulse değeri yazacağız. <br> 
• Period kısmını Duty Cycle en fazla 100 olduğundan Period kısmına 100-1 olarak gireriz. Yani Period 100 ve Pulse değeri 50 girersek aslında %50 Duty Cycle olur. <br>
• 10 kHZ için işlem sonucunda Prescaler 90 girilir. <br>
• 1 kHZ = 1000Hz <br>
<img src="image\image-4.png" width="400"> <br>
<img src="image\image-5.png" width="300"> <br>
<img src="image\image-6.png" width="300"> <br>
• Mode 1 ile Mode 2 arasındaki fark High ile Low durumların tersi olmasıydı. <br>
• Mode 1 durumunda kanal %25 ise %25'te High %75'te Low oluyordu. <br>
%75 olduğunda %25'te Low %75'te High oluyor. <br>
• Fast Mode durumun Disable olduğu zaman saymaya yaparken üst limite kadar saydıktan sonra 0'a doğru azala azala inerken Enabled olduğu zaman 0'a doğru birden iner. <br>


## Kod Kısmı

• hal_tim.c dosyasından Timer'ı PWM ile başlatmamız gerekiyor. <br>
<img src="image\image-7.png" width="500"> <br>
<img src="image\image-8.png" width="300"> <br>
<img src="image\image-9.png" width="150"> <br>
<img src="image\image-10.png" width="600"> <br>
• Compare kısmına Pulse değerini yazıyoruz. <br>
<img src="image\image-11.png" width="400"> <br>


---

<br>


> ## **REGISTER**

## Konfigürasyon Kısmı

• RCC için yazdığımız fonksiyonlar aşağıdaki gibidir. <br>
<img src="image\image-12.png" width="300"> <br>
• GPIO için çıkışlarını alternatif fonksiyon yapıyoruz. <br>
<img src="image\image-13.png" width="450"> <br>
• Kart üzerindeki ledleri kullanıyoruz. 24., 26., 28. ve 30.biti 1 yapıyoruz. <br>
<img src="image\image-14.png" width="400"> <br>
<img src="image\image-15.png" width="300"> <br>
• Alternatif fonksiyon ile kast edilen pinin çevresel birimlerden I2C, SPI  olarak kullanılacağını belirtiyor. Biz burada TIM4 için kullanacağımızı belirteceğiz. <br>
<img src="image\image-16.png" width="450"> <br>
<img src="image\image-17.png" width="450"> <br>
• Low ile 0 ile 7.pinler arası iken high 8 ile 15.pinler arasıdır. Biz 12, 13,14 ve 15. pinleri kullandığımızdan high olanı kullanıyoruz. <br>
<img src="image\image-18.png" width="300"> <br>
• Seçtiğimiz TIM4 çevresel birimi hangi AF'de olduğunu bilmek için Reference Manuel kitapçığına bakıyoruz. <br>
<img src="image\image-19.png" width="400"> <br>
• TIM4, AF2'de bulunuyor. Böylece pinlere AF2 için olan 0010 tanımlaması yapacağız. <br>
• AFR'nin High ve Low olduğunda belirtmemiz gerekiyor. AFR'ye Ctrl ile sağ tıklarız. AFR'nin parantez içinde 2 elemanlı dizi olduğunu gösterir. 0.eleman low, 1.eleman high temsil eder. Biz 1 yazıyoruz. <br>
<img src="image\image-20.png" width="600"> <br>
<img src="image\image-21.png" width="400"> <br>
• GPIO için yazdığımız fonksiyon aşağıdaki gibidir. <br>
<img src="image\image-22.png" width="600"> <br>
• TIM4'nin clock hattı APB1'e gidiyor. <br>
<img src="image\image-23.png" width="300"> <br>
<img src="image\image-24.png" width="450"> <br>
<img src="image\image-25.png" width="200"> <br>
<img src="image\image-26.png" width="300"> <br>
<img src="image\image-27.png" width="450"> <br>
• Sayma yapacağımdan saymayı başlatmak için 0.biti aktif ediyoruz. Sayma başlayacağından bu işlem fonksiyonun en son satırında olmalı. <br>
<img src="image\image-28.png" width="400"> <br>
<img src="image\image-29.png" width="150"> <br>
• Saymanın yönünü belirliyoruz. Biz yukarı doğru saymasını istiyoruz. <br>
<img src="image\image-30.png" width="400"> <br>
<img src="image\image-31.png" width="150"> <br>
• 5. ve 6.biti 0 yapıyoruz. <br>
<img src="image\image-32.png" width="400"> <br>
<img src="image\image-33.png" width="150"> <br>
• Sistem clock 168MHz ayarlamıştık ve TIM4 clock veri yolu ise 42MHz'dir fakat bunun 2 katı değeri alıyorlardı yani 84MHz'dir. Biz bunu bölmek istiyorsak ayarlayabiliyoruz. Biz bölmüyoruz. <br>
<img src="image\image-34.png" width="400"> <br>
• 8. ve 9.biti 0 yapıyoruz. <br>
<img src="image\image-35.png" width="150"> <br>
• PWM aslında capture/compare mode kısmına giriyor. <br>
<img src="image\image-36.png" width="450"> <br>
• 1.kanal için output yapıyoruz yani ilk 2 bit 0 yapıyoruz. <br>
<img src="image\image-37.png" width="400"> <br>
• Mod olarak PWM mode 1 seçiyoruz. Bunun için bite 110 yazıyoruz. <br>
<img src="image\image-38.png" width="400"> <br>
• 2.kanal için output yapıyoruz. 8. ve 9.biti 0 yapıyoruz. <br>
<img src="image\image-39.png" width="400"> <br>
• 2.kana'lın modunu 1.kanal'da yaptığımız gibi PWM Mode 1 yapıyoruz. <br>
<img src="image\image-40.png" width="250"> <br>
<img src="image\image-41.png" width="300"> <br>
<img src="image\image-42.png" width="450"> <br>
• CCMR2 ile bu sefer kanal 3 ve 4 için yapıyoruz. Kanal 1 ve 2 ile yaptıklarımızın aynısını yapıyoruz. <br>
<img src="image\image-43.png" width="400"> <br>
<img src="image\image-44.png" width="300"> <br>
<img src="image\image-45.png" width="450"> <br>
• Çıkışları Enabled yapıyoruz. <br> 
0., 4., 8. ve 12. bitleri 1 yapıyoruz. <br>
<img src="image\image-46.png" width="400"> <br>
<img src="image\image-47.png" width="200"> <br>
<img src="image\image-48.png" width="300"> <br>
<img src="image\image-49.png" width="450"> <br>
• Prescalaer bizim sayısının en üst seviyesini belirler. <br> 
• Sayma işlemi 0'dan başlamayıp 1'den başladığından 1 eksiğini alarak yazarız. <br>
• TIM4 clock hızı 84MHz olduğundan bunu kaça bölmeliyim diye soruyoruz. Bu clock hız için 42000'e bölüyoruz. Bu sayı da 41999 sayısı yapıyor. <br> 
<img src="image\image-50.png" width="400"> <br>
<img src="image\image-51.png" width="150"> <br>
• 84MHz'i 42000'e böldüğümüzde 2000 sayısı yapıyor. Bu değer auto-reload oluyor. Bunun 1 eksiğini yazıyoruz. <br>
<img src="image\image-52.png" width="450"> <br>
<img src="image\image-53.png" width="400"> <br>
<img src="image\image-54.png" width="150"> <br>
• Böylece 1 sn'de 2000'e kadar sayıyor. <br>
• Pinlere atayacağımız paslar CCR1 12.pin, CCR2 13.pin, CCR3 14.pin ve CCR4 15.pin içindir. <br>
<img src="image\image-55.png" width="500"> <br>
• Bunlara atayacağımız değerler en fazla Auto-reload değeri kadar olabilir. <br>
<img src="image\image-56.png" width="150"> <br>
• TIM için yazdığımız fonksiyonlar aşağıdaki gibidir. <br>
<img src="image\image-57.png" width="700"> <br>

## Kod Kısmı

• Pindeki ledlerin durumu 12.pin %25, 13.pin %50, 14.pin %75, 15.pin %100 parlaklıkta yanıyor. <br>
<img src="image\image-58.png" width="150"> <br>

---

<br>