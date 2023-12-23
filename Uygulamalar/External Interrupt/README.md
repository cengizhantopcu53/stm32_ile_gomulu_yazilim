
# External Interrupt

> ## **HAL**

## Giriş

• Interrupt olduğunda gittiği yerdeki fonksiyon içerisindeki kod çalışır. Buradan çıktığı zaman kaldığı yere geri döner. <br> 
• [Örnek](https://www.youtube.com/watch?v=hikauabT0bM) uygulamayı inceleyebiliriz. <br>


## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="500"> <br>
• NVIC kısmından işaretlediğimiz pinlerin kesme işlemi yapabilmesi için Enabled kısımı işaretliyoruz. <br>
<img src="image\image-3.png" width="500"> <br>


## Kod Kısmı

• it.c dosyasına gittiğimizde 3 adet kesme fonksiyonları oluşturulmuştur. <br>
<img src="image\image-4.png" width="250"> <br>
<img src="image\image-5.png" width="250"> <br>
<img src="image\image-6.png" width="250"> <br>
• İçerisinde yazılı olana Ctrl + Space tıkladığımızda hal_gpio.c dosyaya götürür. Burada en son satırda Callback fonksiyonunu çağırır. <br> 
<img src="image\image-7.png" width="300"> <br>
• Buna aynı şekilde gittiğimizde bu dosya üzerinde yer alır. Biz main.c dosyamızda bu fonksiyonu kullanıp kesme işlemi yapacağız. <br>
<img src="image\image-8.png" width="500"> <br>
• While döngüsü ile tüm pinleri yaktık ve count değişkeni değerinde delay süresi verdik. <br> 
<img src="image\image-9.png" width="200"> <br>
<img src="image\image-10.png" width="300"> <br>
• Count değişkenini kesme olduğunda her buton için ayrı delay süreleri verdik. <br>
<img src="image\image-11.png" width="300"> <br>


---

<br>


> ## **REGISTER**

## Konfigürasyon Kısmı

• External Interrup'ın clock hattı APB2'ye gidiyor. <br>
<img src="image\image-12.png" width="250"> <br>
<img src="image\image-13.png" width="400"> <br>
<img src="image\image-14.png" width="300"> <br>
• 14.pini 1 yapıyoruz. <br>
<img src="image\image-15.png" width="300"> <br>
• 3 tane interrupt pini kullanacağımızdan öncelikle bunları aktif edip, öncelik sırası belirlemeliyiz. <br>
• core_cm4.h kütüphanesinde bu fonksiyonları görebiliriz. <br> 
<img src="image\image-16.png" width="400"> <br>
• İkinci değere öncelik numarası yazıyoruz. Ne kadar küçük olursa öncelik sıralamasında önde olur. <br>
<img src="image\image-17.png" width="450"> <br>
<img src="image\image-18.png" width="200"> <br>
• Interrupt olarak mı event olarak mı kullanacağımızı belirliyoruz. Interrupt olarak kullanacağız. <br>
<img src="image\image-19.png" width="450"> <br>
<img src="image\image-20.png" width="300"> <br>
• İlk 3 pine 1 yazıyoruz. <br>
<img src="image\image-21.png" width="150"> <br>
• Alçalan kenar mı yükselen kenar mı kullanacağımızı belirliyoruz. Yükselen kenar kullanacağız. <br>
<img src="image\image-22.png" width="420"> <br>
<img src="image\image-23.png" width="300"> <br>
• İlk 3 pine 1 yazıyoruz. <br>
<img src="image\image-24.png" width="150"> <br>
• Butonları external interrupt için aktif etmemiz gerekiyor. <br> 
• Buton için A portunu kullanıyoruz. <br> 
<img src="image\image-25.png" width="450"> <br>
<img src="image\image-26.png" width="300"> <br>
<img src="image\image-27.png" width="150"> <br>
• RCC, GPIO ve EXTI için yazdığımız fonksiyonlar aşağıdaki gibidir. <br>
<img src="image\image-28.png" width="350"> <br>
<img src="image\image-29.png" width="400"> <br>
<img src="image\image-30.png" width="350"> <br>


## Kod Kısmı

• İlk önce while döngüsünde tüm ledleri açıyoruz. <br>
<img src="image\image-31.png" width="250"> <br>
• Pinde kesme olup olmadığını öğrenmemiz gerekiyor. Bitte değer olduğunda kesmeye girmiş oluyor. Tekrar 1 yazarak bayrağı indiriyoruz. <br>
<img src="image\image-32.png" width="500"> <br>
<img src="image\image-33.png" width="350"> <br>
• Eğer kesmeye giriliyorsa 2 saniye boyunca belirlediğimiz ledi açıp diğerlerini kapatıyoruz. <br> 
<img src="image\image-34.png" width="250"> <br>
<img src="image\image-35.png" width="250"> <br>
<img src="image\image-36.png" width="250"> <br>


---

<br>