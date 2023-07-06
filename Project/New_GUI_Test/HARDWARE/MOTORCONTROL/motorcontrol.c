#include "motorcontrol.h"
#include "led.h"
#include "timer.h"

#define GET_CLOSER 0
#define GET_AWAY 1

MotorControlStruct MotorConfig = {0, 0, 0, 0, 0};

/**
 * Start the motors as configurated.
 * @param *pMotorConfig
 * @return The current mode of MotorConfig
 */
u8 Motor_Start(MotorControlStruct *pMotorConfig)
{
    u16 reload_value;

    if (pMotorConfig->enable)
    {
        return pMotorConfig->mode;
    }

    switch (pMotorConfig->mode)
    {
    case 0:
        // Both motors start working
        {
            // TODO reload value
            reload_value = 1000;
            if (pMotorConfig->direction) // Go reversely
            {
                TIM2_PWM_Init(reload_value, 108 - 1, GET_AWAY); //! The frequency of timer is 108M/108=1M,
                                                                //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            else    // Get closer
            {                                                     
                TIM2_PWM_Init(reload_value, 108 - 1, GET_CLOSER); //! The frequency of timer is 108M/108=1M,
                                                                  //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                  //! So the range of PWM frequency is 200Hz ~ 2kHz
            }

            break;
        }
    case 1:
        // Only left motor starts working
        {
            //! The range of reload_value: 500 ~ 5000
            reload_value = -(pMotorConfig->left_speed) + 5500;
            if (pMotorConfig->direction) // Go reversely
            {
                TIM2_PWM_Init(reload_value, 108 - 1, GET_CLOSER); //! The frequency of timer is 108M/108=1M,
                                                                  //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                                  //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            else    // Get closer
            {                                           
                TIM2_PWM_Init(1000, 108 - 1, GET_AWAY); //! The frequency of timer is 108M/108=1M,
                                                        //! if reload_value = 1000, then PWM frequency is 1M/1000=1kHZ
                                                        //! So the range of PWM frequency is 200Hz ~ 2kHz
            }
            break;
        }
    // Only right motor starts working
    case 2:
    {
        if (pMotorConfig->direction) // Go reversely
        {
        }
        else    // Get closer
        { 
        }
        break;
    }
    }
    pMotorConfig->enable = 1;
    //! printf("start：%u",pMotorConfig->enable);
    // Flash green LED
    LED1(0);
    LED0(1);
    return pMotorConfig->mode;
}

/**
 * Stop all motors.
 * @param *pMotorConfig
 * @return The current mode of MotorConfig
 */
u8 Motor_Stop(MotorControlStruct *pMotorConfig)
{
    if (!pMotorConfig->enable)
    {
        return pMotorConfig->mode;
    }

    // TODO： 把另一个计时器的停止控制也加入进来
    if (pMotorConfig->direction)
    {
        HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_1);
        printf("ahahah\r\n");
    }
    else
    {
        HAL_TIM_PWM_Stop(&TIM2_Handler, TIM_CHANNEL_2);
        printf("bbbbbbb\r\n");
    }

    // Flash red LED
    LED1(1);
    LED0(0);
    pMotorConfig->enable = 0;
    return pMotorConfig->mode;
}

/*********EOF*********/
