#include "adc.h"
#include "delay.h"

//////////////////////////////////////////////////////////////////////////////////	 
//ADC驱动代码 -- 芯片F767ZGT6	
// 基于ALIENTEK STM32F7开发板代码模板 
////////////////////////////////////////////////////////////////////////////////// 	

ADC_HandleTypeDef ADC3_Handler;     //! ADC句柄
u8 adc_flag = 0;    // 采样完成标志


//初始化ADC
//ch: ADC_channels 
//通道值 0~16取值范围为：ADC_CHANNEL_0~ADC_CHANNEL_16
void MY_ADC_Init(void)
{ 
    ADC3_Handler.Instance=ADC3;     //! 使用ADC3
    ADC3_Handler.Init.ClockPrescaler=ADC_CLOCK_SYNC_PCLK_DIV4;   //4分频，ADCCLK=PCLK2/4=108/4=27MHZ
    ADC3_Handler.Init.Resolution=ADC_RESOLUTION_12B;             //12位模式
    ADC3_Handler.Init.DataAlign=ADC_DATAALIGN_RIGHT;             //右对齐
    ADC3_Handler.Init.ScanConvMode=DISABLE;                      //非扫描模式
    ADC3_Handler.Init.EOCSelection=DISABLE;                      //关闭EOC中断
    ADC3_Handler.Init.ContinuousConvMode=DISABLE;                //关闭连续转换
    ADC3_Handler.Init.NbrOfConversion=1;                         //1个转换在规则序列中 也就是只转换规则序列1 
    ADC3_Handler.Init.DiscontinuousConvMode=DISABLE;             //禁止不连续采样模式
    ADC3_Handler.Init.NbrOfDiscConversion=0;                     //不连续采样通道数为0
    ADC3_Handler.Init.ExternalTrigConv=ADC_SOFTWARE_START;       //软件触发
    ADC3_Handler.Init.ExternalTrigConvEdge=ADC_EXTERNALTRIGCONVEDGE_NONE;//使用软件触发
    ADC3_Handler.Init.DMAContinuousRequests=DISABLE;             //关闭DMA请求
    HAL_ADC_Init(&ADC3_Handler);                                 //初始化 
}

//ADC底层驱动，引脚配置，时钟使能
//此函数会被HAL_ADC_Init()调用
//hadc:ADC句柄
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_ADC3_CLK_ENABLE();            //!使能ADC3时钟
    __HAL_RCC_GPIOF_CLK_ENABLE();			//!开启GPIOF时钟
	
    GPIO_Initure.Pin=GPIO_PIN_8;            //! PF8
    GPIO_Initure.Mode=GPIO_MODE_ANALOG;     //模拟
    GPIO_Initure.Pull=GPIO_NOPULL;          //不带上下拉
    HAL_GPIO_Init(GPIOF,&GPIO_Initure);     //! 初始化GPIO
}

//获得ADC值
//ch: 通道值 0~16，取值范围为：ADC_CHANNEL_0~ADC_CHANNEL_16
//返回值:转换结果
u16 Get_Adc(u32 ch)   
{
    ADC_ChannelConfTypeDef ADC3_ChanConf;   //! ADC3初始化配置
    
    ADC3_ChanConf.Channel=ch;                                   //!通道
    ADC3_ChanConf.Rank=1;                                       //1个序列
    ADC3_ChanConf.SamplingTime=ADC_SAMPLETIME_480CYCLES;        //采样时间
    ADC3_ChanConf.Offset=0;                 
    HAL_ADC_ConfigChannel(&ADC3_Handler,&ADC3_ChanConf);        //通道配置
	
    HAL_ADC_Start(&ADC3_Handler);                               //开启ADC
	
    HAL_ADC_PollForConversion(&ADC3_Handler,10);                //轮询转换
   
	return (u16)HAL_ADC_GetValue(&ADC3_Handler);	            //返回最近一次ADC1规则组的转换结果
}

//获取指定通道的转换值，取times次,然后平均 
//times:获取次数
//返回值:通道ch的times次转换结果平均值
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

//deprecated
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
    //EDIT_SetText(adcSingleEdit, str);
    //EDIT_SetText(adcDualEdit, str);
    //LED0_Toggle;
} 

//deprecated
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
    //EDIT_SetText(adcSingleEdit, str);
    //EDIT_SetText(adcDualEdit, str);
    //LED0_Toggle;
}
