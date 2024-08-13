# Sinyal Okuma

> ## **BUTTON**

## Teori

• Buton, GPIOA üzerindeki PA0 pinine bağlıdır ve bu pin, yükselen kenar kesmesi (bir butona basıldığında) üretmek üzere ayarlanmıştır. Ayrıca, zamanlayıcı (TIM2) kesmesi de yapılandırılmıştır. Zamanlayıcı, butona basıldığında başlatılır ve süre sonunda durdurulur. Bu süreç, buton durumunun belirlenmesi için kullanılır.

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="450"> <br>
<img src="image\image-2.png" width="550"> <br>
• İşlemci clock hızı 48Mhz yapıldı.  <br>
• TIM2, APB1 clock hattına bağlı burada clock hızı 48Mhz'dir. <br> 
• 50 ms sonra taşma oluşturacak şekilde Prescaler ve Period değerleri belirlendi. <br> 
<img src="image\image-3.png" width="400"> <br>
<img src="image\image-4.png" width="300"> <br>
<img src="image\image-5.png" width="500"> <br>


## Kod Kısmı

• Buton için NULL, START ve STOP için tanımlama ve sonrasında başlangıç ataması yaptık. <br>
<img src="image\image-6.png" width="150"> <br>
<img src="image\image-7.png" width="250"> <br>
• GetBtnState() fonksiyonu GPIO pininden buton durumunu okuyup bu duruma göre bir Btn_State tipinde değer döndürüyor. <br>
• buttoncounter adında statik bir uint8_t tipinde sayaç değişkeni tanımlanmıştır. Bu değişken fonksiyon çağrıları arasında değerini korur (yani her fonksiyon çağrısında sıfırlanmaz). <br>
• Butonun durumunu okur eğer buton basılı ise, buttoncounter değişkenini bir arttırır. <br>
• buttoncounter'ın çift veya tek olma durumuna göre farklı sonuçlar döndürür. Eğer buttoncounter çift ise, fonksiyon STOP değerini döndürür. Tek ise START değerini döndürür. <br>
<img src="image\image-8.png" width="500"> <br>
• Bir kesme işlevi içindeki bu yapı buton debouncing yani sıçramayı engelleme gerektirdiğinden kullanıldı. <br>
• Buton basıldığında sayacın değeri 0 ise, zamanlayıcı başlar ve belirli bir süre sonunda ilgili işlemler gerçekleştirilir. <br>
<img src="image\image-9.png" width="400"> <br>
• Doğru zamanlayıcıdan kesme geldiyse, buton okuma fonksiyonu çağrılarak mevcut buton durumu alınır ve state değişkenine atanır. <br>
• Zamanlayıcı durdurulur ve sayaç değeri 0'a sıfırlanır. 
Bu, zamanlayıcının bir sonraki tetikleme için hazır hale getirilmesini sağlar. <br>
<img src="image\image-10.png" width="500"> <br>
• Buton geçişlerinde START durumunda Led yanıyor, tekrar basıldığında STOP durumuna geçip ledi söndürüyor. <br>
<img src="image\image-11.png" width="500"> <br>


---


<br>




