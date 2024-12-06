
# Harici Led Yakma

> ## **HAL**

#### Polling

## Konfigürasyon Kısmı

<img src="image\image-2.png" width="400"> <br>
<img src="image\image-3.png" width="500"> <br>

## Kod Kısmı

• RCC için bir değişiklik yapmadığımızdan fonksiyon içeriği aynıdır. <br> 
• hal_gpio.c kısmından ReadPin fonksiyonlarına ulaşabiliriz. <br>
<img src="image\image-4.png" width="400"> <br>
Buton için count değişkeni atıyoruz. <br>
<img src="image\image-5.png" width="150"> <br>
• Okuma yaptığında yani butona bastığımızda if yapısının içine girer ve while ile kullanıcının eli butona basılı olup olmadığını kontrol ederiz. Elini çektiğinde count değerini 1 arttırıyor. <br>
• Count değerin modunu aldığımızda 0 iken RESET, 1 iken SET durumundadır. <br>
<img src="image\image-6.png" width="550"> <br>

<br>

#### Interrupt

## Giriş

• Interrupt olduğunda gittiği yerdeki fonksiyon içerisindeki kod çalışır. Buradan çıktığı zaman kaldığı yere geri döner. <br> 
• [Örnek](https://www.youtube.com/watch?v=hikauabT0bM) uygulamayı inceleyebiliriz. <br>


## Konfigürasyon Kısmı

<img src="image\image-7.png" width="400"> <br>
<img src="image\image-8.png" width="500"> <br>
• NVIC kısmından işaretlediğimiz pinlerin kesme işlemi yapabilmesi için Enabled kısımı işaretliyoruz. <br>
<img src="image\image-9.png" width="500"> <br>


## Kod Kısmı

• it.c dosyasına gittiğimizde 3 adet kesme fonksiyonları oluşturulmuştur. <br>
• Önce kesme işleyicisi (IRQ handler) çalışır ve bu işleyicinin içinde belirli olayları işleyen callback fonksiyonları tetiklenir. <br> 
<img src="image\image-10.png" width="250"> <br>
<img src="image\image-11.png" width="250"> <br>
<img src="image\image-12.png" width="250"> <br>
• İçerisinde yazılı olana Ctrl + Space tıkladığımızda hal_gpio.c dosyaya götürür. Burada en son satırda Callback fonksiyonunu çağırır. <br> 
<img src="image\image-13.png" width="300"> <br>
• Buna aynı şekilde gittiğimizde bu dosya üzerinde yer alır. Biz main.c dosyamızda bu fonksiyonu kullanıp kesme işlemi yapacağız. <br>
<img src="image\image-14.png" width="500"> <br>
• While döngüsü ile tüm pinleri yaktık ve count değişkeni değerinde delay süresi verdik. <br> 
<img src="image\image-15.png" width="200"> <br>
<img src="image\image-16.png" width="300"> <br>
• Count değişkenini kesme olduğunda her buton için ayrı delay süreleri verdik. <br>
<img src="image\image-17.png" width="300"> <br>

---

<br>
