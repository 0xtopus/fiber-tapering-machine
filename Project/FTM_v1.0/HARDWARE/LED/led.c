#include "led.h"
//////////////////////////////////////////////////////////////////////////////////	 
//LED��������	   						  
////////////////////////////////////////////////////////////////////////////////// 	

//��ʼ��PE2,PE3Ϊ���.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOE_CLK_ENABLE();			//����GPIOEʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_2|GPIO_PIN_3; //PE2,3
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //�������
    GPIO_Initure.Pull=GPIO_PULLUP;          //����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;     //����
    HAL_GPIO_Init(GPIOE,&GPIO_Initure);
	
    HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,GPIO_PIN_SET);	//PE2��0
	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_3,GPIO_PIN_SET);	//PE3��0
}

