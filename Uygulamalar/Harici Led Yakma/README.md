
# Harici Led Yakma

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


## Git Kısmı

• STM32CubeIDE üzerinden oluşturduğumuz projeyi git ile kullanmak için [videoya](https://www.youtube.com/watch?v=_96FSH7uI0E) ve [makaleye](https://shadyelectronics.com/how-to-use-github-with-stm32cubeide/) göz atabiliriz. 


---

<br>


> ## **REGISTER**

## Konfigürasyon Kısmı

• main.c dosyasındaki yorum satırları silip sadece hale getiriyoruz. <br>
<img src="image\image-11.png" width="200"> <br>
• system_stmf4xx.c dosyasındaki 182.satırdaki SystemCoreClock kısmına Ctrl ile sağ tıklıyoruz ve  bizi system_stmf4xx.h dosyasındaki 59.satıra götürüyor. Bu satırı kopyalayıp main.c dosyasına yapıştırıyoruz. <br>
<img src="image\image-12.png" width="300"> <br>
<img src="image\image-13.png" width="500"> <br>
<img src="image\image-14.png" width="200"> <br>
<img src="image\image-15.png" width="400"> <br>
<img src="image\image-16.png" width="300"> <br>
<img src="image\image-17.png" width="400"> <br>
• STM32F407VG mikrodenetleyicinin Reference Manuels'de RCC kısmına bakıyoruz. Mikrodenetleyici 32 bittir. Bu sebeple kaydediciler olan registerler 32 bittir. <br> 
• Bit değerlerinde yazan r ile rw'nin anlamı r'nin read yani okunabilir, w'nin write yani yazılabilir anlamı vardır. <br> 
r olan yerlere müdahale edemiyoruz ama rw yazan bitlere müdahale edebiliyoruz. <br>
<img src="image\image-18.png" width="500"> <br>
• Adress offset bizim ilk olarak kaydedilen yeri gösterir. <br> 
• Reset value ise girilen değer sonrası tüm bitler sıfırlanır. <br>  
Burada resetleme işlemi yapıyoruz. <br>  
<img src="image\image-19.png" width="150"> <br>
• "&=" anlam kaydet anlamındadır. <br> 
Harici osilatör kullanacağımdan HSEON olan 16.biti 1 yapmam gerekiyor. <br> 
<img src="image\image-20.png" width="500"> <br>
• "|=" anlamı ise öncekine 1 ekle ve eşitle anlamındadır. Bunu kullanırken ekleme yani öteleme yapıyoruz. <br>  
16.biti 1 yapmak için öteleme kullanırken 1 << 16 yazıyoruz yani 0.bitte 1 yazıp 16 bit öteliyor. <br> 
<img src="image\image-21.png" width="150"> <br>
• Bunu denetlemek için 17.biti kullanıyoruz. Yani 16.bit 1 olup olmadığını HSE osilatör 6 clock cycles yaptıktan sonra 17.bit olan HSERDY biti 1 oluyor. <br>
<img src="image\image-22.png" width="500"> <br>
• While döngüsü 1 olduğu sürece çalışır. HSERDY biti 1 olana dek 0 olacağından ve döngünün çalışabilmesi için başına "!" işareti koyarak tersliyoruz. <br> 
17.bit 1 olduğunda döngüden çıkacaktır. <br>
• & biti lojik kapılarda olduğu gibi 0&0 ile 0&1 olduğunda çıkışında 0 verir. 1&1 olduğunda çıkışında 1 verir. <br> 
• Buradaki 1 << 17 işlemini yapabilmesi için 6 clock cycles zaman geçmesi gerekiyor. Öteleme işlem yaptığını anlamak için RCC->CR 1 olduğunda 17.bit 1 olmuş oluyor. Böylece 1&1'den 1 oluyor ve !1'den 0 olarak döngüden çıkıyor. <br>
<img src="image\image-23.png" width="150"> <br>
• HSI kapatmak için HSION bitini 0 yapmam gerekiyor. <br>
<img src="image\image-24.png" width="500"> <br>
• 1 << 0 ile 0.bit 1 yapılır ardından ~ işareti ile 0 yapılır. <br> 
<img src="image\image-25.png" width="150"> <br>
• Şu an mikrodenetleyici 8 000 000Hz'de çalışıyor. PLL ile 168 000 000Hz'e çıkaracağız. <br>
<img src="image\image-26.png" width="500"> <br>
• 19.bit 1 yapılır. <br>
<img src="image\image-27.png" width="150"> <br>
• PLLON 24.bit 1 yapılmadan önce PLL'nin konfigürasyonlarını yapmamız gerekiyor. <br>
<img src="image\image-28.png" width="500"> <br>
• PLL için M, N ve P değerlerine göre sistem saati 168MHz yapıyoruz. Bunun için M değerine 4, N değerine 168 ve P değerine 2 verdiğimizde bu işlemi sağlamış oluyoruz. <br>
• M için PLLM kısmında ilk 6 bitte yazacağız. Bunun için 000100 değeri için 0., 1., 3., 4. ve 5.bite 0 yapıyorken 2.biti 1 yapıyoruz. <br> 
• 2.biti 1 yaparken ekleme yaparak yani "|=" işaretini kullanırken diğerlerine sadece 0 bite kaydetmek için "&=" işaretini kullanıyoruz. <br>
<img src="image\image-29.png" width="500"> <br>
<img src="image\image-30.png" width="250"> <br>
• N için PLLN kısmını kullanıyoruz. <br>
<img src="image\image-31.png" width="500"> <br>
<img src="image\image-32.png" width="100"> <br>
• 168 decimal sayısının binary karşılığı 1010 1000'dir. Biz burada 9 bit olduğundan 010101000 yazacağız. <br> 
• Biz bununla uğraşmak yerine 6 bit öteleyip 168 sayısını yazacağız. <br>
<img src="image\image-33.png" width="250"> <br>
• Aynı işlemi M için de yapabiliriz. <br>
<img src="image\image-34.png" width="250"> <br>
• P için PLLP kısmını kullanıyoruz. 2 değeri için iki biti 0 yap diyor. <br>
<img src="image\image-35.png" width="500"> <br>
<img src="image\image-36.png" width="250"> <br>
• PLL için başlangıçta tüm bitleri 0 yapıyoruz. <br>
• Burada 8 tane sıfır var. Buradaki her biri 32 bit'de 4 bite karşılık geliyor. <br>
<img src="image\image-37.png" width="150"> <br>
• Tüm bitleri başlangıçta 0 yaptığımız için PLL'de P için yaptığımız 0'lama işlemine gerek kalmadı. <br>
<img src="image\image-38.png" width="300"> <br>
<img src="image\image-39.png" width="200"> <br>
• PLLSRC ile PLL sürücüsü seçilir. Bu bit için HSI kullanırsak 0, HSE kullanırsak 1 yapılır. Biz HSE kullandığımızdan bu biti 1 yapıyoruz. <br>
<img src="image\image-40.png" width="500"> <br>
<img src="image\image-41.png" width="150"> <br>
<img src="image\image-42.png" width="500"> <br>
<img src="image\image-43.png" width="150"> <br>
<img src="image\image-44.png" width="500"> <br>
<img src="image\image-45.png" width="200"> <br>
<img src="image\image-46.png" width="500"> <br>
• İlk önce 0.bit 0 yapıldı daha sonra 1.bit 1 yapılarak sistemin saatini PLL ile ayarladığımızı belirtiyoruz. <br>
<img src="image\image-47.png" width="500"> <br>
<img src="image\image-48.png" width="150"> <br>
<img src="image\image-49.png" width="500"> <br>
<img src="image\image-50.png" width="200"> <br>
<img src="image\image-51.png" width="300"> <br>
<img src="image\image-52.png" width="400"> <br>
<img src="image\image-53.png" width="500"> <br>
• Pinlerin nasıl kullanacağımızı seçtiğimiz kısımdır. Her iki bit bir pini temsil ediyor. <br>
• Pini giriş, çıkış, analog ya da alternatif fonksiyon olarak mı kullanacağımızı belirtiyoruz. Alternatif fonksiyon ile kast edilen pinin çevresel birimlerden I2C, SPI  olarak kullanılacağını belirtiyor. <br>
<img src="image\image-54.png" width="500"> <br>
• STM32f407VG mikrodenetleyicisinin board üzerindeki led pinleri D12, D13, D14 ve D15'tir. <br>
<img src="image\image-55.png" width="250"> <br>
• D portundaki belirlediğimiz pinlerimizi output yani çıkış olarak tanımlıyoruz ama öncesinde D portunu clock hattına aktarmamız gerekiyor. <br>
<img src="image\image-56.png" width="250"> <br>
• Output ayarı için her bir pine bir bit ayrılmıştır. Kullanacağımız push-pull reset durumunda 0 olduğundan bir ayar yapmamıza gerek yok. <br> 
<img src="image\image-57.png" width="500"> <br>
<img src="image\image-58.png" width="400"> <br>
• Pinlerin very high speed olmasını istiyoruz. Pinleri 1 yapıyoruz. <br>
<img src="image\image-59.png" width="500"> <br>
<img src="image\image-60.png" width="400"> <br>
<img src="image\image-61.png" width="150"> <br>
• Bu şekilde tek tek yazmak yerine 32 bitinin son sekize 1 yazarak hex kısmı yazabiliriz. <br>
<img src="image\image-62.png" width="200"> <br>
<img src="image\image-63.png" width="200"> <br>
• 8 biti 1 yaptığımızda HEX olarak FF veriri. 24.bite eklemeli şekilde de yapabiliriz. <br> 
<img src="image\image-64.png" width="200"> <br>
• Kullanacağımız no pull-up, no pull-down reset durumunda 0 olduğundan bir ayar yapmamıza gerek yok. <br>
<img src="image\image-65.png" width="500"> <br>
<img src="image\image-66.png" width="400"> <br>
• Öncesinde clock hattını aktif etmemiz gerekiyor. Portlar AHB1 kısmına gidiyor. <br>
<img src="image\image-67.png" width="300"> <br>
<img src="image\image-68.png" width="500"> <br>
• Biz D portunu kullandığımızdan sadece bunu aktif ediyoruz. <br>
<img src="image\image-69.png" width="200"> <br>
<img src="image\image-70.png" width="150"> <br>
• Pinleri set ya da reset edeceğimiz kısımdır. Bunları while döngüsü içerisinde yazıyoruz. <br>
<img src="image\image-71.png" width="500"> <br>
<img src="image\image-72.png" width="400"> <br>
<img src="image\image-73.png" width="150"> <br>
• Clock ayarlarını aşağıdaki gibi düzelttik. <br> 
• Önceki yaptıklarımızın hepsini HEX formatında olacak şekilde düzelttik. <br> 
• Konunun videosu eski olduğundan önceki yaptığımız örneklerden farklılık olarak eskilerde RCC_CFGR register kısmın 4:7 arası bitler koda eklenmişken yenilerde ekli olan 0:3 arası bitler eklenmemiş. <br> 
• Eski videoda döngüde açılan flagların kapatılması için RCC_CIR registerın 11. ve 23.bitleri resetlemiş. <br>
<img src="image\image-74.png" width="350"> <br>
• GPIO ayarlarını aşağıdaki gibi düzelttik. <br> 
<img src="image\image-75.png" width="400"> <br>


## Kod Kısmı

• RCC ve GPIO için yazdığımız fonksiyonları ekledik ardından while dönüsü içersinde led blink uygulamasını gerçekleştirdik. <br>
<img src="image\image-76.png" width="250"> <br>


---

<br>