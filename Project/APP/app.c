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
*                                       uC/OS-III Application Code
*                                                Template
*
* The template application code provided here can be used as a foundation for your own uC/OS-III-based
* projects.  The code includes a declaration of main() that creates a single task named AppTaskStart().
*
* Filename      : app.c
* Version       : V1.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#include <includes.h>

/*
*********************************************************************************************************
*                                           LOCAL VARIABLES
*********************************************************************************************************
*/

static            OS_TCB       AppTaskStart_TCB;
static            CPU_STK      AppTaskStart_Stk[APP_TASK_START_STK_SIZE];

static	OS_TCB	LED1_TCB;
static	CPU_STK	LED1_Stk[TASK_LED1_STK_SIZE];
/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void         AppTaskCreate      (void);
static	void	     AppEventCreate     (void);

static  void         AppTaskStart       (void *p_arg);
static  void         Task_LED1          (void *p_arg);
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*********************************************************************************************************
*/

int  main (void)
{
    OS_ERR     err;


    BSP_IntDisAll();                                            /* Disable all interrupts.                              */

    OSInit(&err);                                               /* Init uC/OS-III.                                      */
    
    OSTaskCreate((OS_TCB     *)&AppTaskStart_TCB,               /* Create the start task                                */
                 (CPU_CHAR   *)"Start",
                 (OS_TASK_PTR )AppTaskStart,
                 (void       *)0,
                 (OS_PRIO     )APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStart_Stk[0],
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);

    OSStart(&err);                                              /* Start multitasking (i.e. give control to uC/OS-III). */
}


/*
*********************************************************************************************************
*                                          STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'AppTaskStart_()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  AppTaskStart (void *p_arg)
{
    CPU_INT32U   freq;
    CPU_INT32U   cnts;
    OS_ERR       err;


   (void)p_arg;
   
    BSP_Init();                                                       /* Initialize BSP functions                          */
    CPU_Init();                                                       /* Initialize the uC/CPU services                    */

    freq = BSP_CPU_ClkFreq();                                         /* Determine SysTick reference freq.                 */                                                                        
    cnts = freq / (CPU_INT32U)OSCfg_TickRate_Hz;                      /* Determine nbr SysTick increments                  */
    OS_CPU_SysTickInit(cnts);                                         /* Init uC/OS periodic time src (SysTick).           */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                                     /* Compute CPU capacity with no task running         */
#endif

#ifdef  CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif

    AppEventCreate();                                                 /* Create Application Kernel objects                 */

    AppTaskCreate();                                                  /* Create application tasks                          */
    
    
    while (DEF_TRUE) {                                                /* Task body, always written as an infinite loop.    */
		
        OSTimeDlyHMSM(0, 0, 0, 200,                                   /* Delay task for 200 ms                             */
                      OS_OPT_TIME_HMSM_STRICT,
                      &err);
        
    }
}


/*
*********************************************************************************************************
*                                      CREATE APPLICATION TASKS
*
* Description:  This function creates the application tasks.
*
* Arguments  :  none
*
* Returns    :  none
*********************************************************************************************************
*/

static  void  AppTaskCreate (void)
{
  OS_ERR      err;
  OSTaskCreate((OS_TCB     *)&LED1_TCB,     
                 (CPU_CHAR   *)"LED1",	
                 (OS_TASK_PTR )Task_LED1, 
                 (void       *)0,	
                 (OS_PRIO     )TASK_LED1_PRIO,	
                 (CPU_STK    *)&LED1_Stk[0],	
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE/10,
                 (CPU_STK_SIZE)TASK_LED1_STK_SIZE,
                 (OS_MSG_QTY  )0,			 		
                 (OS_TICK     )0,			 			
                 (void       *)0,			 			
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),	
                 (OS_ERR     *)&err);		 			
				 
}



/*
*********************************************************************************************************
*                                          AppEventCreate()
*
* Description : Create application kernel objects tasks.
*
* Argument(s) : none
*
* Return(s)   : none
*
* Caller(s)   : AppTaskStart()
*
* Note(s)     : none.
*********************************************************************************************************
*/

static void AppEventCreate(void)
{
}


void Task_LED1(void *p_arg)
{
	OS_ERR err;
    (void)p_arg;
	
    while (1)
    {
		LED0(ON);
		OSTimeDlyHMSM(0, 0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
		LED0(OFF);
		OSTimeDlyHMSM(0, 0,0,500,OS_OPT_TIME_HMSM_STRICT,&err);
    }
}