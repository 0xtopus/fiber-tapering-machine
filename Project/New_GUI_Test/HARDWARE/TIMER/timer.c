#include "timer.h"
#include "led.h"
#include "GUI.h"

//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// ALIENTEK STM32F7������
// ��ʱ���ж���������
// ����ԭ��@ALIENTEK
// ������̳:www.openedv.com
// ��������:2015/11/27
// �汾��V1.0
// ��Ȩ���У�����ؾ���
// Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
// All rights reserved
//////////////////////////////////////////////////////////////////////////////////

extern __IO int32_t OS_TimeMS;

TIM_HandleTypeDef TIM3_Handler;     // ��ʱ�����
TIM_HandleTypeDef TIM4_Handler;     // ��ʱ�����
TIM_HandleTypeDef TIM2_Handler;     //! ��ʱ��2���
TIM_OC_InitTypeDef TIM2_CH1Handler; //! ��ʱ��2ͨ��1���
TIM_OC_InitTypeDef TIM2_CH2Handler; //! ��ʱ��2ͨ��2���

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

// ͨ�ö�ʱ��4�жϳ�ʼ��
// arr���Զ���װֵ��
// psc��ʱ��Ԥ��Ƶ��
// ��ʱ�����ʱ����㷽��:Tout=((arr+1)*(psc+1))/Ft us.
// Ft=��ʱ������Ƶ��,��λ:Mhz
// ����ʹ�õ��Ƕ�ʱ��4!(��ʱ��4����APB1�ϣ�ʱ��ΪHCLK/2)
void TIM4_Init(u16 arr, u16 psc)
{
    TIM4_Handler.Instance = TIM4;                       // ͨ�ö�ʱ��4
    TIM4_Handler.Init.Prescaler = psc;                  // ��Ƶ
    TIM4_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; // ���ϼ�����
    TIM4_Handler.Init.Period = arr;                     // �Զ�װ��ֵ
    TIM4_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_Base_Init(&TIM4_Handler);

    HAL_TIM_Base_Start_IT(&TIM4_Handler); // ʹ�ܶ�ʱ��3�Ͷ�ʱ��3�ж�
}

//! Timer2 PWM PA5/PA1 output
//! �˺���������Timer2��PA5��PA1�������PWM�ĳ�ʼ������
void TIM2_PWM_Init(u16 arr, u16 psc, pwmout_struct pwmout_config)
{
    TIM2_Handler.Instance = TIM2;
    TIM2_Handler.Init.Prescaler = psc;                  // ��ʱ����Ƶ
    TIM2_Handler.Init.CounterMode = TIM_COUNTERMODE_UP; // ���ϼ���ģʽ
    TIM2_Handler.Init.Period = arr;                     // �Զ���װ��ֵ
    TIM2_Handler.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM2_Handler); // ��ʼ��PWM

    TIM2_CH1Handler.OCMode = TIM_OCMODE_PWM1;                                  // ģʽѡ��PWM1
    TIM2_CH1Handler.Pulse = arr / 2;                                           //! ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
    TIM2_CH2Handler.OCMode = TIM_OCMODE_PWM1;                                  // ģʽѡ��PWM1
    TIM2_CH2Handler.Pulse = arr / 2;                                           //! ���ñȽ�ֵ,��ֵ����ȷ��ռ�ձȣ�
                                                                               // Ĭ�ϱȽ�ֵΪ�Զ���װ��ֵ��һ��,��ռ�ձ�Ϊ50%
    TIM2_CH1Handler.OCPolarity = TIM_OCPOLARITY_LOW;                           // ����Ƚϼ���Ϊ��
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler, &TIM2_CH1Handler, TIM_CHANNEL_1); //! ����TIM2ͨ��1
    HAL_TIM_PWM_ConfigChannel(&TIM2_Handler, &TIM2_CH2Handler, TIM_CHANNEL_2); //! ����TIM2ͨ��2
    if (pwmout_config.left_motor)   //! ����������Ҫת��
    {
        HAL_TIM_PWM_Start(&TIM2_Handler, TIM_CHANNEL_1); //! ����PWMͨ��1
    }

    if (pwmout_config.right_motor)  //! ����������Ҫת��
    {
        HAL_TIM_PWM_Start(&TIM2_Handler, TIM_CHANNEL_2); //! ����PWMͨ��2
    }
}

//! ��ʱ���ײ�������ʱ��ʹ�ܣ���������
//! �˺����ᱻHAL_TIM_PWM_Init()����
//! htim:��ʱ�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == TIM2)
    {
        GPIO_InitTypeDef GPIO_Initure;
        __HAL_RCC_TIM2_CLK_ENABLE();  //! ʹ�ܶ�ʱ��2
        __HAL_RCC_GPIOA_CLK_ENABLE(); //! ����GPIOAʱ��

        GPIO_Initure.Mode = GPIO_MODE_AF_PP;        // �����������
        GPIO_Initure.Pull = GPIO_PULLDOWN;          // !����
        GPIO_Initure.Speed = GPIO_SPEED_HIGH;       // ����
        GPIO_Initure.Pin = GPIO_PIN_5 | GPIO_PIN_1; //! PA5��PA1
        GPIO_Initure.Alternate = GPIO_AF1_TIM2;     //! PA5����ΪTIM2_CH1��PA1����ΪTIM2_CH2
        HAL_GPIO_Init(GPIOA, &GPIO_Initure);
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
    else if (htim->Instance == TIM4)
    {
        __HAL_RCC_TIM4_CLK_ENABLE();           // ʹ��TIM4ʱ��
        HAL_NVIC_SetPriority(TIM4_IRQn, 2, 3); // �����ж����ȼ�����ռ���ȼ�2�������ȼ�0
        HAL_NVIC_EnableIRQ(TIM4_IRQn);         // ����ITM4�ж�
    }
}

// ��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM3_Handler);
}

// ��ʱ��4�жϷ�����
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_Handler);
}

// ��ʱ��3�жϷ���������
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == (&TIM3_Handler))
    {
        OS_TimeMS++;
    }
    else if (htim == (&TIM4_Handler))
    {
        GUI_TOUCH_Exec();
    }
}
