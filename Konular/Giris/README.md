# Giris

- Gömülü yazılım, belirli bir donanım üzerinde belirli görevleri yerine getirmek üzere tasarlanmış, genellikle gerçek zamanlı çalışan özel amaçlı yazılımlardır. Bu yazılımlar; ev aletlerinden otomobillere, endüstriyel kontrol sistemlerinden tıbbi cihazlara kadar birçok cihazın içinde yer alır ve donanımın beyni olarak görev yapar.
- Gömülü sistemlerde, yazılım doğrudan mikrodenetleyici (MCU) veya mikroişlemci (MPU) gibi donanım bileşenleri üzerinde çalışır. Bu tür sistemlerde performans, bellek ve enerji tüketimi gibi sınırlamalar dikkate alınarak optimize edilmiş yazılımlar geliştirilir. Gömülü yazılım; donanımı doğrudan kontrol edebilen, kesme yönetimi yapabilen, haberleşme protokollerini işleyebilen ve genellikle işletim sistemi olmadan (bare-metal) ya da gerçek zamanlı işletim sistemi (RTOS) ile çalışan yapılardır.
- Gömülü yazılım geliştirme süreci; donanımı tanımayı, düşük seviyeli programlamayı, hata ayıklamayı ve sistem kaynaklarını verimli kullanmayı gerektirir. Bu alandaki yazılımcılar, yalnızca yazılım bilgisine değil, aynı zamanda donanım bilgisine de sahip olmalıdır.
- Bu kitapçıkta, gömülü yazılım dünyasına adım atmak isteyenler için temel kavramlardan başlayarak pratik uygulamalara kadar birçok konuyu ele alacağız. Amacımız, yazılım geliştiricilere hem teorik hem de uygulamalı bir bakış açısı kazandırmaktır.

## Temel Kavramlar

### Mikroişlemci

- Mikroişlemci yapısında bir CPU (Central Processing Unit), Ön bellek ve Input/Output (Giriş/Çıkış) birimleri bulunan devrelere microprocessor denir.
Bu üç temel unsur birbirlerine bus, iletişim yolları ile bağlıdır.
- Mikroişlemcinin beyni CPU'dur. Veri akışı ve veri işleme bu birim sayesinde gerçeleşir.
- Bu veri işleme genellikle CPU içerisinde yer alan ALU (Aritmetic Logic Unit)'da uygulanır. Bu birimde sayısal ve lojik işlemler yapılır. Tüm dijital elektronik işlemler CPU'ların en temel işlemleridir.
- CPU'ların içerisinde 8-16-32-64 bitlik registerler bulunmaktadır. Register, bilgilerin geçici sürede depolanmasını sağlarlar.
- CPU'lar, mikroişlemcinin hafızasındaki programları bulma, çağırma ve onları çalıştırma görevi görürler. Veri İşleme Adımları; Veriyi Getirmek (Fetch), Veriyi Çözmek (Decode), Veriyi İşlemek (Execute), Veriyi Hafızata, Geri Depolamak (Store)
- Merkezi işlem birimi, üç birimden oluşur.
    - Aritmetik Mantık Birimi (ALU), hafıza biriminden gelen verilerin işlenmesinde görev alır. Bu işlemlerise aritmetik olarak toplama, çıkarma, bölme ve çapmadır. İkili sayı tabanındaki (binary) mantık işlemleri VE (AND), OR (VEYA) ve bit kaydırma işlemleridir.
    - Kayıtçılar (Registers), hafızadaki veriler ALU tarafından işlenirken kullnılan geçici ve kalıcı saklayıcılardır. Registerler işlemcinin çekirdeğinde olduklarından verilere ulaşmak daha hızlı gerçekle 
    - Kontrol Birimi (CU), işlemcinin çalışmasını yönlendiren birimdir. İşlemci içerisindeki ve dışarısındaki birimlerin senkron şekilde çalışmasını sağlar.


### Bellek Yapıları

<img src="image\image-1.png" width="400"> <br>
- RAM, ROM ve EEPROM, hafızanın temel birimleridir.
- Mikroişlemciye atılan veriler ilk olarak hafızaya gelir ve burada depolanır. CPU'ların doğrudan eriştiği birim bellektir. Bellekte iki tane birincil hafıza birimi vardır.
    - RAM (Random Access Memory), mikroişlemcinin elektrik alması durumunda geçici hafıza olarak kullandığı birimdir. Elektrik kesildiği zaman bu veriler silinir ve bir daha kullanılmaz. RAM, diğer hafıza birimleri gibi verileri önceden verilen bir sırayla dizmez. Bu sebeple ismi rastgele erişim bellek olarak konulmuştur. RAM, Dinamik Rastgele Erişim Bellek ve Statik Rastgele Erişim Bellek olmak üzere ikiye ayrılır. 
    - ROM (Read Only Memory), sadece okunabilir bir bellektir. Elektrik kesildiğinde bu bellekteki veriler silinmez. ROM üzerindeki yazılmış fabrikasyon yazılımlar kullanıcılar tarafından değiştirilip, silinemez. 
    - EEPROM (Electronically Erasable Programmable Read-Only Memory), elektrik ile defalarca yazılıp silinebilen bellektir. Elektrik kesildiğinde bu bellekteki veriler silinmez. Flash belleklerde bir eeprom türüdür.


### Veri Yolları

<img src="image\image-2.png" width="400"> <br>
- Giriş - Çıkış birimleri mikroişlemci ile dış dünyanın sinyaller aracılığı ile haberleştiği birimdir. <br>
Bu giriş ve çıkışlar; Giriş/ Çıkış portları, harici elektronik birimler, fiziksel cihazlar ve yazılımlar olabilir. 
- CPU daki veri akışının aktarılması, bellek ve Giriş/Çıkşı birimlerinin bağlantılarını sağlayan üç çeşit bus vardır. 
    - Address Bus, verinin okunacağı veya verinin yazılacağı bölgeyi belirten adres bilgilerinin taşınmasını sağlar. Tek yönlü bir veri yoludur.
    - Data Bus, CPU'dan bellek ve Giriş/Çıkış portlarına veya bu birimlerden CPU'ya çift yönlü bir hat vardır.
    - Control Bus, mikroişlemcideki birimler arasında iletişimi sağlayan sinyalleri ileten, kontrol eden veri hattıdır. Her mikroişlemci farklı sayıda Control Bus'a sahiptir.

### Mikrodenetleyici

- Mikroişlemcili bir sistemin içerisinde bulunması gereken temel bileşenlerden RAM, ROM, ALU, kontrol ünitersi ve I/O ünitesini tek bir çip içerisinde barındıran entegre devreye microcontroller denir.
- Mikrodenetleyici, dışarıdan gelen bir veriyi hafızasına alan, derleyen ve sonucunda çıktı elde eden bir bilgisayardır. Mikrodenetleyicilerin yapısında; CPU, RAM, ROM, I/O Portları, Seri ve Paralel Portlar, Zamanlayıcılar, ADC ve DAC çevre birimleri
- Mikrodenetleyiciler gerçek zamanlı işlemlerde oldukça başarılılardır.
- Mikrodenetleyiciler herhangi bir işi çok küçük boyutlarda ve daha düşük enerjide yaparlar.
- Mikroişlemcili ile kontrol edilecek bir sistemi kurmak için gerekli olan minimum donanımda CPU, RAM, I/O bulunmalıdır. Bunlar arasında veri alışverişini sağlamak için ise veri yolu, adres yolu ve kontrol yolu gereklidir. Birimler arasındaki iletişimi sağlayan bu yolları yerleştirmek içinde bir anakart gereklidir.
- Mikrodenetleyici ile kontrol edilecek sistemde ise yukarıda saydığımız birimler tek zaten mikrodenetleyici içerisinde bulunmaktadır. Bu da maliyetin daha düşük olacağı anlamına gelir.
- Mikrodenetleyiciler çok az sayıda ve karmaşık olmayan komutlarla programlanabilen sistemlerdir.
- Mikronetleyiciler hız bakımıından mikroişlemcilerden daha hızlıdır. Güç tüketimi mikrodenetleyicilerde daha azdır. Fiyatları mikroişlemcilere göre daha uygundur.
- Mikroişlemcili sistemlerde harici donanım desteği gerekli iken, mikrodenetleyicilerde bu gereklilik çok azdır.

## İşlemci ve Çekirdek Bileşenleri

- Cortex-M işlemcisi ARM tarafından tasarlanmış, gömülü sistemlerde çok yaygın kullanılan 32-bit RISC tabanlı bir mikrodenetleyici çekirdeğidir.
    - Mimari: ARMv7-M mimarisine dayanır.
    - 32-bit: Veri yolu, adresleme ve register yapısı 32-bit’tir.
    - Performans: Tek çevrimlik çoğu talimat ile yüksek verimlilik sağlar.
    - Donanım Çarpma/Bölme: 32x32 → 64 bit çarpma ve hızlı bölme desteği vardır.
    - DSP Özellikleri: FIR/IIR filtreleri, FFT gibi sayısal sinyal işleme uygulamaları için özel SIMD (Single Instruction, Multiple Data) talimatları bulunur.
    - Floating Point Unit (FPU): Bazı modellerde donanım tabanlı kayan nokta birimi (single precision) entegre gelir.
    - Düşük Güç: Gömülü sistemler için optimize edilmiş düşük güç modları bulunur.
    - Kesme Sistemi: Nested Vectored Interrupt Controller (NVIC) ile çok hızlı ve düşük gecikmeli kesme yönetimi yapılır.

<img src="image\image-3.png" width="350"> <br>
- Cortex çekirdeği, üreticiye özgü çevre birimlerinden bağımsız olarak her cihazda bulunan bazı çekirdek çevre birimleri (core peripherals) içerir. Bu birimler, işlemcinin kesme yönetimi, zamanlama, bellek koruması ve matematiksel hesaplama gibi sistem seviyesinde kritik görevlerini üstlenir.

<img src="image\image-4.png" width="300"> <br>
    - NVIC (Nested Vectored Interrupt Controller)
        - NVIC, düşük gecikmeli kesme yönetimini sağlar. Tüm kesmelerin önceliklendirilmesini ve hızlı şekilde işlenmesini mümkün kılar. Bu sayede gerçek zamanlı uygulamalarda hızlı tepki süresi elde edilir.
    - SCB (System Control Block)
        - SCB, işlemciye ait sistem kontrolü ve yapılandırma işlemleri için programcı arayüzünü sunar. Exception yönetimi, hata raporlama ve bazı sistemsel ayarlar SCB üzerinden yapılır.
    - SysTick Timer
        - SysTick, 24-bit geri sayım temelli bir sistem sayacıdır. Gerçek Zamanlı İşletim Sistemlerinde (RTOS) görev zamanlayıcısı olarak veya basit bir zaman ölçer olarak kullanılabilir.
    - MPU (Memory Protection Unit)
        - MPU, bellek bölgelerinin erişim haklarını ve özelliklerini tanımlayarak sistemin güvenliğini ve güvenilirliğini artırır. Cortex çekirdeğinde sekiz farklı bellek bölgesi tanımlanabilir.
    - FPU (Floating-Point Unit)
        - FPU, IEEE754 standardına uygun 32-bit tek duyarlıklı kayan nokta işlemlerini donanımsal olarak gerçekleştirir. Bu sayede sinyal işleme, kontrol algoritmaları ve matematiksel yoğunluğu yüksek uygulamalarda performans artışı sağlar.

### Programmers Model

- STM32 mikrodenetleyicilerinde ARM Cortex-M mimarisi üzerinde çalışan core registerları bulunmaktadır. CPU core register’ları, işlemcinin çalışması için en kritik donanım alanıdır. 
- Kodun çalışacağı adres (PC), stack yapısı (SP), fonksiyon dönüşleri (LR), işlem sonuç bayrakları (xPSR) ve genel veri saklama alanları (R0–R12) bu register’larda tutulur. 
Debugger aracılığıyla bu değerler görüntülenerek programın kontrol akışı ve bellek kullanımı hakkında bilgi edinilebilir.
    - R0 – R12 (General-purpose registers), işlemci bunları geçici değer tutmak, aritmetik/lojik işlemler yapmak, fonksiyon parametrelerini taşımak gibi işler için kullanır. Derleyici de bunları yoğun kullanır.
        - 0xFFFFFFFF → muhtemelen debugger reset sonrası init olmamış (RAM içerikleri de belirsizdir).
    - R13 (SP - Stack Pointer), Bellekteki stack (yığın) bölgesinin tepe adresini tutar. MSP (Main Stack Pointer) ve PSP (Process Stack Pointer) olmak üzere ikiye ayrılır. Sıfırlama sırasında işlemci MSP'ye 0x00000000 adresindeki değeri yükler. 
        - 0x20000660 → Stack RAM içinde 0x20000660 adresinden aşağı doğru büyüyor. STM32 datasheet’inde başlangıç stack adresi vector table’ın ilk kelimesidir (bootloader ilk iş olarak SP’yi oraya yükler).
    - R14 (LR - Link Register), fonksiyonlardan dönüş adresini tutar. Fonksiyon bittiğinde program LR’deki adrese geri döner. Sıfırlama sırasında işlemci LR değerini 0xFFFFFFFF olarak ayarlar.
        - 0xFFFFFFFF görünüyor → Geçerli bir return adresi yok gibi. Reset sonrası normal.
    - R15 (PC - Program Counter), işlemcinin bir sonraki çalıştıracağı komutun adresini tutar. Kod yürütmenin akışını belirler. Atlamalar (branch, jump) bu register’ın değerini değiştirir.
    Sıfırlandığında, işlemci PC'ye 0x00000004 adresinde bulunan sıfırlama vektörünün değerini yükler.
        - 0x0800015C → Flash bellekteki (0x0800xxxx STM32’de Flash’tır) adresteki komutu çalıştırıyor. Yani bootloader kodun buradan devam ediyor.
    - xPSR (Program Status Register)
        - İşlemcinin durumunu ve bayraklarını tutar. 
        - İçerisinde şunlar bulunur:
            - N (Negative): Sonucun negatif olduğunu gösterir.
            - Z (Zero): Sonucun sıfır olduğunu gösterir.
            - C (Carry): Taşma/borç durumunu gösterir.
            - □ V (Overflow): İşaretli taşma durumunu gösterir.
            - Interrupt Mask bitleri: Kesme izinlerini kontrol eder.

<img src="image\image-5.png" width="400"> <br>

### Memory Model

- İşlemcinin, maksimum 4 GB adreslenebilir bellek sağlayan sabit bir varsayılan bellek haritası vardır.

<img src="image\image-6.png" width="450"> <br>

### Exception Model

- Cortex-M çekirdeğinde tüm exception’lar öncelik sırasına göre numaralandırılır. Negatif numaralar sistem exception’larını, sıfır ve üzeri numaralar ise harici kesmeleri (IRQ) temsil eder.
    - Reset, en yüksek önceliğe sahiptir. Sistem açıldığında veya reset durumunda çalışır.
    - NMI (Non-Maskable Interrupt), maskelenemeyen, çok kritik olaylar için ayrılmış kesme.
    - Fault Exceptions, hatalar için tetiklenen exception’lar (HardFault, MemManage, BusFault, UsageFault)
        - HardFault, daha düşük seviyeli fault’ların ele alınamadığı durumlarda devreye girer.
        - MemManage, bellek koruması ihlali olduğunda tetiklenir. MPU (Memory Protection Unit) ile ilişkilidir.
        - BusFault, veri yolundaki hatalarda tetiklenir
        - UsageFault, geçersiz komut, yanlış hizalanmış erişim gibi CPU kullanım hatalarında tetiklenir
    - System Exceptions → Çekirdeğe özgü özel kesmeler (ör. SVCall, SysTick, PendSV)
        - SVCall (Supervisor Call), genellikle işletim sistemi çağrılarında kullanılır.
        - PendSV (Ertelenmiş kesme),özellikle RTOS’larda görev değiştirmeiçin kullanılır.
        - SysTick, genellikle RTOS tick üretiminde veya zamanlama amaçlı kullanılır.
    - External Interrupts (IRQs) → Mikrodenetleyiciye bağlı çevre birimlerden gelen normal kesmeler.
- Cortex-M mimarisinde exception’lar farklı gruplara ayrılır ve her biri kendi handler fonksiyonuyla karşılanır.
    - Interrupt Service Routines (ISRs): IRQ kesmeleri ISR’ler tarafından işlenen exception'lardır.
    - Fault Handlers: HardFault, MemManage Fault, UsageFault ve BusFault, fault handler tarafından işlenen fault exceptions.
    - System Handlers: NMI, SVCall, PendSV,  SysTick ve hata istisnalarının tamamı system exceptions ve system handler tarafından işlenir.

<img src="image\image-7.png" width="500"> <br>
- Vektör tablosu, stack pointer’ın başlangıç değerini ve tüm exception handlers için başlangıç adreslerini (exception vectors olarak da adlandırılır) içerir. 
- Sistem resetlendiğinde, vektör tablosu varsayılan olarak 0x00000000 adresinde bulunur. 
Ancak yetkili yazılım, VTOR kaydını kullanarak bu tabloyu başka bir bellek bölgesine taşıyabilir. Bu taşıma, tablonun başlangıç adresini 0x00000080 ile 0x3FFFFF80 aralığında herhangi bir konuma ayarlamayı mümkün kılar.

<img src="image\image-8.png" width="300"> <br>

## Bellek ve Veri Yolu Mimarisi

- Bellek mimarisi, sistemin bellek kaynaklarının nasıl yapılandırıldığını ve yönetildiğini belirler.
    - ROM (Read-Only Memory)
        - Kalıcı veriler ve program kodu saklanır.
        - Mikrodenetleyicinin yeniden başlatılmasında bile veriler silinmez.
    - Flash Memory
        - Program ve veri saklama için kullanılan yeniden programlanabilir ROM türüdür.
        - Genellikle firmware ve yazılım güncellemeleri burada saklanır.
    - SRAM (Static RAM)
        - Geçici veri depolama için kullanılır.
        - Hızlı erişim süresine sahiptir ve genellikle çalışma sırasında kullanılan veri ve değişkenler burada saklanır.
    - EEPROM (Electrically Erasable Programmable ROM)
        - Küçük veri parçalarını kalıcı olarak saklamak için kullanılır.
        - Elektriksel olarak silinebilir ve yeniden programlanabilir.
    - CCM (Core Coupled Memory)
        - ARM Cortex-M4 işlemcisine yakın, düşük gecikmeli bellek alanıdır.
        - Yüksek performans gerektiren işlemler için kullanılır.
- Veri yolu mimarisi, farklı bileşenlerin birbirleriyle nasıl iletişim kurduğunu ve veri transferi yaptığını belirler. 
    - System Bus (Sistem Veri Yolu)
        - CPU, bellek ve çevresel birimler arasındaki ana iletişim hattıdır.
        - ARM Cortex-M4 gibi işlemciler genellikle AHB (Advanced High-performance Bus) veya APB (Advanced Peripheral Bus) kullanır.
    - AHB (Advanced High Performance Bus)
        - Yüksek hızlı veri transferi sağlar.
        - Genellikle CPU, bellek ve yüksek hızlı çevresel birimler arasında kullanılır.
    - APB (Advanced Peripheral Bus)
        - Daha düşük hız gerektiren çevresel birimler için kullanılır.
        - Daha az karmaşıktır ve daha az güç tüketir.
    - DMA (Direct Memory Access)
        - CPU müdahalesi olmadan veri transferi yapar.
        - Bellekler ve çevresel birimler arasında hızlı veri transferi sağlar.
    - Bus Matrix:
        - Birden fazla master ve slave bileşenin aynı anda veri transferi yapmasını sağlar.
        - STM32F407 şemasında görüldüğü gibi, bus matrix-S veri yollarını birbirine bağlar ve verimli veri transferi sağlar.
        - I-bus, D-bus ve S-bus veri yolları ile bellek ve çevresel birimlere bağlanır. 
        - I-bus talimatlar için, D-bus veriler için ve S-bus sistem veri yolu için kullanılır.

### Sistem Mimarisi

- STM32F407 mikrodenetleyicisinin sistem mimarisi, 32-bit çok katmanlı AHB veri yolu matrisi üzerine kuruludur. Bu matriste sekiz master ve yedi slave bileşen bulunur:
    - Master bileşenler, veri yolu üzerinde kontrol yetkisine sahiptir ve veri transferini başlatabilir. İşlemci veya DMA gibi master bileşenler, veri yolu üzerinden slave bileşenlere erişim talimatları göndererek veri okuyabilir veya yazabilir.
        - Cortex®-M4 with FPU core I-bus, D-bus and S-bus 
        - DMA1 memory bus 
        - DMA2 peripheral bus 
        - Ethernet DMA bus 
        - USB OTG HS DMA bus 
    - Slave bileşenler, genellikle veri depolama veya belirli bir işlevi yerine getirme rolüne sahiptir. Bunlar, kendi başlarına aktif olarak veri yolu üzerinde veri transferi başlatamazlar. Bu yüzden veri alışverişi yapabilmek için bir master bileşenin aktivasyonuna ve yönlendirmesine ihtiyaç duyarlar.
        - Internal Flash memory ICode bus
        - Internal Flash memory DCode bus
        - Main internal SRAM1 (112 KB)
        - Auxiliary internal SRAM2 (16 KB) 
        - AHB1 peripherals including AHB to APB bridges and APB peripherals
        - AHB2 peripherals 
        - FSMC

<img src="image\image-9.png" width="600"> <br>


### Bellek Organizasyonu

- Program belleği, veri belleği, kayıtlar ve I/O portları, aynı doğrusal 4 GB adres alanı içinde düzenlenmiştir.
- İşlemcimiz 32 bit veri yoluna sahiptir. Bu, 2^32 işlemiyle hesaplanan 4.294.967.296 (4 GB) adresleyebilme kapasitesine sahip olduğu anlamına gelir. Bu sayıyı ondalık (decimal) sistemden onaltılık (hexadecimal) sisteme çevirdiğimizde 0x100000000 sonucunu elde ederiz. Buradan 1 çıkardığımızda ise 0xFFFFFFFF değerine ulaşırız. Adres uzayı 0x00000000 adresinden başlar ve 0xFFFFFFFF adresine kadar devam eder. <br>
Unutulmamalıdır ki, hex formatında her bir rakam 4 bitlik bir değere karşılık gelir.
- Bellekteki baytlar little endian formatında kodlanmıştır. En düşük numaralı bayt, kelimenin en az anlamlı baytı olarak kabul edilir; en yüksek numaralı bayt ise kelimenin en anlamlı baytıdır.
- Adreslenebilir bellek alanı, her biri 512 MB olan 8 ana bloğa bölünmüştür. <br>
On-chip bellekler ve çevresel birimlere tahsis edilmemiş tüm bellek alanları Reserved olarak kabul edilir.

### Bellek Haritası

<img src="image\image-10.png" width="700"> <br>

<img src="image\image-11.png" width="350"> <br>

### Boot Konfigurasyonu

- STM32’de BOOT pinleri ile farklı bellek bölgeleri 0x0000 0000 adresine haritalanabilir. Aslında işlemcinin gördüğü 0x0000 0000 adresi donanım tarafından seçilen bellek bölgesine yansıtılır.
    - Main Flash (0x0800 0000) → Normal uygulama başlatma
    - System Memory (0x1FFF xxxx) → ST’nin dahili bootloader’ı
    - SRAM (0x2000 0000) → RAM’den çalıştırma

<img src="image\image-12.png" width="500"> <br>

## Flash Memory

- Cortex-M çekirdeğinin aynı anda hem komut hem veri hem de sistem erişimlerini paralel olarak yapabilmesini sağlar. Flash interface 128-bit geniş erişimle Flash’tan bloklar alır, bunları cache’ler ve CPU’ya 32-bit olarak iletir. Böylece Flash’ın görece yavaş hızına rağmen işlemci yüksek performansta çalışır.

<img src="image\image-13.png" width="500"> <br>

- Mikrodenetleyicinin hafıza organizasyonu aşağıda detaylı bir şekilde açıklanmaktadır.
    - Flash Bellek, uygulama kodumuzu saklamak ve programın verilerini okumak için kullanılır. Ayrıca vektör tablolarını saklamak için de kullanılır.
        - Boyut: 1 Mbyte
        - Başlangıç: 0x0800 0000
        - Bitiş: 0x080F FFFF
        - İçine yazılan veriler kalıcıdır. (Non Volatile)
    -  SRAM, mikrodenetleyicinin rastgele erişim belleği sayısı 2'dir.
        - SRAM1, uygulamamızdaki global verileri ve statik değişkenlerimizi depolamak için kullanılır. Ayrıca stack ve heap amacıyla kullanılır. Bu bellekten kod çalıştırılabilir. Yani burada herhangi bir talimat sakladıysanız, işlemcinin bunu yürütebilmesi için SRAM’e geçebileceği anlamına gelir.
            - Boyut: 112 Kbyte
            - Başlangıç: 0x2000 0000
            - Bitiş: 0x2001 BFFF
            - İçine yazılan veriler kalıcı değildir (Volatile)
        - SRAM2, boyut olarak SRAM1’den daha küçüktür ve bellek haritasında SRAM1’den hemen sonra gelir. Uygulamalarımızda global verileri ve statik değişkenleri depolamak için kullanılır. Ayrıca heap ve stack oluşturabiliriz. Yine bu bellekten de kod çağrılabilir.
            - Boyut: 16 Kbyte
            - Başlangıç: 0x2001 0000
            - Bitiş: 0x2001 FFFF
            - İçine yazılan veriler kalıcı değildir. (Volatile)
    - ROM (Read Only Memory) belleğine sahiptir. ST dokümanlarında bu bellek System Memory olarak da adlandırılmaktadır. Read Only Memory olduğu için sadece okunabilir bir bellektir ve herhangi bir veri bu hafıza alanına yazılamaz. Bu bellek, ST tarafından oluşturulan bootloader'ın saklandığı bellek bölgesidir. Yani STM ürünlerinin önyükleyicileri ROM'da saklanır ve tek seferlik programlanabilir hafıza olarak adlandırılan veriye sahiptir
        - Boyut: 30 Kbyte
        - Başlangıç: 0x1FFF 0000
        - Bitiş: 0x1FFF 77FF
    - OTP belleği de yalnızca bir kez programlanabilir ve bu bilgi genellikle bir ürünün ürün numarası veya seri numarasını kullanıcı tarafından saklamak için kullanılır.
        - Boyut: 528 bayt
        - Başlangıç: 0x1FFF 7800
        - Bitiş: 0x1FFF 7A0F
    - Option Bytes Memory bulunmaktadır. Genel kullanım için değildir. Bu baytların flash belleğe erişimi kontrol eden bazı kaynakları vardır.
        - Boyut: 8 Kbyte
        - Başlangıç: 0x1FFF C000
        - Bitiş: 0x1FFF C00F

<img src="image\image-14.png" width="500"> <br>

### Register

<img src="image\image-18.png" width="600"> <br>

- FLASH_ACR (Flash Access Control Register), Flash erişim parametrelerini kontrol eder.
    - LATENCY: Flash erişim gecikme ayarı. CPU hızına göre doğru değer seçilmeli
        - 000: Zero wait state
        - 001: One wait state
        - 010: Two wait states
        - 011: Three wait states
        - 100: Four wait states
        - 101: Five wait states
        - 110: Six wait states
111: Seven wait states
    - PRFTEN: Prefetch buffer enable. Önbellekleme açılır
    - ICEN: Instruction cache enable
    - DCEN: Data cache enable
    - ICRST / DCRS: Instruction/Data cache reset
- FLASH_KEYR (Flash Key Register), Flash kontrol register’ını kilitli durumdan çıkarmak için yazılır
    - KEY[31:0] alanına doğru anahtar değerler yazılmalıdır yoksa yazma/silme işlemi yapılamaz
        - KEY1 = 0x45670123
        - KEY2 = 0xCDEF89AB
- FLASH_OPTKEYR (Flash Option Key Register), Option byte’lara erişim için kilit açma register’ı
    - OPTKEY[31:0] alanına sırasıyla,
        - OPTKEY1 = 0x08192A3B
        - OPTKEY2 = 0x4C5D6E7F
- FLASH_SR (Status Register), Flash işlemleri sırasında hata ve durum bilgisi verir.
    - EOP: End of operation (işlem tamamlandı)
    - OPERR: Operation error
    - WRPERR: Write protection error
    - PGAERR: Programming alignment error
    - PGPERR: Programming parallelism error
    - PGSERR: Programming sequence error
    - BSY: Flash bellek işleminin devam etmekte olduğunu gösterir
- FLASH_CR (Control Register), Flash üzerinde silme, yazma ve programlama işlemlerini başlatır.
    - PG: Programlama modunu aktif et
    - SER: Sektör silme
    - MER: Tüm Flash’ı sil
    - SNB: Silinecek sektör numarası
        - 0000 sector 0
        - 0001 sector 1
        - ...
        - 1011 sector 11
    - PSIZE: Programlama boyutu 
        - 00 program x8
        - 01 program x16
        - 10 program x32
        - 11 program x64
    - STRT: Başlatma biti (işlemi başlatır)
    - EOPIE:  End of operation interrupt enable
    - LOCK: Register kilidi
        - Sadece 1 yazılabilir. Bu bit set edildiğinde,kontrol registerın kilitli olduğunu gösterir.
        - Kilit açma işlemi başarıyla algılandığında, bu bit donanım tarafından otomatik olarak sıfırlanır.
        - Eğer kilit açma işlemi başarısız olursa, bu bit bir sonraki reset yani yeniden başlatma gerçekleşene kadar setli kalır.
- FLASH_OPTCR (Option Control Register), Option byte ayarlarını tutar (boot ayarları, write protect, RDP vb.).
    - OPTLOCK: Option byte lock
    - OPTSTRT: Option byte programlama başlat
    - BOR_LEV: Brown-out reset seviyesi
    - WDG_SW: Watchdog donanım/yazılım seçimi
    - RDP: Read protection level
    - nWRP: Sektör write protection

### Konfigürasyon Ayarları
1. Flash kilidini aç (Unlock)
    - Flash belleğe yazmadan önce, kilidi açmak gerekir. Çünkü işlemci flash’ı korumalı tutar yanlışlıkla veri silinmesin diye. Bu yüzden unlock işlemi yapılır.
2. Gerekirse sektörü/sayfayı sil (Erase)
    - Flash’a yeni veri yazmadan önce, o bölge doluysa önce silmek gerekir. Silme işlemi sektör/page yapılır örneğin: Sektor/Page 3’ü sil gibi
    - Erase işlemi bittiğinde, bellekteki o alan 0xFF değerleriyle dolar.
3. Veriyi yaz (Program)
    - Flash yazma işlemi RAM’den farklıdır. Tek tek byte veya word halinde yazılır.
    - Yazarken işlemci, her yazılan kelimeyi Flash’a “programlar”. Bu sırada busy durumuna geçer, bitince tekrar hazır olur.
4. Flash’ı tekrar kilitle (Lock)
    - İş bitince lock yapılır. Bu, Flash register’larının tekrar korunmasını sağlar.
5. İstersen kontrol et (Verify)
    - Yazma işleminin doğru yapıldığını kontrol etmek için yazdığın adresi tekrar oku ve yazdığın veriyle karşılaştır.
6. Okuma için sadece adresi oku (Read)
    - Flash’ı okumak çok kolaydır. RAM’deki bir değişken gibi okunur. Yani sadece Flash adresinden veri alırsın.

## Clock

- STM32 mikrodenetleyicilerde saat (clock) sistemi oldukça esnektir ve farklı kaynaklardan gelen saat sinyalleri kullanılarak sistemin farklı bölümleri çalıştırılabilir.
- SYSCLK, mikrodenetleyicinin ana çekirdek saatidir. <br>
SYSCLK kaynağı olarak şunlar seçilebilir:
    - HSI
    - HSE
    - PLL (Phase Locked Loop) 
        - PLL kullanımı genellikle en yaygın sistem saat kaynağıdır çünkü yüksek frekanslar elde etmek mümkündür. HSE veya HSI kaynak olarak kullanılarak çarpanla yüksek frekanslar elde edilir.
- Cihazlarda ayrıca iki ikincil saat kaynağı bulunur:
    - LSI
    - LSE

| Kısaltma | Açılım               | Açıklama                                                                 |
|----------|----------------------|--------------------------------------------------------------------------|
| HSI      | High Speed Internal  | 8 MHz (bazı serilerde 16 MHz) dahili osilatör. Harici devre gerektirmez |
| HSE      | High Speed External  | Harici kristal osilatör veya osilatör devresi ile kullanılan saat kaynağıdır. Genellikle 8-25 MHz arası |
| LSI      | Low Speed Internal   | ~32 kHz civarında, düşük frekanslı dahili osilatör. RTC veya watchdog için kullanılır |
| LSE      | Low Speed External   | Harici 32.768 kHz kristal. Genelde gerçek zamanlı saat (RTC) için        |

<img src="image\image-15.png" width="700"> <br>

- AHB (Advanced High-performance Bus) Clock, STM32 mikrodenetleyicilerde saat sistemi, SYSCLK olarak adlandırılan sistem saatinden türetilen AHB ve APB veriyolları üzerinden çevre birimlere dağıtılır. SYSCLK, öncelikle AHB adı verilen yüksek hızlı veri yoluna aktarılır. RAM, Flash bellek, DMA ve GPIO gibi yüksek hız gereksinimi olan birimlerin saat kaynağını sağlar. Bu saat, prescaler kullanılarak gerektiğinde yavaşlatılabilir; örneğin 1, 2, 4, 8 gibi bölücülerle çalışabilir. AHB üzerinden türeyen iki önemli alt saat yolu ise APB1 ve APB2’dir. 
    - APB1 (Advanced Peripheral Bus 1), APB1, daha düşük hızda çalışması gereken çevre birimlerine hizmet verir. Bu bus üzerinden USART2 ve USART3 gibi seri haberleşme birimleri, I2C arayüzleri, CAN modülü, DAC ve zamanlayıcılar (TIM2-TIM7 gibi) çalıştırılır. Genellikle bu veri yolu için tanımlanan maksimum frekans STM32F4 serisinde 42 MHz’tir.
    - APB2 (Advanced Peripheral Bus 2), PB2 veri yolu daha yüksek hızlara uygun çevre birimlerini besler. Bu bus üzerinden USART1, SPI1, ADC ve TIM1 gibi çevre birimleri saat sinyali alır. STM32F4 serisinde APB2'nin maksimum frekansı genellikle 84 MHz’e kadar çıkabilir. Bu yapı sayesinde farklı hız gereksinimleri olan çevre birimleri, sistem performansı ve enerji verimliliği gözetilerek uygun saat kaynaklarıyla çalıştırılabilir.
- STM32 mikrodenetleyicilerde clock yapılandırma süreci, öncelikle sistemin hangi ana saat kaynağını kullanacağına karar verilmesiyle başlar; bu kaynak dahili HSI veya harici HSE osilatörü olabilir. Seçilen bu saat kaynağı, ihtiyaç duyulan daha yüksek frekanslar için PLL (Phase-Locked Loop) devresi kullanılarak çarpılabilir. PLL kullanımı sayesinde sistem saati (SYSCLK) istenilen frekansa yükseltilmiş olur. Belirlenen SYSCLK daha sonra AHB veri yoluna aktarılır ve buradan AHB’ye bağlı çevre birimlerine saat sinyali sağlanır. AHB üzerinden türetilen APB1 ve APB2 veri yolları aracılığıyla ise düşük ve yüksek hızlı çevre birimlerine uygun saat sinyalleri dağıtılarak sistem genelinde senkronizasyon sağlanır.

<img src="image\image-16.png" width="300"> <br>

- APB1 frekansı düşük tutulur çünkü düşük hızlı çevre birimleri buraya bağlıdır.
- RCC (Reset and Clock Control) register’ları üzerinden bu ayarlar yapılır.

### Çevresel Saat Etkinleştirme Kayıtları

- Her bir çevresel birimin saati, ilgili register kayıtlarındaki etkinleştirme biti ile etkinleştirilebilir. <br>
Çevresel saat aktif değilken, çevresel birimin kayıtlarına okuma veya yazma erişimleri desteklenmez.
- Etkinleştirme bitinin, çevresel birim için parazitsiz glitch-free bir saat oluşturmak üzere bir senkronizasyon mekanizması vardır. <br>
Etkinleştirme biti set edildikten sonra, saatin aktif hale gelmesi için 2 saat döngüsü (clock cycle) gecikme vardır. Bu durum, yazılım tarafından dikkate alınmalıdır.

## Birim Yapısı

<img src="image\image-17.png" width="800"> <br>





















































































































































































































































