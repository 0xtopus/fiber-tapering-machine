#ifndef __ADC_H
#define __ADC_H
#include "sys.h"
#include "DIALOG.h"
#include "led.h"
#include "motorcontrol.h"
#include <string.h>
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F7������
//ADC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/12/26
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
#define ADC_BUFF_SIZE 2048

extern WM_HWIN adcSingleEdit;
extern WM_HWIN adcDualEdit;
extern float adc_buff[ADC_BUFF_SIZE];
extern u8 adc_flag;

void MY_ADC_Init(void); 				//ADCͨ����ʼ��
u16  Get_Adc(u32 ch); 		        //���ĳ��ͨ��ֵ 
u16 Get_Adc_Average(u32 ch,u8 times);//�õ�ĳ��ͨ����������������ƽ��ֵ
void Display_Adc_Value(u32 ch, u8 times);    //! ��emWin����ʾADC�Ĳ���ֵ
void Display_Freq_Value(float value);

#endif 
