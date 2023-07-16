#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "key.h"
#include "sdram.h"
#include "tftlcd.h"
#include "ltdc.h"
#include "mpu.h"
#include "timer.h"
#include "usmart.h"
#include "malloc.h"
#include "touch.h"
#include "GUI.h"
#include "WM.h"

/************************************************
 �޸��ԣ�
 ALIENTEK STM32������STemWinʵ��
 STemWin�޲���ϵͳ��ֲʵ��
************************************************/
int main(void)
{
    Write_Through();         // Cahceǿ��͸д
    MPU_Memory_Protection(); // ������ش洢����
    Cache_Enable();          // ��L1-Cache

    Stm32_Clock_Init(432, 25, 2, 9); // ����ʱ��,216Mhz
    HAL_Init();                      // ��ʼ��HAL��
    delay_init(216);                 // ��ʱ��ʼ��
    uart_init(115200);               // ���ڳ�ʼ��
    KEY_Init();                      // ������ʼ��
    LED_Init();                      // ��ʼ��LED
    SDRAM_Init();                    // SDRAM��ʼ��
    TFTLCD_Init();                   // ��ʼ��LCD
    TP_Init();                       // ��������ʼ��
    TIM3_Init(999, 107);             // 1KHZ ��ʱ��3����Ϊ1ms
    TIM4_Init(999, 1079);            // ������ɨ���ٶ�,100HZ.
    // TIM2_PWM_Init(500-1,108-1);

    my_mem_init(SRAMIN);             // ��ʼ���ڲ��ڴ��
    my_mem_init(SRAMEX);             // ��ʼ���ⲿSDRAM�ڴ��
    my_mem_init(SRAMDTCM);           // ��ʼ���ڲ�DTCM�ڴ��
    __HAL_RCC_CRC_CLK_ENABLE();      // ʹ��CRCʱ��
    WM_SetCreateFlags(WM_CF_MEMDEV); // ����STemWin�洢�豸
    GUI_Init();
    WM_MULTIBUF_Enable(1); // ����STemWin�໺�壬RGB�����ܻ��õ�
    MainTask();            //! STemWin ��ʾdemo
    while (1)
    {
    }
}
