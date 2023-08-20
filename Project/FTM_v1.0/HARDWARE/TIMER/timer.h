#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
// ��ʱ����������	
// ����ALIENTEK STM32F7���������ģ�� 				  
////////////////////////////////////////////////////////////////////////////////// 
#define TIM_LEFT_HANDLE &TIM2_Handler
#define TIM_RIGHT_HANDLE &TIM5_Handler
#define TIM3_RELOAD_VALUE 200    //  Sampling rate: 1M / 200 = 5000 Hz

extern TIM_HandleTypeDef TIM3_Handler;      //��ʱ����� 
extern TIM_HandleTypeDef TIM2_Handler;     //! ��ʱ��2���
extern TIM_HandleTypeDef TIM5_Handler;     //! ��ʱ��5���

void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr, u16 psc, u8 direction);
void TIM5_PWM_Init(u16 arr, u16 psc, u8 direction);
#endif

