
# Motor Sürme

> ## **L298N**

## Teori

https://www.sailteknoloji.com/arduino/147-l298n-voltaj-regulatorlu-cift-motor-surucu.html, https://www.instructables.com/L298N-Motor-Driver-Controller-Board/, https://www.direnc.net/l298n-cift-tam-kopru-surucu-entegresi-multiwatt15 linklerinden kullandığımız motor sürücü hakkında detaylı bilgilere ulaşabiliriz. <br>
ENA, IN1 ve IN2 ile ifade edilenler sol motor, ENB, IN3 ve IN4 ile ifade edilenler sağ motordur. <br>
ENA ve ENB ile motorun hızı, IN1, IN2, IN3 ve IN4 ile yön ifade edilir. <br>
Yön ifadesi için IN ifadelerine 1 veya 0 değerlerini vermemiz gerekiyor. Bunun için datasheetteki tabloya bakıyoruz. <br>
<img src="image\image-1.png" width="300"> <br>
İleri gitmesi için ilk kısım HIGH ikinci kısım LOW yapılmalı eğer tersi yapılırsa geri döner. <br>
Durması için iki kısmın aynı olması gerekir yani ikisi ya LOW olacak ya da HIGH olacak. <br>
[Linkte](https://gelecegiyazanlar.turkcell.com.tr/konu/egitim/arduino-301/bluetooth-kontrollu-arac-yapimi) yazılmış kodu inceleyebiliriz. 
Yaptığımız bu kod yapısı ile Uzaktan Kontrollü Robot yapabiliriz. <br>


## Konfigürasyon Kısmı

<img src="image\image-2.png" width="450"> <br>
<img src="image\image-3.png" width="450"> <br>
<img src="image\image-4.png" width="450"> <br>
Timers kısmından TIM4 seçimi yapılır. Ardından Mod kısmından kanal seçimi yapılır. <br>
<img src="image\image-5.png" width="400"> <br>
<img src="image\image-6.png" width="300"> <br>
<img src="image\image-7.png" width="300"> <br>

## Kod Kısmı

Motorların hızını %70 oranında çalıştırıyoruz. <br>
<img src="image\image-8.png" width="175"> <br>
Yön fonksiyonlarını yazarken sol ve sağ motorların ileri döndürülmesi için IN1 ile IN3 HIGH, IN2 ve IN4 LOW yapılmalıdır eğer motorun ters gitmesi için tam tersi yapılması gerekir. <br>
Sağa dönme yapılacaksa sol motor kısmın IN1 HIGH, IN2 LOW yapılarak ileri döndürülmesi sağlanırken sağ motorun IN3 ve IN4 LOW yapılarak durdurulur eğer sola dönme yapılacaksa tam tersi yapılması gerekir. <br>
<img src="image\image-9.png" width="400"> <br>
<img src="image\image-10.png" width="300"> <br>
<img src="image\image-11.png" width="400"> <br>


## Logic Analyzer Kısmı

<img src="image\image-12.png" width="500"> <br>
---

<br>

