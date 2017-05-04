#include  "rf_wireless.h"
#include "string.h"

// Configuration Registers
#define TI_CCxxx0_IOCFG2       0x00        // GDO2 output pin configuration
#define TI_CCxxx0_IOCFG1       0x01        // GDO1 output pin configuration
#define TI_CCxxx0_IOCFG0       0x02        // GDO0 output pin configuration
#define TI_CCxxx0_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define TI_CCxxx0_SYNC1        0x04        // Sync word, high byte
#define TI_CCxxx0_SYNC0        0x05        // Sync word, low byte
#define TI_CCxxx0_PKTLEN       0x06        // Packet length
#define TI_CCxxx0_PKTCTRL1     0x07        // Packet automation control
#define TI_CCxxx0_PKTCTRL0     0x08        // Packet automation control
#define TI_CCxxx0_ADDR         0x09        // Device address
#define TI_CCxxx0_CHANNR       0x0A        // Channel number
#define TI_CCxxx0_FSCTRL1      0x0B        // Frequency synthesizer control
#define TI_CCxxx0_FSCTRL0      0x0C        // Frequency synthesizer control
#define TI_CCxxx0_FREQ2        0x0D        // Frequency control word, high byte
#define TI_CCxxx0_FREQ1        0x0E        // Frequency control word, middle byte
#define TI_CCxxx0_FREQ0        0x0F        // Frequency control word, low byte
#define TI_CCxxx0_MDMCFG4      0x10        // Modem configuration
#define TI_CCxxx0_MDMCFG3      0x11        // Modem configuration
#define TI_CCxxx0_MDMCFG2      0x12        // Modem configuration
#define TI_CCxxx0_MDMCFG1      0x13        // Modem configuration
#define TI_CCxxx0_MDMCFG0      0x14        // Modem configuration
#define TI_CCxxx0_DEVIATN      0x15        // Modem deviation setting
#define TI_CCxxx0_MCSM2        0x16        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM1        0x17        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_MCSM0        0x18        // Main Radio Cntrl State Machine config
#define TI_CCxxx0_FOCCFG       0x19        // Frequency Offset Compensation config
#define TI_CCxxx0_BSCFG        0x1A        // Bit Synchronization configuration
#define TI_CCxxx0_AGCCTRL2     0x1B        // AGC control
#define TI_CCxxx0_AGCCTRL1     0x1C        // AGC control
#define TI_CCxxx0_AGCCTRL0     0x1D        // AGC control
#define TI_CCxxx0_WOREVT1      0x1E        // High byte Event 0 timeout
#define TI_CCxxx0_WOREVT0      0x1F        // Low byte Event 0 timeout
#define TI_CCxxx0_WORCTRL      0x20        // Wake On Radio control
#define TI_CCxxx0_FREND1       0x21        // Front end RX configuration
#define TI_CCxxx0_FREND0       0x22        // Front end TX configuration
#define TI_CCxxx0_FSCAL3       0x23        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL2       0x24        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL1       0x25        // Frequency synthesizer calibration
#define TI_CCxxx0_FSCAL0       0x26        // Frequency synthesizer calibration
#define TI_CCxxx0_RCCTRL1      0x27        // RC oscillator configuration
#define TI_CCxxx0_RCCTRL0      0x28        // RC oscillator configuration
#define TI_CCxxx0_FSTEST       0x29        // Frequency synthesizer cal control
#define TI_CCxxx0_PTEST        0x2A        // Production test
#define TI_CCxxx0_AGCTEST      0x2B        // AGC test
#define TI_CCxxx0_TEST2        0x2C        // Various test settings
#define TI_CCxxx0_TEST1        0x2D        // Various test settings
#define TI_CCxxx0_TEST0        0x2E        // Various test settings

// Strobe commands
#define TI_CCxxx0_SRES         0x30        // Reset chip.
#define TI_CCxxx0_SFSTXON      0x31        // Enable/calibrate freq synthesizer
#define TI_CCxxx0_SXOFF        0x32        // Turn off crystal oscillator.
#define TI_CCxxx0_SCAL         0x33        // Calibrate freq synthesizer & disable
#define TI_CCxxx0_SRX          0x34        // Enable RX.
#define TI_CCxxx0_STX          0x35        // Enable TX.
#define TI_CCxxx0_SIDLE        0x36        // Exit RX / TX
#define TI_CCxxx0_SAFC         0x37        // AFC adjustment of freq synthesizer
#define TI_CCxxx0_SWOR         0x38        // Start automatic RX polling sequence
#define TI_CCxxx0_SPWD         0x39        // Enter pwr down mode when CSn goes hi
#define TI_CCxxx0_SFRX         0x3A        // Flush the RX FIFO buffer.
#define TI_CCxxx0_SFTX         0x3B        // Flush the TX FIFO buffer.
#define TI_CCxxx0_SWORRST      0x3C        // Reset real time clock.
#define TI_CCxxx0_SNOP         0x3D        // No operation.

// Status registers
#define TI_CCxxx0_PARTNUM      0x30        // Part number
#define TI_CCxxx0_VERSION      0x31        // Current version number
#define TI_CCxxx0_FREQEST      0x32        // Frequency offset estimate
#define TI_CCxxx0_LQI          0x33        // Demodulator estimate for link quality
#define TI_CCxxx0_RSSI         0x34        // Received signal strength indication
#define TI_CCxxx0_MARCSTATE    0x35        // Control state machine state
#define TI_CCxxx0_WORTIME1     0x36        // High byte of WOR timer
#define TI_CCxxx0_WORTIME0     0x37        // Low byte of WOR timer
#define TI_CCxxx0_PKTSTATUS    0x38        // Current GDOx status and packet status
#define TI_CCxxx0_VCO_VC_DAC   0x39        // Current setting from PLL cal module
#define TI_CCxxx0_TXBYTES      0x3A        // Underflow and # of bytes in TXFIFO
#define TI_CCxxx0_RXBYTES      0x3B        // Overflow and # of bytes in RXFIFO
#define TI_CCxxx0_NUM_RXBYTES  0x7F        // Mask "# of bytes" field in _RXBYTES

// Other memory locations
#define TI_CCxxx0_PATABLE      0x3E
#define TI_CCxxx0_TXFIFO       0x3F
#define TI_CCxxx0_RXFIFO       0x3F

// Masks for appended status bytes
#define TI_CCxxx0_LQI_RX       0x01        // Position of LQI byte
#define TI_CCxxx0_CRC_OK       0x80        // Mask "CRC_OK" bit within LQI byte

// Definitions to support burst/single access:
#define TI_CCxxx0_WRITE_BURST  0x40
#define TI_CCxxx0_READ_SINGLE  0x80
#define TI_CCxxx0_READ_BURST   0xC0

//-----------------1101------------------------
//PC7---PC6---PB12---PB13---PB14---PB15
//  |	  |		|	    |		   |		  |
//GDO0-GDO2--CSn----SCLK--MISO---  MOSI  

#define SPI_CSn_GPIO 	GPIOB  
#define SPI_CSn_RCC	    RCC_APB2Periph_GPIOB
#define SPI_CSn_Pin	    GPIO_Pin_12
#define SPI_CSn_1  	    GPIO_SetBits(SPI_CSn_GPIO, SPI_CSn_Pin)        
#define SPI_CSn_0       GPIO_ResetBits(SPI_CSn_GPIO, SPI_CSn_Pin)    

#define	SPI_SCLK_GPIO 	GPIOB  
#define SPI_SCLK_RCC	RCC_APB2Periph_GPIOB
#define	SPI_SCLK_Pin	GPIO_Pin_13
#define SPI_SCLK_1      GPIO_SetBits(SPI_SCLK_GPIO, SPI_SCLK_Pin)
#define SPI_SCLK_0      GPIO_ResetBits(SPI_SCLK_GPIO, SPI_SCLK_Pin)

#define	SPI_MISO_GPIO	GPIOB  
#define	SPI_MISO_RCC	RCC_APB2Periph_GPIOB
#define	SPI_MISO_Pin	GPIO_Pin_14
#define SPI_MISO_1      GPIO_SetBits(SPI_MISO_GPIO, SPI_MISO_Pin)
#define SPI_MISO_0      GPIO_ResetBits(SPI_MISO_GPIO, SPI_MISO_Pin)
#define SPI_MISO_IN     GPIO_ReadInputDataBit(SPI_MISO_GPIO, SPI_MISO_Pin) 

#define SPI_MOSI_GPIO	GPIOB  
#define SPI_MOSI_RCC	RCC_APB2Periph_GPIOB
#define SPI_MOSI_Pin	GPIO_Pin_15
#define SPI_MOSI_1      GPIO_SetBits(SPI_MOSI_GPIO, SPI_MOSI_Pin)
#define SPI_MOSI_0      GPIO_ResetBits(SPI_MOSI_GPIO, SPI_MOSI_Pin)

#define	SPI_GDO0_GPIO	GPIOB 
#define	SPI_GDO0_RCC	RCC_APB2Periph_GPIOB
#define	SPI_GDO0_Pin	GPIO_Pin_6
#define SPI_GDO0_1      GPIO_SetBits(SPI_GDO0_GPIO, SPI_GDO0_Pin)
#define SPI_GDO0_0      GPIO_ResetBits(SPI_GDO0_GPIO, SPI_GDO0_Pin)
#define TI_CC_GDO0_IN   GPIO_ReadInputDataBit(SPI_GDO0_GPIO, SPI_GDO0_Pin)

#define	SPI_GDO2_GPIO	GPIOB 
#define	SPI_GDO2_RCC	RCC_APB2Periph_GPIOB
#define	SPI_GDO2_Pin	GPIO_Pin_8
#define SPI_GDO2_1      GPIO_SetBits(SPI_GDO2_GPIO, SPI_GDO2_Pin)
#define SPI_GDO2_0      GPIO_ResetBits(SPI_GDO2_GPIO, SPI_GDO2_Pin)
#define TI_CC_GDO2_IN   GPIO_ReadInputDataBit(SPI_GDO2_GPIO, SPI_GDO2_Pin)

#define MAX_CHANNER     121 //(0~120)
#define MAX_SPD_RATE      7 //(0~6)
static const CPU_INT08U MDMCFG4[]={0xF6,0xC8,0xCA,0x7B,0x5B,0x2D,0x0E};
static const CPU_INT08U MDMCFG3[]={0x83,0x93,0x83,0x83,0xF8,0x3B,0x3B};	
static const CPU_INT08U DEVIATN[]={0x15,0x34,0x35,0x42,0x47,0x62,0x67};
static const CPU_INT08U FSCTRL1[]={0x06,0x06,0x06,0x08,0x08,0x0C,0x0E};
static const CPU_INT08U PowerTab[] = {0x60,0x84,0xc8,0xc0};//cc1101send power 0,5,7,10dB
static CPU_INT08U RSSI;

 void SPIInit(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  
  /* Enable GPIO OUT */
  GPIO_InitStructure.GPIO_Pin = SPI_CSn_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* Enable GPIO IN */
  GPIO_InitStructure.GPIO_Pin = SPI_MISO_Pin| SPI_MOSI_Pin | SPI_SCLK_Pin;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  /* Connect GDO0 EXTI Line to GDO0 GPIO Pin */
  GPIO_InitStructure.GPIO_Pin = SPI_GDO0_Pin ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SPI_GDO0_GPIO, &GPIO_InitStructure);

  /* SPI2 configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex; 
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);
  SPI_Cmd(SPI2, ENABLE);
  
  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);
  EXTI_InitStructure.EXTI_Line = EXTI_Line6;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
//  EXTI_GenerateSWInterrupt(EXTI_Line6);
  
  BSP_IntVectSet(BSP_INT_ID_EXTI9_5, BSP_IntHandlerEXTI9_5); 
  BSP_IntPrioSet(BSP_INT_ID_EXTI9_5,1);   
  BSP_IntDis(BSP_INT_ID_EXTI9_5);
}

/* enable interrupt pc.7*/
 void PortC7EnInt(void)
{
  BSP_IntEn(BSP_INT_ID_EXTI9_5);  
}
/*disable interrupt pc.7*/
 void PortC7DisInt(void)
{
  BSP_IntDis(BSP_INT_ID_EXTI9_5);
}

//*----------------------------------------------------------------------------
//*Function Name       :SPISendByte
//*Object              :Write the CC110X register 
//*Input parameters    :ch
//*Output parameters   :none
//*----------------------------------------------------------------------------
 CPU_INT08U SPISendByte(CPU_INT08U ch)
{
  /* Loop while DR register in not emplty */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET);
  /* Send byte through the SPI2 peripheral */
  SPI_I2S_SendData(SPI2, (uint16_t)ch);
  /* Wait to receive a byte */
  while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET);
  /* Return the byte read from the SPI bus */
  return (CPU_INT08U)SPI_I2S_ReceiveData(SPI2);
}

 CPU_INT08U SPIReceiveByte(void)
{
  return (CPU_INT08U)SPISendByte(0xAA);
}

 void TI_CC_SPIWriteReg(CPU_INT08U addr, CPU_INT08U value)
{
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(addr);
  SPISendByte(value);
  SPI_CSn_1;  
}

 void TI_CC_SPIWriteBurstReg(CPU_INT08U addr, CPU_INT08U *buffer, CPU_INT08U count)
{
  u8 i;
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(addr | TI_CCxxx0_WRITE_BURST);
  for (i = 0; i < count; i++)
  {
    SPISendByte(buffer[i]);
  }	
  SPI_CSn_1;  
}

 CPU_INT08U TI_CC_SPIReadReg(CPU_INT08U addr)
{
  u8 dat;
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(addr | TI_CCxxx0_READ_SINGLE);
  dat=SPIReceiveByte();
  SPI_CSn_1;
  return (dat);
}

 void TI_CC_SPIReadBurstReg(CPU_INT08U addr, CPU_INT08U *buffer, CPU_INT08U count)
{
  u16 i;
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(addr | TI_CCxxx0_READ_BURST);
  for(i=0;i<count;i++)
  {
    buffer[i]=SPIReceiveByte();
  }
  SPI_CSn_1;
}

 CPU_INT08U TI_CC_SPIReadStatus(CPU_INT08U addr)
{
  u8 dat;
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(addr | TI_CCxxx0_READ_BURST);
  dat=SPIReceiveByte();
  SPI_CSn_1;
  return dat;
}

 void TI_CC_SPIStrobe(CPU_INT08U strobe)
{
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(strobe);
  SPI_CSn_1;
}

 void TI_CC_PowerupResetwireless(void)
{
  SPI_CSn_1;
  Delay_10us(20);
  SPI_CSn_0;
  Delay_10us(20);
  SPI_CSn_1;
  Delay_10us(20);
  
  SPI_CSn_0;
//  while(SPI_MISO_IN);
  SPISendByte(TI_CCxxx0_SRES);
  while(SPI_MISO_IN);
  SPI_CSn_1;
}

/*****************************************************************
*fuction£ºvoid B_writeRFSettings(void) cc1101 configration register
*inlet parameter£ºvoid
*outlet parameter£ºvoid
******************************************************************/
 void writeRFSettings(void)
{          
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG2,   0x06); // GDO2 output pin config.     
    TI_CC_SPIWriteReg(TI_CCxxx0_IOCFG0,   0x06); // GDO0 output pin config.     
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTLEN,   0x3D); // Packet length.              
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL1, 0x04); // Packet automation control.  
    TI_CC_SPIWriteReg(TI_CCxxx0_PKTCTRL0, 0x05); // Packet automation control.  
    TI_CC_SPIWriteReg(TI_CCxxx0_ADDR,     0x00); // Device address.             
    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   0X60); // Channel number.  
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  0x08); // Freq synthesizer control.   
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL0,  0x00); // Freq synthesizer control.   
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ2,    0x10); // Freq control word, high byte
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ1,    0xA7); // Freq control word, mid byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_FREQ0,    0x62); // Freq control word, low byte.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  0X7B); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  0X83); // Modem configuration.
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG2,  0x03); // Modem configuration.        
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG1,  0x22); // Modem configuration.        
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG0,  0xF8); // Modem configuration.        
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  0x42); // Modem dev (when FSK mod en) 
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM1 ,   0x30); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_MCSM0 ,   0x18); //MainRadio Cntrl State Machine
    TI_CC_SPIWriteReg(TI_CCxxx0_FOCCFG,   0x1D); // Freq Offset Compens. Config 
    TI_CC_SPIWriteReg(TI_CCxxx0_BSCFG,    0x1C); //  Bit synchronization config.
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL2, 0xC7); // AGC control.                
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL1, 0x00); // AGC control.                
    TI_CC_SPIWriteReg(TI_CCxxx0_AGCCTRL0, 0xB2); // AGC control.                
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND1,   0xB6); // Front end RX configuration. 
    TI_CC_SPIWriteReg(TI_CCxxx0_FREND0,   0x10); // Front end RX configuration. 
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL3,   0xEA); // Frequency synthesizer cal.  
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL2,   0x2A); // Frequency synthesizer cal.  
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL1,   0x00); // Frequency synthesizer cal.  
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCAL0,   0x1F); // Frequency synthesizer cal.  
    TI_CC_SPIWriteReg(TI_CCxxx0_FSTEST,   0x59); // Frequency synthesizer cal.  
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST2,    0x81); // Various test settings.      
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST1,    0x35); // Various test settings.      
    TI_CC_SPIWriteReg(TI_CCxxx0_TEST0,    0x09); // Various test settings.      
}

/*****************************************************************
*fuction£ºvoid ChangeChannel(u8 CH);change channel ;(work frequency =433M+200K*channel)
*inlet parameter£ºCH channel
*outlet parameter£º void
******************************************************************/
 void ChangeChannel(CPU_INT08U CH)
{
    TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
    TI_CC_SPIWriteReg(TI_CCxxx0_CHANNR,   CH%MAX_CHANNER); 
    TI_CC_SPIStrobe(TI_CCxxx0_SRX);
}

/*****************************************************************
*fuction£ºvoid ChangePower(CPU_INT08U PW);configration send power
*inlet parameter£ºPW -> power[0,5,7,10]
*outlet parameter£ºvoid
******************************************************************/
 void ChangePower(CPU_INT08U PW)
{
  TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
  switch(PW)
  {
  case 0x00:
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE,(CPU_INT08U*)&PowerTab[0], 1);
    break;
  case 0x05:
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE,(CPU_INT08U*)&PowerTab[1], 1);
    break;
  case 0x07:
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE,(CPU_INT08U*)&PowerTab[2], 1);
    break;
  case 0x0a:
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE,(CPU_INT08U*)&PowerTab[3], 1);
    break;
  default:
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_PATABLE,(CPU_INT08U*)&PowerTab[0], 1);
    break;
  }
  TI_CC_SPIStrobe(TI_CCxxx0_SRX);
}

/*****************************************************************
*fuction£ºvoid ChangeTrafficRate(u8 SP); change traffic rate
*inlet parameter£ºSP ->traffic rate [0,1,2,3,4,5,6]
*outlet parameter£º
******************************************************************/
 void ChangeTrafficRate(CPU_INT08U SP)
{
    TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG4,  MDMCFG4[SP%(MAX_SPD_RATE+1)]);  
    TI_CC_SPIWriteReg(TI_CCxxx0_MDMCFG3,  MDMCFG3[SP%(MAX_SPD_RATE+1)]); 
    TI_CC_SPIWriteReg(TI_CCxxx0_DEVIATN,  DEVIATN[SP%(MAX_SPD_RATE+1)]);
    TI_CC_SPIWriteReg(TI_CCxxx0_FSCTRL1,  FSCTRL1[SP%(MAX_SPD_RATE+1)]);
    TI_CC_SPIStrobe(TI_CCxxx0_SRX);
}

/*
*fuction:RFSendPacket send packet
*inlet parameter:txBuffer->data size->datalength
*outlet parameter:void
*/
 void RFSendPacket(CPU_INT08U *txBuffer, CPU_INT08U size)
{    
    TI_CC_SPIWriteBurstReg(TI_CCxxx0_TXFIFO, txBuffer, size); // Write TX data
    TI_CC_SPIStrobe(TI_CCxxx0_STX);         // Change state to TX, initiating;data transfer
    while (!(TI_CC_GDO0_IN));               // Wait GDO0 to go hi -> sync TX'ed
    while (TI_CC_GDO0_IN);                  // Wait GDO0 to clear -> end of pkt
    TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);        
}

/*
*fuction:RFReceivePacket receive packet
*    if(RSSI<128){
      *(rxBuffer+*length)=(RSSI>>1)-79;
    }
    else {
      *(rxBuffer+*length)=((RSSI-256)>>1)-79;
    }
*inlet parameter:rxBuffer length
*outlet parameter:0 error !0 no error
*/
 CPU_INT08U RFReceivePacket(CPU_INT08U *rxBuffer, CPU_INT08U *length)
{
  CPU_INT08U status[2];
  CPU_INT08U pktLen;

  TI_CC_SPIStrobe(TI_CCxxx0_SIDLE);
  TI_CC_SPIStrobe(TI_CCxxx0_SRX);
  
  if ((TI_CC_SPIReadStatus(TI_CCxxx0_RXBYTES) & TI_CCxxx0_NUM_RXBYTES))
  {
    pktLen =TI_CC_SPIReadReg(TI_CCxxx0_RXFIFO); // Read length byte

    if (pktLen <= *length)                  // If pktLen size <= rxBuffer
    {
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, rxBuffer, pktLen); // Pull data
      *length = pktLen;                     // Return the actual size
      TI_CC_SPIReadBurstReg(TI_CCxxx0_RXFIFO, status, 2);
      RSSI=status[0];
      return (CPU_INT08U)(status[TI_CCxxx0_LQI_RX]&TI_CCxxx0_CRC_OK);
    }                                       // Return CRC_OK bit
    else
    {
      *length = pktLen;                     // Return the large size
      TI_CC_SPIStrobe(TI_CCxxx0_SFRX);      // Flush RXFIFO
      return 0;                           
    }
  }
  else
      return 0;                             // Error
}

/*
*fuction: INT_FlushRxbuff 
*inlet parameter: void
*outlet parameter: void
*/
void INT_FlushRxbuff(void)
{
  TI_CC_SPIStrobe(TI_CCxxx0_SIDLE); 
  TI_CC_SPIStrobe(TI_CCxxx0_SFRX);  // Flush RXFIFO
  TI_CC_SPIStrobe(TI_CCxxx0_SRX);   // rx enable
}

/*
*fuction:Delay_10us 
*inlet parameter:nCount 
*outlet parameter:
*/
 void Delay_10us(u32 nCount)
{
  u16	i;
  for(; nCount != 0; nCount--)
    for(i=0;i<79;i++);
}
