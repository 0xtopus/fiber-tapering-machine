#ifndef _KEY_H
#define _KEY_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//KEY驱动代码	   			  
//////////////////////////////////////////////////////////////////////////////////
#define KEY0        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_2)  //KEY0按键PC2
#define KEY1        HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_3)  //KEY1按键PC3

#define KEY0_PRES 	1
#define KEY1_PRES	2

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
#endif
