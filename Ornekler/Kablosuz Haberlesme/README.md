
# Kablosuz Haberleşme

> ## **LORA**

#### E32

## Giriş

• LoRa haberleşme, uzun menzilli düşük güç tüketimli kablosuz bir iletişim protokolüdür. <br> 
Düşük veri hızlarında geniş kapsama alanı sağlamak amacıyla optimize edilmiştir. <br>
• Ebyte firmasının E32, E220; Elecrow firmasının RA-01 gibi LoRa haberleşme modülleri sıklıkla kullanılıyor. <br>
• E32 ve RA-01 modüllerinin içinde SX1278; E220 modülün içinde LLCC68 LoRa transceiver yongası kullanılmaktadır. Bu yongalar Semtech tarafından geliştirilen ve LoRa teknolojisini uygulamak için kullanılan bir yongadır. <br> 
• Düşük güç tüketimi ve uzun menzil özelliklerine sahiptir. LoRa modülasyonunu destekleyerek veri iletimini geniş bir kapsama alanında ve düşük veri hızlarıyla gerçekleştirebilir. 433MHz, 868MHz veya 915MHz frekans bantlarında çalışabilen farklı sürümleri bulunur. <br>
• Bu sadece bazı örneklerdir ve pazarda birçok farklı LoRa haberleşme modülü bulunmaktadır. Modül seçimi, kullanım senaryosuna, uyumluluğa, maliyet faktörlerine ve diğer gereksinimlere bağlı olarak yapılmalıdır. Modüller genellikle üreticinin sağladığı yazılım kütüphaneleri veya geliştirme araçlarıyla birlikte gelir ve LoRa haberleşmesini kolayca entegre etmenize olanak tanır. <br>
• Ebyte ürünleri için https://fixaj.com/lora-modulunun-temelleri/ linkinden lora hakkında detaylı bilgi alabiliriz. https://github.com/Bob0505/E32-TTL-100 link ile kod ile parametre ayarı ve veri alışverişin nasıl yapıldığını öğrenebiliriz. https://www.ebyte.com/en/product-class.html link üzerinden satıcının ürün hakkında paylaştığı dökümanlara ulaşabiliriz. <br>
• RA-01 için https://www.circuitstate.com/tutorials/interfacing-ra-01-ra-02-sx1278-lora-modules-with-esp32-using-arduino/ ile https://blog.domski.pl/stm32-hal-driver-for-lora-sx1278-wireless-module/ link ile modül hakkında bilgi edinebilir, https://youtu.be/jMGnSQyCUqw link ile uygulamalı örnek yapabiliriz. <br>

## Teori

• Kullanacağımız modülün default hali aşağıdaki durumdadır. <br> 
<img src="image\image-1.png" width="550"> <br>
• Modüllerin parametre ayarlarında değişiklik yapmak için RF Setting programını kullanıyoruz. <br>
• Program ile modül bağlantı için TTL dönüştürücü kullanırız. <br>
<img src="image\image-2.png" width="400"> <br>
• Her iki modül için aşağıdaki seçimler yapılır daha sonra Address ve Channel değerleri yazılır. <br> 
<img src="image\image-3.png" width="350"> <br>
• Channel değeri frekansı temsil ediyor. 410 + Channel değeri bize kullanacağımız frekans değerini veriyor. Biz 433MHz'de haberleşme yapacağımızdan her iki modül için 23 değerini yazıyoruz. <br>
• Address değeri her iki modül için farklı olmalıdır. Alıcı için 1281, verici için 1282 değerlerini kullanacağız. <br>
Kod içerisinde değerleri hex şeklinde yazmamız gerekir. Decimal değerleri hex'e çevirirsek 1281 değeri 501, 1282 değeri 502, 23 değeri 17 oluyor. <br> 
• Gönderilen dizisinin ilk iki elemanı alıcının adresi, üçüncü elemanı kanal bilgisidir ve sonrası gönderilecek verilerdir. <br>
• Fixed modda adres ve kanal bilgisi gerekirken broadcast modda sadece kanal bilgisi yazılır. <br> 
• Modülün M0 ve M1 pinleri sıfıra çekildi.

---

> ## **NRF24**

## Teori

• [Örnek](https://youtu.be/O2dg2Eo7vo8) için linkten yararlanıyoruz. <br>
• CE modülü aktif hale getirirken CSN ise SPI haberleşmeyi aktif ediyor. CE low iken NRF modülün üzerindeki çipin gücünü kapatmış oluyoruz. Konfigürasyon ayarlarında CE ve CSN pinini output olarak kullanıyoruz. <br>
• Modül transmit ve receive işlemini gerçekleştirirken bir interrupt oluşturuyor ve bunu IRQ pini ile gerçekleştiriyor. Konfigürasyon ayarlarında IRQ pini için input değil exti olarak kullanıyoruz. <br>

---

<br>