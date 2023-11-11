
# Arayuz ile Test Etme
• Mikrodenetleyici üzerinden gönderdiğimiz verileri Grafiksel Kullanıcı Arayüzü (GUI) uygulamaları ile verileri görselleştirebiliriz. Masaüstü tarafında C#, Matlab, Pyhton; Mobil uygulamada Java, Kotlin, Flutter gibi diller kullanabiliriz.

#### Firmware

```c
int main(void)
{

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_USART1_UART_Init();

  while (1)
  {
	    if (HAL_UART_Receive(&huart1, (uint8_t*) &c, 1, HAL_MAX_DELAY) == HAL_OK)
	    {
	      if (c == '1')
	      {
	        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
	        HAL_UART_Transmit(&huart1, (uint8_t*) "Led Yandi\r\n", 11, HAL_MAX_DELAY);
	      }
	      else if (c == '0')
	      {
	        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
	        HAL_UART_Transmit(&huart1, (uint8_t*) "Led Sondu\r\n", 11, HAL_MAX_DELAY);
	      }
	    }
  }
}
``` 
#### Software

> ## **C#**

## Giriş

• C# dili için Visual Studio IDE üzerinden Windows Form veya WPF kullanabiliriz. 
• https://youtu.be/vtI6Wd7DogQ linkteki videoyu izleyerek konuya giriş yapabiliriz. Yapılmış örnek çalışmalara https://maker.robotistan.com/kategori/arduino/arduino-c-sharp-projeleri/ linkten ulaşabiliriz. Bu konuda daha ayrıntılı bilgi almak için https://www.youtube.com/playlist?list=PLT19xuXjmpJTbKhcx3sBpgcf6sAIbAtPt , https://www.youtube.com/playlist?list=PLre4S1H8v3bSKyBpziWr_gcYMuA3iiO7Y ile https://www.youtube.com/playlist?list=PL33a8qXOY4kfskfUr_4BnrzFu1znytMOb linklerdeki oynatma listesine eğer kurs olarak izlemek isterseniz https://www.udemy.com/course/stm32-programlama-ve-c-uzerinde-test-etme/ linke bakabilirsiniz.
• https://koddefteri.net/c-sharp/c-sharp-ile-seri-port-kullanimi.html , https://mustafabukulmez.com/2021/05/06/c-seri-port-rs232-veri-okuma/ ve https://www.kaizen40.com/c-seri-port-oku-yaz/ linkteki makaleleri okuyabiliriz.


## Teori

## Kod Kısmı


---

<br>
