#include "timer.h"
#include "led.h"
#include "GUI.h"
#include "adc.h"
#include "includes.h"
#include "FTM_FrameDLG.h"
//////////////////////////////////////////////////////////////////////////////////
// ��ʱ���ж��������� -- оƬF767ZGT6
// ����ALIENTEK STM32F7���������ģ�� 
//////////////////////////////////////////////////////////////////////////////////

TIM_HandleTypeDef TIM3_Handler; // ��ʱ�����

TIM_HandleTypeDef TIM4_Handler;     //! ��ʱ��4���
TIM_OC_InitTypeDef TIM4_CH1Handler; //! ��ʱ��4ͨ��1���
TIM_OC_InitTypeDef TIM4_CH2Handler; //! ��ʱ��4ͨ��2���

TIM_HandleTypeDef TIM9_Handler;     //! ��ʱ��9���
TIM_OC_InitTypeDef TIM9_CH1Handler; //! ��ʱ��9ͨ��1���
TIM_OC_InitTypeDef TIM9_CH2Handler; //! ��ʱ��9ͨ��1���

// ͨ�ö�ʱ��3�жϳ�ʼ��
// arr���Զ���װֵ��
// psc��ʱ��Ԥ��Ƶ��
// ��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
// Ft=��ʱ������Ƶ��,��λ:Mhz
// ����ʹ�õ��Ƕ�ʱ��3!(��ʱ��3����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM3_Init(u16 arr, u16 psc)
{
    TIM3_Handler.Instance = TIM3;                             // ͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler = psc;                        // ��Ƶ
    TIM3_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;       // ���ϼ�����
    TIM3_Handler.Init.Period = arr;                           // �Զ�װ��ֵ
    TIM3_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // ʱ�ӷ�Ƶ����
    HAL_TIM_Base_Init(&TIM3_Handler);

    HAL_TIM_Base_Start_IT(&TIM3_Handler); // ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�����жϣ�TIM_IT_UPDATE
}

//! Timer4 --- PB6,PB7
//! �˺���������Timer4��PB6��PB7�������PWM�ĳ�ʼ������
//! (��ʱ��4����APB1�ϣ�ʱ��ΪHCLK/2)
//! arr���Զ���װֵ��
//! psc��ʱ��Ԥ��Ƶ��
//! direction: ���򣬶�Ӧͨ��1��ͨ��2
//! ��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//! Ft=��ʱ������Ƶ��,��λ:Mhz
void TIM4_PWM_Init(u16 arr, u16 psc, u8 direction)
{
    TIM4_Handler.Instance = TIM4;
    TIM4_Handler.Init.Prescaler = psc;                  // ��ʱ����Ƶ
    TIM4_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; // ���ϼ���ģʽ
    TIM4_Handler.Init.Period = arr;                     // �Զ���װ��ֵ
    TIM4_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM4_Handler); // ��ʼ��PWM

    if (direction) //! ��׶
    {
        TIM4_CH1Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // ����Ƚϼ���Ϊ��
        TIM4_CH1Handler.OCMode = TIM_OCMODE_PWM1;                                  // ģʽѡ��PWM1
        TIM4_CH1Handler.Pulse = arr / 2;                                           //! ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                                                                   //! ռ�ձȶ����ǵĵ��ת��û��Ӱ��
                                                                                   // Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
        HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CH1Handler, TIM_CHANNEL_1); //! ����TIM4ͨ��1
        HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_1);
    }
    else //! ��λ
    {
        TIM4_CH2Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // ����Ƚϼ���Ϊ��
        TIM4_CH2Handler.OCMode = TIM_OCMODE_PWM1;                                  // ģʽѡ��PWM1
        TIM4_CH2Handler.Pulse = arr / 2;                                           //! ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                                                                   //! ռ�ձȶ����ǵĵ��ת��û��Ӱ��
                                                                                   // Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
        HAL_TIM_PWM_ConfigChannel(&TIM4_Handler, &TIM4_CH2Handler, TIM_CHANNEL_2); //! ����TIM4ͨ��2
        HAL_TIM_PWM_Start(&TIM4_Handler, TIM_CHANNEL_2);
    }
}

//! Timer9 --- PE5,PE6
//! �˺���������Timer5��PA2��PA3�������PWM�ĳ�ʼ������
//! (��ʱ��9����APB2�ϣ�ʱ��ΪHCLK/2)
//! arr���Զ���װֵ��
//! psc��ʱ��Ԥ��Ƶ��
//! direction: ���򣬶�Ӧͨ��1��ͨ��2
//! ��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
//! Ft=��ʱ������Ƶ��,��λ:Mhz
void TIM9_PWM_Init(u16 arr, u16 psc, u8 direction)
{
    TIM9_Handler.Instance = TIM9;
    TIM9_Handler.Init.Prescaler = psc;                  // ��ʱ����Ƶ
    TIM9_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; // ���ϼ���ģʽ
    TIM9_Handler.Init.Period = arr;                     // �Զ���װ��ֵ
    TIM9_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM9_Handler); // ��ʼ��PWM

    if (direction) //! ��׶
    {
        TIM9_CH1Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // ����Ƚϼ���Ϊ��
        TIM9_CH1Handler.OCMode = TIM_OCMODE_PWM1;                                  // ģʽѡ��PWM1
        TIM9_CH1Handler.Pulse = arr / 2;                                           //! ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                                                                   //! ռ�ձȶ����ǵĵ��ת��û��Ӱ��
                                                                                   // Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
        HAL_TIM_PWM_ConfigChannel(&TIM9_Handler, &TIM9_CH1Handler, TIM_CHANNEL_1); //! ����TIM9ͨ��1
        HAL_TIM_PWM_Start(&TIM9_Handler, TIM_CHANNEL_1);
    }
    else //! ��λ
    {
        TIM9_CH2Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // ����Ƚϼ���Ϊ��
        TIM9_CH2Handler.OCMode = TIM_OCMODE_PWM1;                                  // ģʽѡ��PWM1
        TIM9_CH2Handler.Pulse = arr / 2;                                           //! ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                                                                   //! ռ�ձȶ����ǵĵ��ת��û��Ӱ��
                                                                                   // Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
        HAL_TIM_PWM_ConfigChannel(&TIM9_Handler, &TIM9_CH2Handler, TIM_CHANNEL_2); //! ����TIM9ͨ��2
        HAL_TIM_PWM_Start(&TIM9_Handler, TIM_CHANNEL_2);
    }
}

//! ��ʱ���ײ�������ʱ��ʹ�ܣ���������
//! �˺����ᱻHAL_TIM_PWM_Init()����
//! htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    // ��ʼ��TIM4��ͨ��1��ͨ��2
    if (htim->Instance == TIM4)
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_TIM4_CLK_ENABLE();  //! ʹ�ܶ�ʱ��4
        __HAL_RCC_GPIOB_CLK_ENABLE(); //! ����GPIOBʱ��

        GPIO_Initure.Mode = GPIO_MODE_AF_PP;        // �����������
        GPIO_Initure.Pull = GPIO_PULLDOWN;          // !����
        GPIO_Initure.Speed = GPIO_SPEED_HIGH;       // ����
        GPIO_Initure.Pin = GPIO_PIN_6 | GPIO_PIN_7; //! PB6��PB7
        GPIO_Initure.Alternate = GPIO_AF2_TIM4;     //! PB6����ΪTIM4_CH1��PB7����ΪTIM4_CH2
        HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    }
    // ��ʼ��TIM9��ͨ��1��ͨ��2
    if (htim->Instance == TIM9)
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_TIM9_CLK_ENABLE();  //! ʹ�ܶ�ʱ��9
        __HAL_RCC_GPIOE_CLK_ENABLE(); //! ����GPIOEʱ��

        GPIO_Initure.Mode = GPIO_MODE_AF_PP;        // �����������
        GPIO_Initure.Pull = GPIO_PULLDOWN;          // !����
        GPIO_Initure.Speed = GPIO_SPEED_HIGH;       // ����
        GPIO_Initure.Pin = GPIO_PIN_5 | GPIO_PIN_6; //! PE5��PE6
        GPIO_Initure.Alternate = GPIO_AF3_TIM9;     //! PE5����ΪTIM9_CH1��PE6����ΪTIM9_CH2
        HAL_GPIO_Init(GPIOE, &GPIO_Initure);
    }
}

// ��ʱ���ײ�����������ʱ�ӣ������ж����ȼ�
// �˺����ᱻHAL_TIM_Base_Init()��������
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM3)
    {
        __HAL_RCC_TIM3_CLK_ENABLE();           // ʹ��TIM3ʱ��
        HAL_NVIC_SetPriority(TIM3_IRQn, 1, 3); // �����ж����ȼ�����ռ���ȼ�1�������ȼ�3
        HAL_NVIC_EnableIRQ(TIM3_IRQn);         // ����ITM3�ж�
    }
}

// ��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
#if SYSTEM_SUPPORT_OS // ʹ��UCOS����ϵͳ
    OSIntEnter();
#endif

    HAL_TIM_IRQHandler(&TIM3_Handler);

#if SYSTEM_SUPPORT_OS
    OSIntExit(); // �˳��ж�
#endif
}

// ��ʱ��3�жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static int count = 0;
    if (htim == (&TIM3_Handler))
    {
        
        /* if (!adc_flag) // ADC����δ���
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
        if((oscilldev.buffer!=NULL)&&(oscilldev.adflag==0))	//bufferΪ��(�������������AD�ɼ�
		{
			oscilldev.buffer[count]=(int)((float)Get_Adc(ADC_CHANNEL_6)*oscilldev.resolut);//��ѹֵ,��Ϊ��λmv
			count++;
            //printf("opoing: %d\r\n",oscilldev.buffer[count]);
			if(count>oscilldev.dataxsize)//һ�����ݲɼ����
			{
				count=0;
				oscilldev.adflag=1;//���AD�ɼ����
                //printf("**********%d\r\n",oscilldev.dataxsize);

			}
		}

    }
    /*     else if (htim == (&TIM4_Handler))
        {
            GUI_TOUCH_Exec();
        } */
}
