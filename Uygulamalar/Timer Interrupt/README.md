
# Timer Interrupt

> ## **HAL**

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="400"> <br>
<img src="image\image-2.png" width="400"> <br>
• Timers kısmından TIM2 seçimi yapılır. Ardından Mod kısmından sadece Clock Source kısmını Internal Clock yaparız. <br>
<img src="image\image-3.png" width="300"> <br>
• Sistem clock 180MHz ayarlamıştık ve TIM2 clock veri yolu ise 45MHz'dir. fakat bunun 2 katı değeri alıyorlardı yani 90MHz'dir. <br>
<img src="image\image-4.png" width="250"> <br>
• Daha sonra Parameter Settings'den TIM2 1 saniye aralıklarla tekrarlı şekilde çalıştıracak değerler girilir. <br> 
Sayma işlemi 0'dan başlamayıp 1'den başladığından 1 eksiğini alarak yazarız. <br> 
• Prescalaer bizim sayısının en üst seviyesini belirler. Burası 16 bit olduğundan en fazla 65535 yazabilirim. <br>
TIM2 clock hızı 90MHz olduğundan bunu kaça bölmeliyim diye soruyoruz. Bu clock hız için 45000'e bölüyoruz. Bu sayı da 44999 sayısı yapıyor. Bu değer bizim prescaler ön bölücü değerimiz oluyor. <br>
• 90MHz'i 45000'e böldüğümüzde 2000 sayısı yapıyor. Bu değer Auto-reload oluyor. Bunun da 1 eksiğini yazıyoruz. <br>
Counter Period kısmında her seferinde taşma işlemi bittikten sonra tekrar bunu yükler bu sebeple yükleyeceği değeri yazarız. <br> 
• Sayma şeklini Up belirleyip yukarı doğru sayıyor. <br> 
• Auto-reload preload kısmında Enabled diyerek sayma bittiğinde başa dönmesini sağlarız. <br>
• 2000 değeri yazmasaydık sonuç 2000 Hz olacağından sonucunda 0,0005s yani 1 sn=1000 ms olmak üzere 0,5 ms olacaktı. Aslında bu 0,5 ms değeri bizim period süremiz oluyor. <br> 
• Böylece 2000 kere 0,5 ms aralıklarla sayma yapacak sonucunda 1000ms yani 1 sn sonra taşma olacak. <br>
<img src="image\image-5.png" width="350"> <br>
<img src="image\image-6.png" width="300"> <br>
<img src="image\image-7.png" width="300"> <br>
• NVIC Settings kısmından TIM2 global interrupt Enabled yapılır. Bununla her güncellemede, sayıyı bitirmede bir interrupt oluşmasını sağlıyoruz. <br>
<img src="image\image-8.png" width="450"> <br>

## Kod Kısmı

• hal_tim.c dosyasından Timer'ı Interrupt ile başlatmamız gerekiyor. <br>
<img src="image\image-9.png" width="450"> <br>
<img src="image\image-10.png" width="250"> <br>
• 96.satır çalışınca it.c dosyasına gider. Burada TIM için geçerli fonksiyonu 1sn'de bir çalıştırır. Böylece program 1 sn aralıklarla kesmeye girer. <br>
<img src="image\image-11.png" width="400"> <br>
• 210.satır ile bu fonksiyon dallanır ve dallanan fonksiyon içerisinde Callback fonksiyonu vardır. Bu fonksiyon sayesinde int main içerisinde de kodlarımı yazabilirim. <br>
<img src="image\image-12.png" width="500"> <br>
• 1sn aralıklarla ledi yakıp söndürüyor. <br>
<img src="image\image-13.png" width="500"> <br>
• HAL_TIM_PeriodElapsedCallback fonksiyonu, kullanıcı tarafından özelleştirilerek ihtiyaç duyulan işlevselliği sağlar. Bir timer yapılandırıldığında ve kesme modunda çalıştırıldığında, belirlenen periyot sona erdiğinde bu fonksiyon otomatik olarak çağrılır. <br>
• Fonksiyonunun kullanım alanları; Belirli zaman aralıklarıyla sensörlerden veri okuma, veri işleme, veya durum güncellemeleri gibi işlemler, uygulamanın çalışma süresini ölçmek, belirli süreler sonunda uyarılar veya hatırlatmalar oluşturmak, işlemciyi bloke etmeden belirli bir süre beklemek için kullanılabilir.

---

<br>
