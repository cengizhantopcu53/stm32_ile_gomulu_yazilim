
# Timer Değer Okuma

> ## **REGISTER**

## Konfigürasyon Kısmı

• TIM2'nin clock hattı APB1'e gidiyor. <br>
<img src="image\image-1.png" width="250"> <br>
<img src="image\image-2.png" width="450"> <br>
• 0.biti 1 yapıyoruz. <br>
<img src="image\image-3.png" width="200"> <br>
<img src="image\image-4.png" width="200"> <br>
<img src="image\image-5.png" width="450"> <br>
• Sayma yapacağımdan saymayı başlatmak için 0.biti aktif ediyoruz. Sayma başlayacağından bu işlem fonksiyonun en son satırında olmalı. <br>
<img src="image\image-6.png" width="400"> <br>
<img src="image\image-7.png" width="150"> <br>
• Saymanın yönünü belirliyoruz. Biz yukarı doğru saymasını istiyoruz. <br>
<img src="image\image-8.png" width="400"> <br>
<img src="image\image-9.png" width="150"> <br>
• 5. ve 6.biti 0 yapıyoruz. <br>
<img src="image\image-10.png" width="400"> <br>
• Sistem clock 168MHz ayarlamıştık ve TIM2 clock veri yolu ise 42MHz'dir fakat bunun 2 katı değeri alıyorlardı yani 84MHz'dir. Biz bunu bölmek istiyorsak ayarlayabiliyoruz. Biz bölmüyoruz. <br>
<img src="image\image-11.png" width="400"> <br>
• 8. ve 9.biti 0 yapıyoruz. <br>
<img src="image\image-12.png" width="150"> <br>
<img src="image\image-13.png" width="450"> <br>
• Slave mode çalışmayacağız. <br>
<img src="image\image-14.png" width="400"> <br>
<img src="image\image-15.png" width="150"> <br>
<img src="image\image-16.png" width="450"> <br>
• Sayma dolduğunda sıfırlaması için 1 yaparız. 0.biti 1 yapıyoruz. <br>
<img src="image\image-17.png" width="400"> <br>
<img src="image\image-18.png" width="150"> <br>
<img src="image\image-19.png" width="450"> <br>
• Prescalaer bizim sayısının en üst seviyesini belirler. <br> 
• Sayma işlemi 0'dan başlamayıp 1'den başladığından 1 eksiğini alarak yazarız. <br> 
• TIM2 clock hızı 84MHz olduğundan bunu kaça bölmeliyim diye soruyoruz. Bu clock hız için 42000'e bölüyoruz. Bu sayı da 41999 sayısı yapıyor. Bu değer bizim prescaler ön bölücü değerimiz oluyor. <br>
<img src="image\image-20.png" width="400"> <br>
<img src="image\image-21.png" width="150"> <br>
<img src="image\image-22.png" width="450"> <br>
<img src="image\image-23.png" width="400"> <br>
<img src="image\image-24.png" width="150"> <br>
• 84MHz'i 42000'e böldüğümüzde 2000 sayısı yapıyor. Bu değer auto-reload oluyor. Bunun 1 eksiğini yazıyoruz. <br>
• Böylece 1 sn'de 2000'e kadar sayıyor. <br>
• 2000 değeri yazmasaydık sonuç 2000 Hz olacağından sonucunda 0,0005s yani 1 sn=1000 ms olmak üzere 0,5 ms olacaktı. Aslında bu 0,5 ms değeri bizim period süremiz oluyor. <br> 
• Böylece 2000 kere 0,5 ms aralıklarla sayma yapacak sonucunda 1000ms yani 1 sn sonra taşma olacak. <br>
• RCC ve TIM için yazdığımız fonksiyonlar aşağıdaki gibidir. <br>
<img src="image\image-25.png" width="360"> <br>
<img src="image\image-26.png" width="450"> <br>

## Kod Kısmı

<img src="image\image-27.png" width="450"> <br>
• CNT registerı sayma işlemini burada tutuyor. <br>
• Değişken atayıp bu değişkene CNT registerına eşitliyoruz. <br>
<img src="image\image-28.png" width="150"> <br>
<img src="image\image-29.png" width="200"> <br>
<img src="image\image-30.png" width="450"> <br>

---

<br>
