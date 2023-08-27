#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
#include "DIALOG.h"
#include "led.h"
#include "motorcontrol.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//ADC驱动代码 -- 芯片F767ZGT6	
// 基于ALIENTEK STM32F7开发板代码模板 							  
////////////////////////////////////////////////////////////////////////////////// 	

extern WM_HWIN adcSingleEdit;
extern WM_HWIN adcDualEdit;
extern u8 adc_flag;

void MY_ADC_Init(void); 				//ADC通道初始化
u16  Get_Adc(u32 ch); 		        //获得某个通道值 
u16 Get_Adc_Average(u32 ch,u8 times);//得到某个通道给定次数采样的平均值
//deprecated
void Display_Adc_Value(u32 ch, u8 times);    // 在emWin上显示ADC的采样值
//deprecated
void Display_Freq_Value(float value);

#endif 
