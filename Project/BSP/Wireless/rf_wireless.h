#ifndef __RF_WIRELESS_H
#define __RF_WIRELESS_H

#include "stm32f10x.h"
#include  <cpu.h>
#include "bsp_int.h"

#define CONF_CPS        0
#define CONF_CHANLE     1
#define CONF_POWER      2
#define CONF_SPEED      3

#define READ_ALL        0
#define READ_RSSI       1
#define READ_CPS        2
#define READ_CHANEL     3
#define READ_POWER      4
#define READ_SPEED      5

extern void Delay_10us(unsigned int nValue);
extern void SPIInit(void);
extern CPU_INT08U SPISendByte(CPU_INT08U ch);
extern CPU_INT08U SPIReceiveByte(void);
extern void TI_CC_SPIWriteReg(CPU_INT08U addr, CPU_INT08U value);
extern void TI_CC_SPIWriteBurstReg(CPU_INT08U addr, CPU_INT08U *buffer, CPU_INT08U count);
extern CPU_INT08U TI_CC_SPIReadReg(CPU_INT08U addr);
extern void TI_CC_SPIReadBurstReg(CPU_INT08U addr, CPU_INT08U *buffer, CPU_INT08U count);
extern CPU_INT08U TI_CC_SPIReadStatus(CPU_INT08U addr);
extern void TI_CC_SPIStrobe(CPU_INT08U strobe);
extern void TI_CC_PowerupResetwireless(void);
extern void writeRFSettings(void);
extern void ChangeChannel(CPU_INT08U CH);
extern void ChangePower(CPU_INT08U PW);
extern void ChangeTrafficRate(CPU_INT08U SP);
extern void RFSendPacket(CPU_INT08U *txBuffer, CPU_INT08U size);
extern CPU_INT08U RFReceivePacket(CPU_INT08U *rxBuffer, CPU_INT08U *length); 
extern void INT_FlushRxbuff(void);

#endif