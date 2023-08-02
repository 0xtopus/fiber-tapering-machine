#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "sdram.h"
#include "tftlcd.h"
#include "ltdc.h"
#include "mpu.h"
#include "usmart.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "WM.h"
#include "adc.h"

#include "includes.h"
/************************************************
 ����ALIENTEK STM32������STemWinʵ��
 STemWin STemWin+UCOSIII��ֲʵ��

 UCOSIII���������ȼ��û�������ʹ�ã�ALIENTEK
 ����Щ���ȼ��������UCOSIII��5��ϵͳ�ڲ�����
 ���ȼ�0���жϷ������������� OS_IntQTask()
 ���ȼ�1��ʱ�ӽ������� OS_TickTask()
 ���ȼ�2����ʱ���� OS_TmrTask()
 ���ȼ�OS_CFG_PRIO_MAX-2��ͳ������ OS_StatTask()
 ���ȼ�OS_CFG_PRIO_MAX-1���������� OS_IdleTask()
************************************************/

// �������ȼ�
#define START_TASK_PRIO 3
// �����ջ��С
#define START_STK_SIZE 128
// ������ƿ�
OS_TCB StartTaskTCB;
// �����ջ
CPU_STK START_TASK_STK[START_STK_SIZE];
// ������
void start_task(void *p_arg);

// TOUCH����
// �����������ȼ�
#define TOUCH_TASK_PRIO 4
// �����ջ��С
#define TOUCH_STK_SIZE 128
// ������ƿ�
OS_TCB TouchTaskTCB;
// �����ջ
CPU_STK TOUCH_TASK_STK[TOUCH_STK_SIZE];
// touch����
void touch_task(void *p_arg);

// LED0����
// �����������ȼ�
#define LED0_TASK_PRIO 5
// �����ջ��С
#define LED0_STK_SIZE 128
// ������ƿ�
OS_TCB Led0TaskTCB;
// �����ջ
CPU_STK LED0_TASK_STK[LED0_STK_SIZE];
// led0����
void led0_task(void *p_arg);

// EMWINDEMO����
// �����������ȼ�
#define EMWINDEMO_TASK_PRIO 6
// �����ջ��С
#define EMWINDEMO_STK_SIZE 512
// ������ƿ�
OS_TCB EmwindemoTaskTCB;
// �����ջ
CPU_STK EMWINDEMO_TASK_STK[EMWINDEMO_STK_SIZE];
// emwindemo_task����
void emwindemo_task(void *p_arg);

int main(void)
{
    OS_ERR err;
    CPU_SR_ALLOC();

    Write_Through();         // Cahceǿ��͸д
    MPU_Memory_Protection(); // ������ش洢����
    Cache_Enable();          // ��L1-Cache

    Stm32_Clock_Init(432, 25, 2, 9); // ����ʱ��,216Mhz
    HAL_Init();                      // ��ʼ��HAL��
    delay_init(216);                 // ��ʱ��ʼ��
    uart_init(115200);               // ���ڳ�ʼ��
    KEY_Init();                      // ������ʼ��
    LED_Init();                      // ��ʼ��LED
    //SDRAM_Init();                    // SDRAM��ʼ��
    TFTLCD_Init();                   // ��ʼ��LCD
    TP_Init();                       // ��������ʼ��

    MY_ADC_Init();       // ��ʼ��ADC
    my_mem_init(SRAMIN); // ��ʼ���ڲ��ڴ��
    // my_mem_init(SRAMEX);		    //��ʼ���ⲿ�ڴ��
    my_mem_init(SRAMDTCM); // ��ʼ��DTCM�ڴ��

    OSInit(&err);        // ��ʼ��UCOSIII
    OS_CRITICAL_ENTER(); // �����ٽ���
    // ������ʼ����
    OSTaskCreate((OS_TCB *)&StartTaskTCB,                           // ������ƿ�
                 (CPU_CHAR *)"start task",                          // ��������
                 (OS_TASK_PTR)start_task,                           // ������
                 (void *)0,                                         // ���ݸ��������Ĳ���
                 (OS_PRIO)START_TASK_PRIO,                          // �������ȼ�
                 (CPU_STK *)&START_TASK_STK[0],                     // �����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE / 10,                 // �����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,                      // �����ջ��С
                 (OS_MSG_QTY)0,                                     // �����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK)0,                                        // ��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void *)0,                                         // �û�����Ĵ洢��
                 (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR, // ����ѡ��
                 (OS_ERR *)&err);                                   // ��Ÿú�������ʱ�ķ���ֵ
    OS_CRITICAL_EXIT();                                             // �˳��ٽ���
    OSStart(&err);                                                  // ����UCOSIII
    while (1)
        ;
}

// ��ʼ������
void start_task(void *p_arg)
{
    OS_ERR err;
    CPU_SR_ALLOC();
    p_arg = p_arg;

    CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err); // ͳ������
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN // ���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();
#endif

#if OS_CFG_SCHED_ROUND_ROBIN_EN // ��ʹ��ʱ��Ƭ��ת��ʱ��
    // ʹ��ʱ��Ƭ��ת���ȹ���,����Ĭ�ϵ�ʱ��Ƭ����
    OSSchedRoundRobinCfg(DEF_ENABLED, 1, &err);
#endif
    __HAL_RCC_CRC_CLK_ENABLE(); // ʹ��CRCʱ��
    WM_SetCreateFlags(WM_CF_MEMDEV);
    GUI_Init();            // STemWin��ʼ��
    WM_MULTIBUF_Enable(1); // ����STemWin�໺��,RGB�����ܻ��õ�
    OS_CRITICAL_ENTER();   // �����ٽ���
    // STemWin Demo����
    OSTaskCreate((OS_TCB *)&EmwindemoTaskTCB,
                 (CPU_CHAR *)"Emwindemo task",
                 (OS_TASK_PTR)emwindemo_task,
                 (void *)0,
                 (OS_PRIO)EMWINDEMO_TASK_PRIO,
                 (CPU_STK *)&EMWINDEMO_TASK_STK[0],
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE / 10,
                 (CPU_STK_SIZE)EMWINDEMO_STK_SIZE,
                 (OS_MSG_QTY)0,
                 (OS_TICK)0,
                 (void *)0,
                 (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *)&err);
    // ����������
    OSTaskCreate((OS_TCB *)&TouchTaskTCB,
                 (CPU_CHAR *)"Touch task",
                 (OS_TASK_PTR)touch_task,
                 (void *)0,
                 (OS_PRIO)TOUCH_TASK_PRIO,
                 (CPU_STK *)&TOUCH_TASK_STK[0],
                 (CPU_STK_SIZE)TOUCH_STK_SIZE / 10,
                 (CPU_STK_SIZE)TOUCH_STK_SIZE,
                 (OS_MSG_QTY)0,
                 (OS_TICK)0,
                 (void *)0,
                 (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *)&err);
    // LED0����
    OSTaskCreate((OS_TCB *)&Led0TaskTCB,
                 (CPU_CHAR *)"Led0 task",
                 (OS_TASK_PTR)led0_task,
                 (void *)0,
                 (OS_PRIO)LED0_TASK_PRIO,
                 (CPU_STK *)&LED0_TASK_STK[0],
                 (CPU_STK_SIZE)LED0_STK_SIZE / 10,
                 (CPU_STK_SIZE)LED0_STK_SIZE,
                 (OS_MSG_QTY)0,
                 (OS_TICK)0,
                 (void *)0,
                 (OS_OPT)OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR,
                 (OS_ERR *)&err);
    OS_TaskSuspend((OS_TCB *)&StartTaskTCB, &err); // ����ʼ����
    OS_CRITICAL_EXIT();                            // �˳��ٽ���
}

// EMWINDEMO����
void emwindemo_task(void *p_arg)
{
    while (1)
    {
        MainTask();
    }
}

// TOUCH����
void touch_task(void *p_arg)
{
    OS_ERR err;
    while (1)
    {
        GUI_TOUCH_Exec();
        OSTimeDlyHMSM(0, 0, 0, 5, OS_OPT_TIME_PERIODIC, &err); // ��ʱ5ms
    }
}

// LED0����
void led0_task(void *p_arg)
{
    OS_ERR err;
    while (1)
    {
        LED0_Toggle;
        OSTimeDlyHMSM(0, 0, 0, 500, OS_OPT_TIME_PERIODIC, &err); // ��ʱ500ms
    }
}