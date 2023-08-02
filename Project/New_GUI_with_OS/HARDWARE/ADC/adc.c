#include "adc.h"
#include "delay.h"

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

ADC_HandleTypeDef ADC3_Handler;     //! ADC���
float adc_buff[ADC_BUFF_SIZE];
u8 adc_flag = 0;


//��ʼ��ADC
//ch: ADC_channels 
//ͨ��ֵ 0~16ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
void MY_ADC_Init(void)
{ 
    ADC3_Handler.Instance=ADC3;     //! ʹ��ADC3
    ADC3_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;   //4��Ƶ��ADCCLK=PCLK2/4=108/4=27MHZ
    ADC3_Handler.Init.Resolution=ADC_RESOLUTION_12B;             //12λģʽ
    ADC3_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //�Ҷ���
    ADC3_Handler.Init.ScanConvMode=DISABLE;                      //��ɨ��ģʽ
    ADC3_Handler.Init.EOCSelection=DISABLE;                      //�ر�EOC�ж�
    ADC3_Handler.Init.ContinuousConvMode=DISABLE;                //�ر�����ת��
    ADC3_Handler.Init.NbrOfConversion=1;                         //1��ת���ڹ��������� Ҳ����ֻת����������1 
    ADC3_Handler.Init.DiscontinuousConvMode=DISABLE;             //��ֹ����������ģʽ
    ADC3_Handler.Init.NbrOfDiscConversion=0;                     //����������ͨ����Ϊ0
    ADC3_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //�������
    ADC3_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//ʹ���������
    ADC3_Handler.Init.DMAContinuousRequests=DISABLE;             //�ر�DMA����
    HAL_ADC_Init(&ADC3_Handler);                                 //��ʼ�� 
}

//ADC�ײ��������������ã�ʱ��ʹ��
//�˺����ᱻHAL_ADC_Init()����
//hadc:ADC���
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC3_CLK_ENABLE();            //!ʹ��ADC3ʱ��
    __HAL_RCC_GPIOF_CLK_ENABLE();			//!����GPIOFʱ��
	
    GPIO_Initure.Pin=GPIO_PIN_6;            //! PF6
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //ģ��
    GPIO_Initure.Pull=GPIO_NOPULL;          //����������
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);     //! ��ʼ��GPIO
}

//���ADCֵ
//ch: ͨ��ֵ 0~16��ȡֵ��ΧΪ��ADC_CHANNEL_0~ADC_CHANNEL_16
//����ֵ:ת�����
u16 Get_Adc(u32 ch)   
{
    ADC_ChannelConfTypeDef ADC3_ChanConf;   //! ADC3��ʼ������
    
    ADC3_ChanConf.Channel=ch;                                   //!ͨ��
    ADC3_ChanConf.Rank=1;                                       //1������
    ADC3_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //����ʱ��
    ADC3_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&ADC3_Handler,&ADC3_ChanConf);        //ͨ������
	
    HAL_ADC_Start(&ADC3_Handler);                               //����ADC
	
    HAL_ADC_PollForConversion(&ADC3_Handler,10);                //��ѯת��
   
	return (u16)HAL_ADC_GetValue(&ADC3_Handler);	            //�������һ��ADC1�������ת�����
}

//��ȡָ��ͨ����ת��ֵ��ȡtimes��,Ȼ��ƽ�� 
//times:��ȡ����
//����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
u16 Get_Adc_Average(u32 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
}

void Display_Adc_Value(u32 ch, u8 times)
{
    u16 adcx;
    float temp;
    char str[6];
    char fraction[4];
    adcx = Get_Adc(ch);
    temp = (float)adcx * (3.3 / 4096);
    // Get the integer part of the adc value
    adcx = temp;
    Int2String(adcx, str);
    strcat(str, ".");
    // Get the fraction part of the adc value
    temp -= adcx;
    temp *= 1000;
    adcx = temp;
    strcat(str, Int2String(adcx, fraction));
    EDIT_SetText(adcSingleEdit, str);
    EDIT_SetText(adcDualEdit, str);
    //LED0_Toggle;
} 

void Display_Freq_Value(float value)
{
    u16 temp;
    char str[8];
    char fraction[4];
    // Get the integer part of the adc value
    temp = value;
    Int2String(temp, str);
    strcat(str, ".");
    // Get the fraction part of the adc value
    value -= temp;
    value *= 10;
    temp = value;
    strcat(str, Int2String(temp, fraction));
    strcat(str, "Hz");
    EDIT_SetText(adcSingleEdit, str);
    EDIT_SetText(adcDualEdit, str);
    //LED0_Toggle;
}
