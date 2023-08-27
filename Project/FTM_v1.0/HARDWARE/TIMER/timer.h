#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
// ��ʱ���������� -- оƬF767ZGT6	
// ����ALIENTEK STM32F7���������ģ�� 				  
////////////////////////////////////////////////////////////////////////////////// 
#define TIM3_RELOAD_VALUE 200    //  Sampling rate: 1M / 200 = 5000 Hz

extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM4_Handler;     //! ��ʱ��4���
extern TIM_HandleTypeDef TIM9_Handler;     //! ��ʱ��9���

void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr, u16 psc, u8 direction);
void TIM9_PWM_Init(u16 arr, u16 psc, u8 direction);
#endif

