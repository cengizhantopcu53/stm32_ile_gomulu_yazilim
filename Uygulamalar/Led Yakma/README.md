# Led Yakma

> ## **HAL**

### Polling

#### Konfigürasyon 

• Bir saniye içerisinde ne kadar talimat çalıştırıyorsa frekansı o kadardır. <br>
• Sistem saatini ayarlamak için öncelikle RCC kısmından HSE'den Crystal/Ceramic Resonator seçilir. Bu seçim işlemi ile beraber Clock Configuration da kutucuk bölme açılır. <br> 
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


#### Kod 

• CubeMX'de ayarlamaları yaptıktan sonra main.c kısmında yaptığımız kısımları kendisi kod içerisinde oluşturmuştur. <br> 
• RCC ve GPIO için iki ayrı fonksiyon oluşturmuştur. <br> 
Oluşturulan iki fonksiyon kod içerisine yazmadan önce private function prototypes kısmında belirtilir. <br>
<img src="image\image-6.png" width="500"> <br>
• Daha sonra bu iki fonksiyon kod içerisine dahil edilir. <br>
• HAL_Init() fonksiyonunu çağırdığında, HAL kütüphanesi SysTick’i 1ms periyotla interrupt üretecek şekilde konfigüre eder. Her 1ms’de bir SysTick_Handler() kesmesi çalışır. <br>
<img src="image\image-7.png" width="500"> <br>
• hal_gpio.c kısmından WritePin ve Toggle Pin fonksiyonlarına ulaşabiliriz. <br>
<img src="image\image-8.png" width="500"> <br>
<img src="image\image-9.png" width="500"> <br>
• Döngümüze aşağıdaki kodu yazarız. <br>
<img src="image\image-10.png" width="500"> <br>
• HAL Delay aslında blocking (CPU boş boş while döngüsünde dönüyor) bir fonksiyondur.
Bu yüzden kritik işlerde kullanılması tavsiye edilmez. Bunun yerine timer tabanlı non-blocking yöntemler tercih edilir.


#### Derleme 

• Oluşturulan klasörün derlemeye dahil olması için klasöre sağ tıklayıp Properties diyoruz ve burada C/C++ Build sekmesinden **Exclude resource from build** ticki kaldırıyoruz. <br>
• Bir dosyanın derlenmesini istemiyorsak **Exclude resource from build** işaretlenir. Böylece derleme aşamasında bu dosya derlenmez. <br> 
• Örneğin Driver adında klasör oluşturup ardından klasörün içine Inc ve Src adında klasör ekliyorum ve son olarak Header dosyalarını Include etmemiz gerekiyor. Bunun için projeye sağ tıklayıp Properties diyoruz. Burada sol tarafta **C/C++ Build** kısımından **Settings** tıklayıp **MCU GCC Compiler** içeriğindeki **Include paths** tıklayıp burada Add diyoruz ve Workspce tıklayıp klasörümüzü ekliyoruz. <br> 
<img src="image\image-77.png" width="700"> <br>
• STM32CubeIDE üzerinden hex dosyası oluşturmak için [link](https://www.youtube.com/watch?v=7FpsxwEXfLc) üzerinden bilgi alabiliriz. <br>
• Proje dosyasına sağ tıklayıp Properties tıklarız. Burada C/C++ Build sekmesinde Setting tıklarız. Bu kısımdan iki şekilde hex dosyası üretebiliriz. <br>
İlk olarak Tool Settings sekmesinden MCU/MPU Post build outputs kısmında kutucuklardan **Convert to Intel Hex file (-O ihex)** olanı işaretleriz. <br>
İkinici olarak Build Steps sekmesine geliriz ve Post-build steps kısmında Command kutucuğuna **arm-none-eabi-objcopy -O ihex ${ProjName}.elf ${ProjName}.hex** yazarız. Bu kod ile .elf dosyasını .hex dosyasına çeviririz. <br>
<img src="image\image-78.png" width="700"> <br>


#### Programlama 

• **ST-LINK/V2** programlayıcı kullanılarak STM32 mikrodenetleyiciye **SWD** (Serial Wire Debug) arayüzü üzerinden kod yüklemek için belirli pin bağlantıları yapılmalıdır. Bu bağlantılar arasında ST-LINK/V2’nin 7 numaralı pininden **SWDIO**, 9 numaralı pininden **SWCLK**, 15 numaralı pininden **NRST**, ve toprak için 4 numaralı pininden **GND** bağlantısı harici STM32’ye yapılmalıdır. Ayrıca 1 numaralı pin olan **VAPP**, ST-LINK’in hedef sistemin voltaj seviyesini algılaması için STM32’nin VCC pinine bağlanmalıdır. Bununla birlikte STM32’ye güç vermek için iki farklı yöntem kullanılabilir. Birincisi, harici bir 3.3V regülatör üzerinden doğrudan VCC pinine güç verilmesidir. İkincisi ise ST-LINK/V2’nin 19 numaralı pini kullanılarak **3.3V** çıkışından besleme sağlamaktır. Ancak bu pinin akım kapasitesi sınırlı olduğundan, yalnızca düşük güç tüketimli devrelerde tercih edilmelidir. Güç ihtiyacı yüksek olan uygulamalarda harici bir 3.3V kaynağı kullanılması daha güvenlidir. Her iki durumda da GND hattı mutlaka ST-LINK ve hedef devre arasında ortaklanmalıdır. Bu bağlantılar doğru şekilde yapıldığında, ST-LINK/V2 üzerinden STM32 mikrodenetleyiciye güvenli şekilde yazılım yüklenebilir. <br>
<img src="image\image-79.png" width="300"> <br>
• **Nucleo** kartları üzerindeki ST-LINK kısmı, harici başka bir STM32 mikrodenetleyiciye programlama ve hata ayıklama yapmak için kullanılabilir. Bu işlem için öncelikle Nucleo kartı üzerindeki ST-LINK programlayıcının, kart üzerindeki dahili mikrodenetleyiciyle olan bağlantısını kesmek gerekir. Bunun için ilgili jumperlar çıkartılır. Ardından, Nucleo kartının ilgili konnektöründen **SWCLK**, **GND**, **SWDIO** ve **NRST** pinleri sırasıyla harici mikrodenetleyicinin ilgili pinlerine bağlanır. Harici STM32’ye güç vermek için harici bir **3.3V** kaynağı kullanılmalıdır. Bu gücü Nucleo kartındaki güç çıkışından alınabilir. Güç bağlantısı yapıldıktan sonra GND hattı mutlaka her iki sistem arasında ortaklanmalıdır.
Programlama işlemi ilgli programlardan, ST-LINK arayüzü ve SWD bağlantı tipi seçilerek gerçekleştirilir. Tüm bağlantılar doğru yapıldığında, Nucleo kartı üzerinden harici STM32 mikrodenetleyiciye başarıyla yazılım yüklenebilir. <br>
• Hex dosyasını yüklemek için **STM32 ST-LINK Utility** ya da **STM32Cube Programmer** programlarını kullanabiliriz.  <br>
• Kodu yükledikten sonra işlemcinin üzerindeki reset tuşuna basarak programın çalışmasını başlatabiliriz. Ancak yükleme işleminin ardından kartın otomatik olarak resetlenmesini istersek, **Reset Mode** ayarını kullanmamız gerekir. Burada **Hardware Reset** seçeneğini seçersek, ST-LINK doğrudan MCU’nun NRST pinini fiziksel olarak GND’ye çekip bırakır. Bu işlem, kart üzerindeki reset tuşuna basmakla aynı etkiyi sağlar. Bunun çalışabilmesi için ST-LINK’in RST pini ile MCU’nun NRST pini mutlaka birbirine bağlı olmalıdır. <br> 
<img src="image\image-80.png" width="800"> <br>

• Bilgisayar ST-LINK'i tanımıyorsa [STSW-LINK009](https://www.st.com/en/development-tools/stsw-link009.html)	yazılımını kullanarak ST-LINK cihazının, bilgisayara bağlandığında doğru şekilde tanınmasını sağlar. Eğer Windows cihazınız ST-LINK cihazınızı tanımıyorsa ya da "Bilinmeyen Aygıt" olarak görüyorsa bu sürücüyü yüklemeniz gerekir. <br>
• ST-LINK'i güncellemek gerekiyorsa [STSW-LINK007](https://www.st.com/en/development-tools/stsw-link007.html) yazılımını kullanarak güncelleme yapılabilir. <br>

#### Debug 

• [Debug](https://www.youtube.com/watch?v=sNGTGVnT0D8) hakkında bilgi edinmek için linkteki videoyu izleyebilirisiniz. <br>
• **Breakpoint**, kodun durmasını istediğimiz duraklar şeklinde tanımlanır. Breakpoint konacak satıra imleci getirip sol kenardaki şeride çift tıklanarak konur. Gerekli yerlere breakpoinler koyulduktan sonra debug modunda proje çalıştırılabilir ya da kısayol tuşu olarak F11'i tuşlayabiliriz. <br>
• **Resume**, breakpointte duran programımın diğer breakpointe kadar çalışmasını sağlar. Kısayol tuşu olarak F8'i tuşlayabiliriz. <br>
• **Step Into**, breakpoint’imizin bulunduğu yerde bir metot var ise o metotun içine girilir. İçine girdiğimiz metot’un breakpoint ile belirlenip belirlenmediğine bakmazsızın yapılır. Kısayol tuşu olarak F5'i tuşlayabiliriz. <br>
• **Step Over**, programın bulunduğu yerden bir satır ilerlemesini sağlanır. Özellikle metotların içerisinde ilerlemede kullanılır. Kısayol tuşu olarak F6'i tuşlayabiliriz. <br>
• **Step Return**, içine girilen metottan geri çıkılmasını sağlar. Metoda girmeden önceki yere gidilir. Metot içerisine tamamen bakılmış olup olmamasına bakmaz. Kısayol tuşu olarak F7'i tuşlayabiliriz. <br>


#### Dokümantasyon 

• STM32CubeIDE üzerinden oluşturduğumuz projeyi git ile kullanmak için [videoya](https://www.youtube.com/watch?v=_96FSH7uI0E) ve [makaleye](https://shadyelectronics.com/how-to-use-github-with-stm32cubeide/) göz atabiliriz. <br>
• Projede koda yorum satırları ekleyerek dokümantasyon oluşturmak için [DoxyGen](https://youtu.be/edkvo5deT0U?si=gtTa2dLLiGC3uDtd) programı kullanarak web sayfası temelli çıktılara dönüştürebiliyoruz. DoxyGen ile nasıl belgeleneceği ve oluşturulan belgelerin Github Pages olarak nasıl yükleneceği hakkında [detaylı](https://youtu.be/EweioUPl_j0?si=Tz6LA5dcIAZ68rgM) bilgi için linkteki videodan yararlanabiliriz.

---

<br>