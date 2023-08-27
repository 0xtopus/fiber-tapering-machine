#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
// 定时器驱动代码 -- 芯片F767ZGT6	
// 基于ALIENTEK STM32F7开发板代码模板 				  
////////////////////////////////////////////////////////////////////////////////// 
#define TIM3_RELOAD_VALUE 200    //  Sampling rate: 1M / 200 = 5000 Hz

extern TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
extern TIM_HandleTypeDef TIM4_Handler;     //! 定时器4句柄
extern TIM_HandleTypeDef TIM9_Handler;     //! 定时器9句柄

void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u16 arr, u16 psc, u8 direction);
void TIM9_PWM_Init(u16 arr, u16 psc, u8 direction);
#endif

