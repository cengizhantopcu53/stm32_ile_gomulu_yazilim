# CAN Kullanımı

> ## **HAL**

## Giriş

• Master buton ile kesme tetiklenir ve CAN Tx üzerinden Slave cihaza veri yollanır, eğer Slave'den veri gelirse CAN Rx kesmesine girer ve led blink işlemi gerçekleştirip tekrar CAN Tx üzerinden Slave cihaza veri yollanır. <br>
• SN65HVD230 entegre ile örnek yapacağız. <br>
• https://www.youtube.com/playlist?list=PL1mJWraoUnOn7DXaqdZrfbejS6mle2voQ, https://www.youtube.com/playlist?list=PLfIJKC1ud8gjzwOPq9fvQt38Ut7EjsgwI, https://youtu.be/6D8HBUpNedU?si=AaZC05jta5cBb6LLlinkteki videoları ya da https://www.udemy.com/course/stm32f4-discovery-karti-ile-can-bus-dersleri/ kurstaki ilgili bölümü izleyebiliriz. <br>
 
## Teori

## Konfigürasyon Kısmı

<img src="image\image-1.png" width="450"> <br>
<img src="image\image-2.png" width="450"> <br>
• A5 pini **led** için C13 pini **button** için kullacağız.<br> Buttonu **external interrupt** şeklinde kullanacağız. <br>
• Ardından haberleşmemiz için **CAN1** seçimi yapılır. <br>
• CAN1_RX pini **Pull-up** olarak ayarlanır ve **Interrupt** Enabled edilir. <br>
• Parameters Setting kısmından **Prescalar** ve **Time Quanta** değerleri oynayarak Baud Rate **500000 bps** ayarlanır. <br>
• Registerda Prescaler için 10 bitlik alan 1 ile 1024 arası,Time Quanta 1 için 4 bitlik alan 1 ile 16 arası, Time Quanta 2 değeri 3 bitlik alan 1 ile 8 arası değer alabilir.
• Çalışma Modu **Normal Mode**'dur. <br>
<img src="image\image-3.png" width="300"> <br>
• Aşağıdaki formül kullarak hesaplayabiliriz.  <br>
*Baud Rate = PCLK / ( Prescaler * ( 1 + Tseg1 + Tseg2 ))* <br>
• CAN1, **APB1** clock hattına bağlıdır ve işlemci hızı 180MHz seçildiğinde hat 45Mhz olmaktadır. <br>
• Baud Rate 500kHz (500000 bit/s), PCLK 45MHz ve örnekleme noktasını %70 olarak kullanacağız. <br>
• Formülden (1 + Tseg1 + Tseg2) için bu değere KUANTA diyelim. <br>
• Bilinen değerleri formülde yerine koyalım. <br>
Prescaler = 45M / ( 500k * KUANTA) <br>
• KUANTA = 10, Prescaler = 9 olacak şekilde denklemi çözeriz.<br>
• Şimdi Tseg1 ile Tseg2 arasındaki oranı ayarlayalım <br>
10 = (1 + Tseg1 + Tseg2) <br>
• Örnekleme noktası oranı periyodun %70'ine denk gelmesini istiyoruz.<br> 
Örnekleme Noktası = (KUANTA * 70) / 100 <br>
Dolayısıyla 10 * 0.7 = 7 olur. Buradan Tseg1 = 6 için ve Tseg2 = 3 olarak bulunur. Bu durumda örnekleme noktası %70'e denk gelir.<br>
<img src="image\image-4.png" width="450"> <br>
• Buton kesmesinin CAN RX kesmesinden daha önce çalışmasını istediğimizden CAN1 RX0 interrupt'ın Sub Priority değeri 1 seçilir.

## Kod Kısmı

• `HAL_CAN_Init` fonksiyonu ile çevre birimi için yaptığımız konfigrasyon ayarlarını registerda ilgili yerlere kaydetmiş oluruz. <br> 
```c
  CAN_HandleTypeDef hcan1;

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 9;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_6TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;

  HAL_CAN_Init(&hcan1);
```
<br> 

• Modülü başlatmak için `HAL_CAN_Start` fonksiyonu kullanırız. <br> Burada MCR registerında INRQ biti temizlenir ve MSR registerında INAK biti kontrol edilir. <br>
• **Interrupt** kullanabilmek için `HAL_CAN_ActivateNotification` fonksiyonu kullanmalıyız. <br>
Receive olduğunda kesmeye girmesi istediğimiz için IER registerında **FMPIE0** biti 1 yapmak için fonksiyona parametre olarak `CAN_IT_RX_FIFO0_MSG_PENDING` tanımlayıcısı kullanır. <br>
```c
  HAL_CAN_Start(&hcan1);
  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);
```
 <br>

• Data Frame'e ulaşmak için `CAN_TxHeaderTypeDef` türünden bir **TxHeader** ile `CAN_RxHeaderTypeDef` türünden bir **RxHeader**, gönderilecek veya alınacak veriler için boyutu 8 byte olan **TxData** ve **RxData** dizileri, Header ve veri mesajını taşıyacak olan bir posta kutusu **TxMailbox** ve Slave'den veri geldiğini onaylamak amacıyla kullanılan **datacheck** değişkeni oluşturulmuştur. <br>
```c
 CAN_TxHeaderTypeDef TxHeader;
 CAN_RxHeaderTypeDef RxHeader;

 uint8_t TxData[8];
 uint8_t RxData[8];

 uint32_t TxMailbox;

 uint8_t datacheck = 0;
```
 <br>

• Burada CAN_ID_STD, **Standart ID**'yi kullandığımız anlamına gelir. <br>
• 0x446 **Identifier**'dır. Bu, vericinin ID'sdir ve Standart ID için maksimum **11 bit** genişliğinde olmalıdır. <br>
• CAN_RTR_DATA, bir **veri çerçevesi** gönderdiğimizi gösterir. <br>
• DLC, **veri baytlarının uzunluğudur** ve burada 2 veri byte gönderiyoruz. <br>
```c
TxHeader.IDE = CAN_ID_STD;
TxHeader.StdId = 0x446;
TxHeader.RTR = CAN_RTR_DATA;
TxHeader.DLC = 2;
```
 <br>

• Butona basıldığında `HAL_GPIO_EXTI_Callback` callback fonksiyonu çalışır
```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == GPIO_PIN_13)
	{
		TxData[0] = 100;   
		TxData[1] = 40;    

		HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	}
}
```
 <br>

• Veri gönderme işlemi, `HAL_CAN_AddTxMessage` fonksiyonunu kullanarak yapıyoruz. Aşağıdaki parametrelere sahiptir. <br>
```c
HAL_StatusTypeDef HAL_CAN_AddTxMessage(CAN_HandleTypeDef *hcan, CAN_TxHeaderTypeDef *pHeader, uint8_t aData[], uint32_t *pTxMailbox)
```
 <br>

• Slave'e veri önderme işlemini yaptık sırada veriyi alma işlemi var. Bunun için interrupt kullanacağız.
• Eğer Slave'den veri gelir ise RX_FIFO 0'da bekleyen mesaj olur ve kesmeyi tetikler ve böylece bir callback fonksiyonu olan `HAL_CAN_RxFifo0MsgPendingCallback` çağrılır. <br>
```c
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	if (RxHeader.StdId == 0x103)
	{
		datacheck = 1;
	}
}
```
<br>

• Veri alma işlemini `HAL_CAN_GetRxMessage` fonksiyonunu kullanarak yapıyoruz. <br> Aşağıdaki parametrelere sahiptir. <br>
• Fonksiyonun ikinci parametresi, alınan verilerin okunacağı FIFO numarasıdır. <br>
```c
HAL_StatusTypeDef HAL_CAN_GetRxMessage(CAN_HandleTypeDef *hcan, uint32_t RxFifo, CAN_RxHeaderTypeDef *pHeader, uint8_t aData[])
```
<br>

• Ana döngü kodumuz aşağıdadır. Buton ile haberleşmeyi başlattıktan sonra Slave'den veri gelmesi beklenir eğer veri gelirse datacheck aktif olur ve ana döngü kodumuz çalışır. <br>
Gelen datanın birinci datası, ledin kaç ms'de bir çalışacağını; ikinci data, ledin kaç kez çalışacağını ayarlar. <br>
Sonra tekrar Slave'e veri gönderilir.
```c
  while (1)
  {
	  if (datacheck)
	  {
		  for (int i=0; i < RxData[1]; i++){
			  HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
			  HAL_Delay(RxData[0]);
		  }
		  datacheck = 0;

		  TxData[0] = 100;  
		  TxData[1] = 40;    

		  HAL_CAN_AddTxMessage(&hcan1, &TxHeader, TxData, &TxMailbox);
	  }
  }
```
 <br>

• Mesaj CAN veri yoluna gönderildiğinde ve bu veri yolundaki tüm CAN aygıtları yollanan mesajı bir şekilde alacaktır. Bir şekilde dedim çünkü mesajın alınıp alınmayacağı her aygıt için **Filter Configuration** bağlıdır. Eğer mesaj filtredeki şartları sağlıyorsa ancak o zaman geçmesine izin verilecektir. <br>
• Mesajları filtreleme işlemini yaparken CPU yükünü azaltmak amacıyla işlemcinin CAN çevre biriminin içine yerleştirilmiş filtreleri vardır. <br>

```c
  CAN_FilterTypeDef canfilterconfig;

  canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
  canfilterconfig.FilterBank = 18;
  canfilterconfig.FilterFIFOAssignment = CAN_FILTER_FIFO0;
  canfilterconfig.FilterIdHigh = 0x103 << 5;
  canfilterconfig.FilterIdLow = 0;
  canfilterconfig.FilterMaskIdHigh = 0x103 << 5;
  canfilterconfig.FilterMaskIdLow = 0x0000;
  canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
  canfilterconfig.FilterScale = CAN_FILTERSCALE_32BIT;
  canfilterconfig.SlaveStartFilterBank = 20;

  HAL_CAN_ConfigFilter(&hcan1, &canfilterconfig);
```
• `FilterActivation`, filtreyi etkinleştirin veya devre dışı bırakın. <br>
• `FilterBank`, başlatılacak filtre bankasını belirtir. <br>
• `FilterFIFOAssignment`, Filtreye atanacak FIFO'yu belirtir. <br>
• `FilterIdHigh` ile `FilterIdLow`, filtre tanımlama numarasını ve `FilterMaskIdHigh` ve `FilterMaskIdLow`, filtre maskesi numarasını belirtir. <br>
Standart ID, **11 bit** uzunluğundadır. Ancak bu tanımlanan filte numaraları **16 bit** olduğundan, ID değeri bu 16 bit içinde uygun pozisyona yerleştirilir. Bu nedenle **5 bit sola kaydırma** yapılır.
• `FilterMode`, başlatılacak filtre modunu belirtir. <br>
• `FilterScale`, filtre ölçeğini belirtir <br>
• `SlaveStartFilterBank`, Slave CAN birimi için başlangıç filtre bankasını seçin
Burada sadece gelen mesajın STD ID'sini karşılaştırmaya karar verdim ve bu yüzden değeri 5 ile kaydırıyorum. STD ID, ID HIGH Register'daki 5. bitten başlar

---

<br>