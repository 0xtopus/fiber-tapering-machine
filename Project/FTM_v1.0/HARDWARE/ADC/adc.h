#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
#include "DIALOG.h"
#include "led.h"
#include "motorcontrol.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//ADC�������� -- оƬF767ZGT6	
// ����ALIENTEK STM32F7���������ģ�� 							  
////////////////////////////////////////////////////////////////////////////////// 	

extern WM_HWIN adcSingleEdit;
extern WM_HWIN adcDualEdit;
extern u8 adc_flag;

void MY_ADC_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u32 ch); 		        //���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u32 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ
//deprecated
void Display_Adc_Value(u32 ch, u8 times);    // ��emWin����ʾADC�Ĳ���ֵ
//deprecated
void Display_Freq_Value(float value);

#endif 
