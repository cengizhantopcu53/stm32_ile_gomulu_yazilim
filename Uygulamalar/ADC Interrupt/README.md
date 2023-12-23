
# ADC Interrupt 

> ## **HAL**

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="500"> <br>
• ADC1 için IN0, Temperature Sensor Channel ve Vrefint Channel seçimi yaptık. <br>
<img src="image\image-3.png" width="150"> <br>
• Scan Mode ile Continuous Mode Enabled yapılır. <br>
<img src="image\image-4.png" width="400"> <br>
• ADC1 için 3 kanal olduğundan her biri için rank işlemi yapılır. <br>
<img src="image\image-5.png" width="400"> <br>
• ADC2 için IN1 seçimi yapılır. <br>
• ADC2 için tek kanal olduğundan Scan Mode seçimi yapılmaz. <br> 
<img src="image\image-6.png" width="400"> <br>
<img src="image\image-7.png" width="400"> <br>
• Interrupt kullanacağımızdan NVIC Settings kısmından Enabled yapılır. <br> 
• Sadece ADC1 değil ADC2 ve ADC3 için interrupts Enabled yapılmış olur. <br> 
<img src="image\image-8.png" width="500"> <br>


## Kod Kısmı

• ADC için Interrupt Mode kullanımı yapacağız. <br>
<img src="image\image-9.png" width="500"> <br>
<img src="image\image-10.png" width="400"> <br>
• Keseme olduğunda it.c dosyasındaki ADC_IRQHandler fonksiyonuna gelir ve fonksiyon içerisindeki HAL_ADC_IRQHandler fonksiyonunu çalıştırır. <br> 
• Bizim main.c dosyasında hazır olarak yazılmıştır. <br>
<img src="image\image-11.png" width="250"> <br>
• 1578.satırdaki Callback fonksiyonu main.c dosyasında kullanarak Interrupt'a girdiğinde yani ADC çevrimi tamamlandığında bu fonksiyon çalışmaya başlayacaktır. <br>
<img src="image\image-12.png" width="400"> <br>
• İçerisine önce hangi ADC'yi çalıştırdığını öğrenmemiz gerekiyor. Bunun için _HAL_ADC_GET_FLAG kullanmamız gerekiyor. <br>
<img src="image\image-13.png" width="450"> <br>
<img src="image\image-14.png" width="700"> <br>
• Temperature için Datasheet kısmından aşağıdaki tabloları kullanıyoruz. <br>  
<img src="image\image-15.png" width="500"> <br>
• Aşağıdaki formül üzerinden hesaplıyoruz. <br>
<img src="image\image-16.png" width="400"> <br>
<img src="image\image-17.png" width="400"> <br>
<img src="image\image-18.png" width="200"> <br>
<img src="image\image-19.png" width="500"> <br>
<img src="image\image-20.png" width="400"> <br>

---

<br>

