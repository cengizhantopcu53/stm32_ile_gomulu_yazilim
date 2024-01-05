
# Harici Led Yakma

> ## **HAL**

## Konfigürasyon Kısmı

• Kullanıcı butonu C portun 13.pinine bağlı. <br>
<img src="image\image-1.png" width="400"> <br>
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

---

<br>

