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
* header file provides definitions and prototypes used in bsp_int.c. 
*
* Filename      : bsp_int.h
* Version       : V1.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP_INT present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  BSP_INT_PRESENT
#define  BSP_INT_PRESENT


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>


/*
*********************************************************************************************************
*                                               EXTERNS
*********************************************************************************************************
*/


#ifdef   BSP_INT_MODULE
#define  BSP_INT_EXT
#else
#define  BSP_INT_EXT  extern
#endif

/*
*********************************************************************************************************
*                                        DEFAULT CONFIGURATION
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               DEFINES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               INT DEFINES
*********************************************************************************************************
*/

#define  BSP_INT_ID_MAX                                   68    /* Total number of interrupt sources in system          */

#define  BSP_INT_ID_WWDG                                   0    /* Window WatchDog Interrupt                            */
#define  BSP_INT_ID_PVD                                    1    /* PVD through EXTI Line detection Interrupt            */
#define  BSP_INT_ID_TAMPER                                 2    /* Tamper Interrupt                                     */
#define  BSP_INT_ID_RTC                                    3    /* RTC global Interrupt                                 */
#define  BSP_INT_ID_FLASH                                  4    /* FLASH global Interrupt                               */
#define  BSP_INT_ID_RCC                                    5    /* RCC global Interrupt                                 */
#define  BSP_INT_ID_EXTI0                                  6    /* EXTI Line0 Interrupt                                 */
#define  BSP_INT_ID_EXTI1                                  7    /* EXTI Line1 Interrupt                                 */
#define  BSP_INT_ID_EXTI2                                  8    /* EXTI Line2 Interrupt                                 */
#define  BSP_INT_ID_EXTI3                                  9    /* EXTI Line3 Interrupt                                 */
#define  BSP_INT_ID_EXTI4                                 10    /* EXTI Line4 Interrupt                                 */
#define  BSP_INT_ID_DMA1_CH1                              11    /* DMA1 Channel 1 global Interrupt                      */
#define  BSP_INT_ID_DMA1_CH2                              12    /* DMA1 Channel 2 global Interrupt                      */
#define  BSP_INT_ID_DMA1_CH3                              13    /* DMA1 Channel 3 global Interrupt                      */
#define  BSP_INT_ID_DMA1_CH4                              14    /* DMA1 Channel 4 global Interrupt                      */
#define  BSP_INT_ID_DMA1_CH5                              15    /* DMA1 Channel 5 global Interrupt                      */
#define  BSP_INT_ID_DMA1_CH6                              16    /* DMA1 Channel 6 global Interrupt                      */
#define  BSP_INT_ID_DMA1_CH7                              17    /* DMA1 Channel 7 global Interrupt                      */
#define  BSP_INT_ID_ADC1_2                                18    /* ADC1 et ADC2 global Interrupt                        */
#define  BSP_INT_ID_CAN1_TX                               19    /* CAN1 TX Interrupts                                   */
#define  BSP_INT_ID_CAN1_RX0                              20    /* CAN1 RX0 Interrupts                                  */
#define  BSP_INT_ID_CAN1_RX1                              21    /* CAN1 RX1 Interrupt                                   */
#define  BSP_INT_ID_CAN1_SCE                              22    /* CAN1 SCE Interrupt                                   */
#define  BSP_INT_ID_EXTI9_5                               23    /* External Line[9:5] Interrupts                        */
#define  BSP_INT_ID_TIM1_BRK                              24    /* TIM1 Break Interrupt                                 */
#define  BSP_INT_ID_TIM1_UP                               25    /* TIM1 Update Interrupt                                */
#define  BSP_INT_ID_TIM1_TRG_COM                          26    /* TIM1 Trigger and Commutation Interrupt               */
#define  BSP_INT_ID_TIM1_CC                               27    /* TIM1 Capture Compare Interrupt                       */
#define  BSP_INT_ID_TIM2                                  28    /* TIM2 global Interrupt                                */
#define  BSP_INT_ID_TIM3                                  29    /* TIM3 global Interrupt                                */
#define  BSP_INT_ID_TIM4                                  30    /* TIM4 global Interrupt                                */
#define  BSP_INT_ID_I2C1_EV                               31    /* I2C1 Event Interrupt                                 */
#define  BSP_INT_ID_I2C1_ER                               32    /* I2C1 Error Interrupt                                 */
#define  BSP_INT_ID_I2C2_EV                               33    /* I2C2 Event Interrupt                                 */
#define  BSP_INT_ID_I2C2_ER                               34    /* I2C2 Error Interrupt                                 */
#define  BSP_INT_ID_SPI1                                  35    /* SPI1 global Interrupt                                */
#define  BSP_INT_ID_SPI2                                  36    /* SPI2 global Interrupt                                */
#define  BSP_INT_ID_USART1                                37    /* USART1 global Interrupt                              */
#define  BSP_INT_ID_USART2                                38    /* USART2 global Interrupt                              */
#define  BSP_INT_ID_USART3                                39    /* USART3 global Interrupt                              */
#define  BSP_INT_ID_EXTI15_10                             40    /* External Line[15:10] Interrupts                      */
#define  BSP_INT_ID_RTC_ALARM                             41    /* RTC Alarm through EXTI Line Interrupt                */
#define  BSP_INT_ID_OTG_FS_WKUP                           42    /* USB WakeUp from suspend through EXTI Line Interrupt  */

#define  BSP_INT_ID_TIM5                                  50    /* TIM5 global Interrupt                                */
#define  BSP_INT_ID_SPI3                                  51    /* SPI3 global Interrupt                                */
#define  BSP_INT_ID_USART4                                52    /* USART4 global Interrupt                              */
#define  BSP_INT_ID_USART5                                53    /* USRT5 global Interrupt                               */
#define  BSP_INT_ID_TIM6                                  54    /* TIM6 global Interrupt                                */
#define  BSP_INT_ID_TIM7                                  55    /* TIM7 global Interrupt                                */
#define  BSP_INT_ID_DMA2_CH1                              56    /* DMA2 Channel 1 global Interrupt                      */
#define  BSP_INT_ID_DMA2_CH2                              57    /* DMA2 Channel 2 global Interrupt                      */
#define  BSP_INT_ID_DMA2_CH3                              58    /* DMA2 Channel 3 global Interrupt                      */
#define  BSP_INT_ID_DMA2_CH4                              59    /* DMA2 Channel 4 global Interrupt                      */
#define  BSP_INT_ID_DMA2_CH5                              60    /* DMA2 Channel 5 global Interrupt                      */

#define  BSP_INT_ID_ETH                                   61    /* ETH  global Interrupt                                */
#define  BSP_INT_ID_ETH_WKUP                              62    /* ETH  WakeUp from EXTI line interrupt                 */
#define  BSP_INT_ID_CAN2_TX                               63    /* CAN2 TX Interrupts                                   */
#define  BSP_INT_ID_CAN2_RX0                              64    /* CAN2 RX0 Interrupts                                  */
#define  BSP_INT_ID_CAN2_RX1                              65    /* CAN2 RX1 Interrupt                                   */
#define  BSP_INT_ID_CAN2_SCE                              66    /* CAN2 SCE Interrupt                                   */
#define  BSP_INT_ID_OTG_FS                                67    /* OTG global Interrupt                                 */

/*
*********************************************************************************************************
*                                          GLOBAL VARIABLES
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                               MACRO'S
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void  BSP_IntClr                       (CPU_INT08U     int_id);

void  BSP_IntDis                       (CPU_INT08U     int_id);

void  BSP_IntDisAll                    (void);

void  BSP_IntEn                        (CPU_INT08U     int_id);

void  BSP_IntInit                      (void);

void  BSP_IntVectSet                   (CPU_INT08U     int_id,
                                        CPU_FNCT_VOID  isr_fnct);

void  BSP_IntPrioSet                   (CPU_INT08U     int_id,
                                        CPU_INT08U     prio);

void  BSP_IntHandler                   (CPU_INT08U     int_id);


void         BSP_IntHandlerWWDG          (void);
void         BSP_IntHandlerPVD           (void);
void         BSP_IntHandlerTAMPER        (void);
void         BSP_IntHandlerRTC           (void);
void         BSP_IntHandlerFLASH         (void);
void         BSP_IntHandlerRCC           (void);
void         BSP_IntHandlerEXTI0         (void);
void         BSP_IntHandlerEXTI1         (void);
void         BSP_IntHandlerEXTI2         (void);
void         BSP_IntHandlerEXTI3         (void);
void         BSP_IntHandlerEXTI4         (void);
void         BSP_IntHandlerDMA1_CH1      (void);
void         BSP_IntHandlerDMA1_CH2      (void);
void         BSP_IntHandlerDMA1_CH3      (void);
void         BSP_IntHandlerDMA1_CH4      (void);
void         BSP_IntHandlerDMA1_CH5      (void);

void         BSP_IntHandlerDMA1_CH6      (void);
void         BSP_IntHandlerDMA1_CH7      (void);
void         BSP_IntHandlerADC1_2        (void);
void         BSP_IntHandlerCAN1_TX       (void);
void         BSP_IntHandlerCAN1_RX0      (void);
void         BSP_IntHandlerCAN1_RX1      (void);
void         BSP_IntHandlerCAN1_SCE      (void);
void         BSP_IntHandlerEXTI9_5       (void);
void         BSP_IntHandlerTIM1_BRK      (void);
void         BSP_IntHandlerTIM1_UP       (void);
void         BSP_IntHandlerTIM1_TRG_COM  (void);
void         BSP_IntHandlerTIM1_CC       (void);
void         BSP_IntHandlerTIM2          (void);
void         BSP_IntHandlerTIM3          (void);
void         BSP_IntHandlerTIM4          (void);
void         BSP_IntHandlerI2C1_EV       (void);

void         BSP_IntHandlerI2C1_ER       (void);
void         BSP_IntHandlerI2C2_EV       (void);
void         BSP_IntHandlerI2C2_ER       (void);
void         BSP_IntHandlerSPI1          (void);
void         BSP_IntHandlerSPI2          (void);
void         BSP_IntHandlerUSART1        (void);
void         BSP_IntHandlerUSART2        (void);
void         BSP_IntHandlerUSART3        (void);
void         BSP_IntHandlerEXTI15_10     (void);
void         BSP_IntHandlerRTCAlarm      (void);
void         BSP_IntHandlerUSBWakeUp     (void);

void         BSP_IntHandlerTIM5          (void);
void         BSP_IntHandlerSPI3          (void);
void         BSP_IntHandlerUSART4        (void);
void         BSP_IntHandlerUSART5        (void);
void         BSP_IntHandlerTIM6          (void);
void         BSP_IntHandlerTIM7          (void);
void         BSP_IntHandlerDMA2_CH1      (void);
void         BSP_IntHandlerDMA2_CH2      (void);
void         BSP_IntHandlerDMA2_CH3      (void);
void         BSP_IntHandlerDMA2_CH4      (void);
void         BSP_IntHandlerDMA2_CH5      (void);
void         BSP_IntHandlerETH           (void);
void         BSP_IntHandlerETHWakeup     (void);
void         BSP_IntHandlerCAN2_TX       (void);
void         BSP_IntHandlerCAN2_RX0      (void);
void         BSP_IntHandlerCAN2_RX1      (void);
void         BSP_IntHandlerCAN2_SCE      (void);
void         BSP_IntHandlerOTG           (void);

/*
*********************************************************************************************************
*                                              ERROR CHECKING
*********************************************************************************************************
*/


/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */

