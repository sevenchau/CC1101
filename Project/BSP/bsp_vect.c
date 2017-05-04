/*
*********************************************************************************************************
*                                              EXAMPLE CODE
*
*                          (c) Copyright 2003-2013; Micrium, Inc.; Weston, FL
*
*               All rights reserved.  Protected by international copyright laws.
*               Knowledge of the source code may NOT be used to develop a similar product.
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           Cortex-M3 BSP Code
*                                                Template
*
* The template code provided here can be used as a foundation for your own board support package.  This 
* code defines the interrupt vector table and should be adjusted according to your project's needs.
*
* Filename      : bsp_vect.c
* Version       : V1.00
*********************************************************************************************************
*/

#include <includes.h>


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                          LOCAL DATA TYPES
*********************************************************************************************************
*/

typedef  union {
    CPU_FNCT_VOID   Fnct;
    void           *Ptr;
} BSP_INTVECT_ELEM;

/*
*********************************************************************************************************
*                                            LOCAL TABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

#pragma language=extended
#pragma segment="CSTACK"

static  void  BSP_NMI_ISR        (void);

static  void  BSP_Fault_ISR      (void);

static  void  BSP_BusFault_ISR   (void);

static  void  BSP_UsageFault_ISR (void);

static  void  BSP_MemFault_ISR   (void);

static  void  BSP_Spurious_ISR   (void);

static  void  BSP_Reserved_ISR   (void);

extern  void  __iar_program_start(void);

//static  void    BSP_IntHandlerWWDG(void);                                         /* 16, INTISR[  0]  Window Watchdog.                    */
//
//static  void    BSP_IntHandlerPVD(void);                                          /* 17, INTISR[  1]  PVD through EXTI Line Detection.    */
//
//static  void    BSP_IntHandlerTAMPER(void);                                       /* 18, INTISR[  2]  Tamper Interrupt.                   */
//
//static  void    BSP_IntHandlerRTC(void);                                          /* 19, INTISR[  3]  RTC Global Interrupt.               */
//
//static  void    BSP_IntHandlerFLASH(void);                                        /* 20, INTISR[  4]  FLASH Global Interrupt.             */
//
//static  void    BSP_IntHandlerRCC(void);                                          /* 21, INTISR[  5]  RCC Global Interrupt.               */
//
//static  void    BSP_IntHandlerEXTI0(void);                                        /* 22, INTISR[  6]  EXTI Line0 Interrupt.               */
//
//static  void    BSP_IntHandlerEXTI1(void);                                        /* 23, INTISR[  7]  EXTI Line1 Interrupt.               */
//
//static  void    BSP_IntHandlerEXTI2(void);                                        /* 24, INTISR[  8]  EXTI Line2 Interrupt.               */
//
//static  void    BSP_IntHandlerEXTI3(void);                                        /* 25, INTISR[  9]  EXTI Line3 Interrupt.               */
//
//static  void    BSP_IntHandlerEXTI4(void);                                        /* 26, INTISR[ 10]  EXTI Line4 Interrupt.               */
//
//static  void    BSP_IntHandlerDMA1_CH1(void);                                     /* 27, INTISR[ 11]  DMA Channel1 Global Interrupt.      */
//
//static  void    BSP_IntHandlerDMA1_CH2(void);                                     /* 28, INTISR[ 12]  DMA Channel2 Global Interrupt.      */
//
//static  void    BSP_IntHandlerDMA1_CH3(void);                                     /* 29, INTISR[ 13]  DMA Channel3 Global Interrupt.      */
//
//static  void    BSP_IntHandlerDMA1_CH4(void);                                     /* 30, INTISR[ 14]  DMA Channel4 Global Interrupt.      */
//
//static  void    BSP_IntHandlerDMA1_CH5(void);                                     /* 31, INTISR[ 15]  DMA Channel5 Global Interrupt.      */
//
//static  void    BSP_IntHandlerDMA1_CH6(void);                                     /* 32, INTISR[ 16]  DMA Channel6 Global Interrupt.      */
//
//static  void    BSP_IntHandlerDMA1_CH7(void);                                     /* 33, INTISR[ 17]  DMA Channel7 Global Interrupt.      */
//
//static  void    BSP_IntHandlerADC1_2(void);                                       /* 34, INTISR[ 18]  ADC1 & ADC2 Global Interrupt.       */
//
//static  void    BSP_IntHandlerCAN1_TX(void);                                      /* 35, INTISR[ 19]  USB High Prio / CAN TX  Interrupts. */
//
//static  void    BSP_IntHandlerCAN1_RX0(void);                                     /* 36, INTISR[ 20]  USB Low  Prio / CAN RX0 Interrupts. */
//
//static  void    BSP_IntHandlerCAN1_RX1(void);                                     /* 37, INTISR[ 21]  CAN RX1 Interrupt.                  */
//
//static  void    BSP_IntHandlerCAN1_SCE(void);                                     /* 38, INTISR[ 22]  CAN SCE Interrupt.                  */
//
//static  void    BSP_IntHandlerEXTI9_5(void);                                      /* 39, INTISR[ 23]  EXTI Line[9:5] Interrupt.           */
//
//static  void    BSP_IntHandlerTIM1_BRK(void);                                     /* 40, INTISR[ 24]  TIM1 Break  Interrupt.              */
//
//static  void    BSP_IntHandlerTIM1_UP(void);                                      /* 41, INTISR[ 25]  TIM1 Update Interrupt.              */
//
//static  void    BSP_IntHandlerTIM1_TRG_COM(void);                                 /* 42, INTISR[ 26]  TIM1 Trig & Commutation Interrupts. */
//
//static  void    BSP_IntHandlerTIM1_CC(void);                                      /* 43, INTISR[ 27]  TIM1 Capture Compare Interrupt.     */
//
//static  void    BSP_IntHandlerTIM2(void);                                         /* 44, INTISR[ 28]  TIM2 Global Interrupt.              */
//
//static  void    BSP_IntHandlerTIM3(void);                                         /* 45, INTISR[ 29]  TIM3 Global Interrupt.              */
//
//static  void    BSP_IntHandlerTIM4(void);                                         /* 46, INTISR[ 30]  TIM4 Global Interrupt.              */
//
//static  void    BSP_IntHandlerI2C1_EV(void);                                      /* 47, INTISR[ 31]  I2C1 Event  Interrupt.              */
//
//static  void    BSP_IntHandlerI2C1_ER(void);                                      /* 48, INTISR[ 32]  I2C1 Error  Interrupt.              */
//
//static  void    BSP_IntHandlerI2C2_EV(void);                                      /* 49, INTISR[ 33]  I2C2 Event  Interrupt.              */
//
//static  void    BSP_IntHandlerI2C2_ER(void);                                      /* 50, INTISR[ 34]  I2C2 Error  Interrupt.              */
//
//static  void    BSP_IntHandlerSPI1(void);                                         /* 51, INTISR[ 35]  SPI1 Global Interrupt.              */
//
//static  void    BSP_IntHandlerSPI2(void);                                         /* 52, INTISR[ 36]  SPI2 Global Interrupt.              */
//
//static  void    BSP_IntHandlerUSART1(void);                                       /* 53, INTISR[ 37]  USART1 Global Interrupt.            */
//
//static  void    BSP_IntHandlerUSART2(void);                                       /* 54, INTISR[ 38]  USART2 Global Interrupt.            */
//
//static  void    BSP_IntHandlerUSART3(void);                                       /* 55, INTISR[ 39]  USART3 Global Interrupt.            */
//
//static  void    BSP_IntHandlerEXTI15_10(void);                                    /* 56, INTISR[ 40]  EXTI Line [15:10] Interrupts.       */
//
//static  void    BSP_IntHandlerRTCAlarm(void);                                     /* 57, INTISR[ 41]  RTC Alarm EXT Line Interrupt.       */
//
//static  void    BSP_IntHandlerUSBWakeUp(void);                                    /* 58, INTISR[ 42]  USB Wakeup from Suspend EXTI Int.   */
//
//static  void    BSP_IntHandlerTIM5(void);                                         /* 66, INTISR[ 50]  TIM5 global Interrupt.              */
//
//static  void    BSP_IntHandlerSPI3(void);                                         /* 67, INTISR[ 51]  SPI3 global Interrupt.              */
//
//static  void    BSP_IntHandlerUSART4(void);                                       /* 68, INTISR[ 52]  UART4 global Interrupt.             */
//
//static  void    BSP_IntHandlerUSART5(void);                                       /* 69, INTISR[ 53]  UART5 global Interrupt.             */
//
//static  void    BSP_IntHandlerTIM6(void);                                         /* 70, INTISR[ 54]  TIM6 global Interrupt.              */
//
//static  void    BSP_IntHandlerTIM7(void);                                         /* 71, INTISR[ 55]  TIM7 global Interrupt.              */
//
//static  void    BSP_IntHandlerDMA2_CH1(void);                                     /* 72, INTISR[ 56]  DMA2 Channel 1 global Interrupt.    */
//
//static  void    BSP_IntHandlerDMA2_CH2(void);                                     /* 73, INTISR[ 57]  DMA2 Channel 2 global Interrupt.    */
//
//static  void    BSP_IntHandlerDMA2_CH3(void);                                     /* 74, INTISR[ 58]  DMA2 Channel 3 global Interrupt.    */
//
//static  void    BSP_IntHandlerDMA2_CH4(void);                                     /* 75, INTISR[ 59]  DMA2 Channel 4 global Interrupt.    */
//
//static  void    BSP_IntHandlerDMA2_CH5(void);                                     /* 76, INTISR[ 60]  DMA2 Channel 5 global Interrupt.    */                                                                
//
//static  void    BSP_IntHandlerETH(void);                                          /* 77, INTISR[ 61]  ETH global Interrupt.               */
//
//static  void   BSP_IntHandlerETHWakeup(void);                                    /* 78, INTISR[ 62]  ETH WakeUp from EXTI line Int.      */
//
//static  void    BSP_IntHandlerCAN2_TX(void);                                      /* 79, INTISR[ 63]  CAN2 TX Interrupts.                 */
//
//static  void    BSP_IntHandlerCAN2_RX0(void);                                     /* 80, INTISR[ 64]  CAN2 RX0 Interrupts.                */
//
//static  void    BSP_IntHandlerCAN2_RX1(void);                                     /* 81, INTISR[ 65]  CAN2 RX1 Interrupt.                 */
//
//static  void    BSP_IntHandlerCAN2_SCE(void);                                     /* 82, INTISR[ 66]  CAN2 SCE Interrupt.                 */
//
//static  void    BSP_IntHandlerOTG(void);                                          /* 83, INTISR[ 67]  OTG global Interrupt.               */   
/*
*********************************************************************************************************
*                                     LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                  EXCEPTION / INTERRUPT VECTOR TABLE
*
* Note(s) : (1) The Cortex-M3 may have up to 256 external interrupts, which are the final entries in the
*               vector table.  
*********************************************************************************************************
*/

__root  const  BSP_INTVECT_ELEM  __vector_table[] @ ".intvec" = {
    { .Ptr = (void *)__sfe( "CSTACK" )},                        /*  0, SP start value.                                  */
    __iar_program_start,                                        /*  1, PC start value.                                  */
    BSP_NMI_ISR,                                                /*  2, NMI.                                             */
    BSP_Fault_ISR,                                              /*  3, Hard Fault.                                      */
    BSP_MemFault_ISR,                                           /*  4, Memory Management.                               */
    BSP_BusFault_ISR,                                           /*  5, Bus Fault.                                       */
    BSP_UsageFault_ISR,                                         /*  6, Usage Fault.                                     */
    BSP_Spurious_ISR,                                           /*  7, Reserved.                                        */
    BSP_Spurious_ISR,                                           /*  8, Reserved.                                        */
    BSP_Spurious_ISR,                                           /*  9, Reserved.                                        */
    BSP_Spurious_ISR,                                           /* 10, Reserved.                                        */
    BSP_Spurious_ISR,                                           /* 11, SVCall.                                          */
    BSP_Spurious_ISR,                                           /* 12, Debug Monitor.                                   */
    BSP_Spurious_ISR,                                           /* 13, Reserved.                                        */
    OS_CPU_PendSVHandler,                                       /* 14, PendSV Handler.                                  */
    OS_CPU_SysTickHandler,                                      /* 15, uC/OS-III Tick ISR Handler.                      */

    BSP_IntHandlerWWDG,                                         /* 16, INTISR[  0]  Window Watchdog.                    */
    BSP_IntHandlerPVD,                                          /* 17, INTISR[  1]  PVD through EXTI Line Detection.    */
    BSP_IntHandlerTAMPER,                                       /* 18, INTISR[  2]  Tamper Interrupt.                   */
    BSP_IntHandlerRTC,                                          /* 19, INTISR[  3]  RTC Global Interrupt.               */
    BSP_IntHandlerFLASH,                                        /* 20, INTISR[  4]  FLASH Global Interrupt.             */
    BSP_IntHandlerRCC,                                          /* 21, INTISR[  5]  RCC Global Interrupt.               */
    BSP_IntHandlerEXTI0,                                        /* 22, INTISR[  6]  EXTI Line0 Interrupt.               */
    BSP_IntHandlerEXTI1,                                        /* 23, INTISR[  7]  EXTI Line1 Interrupt.               */
    BSP_IntHandlerEXTI2,                                        /* 24, INTISR[  8]  EXTI Line2 Interrupt.               */
    BSP_IntHandlerEXTI3,                                        /* 25, INTISR[  9]  EXTI Line3 Interrupt.               */
    BSP_IntHandlerEXTI4,                                        /* 26, INTISR[ 10]  EXTI Line4 Interrupt.               */
    BSP_IntHandlerDMA1_CH1,                                     /* 27, INTISR[ 11]  DMA Channel1 Global Interrupt.      */
    BSP_IntHandlerDMA1_CH2,                                     /* 28, INTISR[ 12]  DMA Channel2 Global Interrupt.      */
    BSP_IntHandlerDMA1_CH3,                                     /* 29, INTISR[ 13]  DMA Channel3 Global Interrupt.      */
    BSP_IntHandlerDMA1_CH4,                                     /* 30, INTISR[ 14]  DMA Channel4 Global Interrupt.      */
    BSP_IntHandlerDMA1_CH5,                                     /* 31, INTISR[ 15]  DMA Channel5 Global Interrupt.      */

    BSP_IntHandlerDMA1_CH6,                                     /* 32, INTISR[ 16]  DMA Channel6 Global Interrupt.      */
    BSP_IntHandlerDMA1_CH7,                                     /* 33, INTISR[ 17]  DMA Channel7 Global Interrupt.      */
    BSP_IntHandlerADC1_2,                                       /* 34, INTISR[ 18]  ADC1 & ADC2 Global Interrupt.       */
    BSP_IntHandlerCAN1_TX,                                      /* 35, INTISR[ 19]  USB High Prio / CAN TX  Interrupts. */
    BSP_IntHandlerCAN1_RX0,                                     /* 36, INTISR[ 20]  USB Low  Prio / CAN RX0 Interrupts. */
    BSP_IntHandlerCAN1_RX1,                                     /* 37, INTISR[ 21]  CAN RX1 Interrupt.                  */
    BSP_IntHandlerCAN1_SCE,                                     /* 38, INTISR[ 22]  CAN SCE Interrupt.                  */
    BSP_IntHandlerEXTI9_5,                                      /* 39, INTISR[ 23]  EXTI Line[9:5] Interrupt.           */
    BSP_IntHandlerTIM1_BRK,                                     /* 40, INTISR[ 24]  TIM1 Break  Interrupt.              */
    BSP_IntHandlerTIM1_UP,                                      /* 41, INTISR[ 25]  TIM1 Update Interrupt.              */
    BSP_IntHandlerTIM1_TRG_COM,                                 /* 42, INTISR[ 26]  TIM1 Trig & Commutation Interrupts. */
    BSP_IntHandlerTIM1_CC,                                      /* 43, INTISR[ 27]  TIM1 Capture Compare Interrupt.     */
    BSP_IntHandlerTIM2,                                         /* 44, INTISR[ 28]  TIM2 Global Interrupt.              */
    BSP_IntHandlerTIM3,                                         /* 45, INTISR[ 29]  TIM3 Global Interrupt.              */
    BSP_IntHandlerTIM4,                                         /* 46, INTISR[ 30]  TIM4 Global Interrupt.              */
    BSP_IntHandlerI2C1_EV,                                      /* 47, INTISR[ 31]  I2C1 Event  Interrupt.              */
    BSP_IntHandlerI2C1_ER,                                      /* 48, INTISR[ 32]  I2C1 Error  Interrupt.              */
    BSP_IntHandlerI2C2_EV,                                      /* 49, INTISR[ 33]  I2C2 Event  Interrupt.              */
    BSP_IntHandlerI2C2_ER,                                      /* 50, INTISR[ 34]  I2C2 Error  Interrupt.              */
    BSP_IntHandlerSPI1,                                         /* 51, INTISR[ 35]  SPI1 Global Interrupt.              */
    BSP_IntHandlerSPI2,                                         /* 52, INTISR[ 36]  SPI2 Global Interrupt.              */
    BSP_IntHandlerUSART1,                                       /* 53, INTISR[ 37]  USART1 Global Interrupt.            */
    BSP_IntHandlerUSART2,                                       /* 54, INTISR[ 38]  USART2 Global Interrupt.            */
    BSP_IntHandlerUSART3,                                       /* 55, INTISR[ 39]  USART3 Global Interrupt.            */
    BSP_IntHandlerEXTI15_10,                                    /* 56, INTISR[ 40]  EXTI Line [15:10] Interrupts.       */
    BSP_IntHandlerRTCAlarm,                                     /* 57, INTISR[ 41]  RTC Alarm EXT Line Interrupt.       */
    BSP_IntHandlerUSBWakeUp,                                    /* 58, INTISR[ 42]  USB Wakeup from Suspend EXTI Int.   */
  
    BSP_Reserved_ISR,                                           /* 59, INTISR[ 43]  USB Wakeup from Suspend EXTI Int.   */
    BSP_Reserved_ISR,                                           /* 60, INTISR[ 44]  USB Wakeup from Suspend EXTI Int.   */
    BSP_Reserved_ISR,                                           /* 61, INTISR[ 45]  USB Wakeup from Suspend EXTI Int.   */
    BSP_Reserved_ISR,                                           /* 62, INTISR[ 46]  USB Wakeup from Suspend EXTI Int.   */
    BSP_Reserved_ISR,                                           /* 63, INTISR[ 47]  USB Wakeup from Suspend EXTI Int.   */
    BSP_Reserved_ISR,                                           /* 64, INTISR[ 48]  USB Wakeup from Suspend EXTI Int.   */
    BSP_Reserved_ISR,                                           /* 65, INTISR[ 49]  USB Wakeup from Suspend EXTI Int.   */
  
    BSP_IntHandlerTIM5,                                         /* 66, INTISR[ 50]  TIM5 global Interrupt.              */
    BSP_IntHandlerSPI3,                                         /* 67, INTISR[ 51]  SPI3 global Interrupt.              */
    BSP_IntHandlerUSART4,                                       /* 68, INTISR[ 52]  UART4 global Interrupt.             */
    BSP_IntHandlerUSART5,                                       /* 69, INTISR[ 53]  UART5 global Interrupt.             */
    BSP_IntHandlerTIM6,                                         /* 70, INTISR[ 54]  TIM6 global Interrupt.              */
    BSP_IntHandlerTIM7,                                         /* 71, INTISR[ 55]  TIM7 global Interrupt.              */
    BSP_IntHandlerDMA2_CH1,                                     /* 72, INTISR[ 56]  DMA2 Channel 1 global Interrupt.    */
    BSP_IntHandlerDMA2_CH2,                                     /* 73, INTISR[ 57]  DMA2 Channel 2 global Interrupt.    */
    BSP_IntHandlerDMA2_CH3,                                     /* 74, INTISR[ 58]  DMA2 Channel 3 global Interrupt.    */
    BSP_IntHandlerDMA2_CH4,                                     /* 75, INTISR[ 59]  DMA2 Channel 4 global Interrupt.    */
    BSP_IntHandlerDMA2_CH5,                                     /* 76, INTISR[ 60]  DMA2 Channel 5 global Interrupt.    */                                                                
    BSP_IntHandlerETH,                                          /* 77, INTISR[ 61]  ETH global Interrupt.               */
    BSP_IntHandlerETHWakeup,                                    /* 78, INTISR[ 62]  ETH WakeUp from EXTI line Int.      */
    BSP_IntHandlerCAN2_TX,                                      /* 79, INTISR[ 63]  CAN2 TX Interrupts.                 */
    BSP_IntHandlerCAN2_RX0,                                     /* 80, INTISR[ 64]  CAN2 RX0 Interrupts.                */
    BSP_IntHandlerCAN2_RX1,                                     /* 81, INTISR[ 65]  CAN2 RX1 Interrupt.                 */
    BSP_IntHandlerCAN2_SCE,                                     /* 82, INTISR[ 66]  CAN2 SCE Interrupt.                 */
    BSP_IntHandlerOTG,                                          /* 83, INTISR[ 67]  OTG global Interrupt.               */   
};

/*
*********************************************************************************************************
*                                            BSP_NMI_ISR()
*
* Description : Handle Non-Maskable Interrupt (NMI).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : (1) Since the NMI is not being used, this serves merely as a catch for a spurious
*                   exception.
*********************************************************************************************************
*/

static  void  BSP_NMI_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}

/*
*********************************************************************************************************
*                                             BSP_Fault_ISR()
*
* Description : Handle hard fault.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_Fault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                           BSP_BusFault_ISR()
*
* Description : Handle bus fault.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_BusFault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                          BSP_UsageFault_ISR()
*
* Description : Handle usage fault.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_UsageFault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                           BSP_MemFault_ISR()
*
* Description : Handle memory fault.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_MemFault_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                           BSP_Spurious_ISR()
*
* Description : Handle spurious interrupt.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_Spurious_ISR (void)
{
    while (DEF_TRUE) {
        ;
    }
}


/*
*********************************************************************************************************
*                                           BSP_Reserved_ISR()
*
* Description : Reserved interrupt vector place holder.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is an ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_Reserved_ISR (void)
{
  
}
//
//
//
//static  void    BSP_IntHandlerWWDG(void)                                         /* 16, INTISR[  0]  Window Watchdog.                    */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerPVD(void)                                          /* 17, INTISR[  1]  PVD through EXTI Line Detection.    */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTAMPER(void)                                       /* 18, INTISR[  2]  Tamper Interrupt.                   */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerRTC(void)                                          /* 19, INTISR[  3]  RTC Global Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerFLASH(void)                                        /* 20, INTISR[  4]  FLASH Global Interrupt.             */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerRCC(void)                                          /* 21, INTISR[  5]  RCC Global Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI0(void)                                        /* 22, INTISR[  6]  EXTI Line0 Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI1(void)                                        /* 23, INTISR[  7]  EXTI Line1 Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI2(void)                                        /* 24, INTISR[  8]  EXTI Line2 Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI3(void)                                        /* 25, INTISR[  9]  EXTI Line3 Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI4(void)                                        /* 26, INTISR[ 10]  EXTI Line4 Interrupt.               */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH1(void)                                     /* 27, INTISR[ 11]  DMA Channel1 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH2(void)                                     /* 28, INTISR[ 12]  DMA Channel2 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH3(void)                                     /* 29, INTISR[ 13]  DMA Channel3 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH4(void)                                     /* 30, INTISR[ 14]  DMA Channel4 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH5(void)                                     /* 31, INTISR[ 15]  DMA Channel5 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH6(void)                                     /* 32, INTISR[ 16]  DMA Channel6 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA1_CH7(void)                                     /* 33, INTISR[ 17]  DMA Channel7 Global Interrupt.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerADC1_2(void)                                       /* 34, INTISR[ 18]  ADC1 & ADC2 Global Interrupt.       */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN1_TX(void)                                      /* 35, INTISR[ 19]  USB High Prio / CAN TX  Interrupts. */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN1_RX0(void)                                     /* 36, INTISR[ 20]  USB Low  Prio / CAN RX0 Interrupts. */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN1_RX1(void)                                     /* 37, INTISR[ 21]  CAN RX1 Interrupt.                  */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN1_SCE(void)                                     /* 38, INTISR[ 22]  CAN SCE Interrupt.                  */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI9_5(void)                                      /* 39, INTISR[ 23]  EXTI Line[9:5] Interrupt.           */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM1_BRK(void)                                     /* 40, INTISR[ 24]  TIM1 Break  Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM1_UP(void)                                      /* 41, INTISR[ 25]  TIM1 Update Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM1_TRG_COM(void)                                 /* 42, INTISR[ 26]  TIM1 Trig & Commutation Interrupts. */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM1_CC(void)                                      /* 43, INTISR[ 27]  TIM1 Capture Compare Interrupt.     */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM2(void)                                         /* 44, INTISR[ 28]  TIM2 Global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM3(void)                                         /* 45, INTISR[ 29]  TIM3 Global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM4(void)                                         /* 46, INTISR[ 30]  TIM4 Global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerI2C1_EV(void)                                      /* 47, INTISR[ 31]  I2C1 Event  Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerI2C1_ER(void)                                      /* 48, INTISR[ 32]  I2C1 Error  Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerI2C2_EV(void)                                      /* 49, INTISR[ 33]  I2C2 Event  Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerI2C2_ER(void)                                      /* 50, INTISR[ 34]  I2C2 Error  Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerSPI1(void)                                         /* 51, INTISR[ 35]  SPI1 Global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerSPI2(void)                                         /* 52, INTISR[ 36]  SPI2 Global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerUSART1(void)                                       /* 53, INTISR[ 37]  USART1 Global Interrupt.            */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerUSART2(void)                                       /* 54, INTISR[ 38]  USART2 Global Interrupt.            */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerUSART3(void)                                       /* 55, INTISR[ 39]  USART3 Global Interrupt.            */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerEXTI15_10(void)                                    /* 56, INTISR[ 40]  EXTI Line [15:10] Interrupts.       */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerRTCAlarm(void)                                     /* 57, INTISR[ 41]  RTC Alarm EXT Line Interrupt.       */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerUSBWakeUp(void)                                    /* 58, INTISR[ 42]  USB Wakeup from Suspend EXTI Int.   */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM5(void)                                         /* 66, INTISR[ 50]  TIM5 global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerSPI3(void)                                         /* 67, INTISR[ 51]  SPI3 global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerUSART4(void)                                       /* 68, INTISR[ 52]  UART4 global Interrupt.             */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerUSART5(void)                                       /* 69, INTISR[ 53]  UART5 global Interrupt.             */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM6(void)                                         /* 70, INTISR[ 54]  TIM6 global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerTIM7(void)                                         /* 71, INTISR[ 55]  TIM7 global Interrupt.              */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA2_CH1(void)                                     /* 72, INTISR[ 56]  DMA2 Channel 1 global Interrupt.    */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA2_CH2(void)                                     /* 73, INTISR[ 57]  DMA2 Channel 2 global Interrupt.    */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA2_CH3(void)                                     /* 74, INTISR[ 58]  DMA2 Channel 3 global Interrupt.    */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA2_CH4(void)                                     /* 75, INTISR[ 59]  DMA2 Channel 4 global Interrupt.    */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerDMA2_CH5(void)                                     /* 76, INTISR[ 60]  DMA2 Channel 5 global Interrupt.    */                                                                
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerETH(void)                                          /* 77, INTISR[ 61]  ETH global Interrupt.               */
//{
//  
//}
//
//
//
//static  void   BSP_IntHandlerETHWakeup(void)                                    /* 78, INTISR[ 62]  ETH WakeUp from EXTI line Int.      */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN2_TX(void)                                      /* 79, INTISR[ 63]  CAN2 TX Interrupts.                 */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN2_RX0(void)                                     /* 80, INTISR[ 64]  CAN2 RX0 Interrupts.                */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN2_RX1(void)                                     /* 81, INTISR[ 65]  CAN2 RX1 Interrupt.                 */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerCAN2_SCE(void)                                     /* 82, INTISR[ 66]  CAN2 SCE Interrupt.                 */
//{
//  
//}
//
//
//
//static  void    BSP_IntHandlerOTG(void) 
//{
//  
//}
