
# Led Yakma

> ## **HAL**

## Konfigürasyon Kısmı

• Bir saniye içerisinde ne kadar talimat çalıştırıyorsa frekansı o kadardır. <br>
• Sistem saatini ayarlamak için öncelikle RCC kısmından HSE'den Crysal/Ceramic Resonator seçilir. Bu seçim işlemi ile beraber Clock Configuration da kutucuk bölme açılır. <br> 
LSE'nin HSE ile aralarındaki farkı düşük hızlı olması ve düşük güç tüketimi için kullanılır. <br>
• System Clock Mux kısmında 3 seçeneğimiz var. Bunlar HSI, HSE ve PLLCLK'tur. HSI dahili iken HSE harici kaynaktır. <br> 
HSI seçersek kutucuktaki değer olur, HSE seçersek giriş frekansı belli MHz aralıktadır. Biz burada kart üzerinde 8MHz olduğundan bu şekilde yazıp kullanıyoruz. <br> 
Eğer PLLCLK seçersek ayarlamalarla maksimum MHz'e kadar istediğimiz değeri seçebiliriz. <br>
<img src="image\image-1.png" width="700"> <br>
<img src="image\image-2.png" width="400"> <br>
• System Core kısmından SYS tıklıyoruz ve Debug'da Serial Wire diyoruz. <br> 
<img src="image\image-3.png" width="500"> <br>
• RCC tıklıyoruz HSE'de Crystal/Ceramic Resonator işaretliyoruz. <br> 
<img src="image\image-4.png" width="500"> <br>
• B portundaki  3., 4., 5. ve 6.pinlere led bağladık. <br>
<img src="image\image-5.png" width="500"> <br>


## Kod Kısmı

• CubeMX'de ayarlamaları yaptıktan sonra main.c kısmında yaptığımız kısımları kendisi kod içerisinde oluşturmuştur. <br> 
• RCC ve GPIO için iki ayrı fonksiyon oluşturmuştur. <br> 
Oluşturulan iki fonksiyon kod içerisine yazmadan önce private function prototypes kısmında belirtilir. <br>
<img src="image\image-6.png" width="500"> <br>
• Daha sonra bu iki fonksiyon kod içerisine dahil edilir. <br>
<img src="image\image-7.png" width="500"> <br>
• hal_gpio.c kısmından WritePin ve Toggle Pin fonksiyonlarına ulaşabiliriz. <br>
<img src="image\image-8.png" width="500"> <br>
<img src="image\image-9.png" width="500"> <br>
• Döngümüze aşağıdaki kodu yazarız. <br>
<img src="image\image-10.png" width="500"> <br>


## Programlama Kısmı

• STM32CubeIDE üzerinden hex dosyası oluşturmak için [link](https://www.youtube.com/watch?v=7FpsxwEXfLc) üzerinden bilgi alabiliriz. <br>
• Proje dosyasına sağ tıklayıp Properties tıklarız. Burada C/C++ Build sekmesinde Setting tıklarız ve burada Build Steps sekmesine geliriz. Burada Post-build steps kısmında Command kutucuğuna **arm-none-eabi-objcopy -O ihex ${ProjName}.elf ${ProjName}.hex** yazarız. Bu kod ile .elf dosyasını .hex dosyasına çeviririz. <br>
• Hex dosyasını yüklemek için STM32 ST-LINK Utility ya da STM32Cube Programmer programlarını kullanabiliriz. Eğer STM32Cube Programmer programını kullanıyorsak kodu yükledikten sonra işlemci üzerindeki reset tuşuna basarak yüklediğimiz kod çalıştırırız. <br>
Eğer STM32Cube Programmer programını kullanıyorsak kodu yükledikten sonra işlemci üzerindeki reset tuşuna basarak yüklediğimiz kod çalıştırırız. <br>

## Debug Kısmı

• [Debug](https://www.youtube.com/watch?v=sNGTGVnT0D8) hakkında bilgi edinmek için linkteki videoyu izleyebilirisiniz. <br>
• **Breakpoint**, kodun durmasını istediğimiz duraklar şeklinde tanımlanır. Breakpoint konacak satıra imleci getirip sol kenardaki şeride çift tıklanarak konur. Gerekli yerlere breakpoinler koyulduktan sonra debug modunda proje çalıştırılabilir ya da kısayol tuşu olarak F11'i tuşlayabiliriz. <br>
• **Resume**, breakpointte duran programımın diğer breakpointe kadar çalışmasını sağlar. Kısayol tuşu olarak F8'i tuşlayabiliriz. <br>
• **Step Into**, breakpoint’imizin bulunduğu yerde bir metot var ise o metotun içine girilir. İçine girdiğimiz metot’un breakpoint ile belirlenip belirlenmediğine bakmazsızın yapılır. Kısayol tuşu olarak F5'i tuşlayabiliriz. <br>
• **Step Over**, programın bulunduğu yerden bir satır ilerlemesini sağlanır. Özellikle metotların içerisinde ilerlemede kullanılır. Kısayol tuşu olarak F6'i tuşlayabiliriz. <br>
• **Step Return**, içine girilen metottan geri çıkılmasını sağlar. Metoda girmeden önceki yere gidilir. Metot içerisine tamamen bakılmış olup olmamasına bakmaz. Kısayol tuşu olarak F7'i tuşlayabiliriz. <br>

## Derleme Özelikleri
• Oluşturulan klasörün derlemeye dahil olması için klasöre sağ tıklayıp Properties diyoruz ve burada C/C++ Build sekmesinden **Exclude resource from build** ticki kaldırıyoruz. 
• Bir dosyanın derlenmesini istemiyorsak **Exclude resource from build** işaretlenir. Böylece derleme aşamasında bu dosya derlenmez. 
• Örneğin Driver adında klasör oluşturup ardından klasörün içine Inc ve Src adında klasör ekliyorum ve son olarak Header dosyalarını Include etmemiz gerekiyor. Bunun için projeye sağ tıklayıp Properties diyoruz. Burada sol tarafta **C/C++ Build** kısımından **Settings** tıklayıp **MCU GCC Compiler** içeriğindeki **Include paths** tıklayıp burada Add diyoruz ve Workspce tıklayıp klasörümüzü ekliyoruz. 

<img src="image\image-11.png" width="700"> <br>

## Dokümantasyon Kısmı

• STM32CubeIDE üzerinden oluşturduğumuz projeyi git ile kullanmak için [videoya](https://www.youtube.com/watch?v=_96FSH7uI0E) ve [makaleye](https://shadyelectronics.com/how-to-use-github-with-stm32cubeide/) göz atabiliriz. <br>
• Projede koda yorum satırları ekleyerek dokümantasyon oluşturmak için [DoxyGen](https://youtu.be/edkvo5deT0U?si=gtTa2dLLiGC3uDtd) programı kullanarak web sayfası temelli çıktılara dönüştürebiliyoruz. DoxyGen ile nasıl belgeleneceği ve oluşturulan belgelerin Github Pages olarak nasıl yükleneceği hakkında [detaylı](https://youtu.be/EweioUPl_j0?si=Tz6LA5dcIAZ68rgM) bilgi için linkteki videodan yararlanabiliriz.

---

<br>


