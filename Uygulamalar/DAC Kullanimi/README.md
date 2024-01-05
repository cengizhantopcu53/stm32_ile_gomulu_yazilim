
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

