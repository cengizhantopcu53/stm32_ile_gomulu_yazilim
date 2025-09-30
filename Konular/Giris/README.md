# Giris

- Gömülü yazılım, belirli bir donanım üzerinde belirli görevleri yerine getirmek üzere tasarlanmış, genellikle gerçek zamanlı çalışan özel amaçlı yazılımlardır. Bu yazılımlar; ev aletlerinden otomobillere, endüstriyel kontrol sistemlerinden tıbbi cihazlara kadar birçok cihazın içinde yer alır ve donanımın beyni olarak görev yapar.
- Gömülü sistemlerde, yazılım doğrudan mikrodenetleyici (MCU) veya mikroişlemci (MPU) gibi donanım bileşenleri üzerinde çalışır. Bu tür sistemlerde performans, bellek ve enerji tüketimi gibi sınırlamalar dikkate alınarak optimize edilmiş yazılımlar geliştirilir. Gömülü yazılım; donanımı doğrudan kontrol edebilen, kesme yönetimi yapabilen, haberleşme protokollerini işleyebilen ve genellikle işletim sistemi olmadan (bare-metal) ya da gerçek zamanlı işletim sistemi (RTOS) ile çalışan yapılardır.
- Gömülü yazılım geliştirme süreci; donanımı tanımayı, düşük seviyeli programlamayı, hata ayıklamayı ve sistem kaynaklarını verimli kullanmayı gerektirir. Bu alandaki yazılımcılar, yalnızca yazılım bilgisine değil, aynı zamanda donanım bilgisine de sahip olmalıdır.
- Bu kitapçıkta, gömülü yazılım dünyasına adım atmak isteyenler için temel kavramlardan başlayarak pratik uygulamalara kadar birçok konuyu ele alacağız. Amacımız, yazılım geliştiricilere hem teorik hem de uygulamalı bir bakış açısı kazandırmaktır.

## Temel Kavramlar

- STM32 Donanım Soyutlama Katmanı (HAL) Yazısı linkten donanım soyutlama katmanı hakkındaki yazıyı okuyabilirsiniz.
Gömülü Sistem, Mikroişlemci, Mikrodenetleyici Nedir?  ile Mikroişlemci Hakkında Bilgilendirme linkteki Gömülü Sistem, Mikroişlemci, Mikrodenetleyici nedir sorularına cevap veren yazıları okuyabilirsiniz.

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
