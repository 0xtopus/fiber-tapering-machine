#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//LED驱动代码	   						  
////////////////////////////////////////////////////////////////////////////////// 	

//初始化PE2,PE3为输出.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();			//开启GPIOE时钟
	
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3; //PE2,3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //高速
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);	//PE2置0
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);	//PE3置0
}

