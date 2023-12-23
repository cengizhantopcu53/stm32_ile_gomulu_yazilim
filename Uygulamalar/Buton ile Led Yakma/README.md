
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


> ## **REGISTER**

## Konfigürasyon Kısmı

• Öncelikle RCC ve GPIO ayarlarını yapıyoruz. <br>
<img src="image\image-7.png" width="350"> <br>
• GPIO ayarlarını aşağıdaki gibi düzelttik.
• A portunu da kullanacağımdan A ve D portlarını RCC clocklarını aktif ediyoruz. <br>
<img src="image\image-8.png" width="350"> <br>
<img src="image\image-9.png" width="400"> <br>

## Kod Kısmı

• Buton için A0 pini için okuma yapacağız. Burada ilk biti kullanacağız. While döngüsü içinde bir if yapısı içinde eğer okuma yapılırsa while döngüsüne girer ve okuma yani butona basma devam ediyorsa count değişkenini 1 arttırır. <br> 
• Buradaki delay ark olayından dolayı kullandık. <br>
<img src="image\image-10.png" width="500"> <br>
<img src="image\image-11.png" width="400"> <br>
<img src="image\image-12.png" width="200"> <br>
• Count ve delay için globalde tanıttık. <br>
• While döngüsünün içi 1 olduğu sürece çalışmaya devam eder ancak 0 olduğunda döngüden çıkıp alt satıra geçer. <br>
<img src="image\image-13.png" width="200"> <br>
• Count değişkenini kalanı 0 ise yani 2.defa basıldığında ledi söndürken kalan 1 olduğunda yani 1.defa basıldığı durumda ledi yakacaktır. <br> 
<img src="image\image-14.png" width="350"> <br>

---

<br>