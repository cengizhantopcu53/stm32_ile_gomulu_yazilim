
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


