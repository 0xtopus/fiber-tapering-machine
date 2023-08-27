#include "timer.h"
#include "led.h"
#include "GUI.h"
#include "adc.h"
#include "includes.h"
#include "FTM_FrameDLG.h"
//////////////////////////////////////////////////////////////////////////////////
// 定时器中断驱动代码 -- 芯片F767ZGT6
// 基于ALIENTEK STM32F7开发板代码模板 
//////////////////////////////////////////////////////////////////////////////////

TIM_HandleTypeDef TIM3_Handler; // 定时器句柄

TIM_HandleTypeDef TIM4_Handler;     //! 定时器4句柄
TIM_OC_InitTypeDef TIM4_CH1Handler; //! 定时器4通道1句柄
TIM_OC_InitTypeDef TIM4_CH2Handler; //! 定时器4通道2句柄

TIM_HandleTypeDef TIM9_Handler;     //! 定时器9句柄
TIM_OC_InitTypeDef TIM9_CH1Handler; //! 定时器9通道1句柄
TIM_OC_InitTypeDef TIM9_CH2Handler; //! 定时器9通道1句柄

// 通用定时器3中断初始化
// arr：自动重装值。
// psc：时钟预分频数
// 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
// Ft=定时器工作频率,单位:Mhz
// 这里使用的是定时器3!(定时器3挂在APB1上，时钟为HCLK/2)
void TIM3_Init(u16 arr, u16 psc)
{
    TIM3_Handler.Instance = TIM3;                             // 通用定时器3
    TIM3_Handler.Init.Prescaler = psc;                        // 分频
    TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;       // 向上计数器
    TIM3_Handler.Init.Period = arr;                           // 自动装载值
    TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // 时钟分频因子
    HAL_TIM_Base_Init(&TIM3_Handler);

    HAL_TIM_Base_Start_IT(&TIM3_Handler); // 使能定时器3和定时器3更新中断：TIM_IT_UPDATE
}

//! Timer4 --- PB6,PB7
//! 此函数是配置Timer4在PB6或PB7引脚输出PWM的初始化函数
//! (定时器4挂在APB1上，时钟为HCLK/2)
//! arr：自动重装值。
//! psc：时钟预分频数
//! direction: 方向，对应通道1和通道2
//! 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//! Ft=定时器工作频率,单位:Mhz
void TIM4_PWM_Init(u16 arr, u16 psc, u8 direction)
{
    TIM4_Handler.Instance = TIM4;
    TIM4_Handler.Init.Prescaler = psc;                  // 定时器分频
    TIM4_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数模式
    TIM4_Handler.Init.Period = arr;                     // 自动重装载值
    TIM4_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM4_Handler); // 初始化PWM

    if (direction) //! 拉锥
    {
        TIM4_CH1Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // 输出比较极性为低
        TIM4_CH1Handler.OCMode = TIM_OCMODE_PWM1;                                  // 模式选择PWM1
        TIM4_CH1Handler.Pulse = arr / 2;                                           //! 设置比较值,此值用来确定占空比，
                                                                                   //! 占空比对我们的电机转速没有影响
                                                                                   // 默认比较值为自动重装载值的一半,即占空比为50%
        HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CH1Handler, TIM_CHANNEL_1); //! 配置TIM4通道1
        HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_1);
    }
    else //! 复位
    {
        TIM4_CH2Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // 输出比较极性为低
        TIM4_CH2Handler.OCMode = TIM_OCMODE_PWM1;                                  // 模式选择PWM1
        TIM4_CH2Handler.Pulse = arr / 2;                                           //! 设置比较值,此值用来确定占空比，
                                                                                   //! 占空比对我们的电机转速没有影响
                                                                                   // 默认比较值为自动重装载值的一半,即占空比为50%
        HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CH2Handler, TIM_CHANNEL_2); //! 配置TIM4通道2
        HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_2);
    }
}

//! Timer9 --- PE5,PE6
//! 此函数是配置Timer5在PA2和PA3引脚输出PWM的初始化函数
//! (定时器9挂在APB2上，时钟为HCLK/2)
//! arr：自动重装值。
//! psc：时钟预分频数
//! direction: 方向，对应通道1和通道2
//! 定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//! Ft=定时器工作频率,单位:Mhz
void TIM9_PWM_Init(u16 arr, u16 psc, u8 direction)
{
    TIM9_Handler.Instance = TIM9;
    TIM9_Handler.Init.Prescaler = psc;                  // 定时器分频
    TIM9_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; // 向上计数模式
    TIM9_Handler.Init.Period = arr;                     // 自动重装载值
    TIM9_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM9_Handler); // 初始化PWM

    if (direction) //! 拉锥
    {
        TIM9_CH1Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // 输出比较极性为低
        TIM9_CH1Handler.OCMode = TIM_OCMODE_PWM1;                                  // 模式选择PWM1
        TIM9_CH1Handler.Pulse = arr / 2;                                           //! 设置比较值,此值用来确定占空比，
                                                                                   //! 占空比对我们的电机转速没有影响
                                                                                   // 默认比较值为自动重装载值的一半,即占空比为50%
        HAL_TIM_PWM_ConfigChannel(&TIM9_Handler, &TIM9_CH1Handler, TIM_CHANNEL_1); //! 配置TIM9通道1
        HAL_TIM_PWM_Start(&TIM9_Handler, TIM_CHANNEL_1);
    }
    else //! 复位
    {
        TIM9_CH2Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // 输出比较极性为低
        TIM9_CH2Handler.OCMode = TIM_OCMODE_PWM1;                                  // 模式选择PWM1
        TIM9_CH2Handler.Pulse = arr / 2;                                           //! 设置比较值,此值用来确定占空比，
                                                                                   //! 占空比对我们的电机转速没有影响
                                                                                   // 默认比较值为自动重装载值的一半,即占空比为50%
        HAL_TIM_PWM_ConfigChannel(&TIM9_Handler, &TIM9_CH2Handler, TIM_CHANNEL_2); //! 配置TIM9通道2
        HAL_TIM_PWM_Start(&TIM9_Handler, TIM_CHANNEL_2);
    }
}

//! 定时器底层驱动，时钟使能，引脚配置
//! 此函数会被HAL_TIM_PWM_Init()调用
//! htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    // 初始化TIM4的通道1和通道2
    if (htim->Instance == TIM4)
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_TIM4_CLK_ENABLE();  //! 使能定时器4
        __HAL_RCC_GPIOB_CLK_ENABLE(); //! 开启GPIOB时钟

        GPIO_Initure.Mode = GPIO_MODE_AF_PP;        // 复用推挽输出
        GPIO_Initure.Pull = GPIO_PULLDOWN;          // !下拉
        GPIO_Initure.Speed = GPIO_SPEED_HIGH;       // 高速
        GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7; //! PB6和PB7
        GPIO_Initure.Alternate = GPIO_AF2_TIM4;     //! PB6复用为TIM4_CH1，PB7复用为TIM4_CH2
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    }
    // 初始化TIM9的通道1和通道2
    if (htim->Instance == TIM9)
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_TIM9_CLK_ENABLE();  //! 使能定时器9
        __HAL_RCC_GPIOE_CLK_ENABLE(); //! 开启GPIOE时钟

        GPIO_Initure.Mode = GPIO_MODE_AF_PP;        // 复用推挽输出
        GPIO_Initure.Pull = GPIO_PULLDOWN;          // !下拉
        GPIO_Initure.Speed = GPIO_SPEED_HIGH;       // 高速
        GPIO_Initure.Pin = GPIO_PIN_5 | GPIO_PIN_6; //! PE5和PE6
        GPIO_Initure.Alternate = GPIO_AF3_TIM9;     //! PE5复用为TIM9_CH1，PE6复用为TIM9_CH2
        HAL_GPIO_Init(GPIOE, &GPIO_Initure);
    }
}

// 定时器底层驱动，开启时钟，设置中断优先级
// 此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();           // 使能TIM3时钟
        HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3); // 设置中断优先级，抢占优先级1，子优先级3
        HAL_NVIC_EnableIRQ(TIM3_IRQn);         // 开启ITM3中断
    }
}

// 定时器3中断服务函数
void TIM3_IRQHandler(void)
{
#if SYSTEM_SUPPORT_OS // 使用UCOS操作系统
    OSIntEnter();
#endif

    HAL_TIM_IRQHandler(&TIM3_Handler);

#if SYSTEM_SUPPORT_OS
    OSIntExit(); // 退出中断
#endif
}

// 定时器3中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static int count = 0;
    if (htim == (&TIM3_Handler))
    {
        
        /* if (!adc_flag) // ADC采样未完成
        {
            adc_buff[2*count] = ((float) Get_Adc(ADC_CHANNEL_4));
            // printf("\r\nususu:%f\r\n", AdcBuff[2*count]);
            adc_buff[2*count+1] = 0;
            count++;
            if (count >= ADC_BUFF_SIZE/2)
            {
                adc_flag = 1;
                count = 0;
            }
        } */
        //Display_Adc_Value(ADC_CHANNEL_4, 10);
        if((oscilldev.buffer!=NULL)&&(oscilldev.adflag==0))	//buffer为空(，并且允许进行AD采集
		{
			oscilldev.buffer[count]=(int)((float)Get_Adc(ADC_CHANNEL_6)*oscilldev.resolut);//电压值,因为单位mv
			count++;
            //printf("opoing: %d\r\n",oscilldev.buffer[count]);
			if(count>oscilldev.dataxsize)//一次数据采集完成
			{
				count=0;
				oscilldev.adflag=1;//标记AD采集完成
                //printf("**********%d\r\n",oscilldev.dataxsize);

			}
		}

    }
    /*     else if (htim == (&TIM4_Handler))
        {
            GUI_TOUCH_Exec();
        } */
}
