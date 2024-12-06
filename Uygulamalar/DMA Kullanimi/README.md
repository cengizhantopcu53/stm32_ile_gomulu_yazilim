# DMA Kullanımı

> ## **HAL**

## Teori
• DMA'nın CPU'yu serbest bırakarak veri transferini nasıl gerçekleştirdiğini gösteren basit bir örnektir. Burada DMA, bir LED'i açıp kapatarak GPIO pinine veri yazıyor ve böylece CPU, bu işlemler sırasında diğer görevlerle meşgul olabilir. <br>

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="450"> <br>
• **DMA1 Channel 1** ile DMA kanalı yapılandırılıyor. <br>
• Direction, **Memory to Memory** transfer olarak ayarlandı. <br>
• Peripheral Increment ve Memory Increment, peripheral ve memory için adresin otomatik olarak artıp artmayacağını belirler, biz artmayacak şekilde olmasını istiyoruz bu sebeple bir seçim yapmadık. <br>
• Data Alignment, hem peripheral hem de bellek veri hizalaması **Word** olarak ayarlandı. <br>
• Mode, DMA'nın **Normal** modda çalışacağı belirtilmiş; bu modda transfer işlemi bir defa gerçekleştirilir. <br>
• Priority, **Low** öncelikli olarak ayarlanmış. <br>
<img src="image\image-2.png" width="450"> <br>

## Kod Kısmı

• Kodda led_data isimli bir dizi tanımlanmış.  <br>
• Bu dizi içinde GPIO_PIN_8 ve onun ters çevrilmiş hali bulunuyor. Bu, GPIO_PIN_8 pininin sırayla SET ve RESET yapılması için kullanılıyor. <br>
<img src="image\image-3.png" width="400"> <br>
• main fonksiyonunda sonsuz bir döngüde, DMA kullanarak led_data[1] değeri GPIOC->BSRR adresine yazılıyor. Bu, PC8 pinini sıfırlıyor (LED kapalı). <br>
• HAL_DMA_PollForTransfer fonksiyonu ile DMA transferinin bitmesi bekleniyor ve ardından 500 ms bekleniyor <br>
• Aynı işlem bu sefer led_data[0] ile yapılıyor, bu da PC8 pinini SET yapıyor <br>
• Yine DMA transferi tamamlanınca 500 ms bekleniyor ve döngü bu şekilde devam ediyor. <br>
<img src="image\image-4.png" width="700"> <br>

<br>

# Interrupt 

## Konfigürasyon Kısmı

• DMA1 Channel 1 için Interrupt aktif edilir.  <br>
<img src="image\image-5.png" width="700"> <br>

## Kod Kısmı

• Benzer çalışmayı Interrupt ile yapmış olduk.  <br>
<img src="image\image-6.png" width="700"> <br>

---

<br>

