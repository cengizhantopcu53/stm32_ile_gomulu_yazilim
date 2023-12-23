
# DAC Kullanımı

> ## **HAL**

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="400"> <br>
• DAC kısmından OUT1 seçiyoruz. <br> 
<img src="image\image-3.png" width="150"> <br>
• Output Buffer, gürültü engelleme; Trigger tetiklemedir. <br> 
• Biz bunları aynı şekilde bırakıyoruz. <br>
<img src="image\image-4.png" width="250"> <br>


## Kod Kısmı

• DAC için toplam iki kanal var. <br>
<img src="image\image-5.png" width="400"> <br>
• DAC kullanmak için iki modumuz var. Biri Polling diğeri DMA'dır. <br> 
• Biz Polling Mode kullanıyoruz. <br>
<img src="image\image-6.png" width="450"> <br>
<img src="image\image-7.png" width="500"> <br>
• DAC için değer verme yapacağımızdan GetValue değil SetValue kullanacağız. Çıkışın voltaj değeri ile oynamış oluyoruz. <br>
<img src="image\image-8.png" width="650"> <br>
• Data kısmına 12 bit çalıştığımızdan 0-4095 arasında değer yazabiliriz. <br>
<img src="image\image-9.png" width="200"> <br>
<img src="image\image-10.png" width="300"> <br>
<img src="image\image-11.png" width="500"> <br>

---

<br>


> ## **REGISTER**

## Konfigürasyon Kısmı

• RCC için 5.satırda 0x00030000 yerine 0x00010000 yazdık. <br> 
• HSERDY kısmı sadece okunabilir olduğundan o biti 1 yapmıyoruz. <br>
<img src="image\image-12.png" width="300"> <br>
• ADC'nin clock hattı APB1'e gidiyor. <br>
<img src="image\image-13.png" width="200"> <br>
<img src="image\image-14.png" width="450"> <br>
<img src="image\image-15.png" width="250"> <br>
<img src="image\image-16.png" width="150"> <br>
<img src="image\image-17.png" width="450"> <br>
• DAC işlemi için channel1 kullanacağımızdan 0.biti aktif etmemiz gerekiyor. <br> 
<img src="image\image-18.png" width="400"> <br>
<img src="image\image-19.png" width="150"> <br>
• Yazılımsal tetikleme kullanmadığımızdan 0. biti 0 yapıyoruz. <br>
<img src="image\image-20.png" width="500"> <br>
<img src="image\image-21.png" width="400"> <br>
<img src="image\image-22.png" width="200"> <br>
• Channel1 için 12 bit sağa ya da sola veya 8 bit sağa kaydedebiliriz. <br>
<img src="image\image-23.png" width="500"> <br>
<img src="image\image-24.png" width="500"> <br>
<img src="image\image-25.png" width="500"> <br>
• 12 bit sağa kaydedeceğiz. <br>
<img src="image\image-26.png" width="400"> <br>
<img src="image\image-27.png" width="500"> <br>
• DAC1  A4 pini olduğundan portunu sadece A portunu aktif ediyoruz. <br>
<img src="image\image-28.png" width="200"> <br>
• RCC ve DAC1 için yazdığımız fonksiyonlar aşağıdaki gibidir. <br>
<img src="image\image-29.png" width="300"> <br>
<img src="image\image-30.png" width="500"> <br>


## Kod Kısmı

<img src="image\image-31.png" width="200"> <br>
• Her i değeri arttığında i değeri kadar kaydetmiş oluyor. <br> 
• A4 pinine led bağladığımızda i değeri arttıkça voltaj değeri artacağından parlaklık artar. <br>
• 4095 olduğunda yani 0x00000FFF olduğunda tam parlaklıkta yanar. <br>
<img src="image\image-32.png" width="200"> <br>

---

<br>