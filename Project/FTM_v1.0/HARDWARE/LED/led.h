#ifndef _LED_H
#define _LED_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//LED驱动代码	   							  
////////////////////////////////////////////////////////////////////////////////// 	

//LED端口定义
#define LED0(n)		(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_RESET))
#define LED0_Toggle (HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3))
#define LED1(n)		(n?HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET):HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_RESET))
#define LED1_Toggle (HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2))

void LED_Init(void);
#endif
