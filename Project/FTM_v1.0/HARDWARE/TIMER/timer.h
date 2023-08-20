#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
// 定时器驱动代码	
// 基于ALIENTEK STM32F7开发板代码模板 				  
////////////////////////////////////////////////////////////////////////////////// 
#define TIM_LEFT_HANDLE &TIM2_Handler
#define TIM_RIGHT_HANDLE &TIM5_Handler
#define TIM3_RELOAD_VALUE 200    //  Sampling rate: 1M / 200 = 5000 Hz

extern TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
extern TIM_HandleTypeDef TIM2_Handler;     //! 定时器2句柄
extern TIM_HandleTypeDef TIM5_Handler;     //! 定时器5句柄

void TIM3_Init(u16 arr,u16 psc);
void TIM4_Init(u16 arr,u16 psc);
void TIM2_PWM_Init(u16 arr, u16 psc, u8 direction);
void TIM5_PWM_Init(u16 arr, u16 psc, u8 direction);
#endif

